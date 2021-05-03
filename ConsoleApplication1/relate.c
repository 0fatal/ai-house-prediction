#include"house-global.h"
#include<math.h>
#include<stdlib.h>

int compare(const void* avg1, const void* avg2)
{
	rNode* a = (rNode*)avg1;
	rNode* b = (rNode*)avg2;
	return a->r > b->r ? -1 : 1;
}

rNode* getRelateOrderByDec(Node* ptr)
{
	int i, j;
	double sum[Dimension], sumy, avgx[Dimension], avgy;
	double realx[Dimension], onlyx[Dimension] ,onlyy;
	rNode *a = (rNode*)malloc(sizeof(rNode)*Dimension);//列
	if (!a) exit(-1);

	for (i = 0; i < Dimension; i++)//求出每列x的和
	{
		sum[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			sum[i] += (ptr + j)->data[i];
		}
		avgx[i] = sum[i] / NUM; //对应列x的平均值
	}

	sumy = 0;
	for (i = 0; i < NUM; i++)
	{
		sumy += (ptr + i)->price;
	}

	avgy = sumy / NUM;      //对应y的平均值;
	// ===================

	// ============皮尔逊分子
	for (i = 0; i < Dimension; i++)//  求对应的（xi-x）*（yi-y）的和
	{
		realx[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			realx[i] += ((ptr + j)->data[i] - avgx[i]) * ((ptr + j)->price - avgy);
		}
	}

	// ============皮尔逊分母
	for (i = 0; i < Dimension; i++)//  求对应的平方(xi-x)的和
	{
		onlyx[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			onlyx[i] += ((ptr + j)->data[i] - avgx[i])* ((ptr + j)->data[i] - avgx[i]);
		}
	}

	onlyy = 0;
	for (i = 0; i < NUM; i++)    //   求(yi - y)平方的和
	{
		onlyy += ((ptr + i)->price - avgy)* ((ptr + i)->price - avgy);
	}

	a[0].r = -1;
	for (i = 1; i < Dimension; i++)  //算出对应x的r
	{
		a[i].r = (realx[i]) / sqrt(onlyx[i] * onlyy);
		a[i].index = i;
	}
	qsort(a, Dimension, sizeof(rNode), compare);
	return a;
}