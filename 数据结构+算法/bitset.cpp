/*
 * 问题：怎么在2.5亿个整数中找出不重复的整数注（PS：内存不足以容纳这2.5亿个整数）
 * 思路：采用2-Bitmap（每个数分配2bit，00表示不存在，01表示出现一次，10表示多次，11无意义），
 * 		 共需60M内存内存，还可以接受。然后扫描这2.5亿个整数，查看Bitmap中相对应位，如果是00变01，01变10，10保持不变。
 *       扫描完事后，查看bitmap，把对应位是01的整数输出即可。
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <bitset>

using namespace std;
 
#define TestArrayLen (100)						// 多少个数
#define RangeValue (100)						// 取值范围
#define BitsPerInt (32)							// Int类型所占位数，int类型改为位存储
#define BitsPerNum (BitsPerInt/2)				// 一个数用2位存储==原一个int类型的整数空间（4字节）可以存储16个数
#define BitArrayLen (1+RangeValue/BitsPerNum)	// 所需位数组长度

bitset<BitsPerInt> *bitArray = new bitset<BitsPerInt>[BitArrayLen];
 

int main()
{
	int *data = new int[TestArrayLen];
	memset(data, 0, TestArrayLen);
 
	// 生成1-TestArrayLen之间的随机数
	srand((unsigned)time(NULL));
	for (int i = 0; i < TestArrayLen; i++)
	{
		data[i] = rand() % RangeValue + 1;
		cout << data[i] << " ";
		if ((i+1)%10 == 0) cout << endl;
	}
	
	int roundNum = 0;	// 取整
	int remainNum = 0;	// 取余
	// 数据在位图中进行存储，即位图排序
	for (int j = 0; j < TestArrayLen; j++)
	{
		roundNum = (data[j]-1) / BitsPerNum;
		remainNum = (data[j]-1) % BitsPerNum;
		// 如果为01，设为10；本来为10，不变
		if (bitArray[roundNum][remainNum*2]==1 || bitArray[roundNum][remainNum*2+1]==1)
		{
			bitArray[roundNum].set(remainNum*2+1, 1);
			bitArray[roundNum].set(remainNum*2, 0);
		}
		// 如果为00，设为01
		else
		{
			bitArray[roundNum].set(remainNum*2, 1);
		}
	}
	
	// 输出所有重复的数
	cout << "所有重复的数：";
	for (int k = 0; k < BitArrayLen; k++)
	{
		for (int l = 0; l < BitsPerNum; l++)
		{
			if (bitArray[k][2*l+1] == 1)
			{
				cout << k*BitsPerNum+l+1 << " ";
			}
		}
	}
	cout << endl;
 
	// 输出所有不重复的数
	cout << "所有不重复的数：";
	for (int m = 0; m < BitArrayLen; m++)
	{
		for (int l = 0; l < BitsPerNum; l++)
		{
			if (bitArray[m][2*l] == 1)
			{
				cout << m*BitsPerNum+l+1 << " ";
			}
		}
	}
	cout << endl;

	return 0;
}
