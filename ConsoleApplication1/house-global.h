#pragma once
#define Dimension 14 // ѵ��ά����
#define learningRate 0.002 // ѧϰ��
#define EPS 0.001 // ������Ծ���
#define testNum 50 // ���Լ��е����ݸ�����ǰNUM-testNum��Ϊѵ��������testNum��Ϊ���Լ���
#define trainNum 100000
#define DATAFILE "housing.txt"

typedef struct {
	double data[Dimension];
	double price;
}Node;

typedef struct {
	double r; // Ƥ��ѷ���ϵ��
	int index; // ά���±�
}rNode;

extern int NUM; // ���ݼ�����
extern Node* ptr; //���ݼ���(ptr+i)->data[j]
extern double* temp, * w, * tempans; // ��ʱ���飬ϵ������ʱԤ����
extern double* max, * min; //�洢����ά�ȵ����ֵ����Сֵ