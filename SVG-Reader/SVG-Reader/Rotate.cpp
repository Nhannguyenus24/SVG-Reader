#include "Rotate.h"

void rotateRight(vector<int>& x, vector<int>& y, int& max_length, int& max_height) {
	for (int i = 0; i < x.size(); i++) {
		rotateR(x[i], y[i], max_height);
	}
	swap(max_length, max_height);
}

void rotateLeft(vector<int>& x, vector<int>& y, int& max_length, int& max_height) {
	for (int i = 0; i < x.size(); i++) {
		rotateL(x[i], y[i], max_length);
	}
	swap(max_length, max_height);
}

void rotateR(int& x, int& y, int max_height) { // ->
	int temp = x;
	x = max_height - y;
	y = temp;
}

void rotateL(int& x, int& y, int max_length) { // <-
	int temp = y;
	y = max_length - x;
	x = temp;
}