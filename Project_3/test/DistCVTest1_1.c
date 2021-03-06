#include "syscall.h"

int num = 0;
int cv=-1;
int lck=-1;


void main()
{
	lck = CreateLock("lock1");
	cv = CreateCV("CV1");
	Print("\nDistCVTest1_1: Created Lock is %d and CV is %d\n", lck, cv, -1);
	
	AcquireLock(lck);

	Print("Client 1: About to go on wait...\n", -1, -1, -1);

	
	WaitCV(lck, cv);

	Print("Client 1: Now out of wait...\n", -1, -1, -1);

	for (num=0; num<1000; num++)
		Print("",-1,-1,-1);
	
	Print("Client 1: About to signal Client 2\n", -1, -1, -1);
	
	SignalCV(lck, cv);

	ReleaseLock(lck);
	AcquireLock(lck);


	ReleaseLock(lck);
	
	
	
	/*
	DestroyLock(lck);
	DestroyCV(cv);
	*/
}
