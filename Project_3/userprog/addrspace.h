// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.


#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "table.h"

#define UserStackSize		1024 	// increase this as necessary!

#define MaxOpenFiles 256
#define MaxChildSpaces 256

enum DiskLocation { EXECUTABLE=0, NOT_ON_DISK, SWAP_FILE };
typedef struct _PageTableEnhancedData
{
	DiskLocation diskLocation;
	int byteOffset;
}PageTableEnhancedData;

class Lock;

class AddrSpace {
  public:
    OpenFile *executable;	// executable pointer
    AddrSpace(OpenFile *executable);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch
    Table fileTable;			// Table of openfiles
	
	// resize the page table to include the stack for the newly created kernel thread
	
	int ResizePageTable();
	
	//clear the stack pages for the thread when it is finishing
	void RemoveThreadStack();
	
	//process to which the adress space belongs
	int associatedProcess;

	//get the number of pages of the address space
	int GetNumPages();

	// define the stack start 
	int stackStart;

	// reclaim page table
	void ReclaimPhysicalPages();

	// set the stack top of the first thread in the process
	void SetDefaultStack();

	// populate the TLB, if TLB miss is found with pageTable entry
	void populateTLBFromPagetable(int currentVPN);
	int handleIPTMiss(int currentVPN);

	PageTableEnhancedData *pageTableX;  // Extented part of pagetable
    TranslationEntry *pageTable;	// Assume linear page table translation
	Lock *addrSpaceLock;
 private:
 unsigned int numPages;		// Number of pages in the virtual 
					// address space
	int lastPhysicalPageMapped;
};

#endif // ADDRSPACE_H
