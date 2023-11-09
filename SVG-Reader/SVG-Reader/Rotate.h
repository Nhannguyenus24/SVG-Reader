#ifndef ROTATE_H
#define ROTATE_H

#include <cmath>
#include <vector>
using namespace std;
struct Rotate { // thay doi toa do vector cac hinh ve
	int max_height, max_length;
	
	void rotateRight(vector<int>& x, vector<int>& y, int max_length, int max_height);
	void rotateLeft(vector<int>& x, vector<int>& y, int max_length, int max_height);
	void rotateR(int& x, int& y, int max_height);
	void rotateL(int& x, int& y, int max_length);
	void rotateLine(vector<line> line_list);
	void rotateLine(vector<rectangle> rect_list);
	void rotateLine(vector<circle> cir_list);
	void rotateLine(vector<ellipse> ellip_list);
	//void rotateLine(vector<polygon> polyg_list);
	//void rotateLine(vector<polyline> polyl_list);
	//void rotateLine(vector<text> text_list);
	void update_max();
};
#endif