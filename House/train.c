#include <stdio.h>
#include "house-global.h"

extern double callLoss(Node* ptr, double* tempans);
extern double getRmse(Node* ptr, double* tempans);

// �ݶ��½������w
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

	printf("\nѵ����%d�κ�w�����\n", index);
	for (int i = 0; i < Dimension; i++) {
		w[i] -= temp[i];
		printf("w[%d]=%.6lf\n", i, w[i]);
	}
}

void train(Node* ptr, double* temp, double* w, double* tempans) {
	for (int i = 0; i < trainNum; i++) {
		calGD(ptr, temp, w, i + 1);
		// ����ÿ��ѵ�������ʧ
		printf("Loss=%.6lf\n", callLoss(ptr, tempans));
	}
	// ������ڲ��Լ�Ԥ�����ľ��������
	printf("RMSE=%.6lf\n", getRmse(ptr, tempans));
}

