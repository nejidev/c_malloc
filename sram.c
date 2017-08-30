#include <string.h>
#include <stdio.h>
#include "sram.h"

//以下定义大小是为了直观的看到程序运行分配结果，取10进制数
//整个SRAM大小
#define SRAM_SIZE (1000)

//堆分块大小
#define HeapBlockSIZE (100)

//以下代码在 GCC 中演示使用编译器分一个大的SRAM 在实际硬件中，直接写内存开始地址就可以
//#define SRAM_BASE_ADDR 0
static char SRAM_BASE_ADDR[SRAM_SIZE] = {0};

/* 管理堆的链表 */
typedef struct A_BLOCK_LINK
{
	char *pV;						        /* 内存实际物理地址 */
	int  index;                             /* 内存编号 */  
	char empty;                             /* 1 空 0 非空  */
	int  heapLen;                           /* 分配长度 */   
	struct A_BLOCK_LINK *pxNextFreeBlock;	/* 上个节点 */
	struct A_BLOCK_LINK *pxPrevFreeBlock;	/* 下个节点 */
} BlockLink_t;

//头节点
static char *HeapHead = NULL;
//块数量
static int BlockTotal = 0;

void TraceHeap(void)
{
	BlockLink_t *pTempBlockLink = (BlockLink_t *)HeapHead;
	printf("\r\n##########TraceHeap#############\r\n");
	while(pTempBlockLink)
	{
		printf("index: %d empty:%d addr:%d \r\n", pTempBlockLink->index, pTempBlockLink->empty, pTempBlockLink->pV - SRAM_BASE_ADDR);
		pTempBlockLink = pTempBlockLink->pxNextFreeBlock;
	}
	printf("\r\n##########TraceHeap#############\r\n");
}

//堆 Heap 分配初始化
void InitHeap(void)
{
	BlockLink_t *pBlockLink, *pTempBlockLink = NULL;
	int i = 0;
	char *pHeapStart = (char *)SRAM_BASE_ADDR;
	char *pHeapEnd   = (char *)(SRAM_BASE_ADDR + SRAM_SIZE);
	pHeapEnd -= HeapBlockSIZE;
	BlockTotal = SRAM_SIZE / (HeapBlockSIZE + sizeof(BlockLink_t));
	while(i < BlockTotal)
	{
		pBlockLink          = (BlockLink_t *)pHeapStart;
		pBlockLink->pxPrevFreeBlock = pTempBlockLink;
		pBlockLink->pV      = pHeapEnd;
		pBlockLink->index   = i;
		pBlockLink->empty   = 1;
		pBlockLink->heapLen = 0;
		//指针重定位
		pHeapEnd   -= HeapBlockSIZE;
		pHeapStart += sizeof(BlockLink_t);
		//双向链表的上一个
		pTempBlockLink = pBlockLink;
		pBlockLink->pxNextFreeBlock = (BlockLink_t *)pHeapStart;	
		i++;
	}
	pBlockLink->pxNextFreeBlock = NULL;
	HeapHead = (char *)SRAM_BASE_ADDR;
}

static BlockLink_t *FindHeap(char *addr)
{
	BlockLink_t *pTempBlockLink = (BlockLink_t *)HeapHead;
	//从低向高查找可用的内存
	while(pTempBlockLink)
	{
		if(pTempBlockLink->pV == addr)
		{
			return pTempBlockLink;
		}
		//切换下一节点
		pTempBlockLink = pTempBlockLink->pxNextFreeBlock;
	}
	return NULL;
}

//查找可用的连续内存
static void *SramFindHeap(int size)
{
	char *mem;
	int seriesSize = 0;           //已查找到连续用的内存
	BlockLink_t *pTempBlockLink;  //头节点
	pTempBlockLink = (BlockLink_t *)HeapHead;
	//从低向高查找可用的内存
	while(pTempBlockLink)
	{
		//如果是未使用的内存
		if(pTempBlockLink->empty)
		{
			seriesSize += HeapBlockSIZE;
		}
		else
		{
			seriesSize = 0;
		}
		//如果查找到连续未使用的内存
		if(seriesSize >= size)
		{	
			//返回内存堆开始地址 
			pTempBlockLink->heapLen = seriesSize; //设置分配堆长度
			mem = pTempBlockLink->pV;
			
			//将内存标记为 已使用
			while(seriesSize && pTempBlockLink)
			{
				seriesSize -= HeapBlockSIZE;
				pTempBlockLink->empty = 0;
				pTempBlockLink = pTempBlockLink->pxPrevFreeBlock;
			}
			return mem;
		}
		//切换下一节点
		pTempBlockLink = pTempBlockLink->pxNextFreeBlock;
	}
	return NULL;
}

//内存碎片整理
static void SramMerge(void)
{
	
}

void *SramMalloc(size_t xWantedSize)
{
	char *mem;
	
	if(! HeapHead)
	{
		InitHeap();
	}
	//地址对齐
	
	mem = SramFindHeap(xWantedSize);
	if(mem)
	{
		return mem;
	}
	//如果没有查找到 整理内存碎片
	SramMerge();
	
	//仍然分配不成功 返回错误
	mem = SramFindHeap(xWantedSize);
	if(mem)
	{
		return mem;
	}
	return NULL;
}

void SramFree( void *pv )
{
	int heapLen = 0;
	//释放内存 从堆的高位开始向低位查找
	BlockLink_t *pTempHeap = FindHeap(pv);
	heapLen = pTempHeap->heapLen;
	while(heapLen && pTempHeap)
	{
		//设为空闲状态
		pTempHeap->empty   = 1;
		pTempHeap->heapLen = 0;
		//查找上个节点
		pTempHeap = pTempHeap->pxPrevFreeBlock;
		heapLen -= HeapBlockSIZE;
	}
}
