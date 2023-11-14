#ifndef ROTATE_H
#define ROTATE_H

#include <cmath>
#include <vector>
#include "Object.h"
using namespace std;
struct Rotate { // thay doi toa do vector cac hinh ve
	int max_height, max_length;
	Rotate(vector<line> line_list, vector<rectangle> rect_list, vector<ellipse> elli_list, vector<circle> cir_list, vector<polygon> polyg_list, vector<polyline> polyl_list, vector<text> text_list);
	void rotateRight(vector<int>& x, vector<int>& y, int max_length, int max_height);
	void rotateLeft(vector<int>& x, vector<int>& y, int max_length, int max_height);
	void rotateR(int& x, int& y, int max_height);
	void rotateL(int& x, int& y, int max_length);
	void mainRotateL(vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list);
	void mainRotateR(vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list);
};
#endif