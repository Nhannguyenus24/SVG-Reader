#include "Rotate.h"

int findMaxValue(const vector<int>& a) {
	if (a.empty()) {
		std::cerr << "Vector is empty. Unable to find the maximum value.\n";
		return -1;
	}

	int maxVal = a[0];

	for (size_t i = 1; i < a.size(); ++i) {
		if (a[i] > maxVal) {
			maxVal = a[i];
		}
	}

	return maxVal;
}

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
Rotate::Rotate(vector<line> line_list, vector<rectangle> rect_list, vector<ellipse> elli_list, vector<circle> cir_list, vector<polygon> polyg_list, vector<polyline> polyl_list, vector<text> text_list) {
	int max_h = 0, max_l = 0;
	for (auto& obj : line_list) {
		if (obj.start.x > max_l)
			max_l = obj.start.x;
		if (obj.start.y > max_h)
			max_h = obj.start.y;
		if (obj.end.x > max_l)
			max_l = obj.end.x;
		if (obj.end.y > max_h)
			max_h = obj.end.y;
	}
	for (auto& obj : rect_list) {
		if (obj.start.x + obj.width > max_l)
			max_l = obj.start.x + obj.width;
		if (obj.start.y + obj.height > max_h)
			max_h = obj.start.y + obj.height;
	}
	for (auto& obj : elli_list) {
		if (obj.center.x + obj.rx > max_l)
			max_l = obj.center.x + obj.rx;
		if (obj.center.y + obj.ry> max_h)
			max_h = obj.center.y + obj.ry;
	}
	for (auto& obj : cir_list) {
		if (obj.center.x + obj.r > max_l)
			max_l = obj.center.x + obj.r;
		if (obj.center.y + obj.r > max_h)
			max_h = obj.center.y + obj.r;
	}
	for (auto& obj : polyg_list) {
		if (findMaxValue(obj.xP) > max_l)
			max_l = findMaxValue(obj.xP);
		if (findMaxValue(obj.yP) > max_h)
			max_h = findMaxValue(obj.yP);
	}
	for (auto& obj : polyl_list) {
		if (findMaxValue(obj.xP) > max_l)
			max_l = findMaxValue(obj.xP);
		if (findMaxValue(obj.yP) > max_h)
			max_h = findMaxValue(obj.yP);
	}
	for (auto& obj : text_list) {
		if (obj.x + obj.text_.length() > max_l)
			max_l = obj.x + obj.text_.length();
		if (obj.y > max_h)
			max_h = obj.y;
	}
	max_height = max_h, max_length = max_l;
}

void Rotate::mainRotateR(vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list) {
	for (auto& obj : line_list) {
		rotateR(obj.start.x, obj.start.y, max_height);
		rotateR(obj.end.x, obj.end.y, max_height);
	}
	for (auto& obj : rect_list) {
		rotateR(obj.start.x, obj.start.y, max_height);
		swap(obj.width, obj.height);
	}
	for (auto& obj : elli_list) {
		swap(obj.rx, obj.ry);
		rotateR(obj.center.x, obj.center.y, max_height);
	}
	for (auto& obj : cir_list) {
		rotateR(obj.center.x, obj.center.y, max_height);
	}
	for (auto& obj : polyg_list) {
		rotateRight(obj.xP, obj.yP, max_length, max_height);
	}
	for (auto& obj : polyl_list) {
		rotateRight(obj.xP, obj.yP, max_length, max_height);
	}
	for (auto& obj : text_list) {
		rotateR(obj.x, obj.y, max_height);
	}
	swap(max_height, max_length);
}
void Rotate::mainRotateL(vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list) {
	for (auto& obj : line_list) {
		rotateL(obj.start.x, obj.start.y, max_length);
		rotateL(obj.end.x, obj.end.y, max_length);
	}
	for (auto& obj : rect_list) {
		rotateL(obj.start.x, obj.start.y, max_length);
		swap(obj.width, obj.height);
	}
	for (auto& obj : elli_list) {
		swap(obj.rx, obj.ry);
		rotateL(obj.center.x, obj.center.y, max_length);
	}
	for (auto& obj : cir_list) {
		rotateL(obj.center.x, obj.center.y, max_length);
	}
	for (auto& obj : polyg_list) {
		rotateLeft(obj.xP, obj.yP, max_length, max_height);
	}
	for (auto& obj : polyl_list) {
		rotateLeft(obj.xP, obj.yP, max_length, max_height);
	}
	for (auto& obj : text_list) {
		rotateL(obj.x, obj.y, max_length);
	}
	swap(max_height, max_length);
}