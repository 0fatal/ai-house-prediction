#pragma once
#define Dimension 14 // 训练维度数
#define learningRate 0.002 // 学习率
#define EPS 0.001 // 浮点相对精度
#define testNum 50 // 测试集中的数据个数，前NUM-testNum个为训练集，后testNum个为测试集。
#define trainNum 100000
#define DATAFILE "housing.txt"

typedef struct {
	double data[Dimension];
	double price;
}Node;

typedef struct {
	double r; // 皮尔逊相关系数
	int index; // 维度下标
}rNode;

extern int NUM; // 数据集总数
extern Node* ptr; //数据集，(ptr+i)->data[j]
extern double* temp, * w, * tempans; // 临时数组，系数，临时预测结果
extern double* max, * min; //存储各个维度的最大值和最小值