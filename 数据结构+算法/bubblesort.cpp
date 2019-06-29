#include <stdio.h>
#include <gtest/gtest.h>


void BubbleSort(int a[], int len)
{
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - i - 1; j++)
		{
			if(a[j] > a[j+1])		// 两两比较相邻记录，这是冒泡排序的基本思想
			{
				int tmp = a[j]; 
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

TEST(BubbleSortTest, BubbleSort)
{
    int a[] = {0, 18, 3, 5, 2, 9, 40};
	int b[] = {0, 2, 3, 5, 9, 18, 40};
	
	BubbleSort(a, sizeof(a)/sizeof(a[0]));
	EXPECT_EQ(memcmp((void *)a, (void *)b, sizeof(a)), 0);
}
