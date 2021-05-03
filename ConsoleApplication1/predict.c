#define _CRT_SECURE_NO_WARNINGS
#include "house-global.h"
#include <stdio.h>
#include <stdlib.h>

extern int readLine(Node* ptr, int flag);
extern rNode* getRelateOrderByDec(Node* ptr);

// ����Ԥ��
double f(Node* ptr, double* w) {
	double res = 0;
	for (int i = 0; i < Dimension; i++) {
		res += w[i] * ptr->data[i];
	}
	return res;
}

void predict(Node* ptr, double* w, double* tempans, int start, int end) {
	for (int i = start; i < end; i++) {
		tempans[i] = f(ptr + i, w); // ÿ�е���ʱԤ����
	}
}

void predictPrice() {
	printf("\nInput data with 13 dimensions:\n");
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) exit(-1);

	if (readLine(p, 1) == -1) exit(-1);
	p->price = w[0];
	for (int i = 1; i < Dimension; i++) {
		p->data[i] = (p->data[i] - min[i]) / (max[i] - min[i]); // ����һ
		p->price += w[i] * p->data[i];
	}
	p->price = p->price * (max[Dimension] - min[Dimension]) + min[Dimension]; // �۸񷴹�һ
	printf("price = %f\n", p->price);
}

void predictPriceByMostRelate(Node* ptr) {
	rNode* r = getRelateOrderByDec(ptr); // ��ȡ����������ϵ���±�
	double sum = 0;

	printf("\n�ĸ������ϵ����\n");
	for (int i = 0; i < 4; i++) {
		printf("r: %.6f, ά���±꣺%d\n", r[i].r, r[i].index);
	}

	printf("\nInput data with these dimensions - :");
	for (int i = 0; i < 4; i++) {
		printf("%d ", r[i].index + 1);
	}
	printf("\n");

	Node* p = (Node*)malloc(sizeof(Node));
	if (!p) exit(-1);

	p->data[0] = 1;
	for (int i = 1; i < Dimension; i++) {
		p->data[i] = 0;
	}

	for (int i = 0; i < 4; i++) {
		if (scanf("%lf", &(p->data[r[i].index])) == EOF) exit(-1);
	}
	p->price = w[0];
	for (int i = 1; i < Dimension; i++) {
		p->data[i] = (p->data[i] - min[i]) / (max[i] - min[i]); // ����һ
		p->price += w[i] * p->data[i];
	}
	p->price = p->price * (max[Dimension] - min[Dimension]) + min[Dimension]; // �۸񷴹�һ
	printf("price = %f\n", p->price);
	free(r);
}

