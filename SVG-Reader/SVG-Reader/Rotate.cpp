#include "Rotate.h"

void Rotate::rotateRight(vector<int>& x, vector<int>& y, int max_length, int max_height) {
	for (int i = 0; i < x.size(); i++) {
		rotateR(x[i], y[i], max_height);
	}
	
}

void Rotate::rotateLeft(vector<int>& x, vector<int>& y, int max_length, int max_height) {
	for (int i = 0; i < x.size(); i++) {
		rotateL(x[i], y[i], max_length);
	}
	
}

void Rotate::rotateR(int& x, int& y, int max_height) { // ->
	int temp = x;
	x = max_height - y;
	y = temp;
}

void Rotate::rotateL(int& x, int& y, int max_length) { // <-
	int temp = y;
	y = max_length - x;
	x = temp;
}

void Rotate::update_max() {
	swap(max_length, max_height);
}