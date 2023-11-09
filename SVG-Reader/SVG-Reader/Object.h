#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "rapidxml.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace rapidxml;
#include "framework.h"
using namespace std;

class color {
public:
	int red, green, blue;
	float alpha;
	color() {
		red = green = blue = 0;
		alpha = 0;
	}
};

class point {
public:
	int x, y;
};

class line {
public:
	point start, end;
	color strokeColor;
	int strokeWidth;
};

class rectangle {
public:
	point start;
	int width, height;
	color fillColor; // màu bên trong hình chữ nhật
	color strokeColor; // màu đường viền 
	int strokeWidth;
};

class ellipse {
public:
	point center;
	int rx, ry; // bán kính chiều ngang, dọc
	color strokeColor, fillColor;
	int strokeWidth;
};

class circle {
public:
	point center;
	int r; // bán kính 
	color fillColor, strokeColor;
	int strokeWidth;
};

void read(string svgFileName, vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list);


#endif