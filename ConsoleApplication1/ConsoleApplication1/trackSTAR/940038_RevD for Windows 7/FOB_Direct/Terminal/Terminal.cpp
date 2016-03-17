/********************************************************************/
/*                                                                  */
/*  Terminal.cpp: Sample LaserBird data aquisition program          */
/*                                                                  */
/*  This is a sample terminal emulator for starting and running     */
/*  the LaserBird.                                                  */
/*                                                                  */
/*  (c)Copyright Ascension Technology Corporation 2002              */
/*                                                                  */
/*  Ascension Technology Corporation                                */
/*  P.O. Box 527                                                    */
/*  Burlington, VT 05402 USA                                        */
/*  (802) 893-6657 PHONE                                            */
/*  (802) 893-6659 FAX                                              */
/*                                                                  */
/********************************************************************/


#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "serialio.h"

#define HEADER_LINE   2      // print format specifier
#define FOOTER_LINE   9      // print format specifier
#define STATUS_LINE   11     // print format specifier


#define STREAM        0x40
#define POINT		  0x42
#define RUN			  0x46
#define SLEEP		  0x47
#define BUTTON_MODE	  0x4d	
#define EXAMINE_VALUE 0x4f
#define CHANGE_VALUE  0x50
#define POS_ANG       0x59
#define RESET		  0x62

// Change/Examine Registers
#define BIRD_STATUS					0
#define BIRD_POSITION_SCALING		3
#define BIRD_MEASUREMENT_RATE		7
#define BIRD_ERROR_CODE				10
#define BIRD_DATA_STATUS			128

// Parameter Data
#define DISABLE    0x00
#define ENABLE     0x01


typedef struct tagBIRDPOSITION
{
	short	nX;			// x-coordinate
	short	nY;			// y-coordinate
	short	nZ;			// z-coordinate
}
BIRDPOSITION;

// Bird angles structure
typedef struct tagBIRDANGLES
{
	short	nAzimuth;	// azimuth angle
	short	nElevation;	// elevation angle
	short	nRoll;		// roll angle
}
BIRDANGLES;

struct pos_ang
{
	BIRDPOSITION pos;
	BIRDANGLES   ang;
	unsigned char status;
};

short decode_bird_data(char * bd, struct pos_ang * pa);
void command_pause(DWORD delay);
unsigned long wait_for_data(DWORD count);

