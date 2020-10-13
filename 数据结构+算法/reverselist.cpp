#include <stdio.h>
#include <gtest/gtest.h>

struct ListNode
{
	int val;
	ListNode *next;
	
	ListNode(int i) : val(i),next(NULL) {}
};

void PrintInfo(ListNode *list, int databuf[])
{
	int i = 0;
	while(list != NULL)
	{
		printf("%d ", list->val);
		databuf[i++] = list->val;
		list = list->next;
	}
	printf("\n");
}

ListNode *ReverseList(ListNode *pNode)
{
	ListNode *prev = NULL;
	while(pNode)
	{
		ListNode *pNext = pNode->next;
		pNode->next = prev;
		prev = pNode;
		pNode = pNext;
	}
	
	return prev;
}

TEST(QuickSortTest, ReverseList)
{
	int datanum = 10;
	
	// 准备链表
	ListNode *pCur = NULL;
	ListNode *pHead = NULL;
	for(int i = 0; i < datanum; i++)
	{
		if(i == 0)
		{
			pCur = new ListNode(i);
			pHead = pCur;
		}
		else
		{
			pCur->next = new ListNode(i);
			pCur = pCur->next;
		}
	}

	int databuf[datanum] = { 0 };
	int reversedatabuf[datanum] = { 0 };
	PrintInfo(pHead, databuf);
	PrintInfo(ReverseList(pHead), reversedatabuf);
	
	for(int i = 0; i < datanum; i++)
	{
		EXPECT_EQ(databuf[i], reversedatabuf[datanum - i - 1]);
	}
}