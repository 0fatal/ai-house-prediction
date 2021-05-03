#include "house-global.h"
#include <stdio.h>
#include <math.h>

extern void normalize(Node* ptr, int start, int end);
extern void normalizeBack(Node* ptr, int start, int end);
extern void predict(Node* ptr, double* w, double* tempans, int start, int end);

// 反归一化ptr和tempans
void normalizeBackPrice(Node* ptr, double* tempans, int start, int end) {
	normalizeBack(ptr, start, end);
	for (int i = start; i < end; i++) {
		tempans[i] = tempans[i] * (max[Dimension] - min[Dimension]) + min[Dimension];
	}
}


// 归一化ptr 和 tempans
void normalizePrice(Node* ptr, double* tempans, int start, int end) {
	normalize(ptr, start, end);
	for (int i = start; i < end; i++) {
		tempans[i] = (tempans[i] - min[Dimension]) / (max[Dimension] - min[Dimension]);
	}
}

/** 
 * 梯度下降时，数据进行了归一化操作，因此计算损失时需要通过normalizePrice对数据和临时数组tempans进行反归一化
 * 预测完成后，重新归一化价格
 */
double callLoss(Node* ptr, double* tempans) {
	predict(ptr, w, tempans, 0, NUM - testNum);
	double loss = 0;
	normalizeBackPrice(ptr, tempans, 0, NUM - testNum);
	
	for (int i = 0; i < NUM - testNum; i++) {
		loss += (ptr[i].price - tempans[i]) * (ptr[i].price - tempans[i]);
	}
	normalizePrice(ptr, tempans, 0, NUM - testNum);
	loss = loss / (2  * (NUM - testNum));
	return loss;
}

double getRmse(Node* ptr, double* tempans) {
	double res = 0;
	predict(ptr, w, tempans, NUM - testNum, NUM);
	normalizeBackPrice(ptr, tempans, NUM - testNum, NUM);
	for (int i = NUM - testNum; i < NUM; i++) {
		printf("%d:\n", i);
		for (int j = 0; j < Dimension; j++) {
			printf("%.6lf  ", ptr[i].data[j]);
		}
		printf("实际房价：%.6lf ", ptr[i].price);
		printf("预测房价：%.6lf\n", tempans[i]);
		res += (tempans[i] - ptr[i].price) * (tempans[i] - ptr[i].price) / testNum;
	}
	res = sqrt(res);
	normalize(ptr, tempans, NUM - testNum, NUM);
	return res;
}