int main(int argc, char* argv[])
{

	unsigned char  byteptr;
    unsigned char  dataoutchar[16];
	unsigned char  inchar;
	unsigned char  datainchar[16];
    DWORD        bytes_read;
	MMRESULT     mmStatus;
	DWORD        response_delay = 1000;			// timeout delay in ms
	
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD page_pos;
    CONSOLE_CURSOR_INFO lpConsoleCursorInfo;
	
	char raw_bird_data[13];
	double pos[3];
	double ang[3];
	double positional_scaling;
	struct pos_ang cooked_bird_data;
	
	
	// Position cursor and print banner on console screen
	page_pos.X = 0;
	page_pos.Y = 0;
	SetConsoleCursorPosition(hconsole, page_pos);
    printf("   Ascension Technology Corporation - BIRD RS-232 Example   01/06/2006\n");
    
    // Open COM port
    if (!serialinit())
    {
        printf("Unable to open COM port.\n\n");
        printf("Press any key to exit.");
        getch();
        return(1);
    } // end if(!seriaalinit())

	page_pos.Y = HEADER_LINE;
	SetConsoleCursorPosition(hconsole, page_pos);
	
	mmStatus = timeBeginPeriod(1);
	
    
	page_pos.Y = HEADER_LINE;
	SetConsoleCursorPosition(hconsole, page_pos);
    printf("Initializing the Bird...\n");
	
	//*****************************************************************************
	// Reset the LaserBird via the RTS line
	//   - this will reset the LaserBird iff LaserBird is set for Reset on CTS
	// for legacy reasons and compatiblity with previous Ascension products
	// leave RTS disabled to run...
	serialRTSstate(TRUE);
	command_pause(1);
	serialRTSstate(FALSE);
	command_pause(2000);

	//*****************************************************************************
	// Reset the LaserBird via software command
	//    - use this if the LaserBird is not set for Reset on CTS

	//dataoutchar[0] = RESET;

	//serialsendcommand(dataoutchar, 1);
	
	//*****************************************************************************
	// Next, Wake the LaserBird up - extraneous if default is Run on Reset
	
	dataoutchar[0] = RUN;
	
	serialsendcommand(dataoutchar, 1);
		
	
	//*****************************************************************************
	// Next, check error code
	
		
	dataoutchar[0] = EXAMINE_VALUE;
	dataoutchar[1] = BIRD_ERROR_CODE;

	serialsendcommand(dataoutchar, 2);
		
	bytes_read = serialreaddata(response_delay,1,datainchar);		// read in single byte

	// set up to read position and angle

	dataoutchar[0] = POS_ANG;

	serialsendcommand(dataoutchar, 1);

	// get position scaling factor

	positional_scaling = 36.0;			// assume 36 inches
	dataoutchar[0] = EXAMINE_VALUE;
	dataoutchar[1] = BIRD_POSITION_SCALING;

	serialsendcommand(dataoutchar, 2);
	bytes_read = serialreaddata(response_delay,2, datainchar);

	// if read back is a 1 then positional scaling is 72 inches 
	if (bytes_read == 2) 
		if (datainchar[0] == 1)
			positional_scaling = 72.0;
	


/*	
	// enable data status out on each data record
	//  - LaserBird specific - not yet in manual

	dataoutchar[0] = CHANGE_VALUE;
	dataoutchar[1] = BIRD_DATA_STATUS;   // 128
	dataoutchar[2] = 1;
	serialsendcommand(dataoutchar, 3);

*/
		

		
	//*****************************************************************************
    // Go get the data!	
 	page_pos.X = 0;
	page_pos.Y = HEADER_LINE;
	SetConsoleCursorPosition(hconsole, page_pos);
/*
//	For a version with the run-time status word
	printf("    X       Y       Z       A       E       R      Status\n");
*/
	printf("    X       Y       Z       A       E       R\n");
	
	page_pos.Y = FOOTER_LINE;
	SetConsoleCursorPosition(hconsole, page_pos);
	printf("Press any key to exit");
	
	// turn off the cursor to remove that annoying flicker.
	GetConsoleCursorInfo(hconsole, &lpConsoleCursorInfo);
	lpConsoleCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hconsole, &lpConsoleCursorInfo);
	
	do
	{
		unsigned long newdata;
		//*****************************************************************************
		// Next, send POINT command 
		// Note that if routine runs faster than LaserBird is reporting then duplicate
		// records are possible

		dataoutchar[0] = POINT;
		
		serialsendcommand(dataoutchar, 1);
		
        
		// fetch data one byte at a time to check for sync bit		
		while(newdata = serialcheckfordata())
		{
			
			inchar = serialgetbyte();
			
			if(inchar & 0x80)
			{
				byteptr = 0;
				raw_bird_data[byteptr++] = inchar;
				
			}
			else if(byteptr)
			{
				raw_bird_data[byteptr++] = inchar;
			}
			
//			if(byteptr >= 13)		// Pos/Angles + Status Byte = 12 + 1 bytes = 13 bytes
			if(byteptr >= 12)
			{
				byteptr = 0;
				// parse the output
				decode_bird_data(raw_bird_data,
					&cooked_bird_data); 
				
				// scale and print output
				pos[0] = cooked_bird_data.pos.nX * positional_scaling / 32768.;
				pos[1] = cooked_bird_data.pos.nY * positional_scaling / 32768.;
				pos[2] = cooked_bird_data.pos.nZ * positional_scaling / 32768.;
				ang[0] = cooked_bird_data.ang.nAzimuth * 180. / 32768.;
				ang[1] = cooked_bird_data.ang.nElevation * 180. / 32768.;
				ang[2] = cooked_bird_data.ang.nRoll * 180. / 32768.;
				
				
				page_pos.Y = HEADER_LINE + 2;
				SetConsoleCursorPosition(hconsole, page_pos);
/*
// with the status byte:
				printf("%+6.1f  %+6.1f  %+6.1f  %+6.1f  %+6.1f  %+6.1f     %x \n",
					pos[0], pos[1], pos[2], ang[0], ang[1], ang[2],cooked_bird_data.status);
*/
				printf("%+6.1f  %+6.1f  %+6.1f  %+6.1f  %+6.1f  %+6.1f      \n",
					pos[0], pos[1], pos[2], ang[0], ang[1], ang[2]);
				Sleep(10);				// avoid sending too many Point Request commmands
					
			} // end if(byteptr >= 13)
		} // while(newdata...
	}while(!kbhit()); // loop until any key is pressed
	
	
	
	page_pos.Y = FOOTER_LINE;
	SetConsoleCursorPosition(hconsole, page_pos);
	printf("EXITING...                             \n");
	
	
	//*****************************************************************************
	// Next, Put the birds to sleep 
	
	dataoutchar[0] = SLEEP;
	
	serialsendcommand(dataoutchar, 1);

	
	//*****************************************************************************
	// Close serial port 
    serialttfn();

    
    printf("\n");
	
	
    return(0);
	
}


short decode_bird_data(char * bd, struct pos_ang * pa)
{
    unsigned char i;
	
	
	// check msb of first byte is a one, signifying the start of the data record
	if (!(bd[0] & 0x80)) 	{
		return(0);
	}
	
	// remove phasing bit from first byte.
	bd[0] = bd[0] & 0x7f;
	
	// left shift each LS byte 1 bit
	for(i=0; i<12; i+=2)
	{
		bd[i] = bd[i] << 1;
	}
	
	// see the Flock of Birds manual (5.3 RS232 Response Format)
	// for an explanation of this smoke and mirrors.
	pa->pos.nX = (bd[1] << 8) | (bd[0] & 0xff);
	pa->pos.nX = pa->pos.nX << 1;
	
	pa->pos.nY = (bd[3] << 8) | (bd[2] & 0xff) ;
	pa->pos.nY = pa->pos.nY<< 1;
	
	pa->pos.nZ = (bd[5] << 8) | (bd[4] & 0xff);
	pa->pos.nZ = pa->pos.nZ << 1;
	
	pa->ang.nAzimuth = (bd[7] << 8) | (bd[6] & 0xff);
	pa->ang.nAzimuth = pa->ang.nAzimuth << 1;
	
	pa->ang.nElevation = (bd[9] << 8) | (bd[8] & 0xff);
	pa->ang.nElevation = pa->ang.nElevation << 1;
	
	pa->ang.nRoll = (bd[11] << 8) | (bd[10] & 0xff);
	pa->ang.nRoll = pa->ang.nRoll << 1;

//	pa->status = bd[12];
	
	return(1);
}


void command_pause(DWORD delay)
{
	DWORD        starttime;
	
	starttime = timeGetTime();
	while(starttime + delay > timeGetTime());
}

