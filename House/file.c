#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "house-global.h"

void printData(Node* ptr) {
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < Dimension; j++) {
			printf("%.6lf ", ptr[i].data[j]);
		}
		printf("实际房价：%.6lf\n", ptr[i].price);
	}
}

int readLine(Node* ptr, int flag) {
	// 将每行的数据，各个维度，存入data
	for (int i = 1; i < Dimension; i++) {
		if (scanf("%lf", &(ptr->data[i])) == EOF) return -1; //
	}

	// 读入价格
	if (!flag && scanf("%lf", &(ptr->price)) == EOF) return -1;

	// 存放 x0 = 1，偏置
	ptr->data[0] = 1;
	return 1;
}


Node* readData(int* num, Node* ptr) {
	//输入重定向，输入数据将从DATAFILE文件中读取
	freopen(DATAFILE, "r", stdin);
	*num = 0;// 第一个测试数据
	ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) exit(-1);

	char s[100];
	scanf("%[^\n]", s); // 读取一行
	while (readLine(ptr + *num, 0) > 0) {
		(*num)++;

		// 根据测试用例个数调整内存大小
		ptr = (Node*)realloc(ptr, (*num + 1)*sizeof(Node));

		if (!ptr) exit(-1);

	}
	
	freopen("CON", "r", stdin); // 恢复输入重定向
	return ptr;
}
