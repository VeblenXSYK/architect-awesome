#include <stdio.h>
#include <gtest/gtest.h>

struct ListNode
{
	int val;
	ListNode *next;
	
	ListNode(int i) : val(i),next(NULL) {}
};

ListNode *CreateList(int datanum, int databuf[])
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

void GetDataInfo(ListNode *list, int databuf[])
{
	int i = 0;
	while(list != NULL)
	{
		databuf[i++] = list->val;
		list = list->next;
	}
}

/*
	基本思想：遍历一遍链表，利用一个辅助指针，存储遍历过程中当前指针指向的下一个元素，然后将当前节点元素的指针反转后，利用已经存储的指针往后面继续遍历。
*/
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

TEST(ReverseListTest, ReverseList)
{	
	// 准备链表
	int databuf[] = { 10, 34, 13, 42, 57 };
	int datanum = sizeof(databuf);
	ListNode *pNode = CreateList(datanum, databuf);
	
	// 反转链表
	int reversedatabuf[datanum] = { 0 };
	GetDataInfo(ReverseList(pNode), reversedatabuf);
	
	// 测试
	for(int i = 0; i < datanum; i++)
	{
		EXPECT_EQ(databuf[i], reversedatabuf[datanum - i - 1]);
	}
}