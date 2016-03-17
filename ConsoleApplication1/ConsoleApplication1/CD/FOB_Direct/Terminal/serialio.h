unsigned char serialinit(void);
DWORD serialsendcommand(unsigned char * cmd, unsigned char cmdsize);
DWORD serialreaddata(DWORD delay, DWORD count, unsigned char * rsp);
void serialttfn(void);
unsigned long serialcheckfordata(void);
unsigned char serialgetbyte(void);
void serialRTSstate(int);