#include <stdlib.h>
#include "house-global.h"

extern void train(Node* ptr, double* temp, double* w, double* tempans);
extern void init();
extern void predictPrice();
extern void predictPriceByMostRelate(Node* ptr);
void clean();

int NUM; // 数据集总数
Node* ptr; //数据集，(ptr+i)->data[j]
double* temp, * w, * tempans; // 临时数组，系数，临时预测结果
double* max, * min; //存储各个维度的最大值和最小值


int main(void) {
	init(); 
	train(ptr, temp, w, tempans);
	predictPrice();
	predictPriceByMostRelate(ptr);
	
	clean(); // 释放占用内存空间
	return 0;
}

void clean() {
	free(ptr);
	free(max);
	free(min);
	free(w);
	free(tempans);
	free(temp);
}

