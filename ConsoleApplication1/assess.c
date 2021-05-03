#include "house-global.h"
#include <stdio.h>
#include <math.h>

extern void normalize(Node* ptr, int start, int end);
extern void normalizeBack(Node* ptr, int start, int end);
extern void predict(Node* ptr, double* w, double* tempans, int start, int end);

// ����һ��ptr��tempans
void normalizeBackPrice(Node* ptr, double* tempans, int start, int end) {
	normalizeBack(ptr, start, end);
	for (int i = start; i < end; i++) {
		tempans[i] = tempans[i] * (max[Dimension] - min[Dimension]) + min[Dimension];
	}
}


// ��һ��ptr �� tempans
void normalizePrice(Node* ptr, double* tempans, int start, int end) {
	normalize(ptr, start, end);
	for (int i = start; i < end; i++) {
		tempans[i] = (tempans[i] - min[Dimension]) / (max[Dimension] - min[Dimension]);
	}
}

/** 
 * �ݶ��½�ʱ�����ݽ����˹�һ����������˼�����ʧʱ��Ҫͨ��normalizePrice�����ݺ���ʱ����tempans���з���һ��
 * Ԥ����ɺ����¹�һ���۸�
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
		printf("ʵ�ʷ��ۣ�%.6lf ", ptr[i].price);
		printf("Ԥ�ⷿ�ۣ�%.6lf\n", tempans[i]);
		res += (tempans[i] - ptr[i].price) * (tempans[i] - ptr[i].price) / testNum;
	}
	res = sqrt(res);
	normalize(ptr, tempans, NUM - testNum, NUM);
	return res;
}