#include "FreeRTOS.h"
#include <stdlib.h>
#include "list.h"


//节点的初始化
void vListInitialiseItem(ListItem_t * const pxItem)
{
	//列表项所在的链表为空，即初始化结束
	pxItem->pvContainer  = NULL;

}

//根节点的初始化
void vListInitialise(List_t* const pxList)
{
	//索引指向最后一个节点
	pxList->pxIndex = (ListItem_t *)&(pxList->xListEnd);
	
	//辅助值初始化为最大值,确保该节点为链表的最后节点
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	//将最后一个节点的前后指针均指向自身，表示链表为空
	pxList->xListEnd.pxPrevious = (ListItem_t *)&(pxList->xListEnd);
	pxList->xListEnd.pxNext     = (ListItem_t *)&(pxList->xListEnd);
	
	//链表节点计数器为0,表示链表为空(U表示无符号)
	pxList->uxNumberOfItems = 0U;
}

//插入最后一个值   形参值(需要插入的链表，插入的节点)
void vListInsertEnd(List_t * const pxList,ListItem_t * const pxNewListItem)
{
	//记录下当前索引指向
	 ListItem_t * const pxIndex = pxList->pxIndex ;

	//将新插入的节点前后指针修改
	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	
	//修改索引指向的节点的前后指针
	pxIndex->pxPrevious->pxNext = pxNewListItem;  
	pxIndex->pxPrevious = pxNewListItem;

	//更新所在链表
	pxNewListItem->pvContainer = (void *)pxList;	
	
	//计数值增加
	(pxList->uxNumberOfItems)++;

}

//将节点按照升序排列插入链表
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	//1.找到需要插入的地方
	//(1)先查看排序辅助值
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	//(2)进行查找
	if(xValueOfInsertion ==portMAX_DELAY ) 			  //判断是否为最后一个节点位
	{
		pxIterator = pxList->xListEnd.pxPrevious; 	//记录下最后一节点前的位置
	}
	else
	{
		for(pxIterator = (ListItem_t *)&(pxList->xListEnd);
				pxIterator->pxNext->xItemValue <= xValueOfInsertion;										
				pxIterator = pxIterator->pxNext		 					 )
		{
		/* 	循环，等待找到节点 */
		}
	}
	//2.进行插入
	//(1)修改前后指针
	pxNewListItem->pxNext = pxIterator->pxNext ;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext->pxPrevious = pxNewListItem;
	pxIterator->pxNext = pxNewListItem;

	//(2)更新所在链表
	pxNewListItem->pvContainer = (void *)pxList;
	//(3)计数值增加
	(pxList->uxNumberOfItems)++;
}

/* 将节点从链表中删除 */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
	/* 获取节点所在的链表 */
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItemToRemove->pvContainer = NULL;
	
	/* 链表节点计数器-- */
	( pxList->uxNumberOfItems )--;

	/* 返回链表中剩余节点的个数 */
	return pxList->uxNumberOfItems;
}

