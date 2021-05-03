#include <stdio.h>
#include "house-global.h"

extern double callLoss(Node* ptr, double* tempans);
extern double getRmse(Node* ptr, double* tempans);

// 梯度下降求最佳w
void calGD(Node* ptr, double* temp, double* w, int index) {
	for (int i = 0; i < Dimension; i++) {
		double res = 0;
		for (int j = 0; j < NUM - testNum; j++) {
			double sum = 0;
			for (int k = 0; k < Dimension; k++) {
				sum += w[k] * ptr[j].data[k];
			}
			res += (sum - ptr[j].price) * ptr[j].data[i];
		};
		temp[i] = learningRate * res / NUM;
	}

	printf("\n训练第%d次后w结果：\n", index);
	for (int i = 0; i < Dimension; i++) {
		w[i] -= temp[i];
		printf("w[%d]=%.6lf\n", i, w[i]);
	}
}

void train(Node* ptr, double* temp, double* w, double* tempans) {
	for (int i = 0; i < trainNum; i++) {
		calGD(ptr, temp, w, i + 1);
		// 计算每次训练后的损失
		printf("Loss=%.6lf\n", callLoss(ptr, tempans));
	}
	// 计算基于测试集预测结果的均方根误差
	printf("RMSE=%.6lf\n", getRmse(ptr, tempans));
}

