#include "FreeRTOS.h"
#include <stdlib.h>
#include "list.h"


//�ڵ�ĳ�ʼ��
void vListInitialiseItem(ListItem_t * const pxItem)
{
	//�б������ڵ�����Ϊ�գ�����ʼ������
	pxItem->pvContainer  = NULL;

}

//���ڵ�ĳ�ʼ��
void vListInitialise(List_t* const pxList)
{
	//����ָ�����һ���ڵ�
	pxList->pxIndex = (ListItem_t *)&(pxList->xListEnd);
	
	//����ֵ��ʼ��Ϊ���ֵ,ȷ���ýڵ�Ϊ��������ڵ�
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	//�����һ���ڵ��ǰ��ָ���ָ��������ʾ����Ϊ��
	pxList->xListEnd.pxPrevious = (ListItem_t *)&(pxList->xListEnd);
	pxList->xListEnd.pxNext     = (ListItem_t *)&(pxList->xListEnd);
	
	//����ڵ������Ϊ0,��ʾ����Ϊ��(U��ʾ�޷���)
	pxList->uxNumberOfItems = 0U;
}

//�������һ��ֵ   �β�ֵ(��Ҫ�������������Ľڵ�)
void vListInsertEnd(List_t * const pxList,ListItem_t * const pxNewListItem)
{
	//��¼�µ�ǰ����ָ��
	 ListItem_t * const pxIndex = pxList->pxIndex ;

	//���²���Ľڵ�ǰ��ָ���޸�
	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	
	//�޸�����ָ��Ľڵ��ǰ��ָ��
	pxIndex->pxPrevious->pxNext = pxNewListItem;  
	pxIndex->pxPrevious = pxNewListItem;

	//������������
	pxNewListItem->pvContainer = (void *)pxList;	
	
	//����ֵ����
	(pxList->uxNumberOfItems)++;

}

//���ڵ㰴���������в�������
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	//1.�ҵ���Ҫ����ĵط�
	//(1)�Ȳ鿴������ֵ
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	//(2)���в���
	if(xValueOfInsertion ==portMAX_DELAY ) 			  //�ж��Ƿ�Ϊ���һ���ڵ�λ
	{
		pxIterator = pxList->xListEnd.pxPrevious; 	//��¼�����һ�ڵ�ǰ��λ��
	}
	else
	{
		for(pxIterator = (ListItem_t *)&(pxList->xListEnd);
				pxIterator->pxNext->xItemValue <= xValueOfInsertion;										
				pxIterator = pxIterator->pxNext		 					 )
		{
		/* 	ѭ�����ȴ��ҵ��ڵ� */
		}
	}
	//2.���в���
	//(1)�޸�ǰ��ָ��
	pxNewListItem->pxNext = pxIterator->pxNext ;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext->pxPrevious = pxNewListItem;
	pxIterator->pxNext = pxNewListItem;

	//(2)������������
	pxNewListItem->pvContainer = (void *)pxList;
	//(3)����ֵ����
	(pxList->uxNumberOfItems)++;
}

/* ���ڵ��������ɾ�� */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
	/* ��ȡ�ڵ����ڵ����� */
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	/* ��ʼ���ýڵ����ڵ�����Ϊ�գ���ʾ�ڵ㻹û�в����κ����� */
	pxItemToRemove->pvContainer = NULL;
	
	/* ����ڵ������-- */
	( pxList->uxNumberOfItems )--;

	/* ����������ʣ��ڵ�ĸ��� */
	return pxList->uxNumberOfItems;
}

