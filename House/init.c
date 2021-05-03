#include <stdlib.h>
#include <stdio.h>
#include "house-global.h"

extern Node* readData(int* num, Node* ptr);
extern void normalize(Node* ptr, int start, int end);

static void printMaxMin(double* max, double* min) {
	for (int i = 0; i <= Dimension; i++) {
		printf("Max[%d]=%.6lf ", i, max[i]);
		printf("Min[%d]=%.6lf\n", i, min[i]);
	}
}

void getMaxMin(Node* ptr) { // 求数据集中各维度的最值，以便归一化
	max = (double*)malloc((Dimension + 1) * sizeof(double));
	if (!max) exit(-1);
	min = (double*)malloc((Dimension + 1) * sizeof(double));
	if (!min) exit(-1);
	// 多一个维度存储价格最值
	max[0] = 1;
	min[0] = 0;
	for (int i = 1; i < Dimension; i++) {
		max[i] = 0;
		min[i] = 1000;
		for (int j = 0; j < NUM; j++) {
			min[i] = min[i] > ptr[j].data[i] ? ptr[j].data[i] : min[i];
			max[i] = max[i] < ptr[j].data[i] ? ptr[j].data[i] : max[i];
		}
	}

	max[Dimension] = 0;
	min[Dimension] = 1000;
	for (int j = 0; j < NUM; j++) {
		min[Dimension] = min[Dimension] > ptr[j].price ? ptr[j].price : min[Dimension];
		max[Dimension] = max[Dimension] < ptr[j].price ? ptr[j].price : max[Dimension];
	}
	printMaxMin(max, min);
}


void init() {
	ptr = readData(&NUM, ptr);
	getMaxMin(ptr);
	normalize(ptr, 0, NUM);

	temp = (double*)malloc(Dimension * sizeof(double));
	if (!temp) exit(-1);

	w = (double*)malloc(Dimension * sizeof(double));
	if (!w) exit(-1);

	tempans = (double*)malloc(NUM * sizeof(double));
	if (!tempans) exit(-1);
	// ======================

	for (int i = 0; i < Dimension; i++) {
		temp[i] = w[i] = 1.0;
	}
}
