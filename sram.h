#ifndef __SRAM_H
#define __SRAM_H															    
void *SramMalloc(unsigned int size);
void SramFree(void *pv);
void TraceHeap(void);
#endif
