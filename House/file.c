#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "house-global.h"

void printData(Node* ptr) {
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < Dimension; j++) {
			printf("%.6lf ", ptr[i].data[j]);
		}
		printf("ʵ�ʷ��ۣ�%.6lf\n", ptr[i].price);
	}
}

int readLine(Node* ptr, int flag) {
	// ��ÿ�е����ݣ�����ά�ȣ�����data
	for (int i = 1; i < Dimension; i++) {
		if (scanf("%lf", &(ptr->data[i])) == EOF) return -1; //
	}

	// ����۸�
	if (!flag && scanf("%lf", &(ptr->price)) == EOF) return -1;

	// ��� x0 = 1��ƫ��
	ptr->data[0] = 1;
	return 1;
}


Node* readData(int* num, Node* ptr) {
	//�����ض����������ݽ���DATAFILE�ļ��ж�ȡ
	freopen(DATAFILE, "r", stdin);
	*num = 0;// ��һ����������
	ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) exit(-1);

	char s[100];
	scanf("%[^\n]", s); // ��ȡһ��
	while (readLine(ptr + *num, 0) > 0) {
		(*num)++;

		// ���ݲ����������������ڴ��С
		ptr = (Node*)realloc(ptr, (*num + 1)*sizeof(Node));

		if (!ptr) exit(-1);

	}
	
	freopen("CON", "r", stdin); // �ָ������ض���
	return ptr;
}
