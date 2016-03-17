#include <windows.h>
#include <stdio.h>

#define TIMEOUT_CONSTANT    2000

HANDLE       comport = NULL; // Handle for COM port
COMMTIMEOUTS savedComTimeouts;     // Stores the original time-outs
DCB          comSettings;          // Contains various port settings

unsigned long wait_for_data(DWORD delay, DWORD count);

unsigned char serialinit(void)
{
	DWORD		 flag;
    COMMTIMEOUTS tempComTimeouts;      // Our temporary time-outs for COM6
    BOOL         comStatus;
	char         port[5];
	unsigned char portnumber = 1;

    sprintf(port, "COM%u", portnumber);

	// Open COM port
    if ((comport = 
		CreateFile(port, //"COM3", 
		GENERIC_READ | GENERIC_WRITE, // for reading and writing
		0,                            // exclusive access
		NULL,                         // no security attributes
		OPEN_EXISTING,              
		FILE_ATTRIBUTE_NORMAL,
		NULL)) == INVALID_HANDLE_VALUE)
    {
        return(0);
    } // end if((comport...


    flag = PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR;

	comStatus = PurgeComm(comport,  // handle to communications resource
		flag);    // action to perform
	
    // Save time-out parameters for COM port 
    GetCommTimeouts(comport,&savedComTimeouts);
    
    // Set our time-outs 
    tempComTimeouts.ReadIntervalTimeout         = TIMEOUT_CONSTANT;
    tempComTimeouts.ReadTotalTimeoutMultiplier  = 0; // TIMEOUT_CONSTANT;
    tempComTimeouts.ReadTotalTimeoutConstant    = TIMEOUT_CONSTANT;
    tempComTimeouts.WriteTotalTimeoutMultiplier = 0; //TIMEOUT_CONSTANT;
    tempComTimeouts.WriteTotalTimeoutConstant   = TIMEOUT_CONSTANT;
    SetCommTimeouts(comport,&tempComTimeouts);
	
    // Set Port parameters.
    // We make a call to GetCommState() first in order to fill
    // the comSettings structure with all the necessary values.
    // Then we change the ones we want and call SetCommState().
    GetCommState(comport, &comSettings);
    comSettings.BaudRate = 115200; 
	//	comSettings.fBinary = TRUE;
    comSettings.fParity  = FALSE;
	//	comSettings.fOutxCtsFlow = FALSE;
	//	comSettings.fOutxDsrFlow = FALSE;
	//	comSettings.fDtrControl = DTR_CONTROL_DISABLE;
	//	comSettings.fDsrSensitivity = FALSE;
	//	comSettings.fTXContinueOnXoff = TRUE;
	//	comSettings.fOutX = FALSE;
	//	comSettings.fInX = FALSE;
	//	comSettings.ErrorChar = FALSE;
	//	comSettings.fNull = FALSE;
	//  comSettings.fRtsControl = RTS_CONTROL_DISABLE;
	comSettings.fAbortOnError = FALSE;
	//	comSettings.fDummy2 = 0;
	//	comSettings.wReserved = 0;
	//	comSettings.XonLim = 0;
	//	comSettings.XoffLim = 0;
    comSettings.ByteSize = 8;
    comSettings.Parity   = NOPARITY;
    comSettings.StopBits = ONESTOPBIT;
	//	comSettings.XonChar = 0;
	//	comSettings.XoffChar = 0;
	//	comSettings.ErrorChar = 0;
	//	comSettings.EofChar = 0;
	//	comSettings.wReserved1 =0;
    SetCommState(comport, &comSettings);

    return(1);

}

DWORD serialsendcommand(unsigned char * cmd, unsigned char cmdsize)
{
	DWORD bytestransmitted = 0;
	DWORD bytes_written = 0;
    BOOL  comStatus;



	comStatus = WriteFile(comport,        // Handle
	              	      &cmd[0],        // Outgoing data
		                  cmdsize,    // Number of bytes to write
		                  &bytes_written, // Number of bytes written
		                  NULL);

	bytestransmitted = bytestransmitted + bytes_written;

	return(bytestransmitted);
}

DWORD serialreaddata(DWORD delay, DWORD count, unsigned char * rsp)
{
	unsigned long readcount;
    DWORD         bytes_read;    // Number of bytes read from port
    BOOL          comStatus;

	readcount = wait_for_data(delay,count);

	comStatus = ReadFile(comport,     // Handle
		rsp,     // Incoming data
		readcount,           // Number of bytes to read
		&bytes_read, // Number of bytes read
		NULL);

    return(bytes_read);
}


// wait for n bytes to be in queue or timeou
unsigned long wait_for_data(DWORD delay, DWORD count)
{
	DWORD t1;
	COMSTAT ComStat;
    DWORD   dwErrorFlags;

	t1 = timeGetTime();
	do
	{
		ClearCommError(comport,
			&dwErrorFlags, 
			&ComStat);
	}while((ComStat.cbInQue < count) && ((t1 + delay) > timeGetTime()));
	
	return(ComStat.cbInQue);
}

void serialttfn(void)
{
	SetCommTimeouts(comport,&savedComTimeouts);
    CloseHandle(comport);
}


unsigned char serialgetbyte(void)
{
	DWORD         bytes_read = 0;
	unsigned char databyte;
    BOOL          comStatus;

	comStatus = ReadFile(comport,     // Handle
		&databyte,     // Incoming data
		1,           // Number of bytes to read
		&bytes_read, // Number of bytes read
		NULL);
    
	return(databyte);
}

unsigned long serialcheckfordata(void)
{
    DWORD   dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(comport,
		&dwErrorFlags, 
		&ComStat);
	
	return(ComStat.cbInQue);
}

void serialRTSstate(int state)
{  
	// We make a call to GetCommState() first in order to fill
    // the comSettings structure with all the necessary values.
    // Then we change the ones we want and call SetCommState().
    GetCommState(comport, &comSettings);

	if (state)
		comSettings.fRtsControl = RTS_CONTROL_ENABLE;
	else
		comSettings.fRtsControl = RTS_CONTROL_DISABLE;

    SetCommState(comport, &comSettings);

}