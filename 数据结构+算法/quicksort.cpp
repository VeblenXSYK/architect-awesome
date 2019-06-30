#include <stdio.h>
#include <gtest/gtest.h>

/*
	基本思想：通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小，
		则可分别对这两部分记录继续进行排序，以达到整个序列有序的目的。
*/
void QuickSort(int a[], int low, int high)
{
	if(low < high)
	{
		int i = low, j = high, x = a[low];
		while(i < j)
		{
			while(i < j && a[j] > x)	// 从右向左找第一个小于x的数
				j--;
			if(i < j)
				a[i++] = a[j];
			
			while(i < j && a[i] < x)	// 从左向右找第一个大于x的数
				i++;
			if(i < j)
				a[j--] = a[i];
		}
		a[i] = x;
		
		QuickSort(a, low, i-1);			// 递归调用
		QuickSort(a, i+1, high);
	}
}

TEST(QuickSortTest, QuickSort)
{
    int a[] = {60, 80, 90, 60, 60};
	int b[] = {60, 60, 60, 80, 90};
	
	QuickSort(a, 0, sizeof(a)/sizeof(a[0])-1);
	EXPECT_EQ(memcmp((void *)a, (void *)b, sizeof(a)), 0);
}