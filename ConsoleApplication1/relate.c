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
	rNode *a = (rNode*)malloc(sizeof(rNode)*Dimension);//��
	if (!a) exit(-1);

	for (i = 0; i < Dimension; i++)//���ÿ��x�ĺ�
	{
		sum[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			sum[i] += (ptr + j)->data[i];
		}
		avgx[i] = sum[i] / NUM; //��Ӧ��x��ƽ��ֵ
	}

	sumy = 0;
	for (i = 0; i < NUM; i++)
	{
		sumy += (ptr + i)->price;
	}

	avgy = sumy / NUM;      //��Ӧy��ƽ��ֵ;
	// ===================

	// ============Ƥ��ѷ����
	for (i = 0; i < Dimension; i++)//  ���Ӧ�ģ�xi-x��*��yi-y���ĺ�
	{
		realx[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			realx[i] += ((ptr + j)->data[i] - avgx[i]) * ((ptr + j)->price - avgy);
		}
	}

	// ============Ƥ��ѷ��ĸ
	for (i = 0; i < Dimension; i++)//  ���Ӧ��ƽ��(xi-x)�ĺ�
	{
		onlyx[i] = 0;
		for (j = 0; j < NUM; j++)
		{
			onlyx[i] += ((ptr + j)->data[i] - avgx[i])* ((ptr + j)->data[i] - avgx[i]);
		}
	}

	onlyy = 0;
	for (i = 0; i < NUM; i++)    //   ��(yi - y)ƽ���ĺ�
	{
		onlyy += ((ptr + i)->price - avgy)* ((ptr + i)->price - avgy);
	}

	a[0].r = -1;
	for (i = 1; i < Dimension; i++)  //�����Ӧx��r
	{
		a[i].r = (realx[i]) / sqrt(onlyx[i] * onlyy);
		a[i].index = i;
	}
	qsort(a, Dimension, sizeof(rNode), compare);
	return a;
}