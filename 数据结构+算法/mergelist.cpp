#include <stdio.h>
#include <gtest/gtest.h>

struct ListNode
{
	int val;
	ListNode *next;
	
	ListNode(int i) : val(i),next(NULL) {}
};

static ListNode *CreateList(int datanum, int databuf[])
{
	// 准备链表
	ListNode *pCur = NULL;
	ListNode *pHead = NULL;
	for(int i = 0; i < datanum; i++)
	{
		if(i == 0)
		{
			pCur = new ListNode(databuf[i]);
			pHead = pCur;
		}
		else
		{
			pCur->next = new ListNode(databuf[i]);
			pCur = pCur->next;
		}
	}
	
	return pHead;
}

static void GetDataInfo(ListNode *list, int databuf[])
{
	int i = 0;
	while(list != NULL)
	{
		databuf[i++] = list->val;
		list = list->next;
	}
}

/*
	建立两个指针p1,p2分别指向两个链表，依次比较p1,p2所指向元素的值，把小的连接到新的链表中，并向后移动。直到p1,p2其中一个指向NULL
*/
static ListNode *MergeList(ListNode *pNodeA, ListNode *pNodeB)
{
	if(pNodeA == NULL)
	{
		return pNodeB;
	}
	
	if(pNodeB == NULL)
	{
		return pNodeA;
	}
	
	ListNode *pHead = NULL, *pNode = NULL;
	if(pNodeA->val < pNodeB->val)
	{
		pHead = pNodeA;
		pNodeA = pNodeA->next;
	}
	else
	{
		pHead = pNodeB;
		pNodeB = pNodeB->next;
	}
	pNode = pHead;
	
	while(pNodeA != NULL && pNodeB != NULL)
	{
		if(pNodeA->val < pNodeB->val)
		{
			pNode->next = pNodeA;
			pNodeA = pNodeA->next;
		}
		else
		{
			pNode->next = pNodeB;
			pNodeB = pNodeB->next;
		}
		
		pNode = pNode->next;
	}
	
	if(pNodeA == NULL)
	{
		pNode->next = pNodeB;
	}
	else
	{
		pNode->next = pNodeA;
	}
	
	return pHead;
}

TEST(MergeListTest, MergeList)
{
	int dataAbuf[] = { 53, 56, 100, 489, 578, 980 };
	int dataBbuf[] = { 52, 57, 490, 545, 1000};
	ListNode *pNodeA = CreateList(sizeof(dataAbuf)/sizeof(int), dataAbuf);
	ListNode *pNodeB = CreateList(sizeof(dataBbuf)/sizeof(int), dataBbuf);

	int datanum = sizeof(dataAbuf)/sizeof(int) + sizeof(dataBbuf)/sizeof(int);
	int databuf[datanum] = { 0 };
	ListNode *pList = MergeList(pNodeA, pNodeB);
	GetDataInfo(pList, databuf);
	for(int i = 0; i < datanum - 1; i++)
	{
		ASSERT_LE(databuf[i], databuf[i+1]);
	}
}