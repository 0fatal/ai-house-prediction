#include "house-global.h"

static void _normalize_single(Node* ptr) {
	// x0为1,不需要归一
	for (int i = 1; i <= Dimension; i++) {
		double  c = max[i] - min[i];
		if (i != Dimension) {
			ptr->data[i] = (ptr->data[i] - min[i]) / c;
		}
		else {
			ptr->price = (ptr->price - min[i]) / c;
		}
	}
}

static void _normalizeBack_single(Node* ptr) {
	for (int i = 1; i <= Dimension; i++) {
		double c = max[i] - min[i];
		if (i != Dimension) {
			ptr->data[i] = ptr->data[i] * c + min[i];
		}
		else {
			ptr->price = ptr->price * c + min[i];
		}
	}
}

void normalize(Node* ptr, int start, int end) {
	for (int i = start; i < end; i++) {
		_normalize_single(ptr + i);
	}
}

void normalizeBack(Node* ptr, int start, int end) {
	for (int i = start; i < end; i++) {
		_normalizeBack_single(ptr + i);
	}
}


