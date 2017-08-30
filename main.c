#include <stdio.h>
#include <string.h>
#include "sram.h"
int main(int argc, char **argv)
{
	char *p1, *p2, *p3, *p4;
	p1 = SramMalloc(300);
	if(! p1)
	{
		printf("p1 malloc err \r\n");
		return 0;
	}
	printf("p1 malloc ok addr:%d \r\n", p1);
	TraceHeap();
	
	p2 = SramMalloc(200);
	if(! p2)
	{
		printf("p2 malloc err \r\n");
		return 0;
	}
	printf("p2 malloc ok addr:%d \r\n", p2);
	TraceHeap();
	
	SramFree(p1);
	printf("p1 free \r\n");
	TraceHeap();
	
	p3 = SramMalloc(100);
	if(! p3)
	{
		printf("p3 malloc err \r\n");
		return 0;
	}
	printf("p3 malloc ok addr:%d \r\n", p3);
	TraceHeap();
	
	SramFree(p2);
	SramFree(p3);
	TraceHeap();
	
	p4 = SramMalloc(1001);
	if(! p4)
	{
		printf("p4 malloc err \r\n");
		return 0;
	}
	return 0;
}
