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
	color() {
		red = green = blue = 0;
	}
};

class point {
public:
	int x, y;
};

class line {
public:
	int ordinal;
	point start, end;
	color strokeColor;
	float stroke_opacity;
	int strokeWidth;
	line() {
		stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class rectangle {
public:
	int ordinal;
	point start;
	int width, height;
	color fillColor; // màu bên trong hình chữ nhật
	color strokeColor; // màu đường viền 
	float fill_opacity, stroke_opacity;
	int strokeWidth;
	rectangle() {
		fill_opacity = stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class ellipse {
public:
	int ordinal;
	point center;
	int rx, ry; // bán kính chiều ngang, dọc
	color strokeColor, fillColor;
	float fill_opacity, stroke_opacity;
	int strokeWidth;
	ellipse() {
		fill_opacity = stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class circle {
public:
	int ordinal;
	point center;
	int r; // bán kính 
	color fillColor, strokeColor;
	float fill_opacity, stroke_opacity;
	int strokeWidth;
	circle() {
		fill_opacity = stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class polygon {
public:
	int ordinal;
	vector<int> xP, yP;
	color fillColor, strokeColor;
	float fill_opacity, stroke_opacity;
	int strokeWidth;
	polygon() {
		fill_opacity = stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class polyline {
public:
	int ordinal;
	vector<int> xP, yP;
	color fillColor, strokeColor;
	float fill_opacity, stroke_opacity;
	int strokeWidth;
	polyline() {
		fill_opacity = 1;
		stroke_opacity = 1;
		strokeWidth = 0;
	}
};

class text {
public:
	int ordinal;
	int x, y;
	int font_size;
	string text_;
	string font_family;
	color fillColor;
	float fill_opacity;
	bool italic;
	text() {
		text_ = "";
		font_family = "Times New Roman";
		italic = false;
		fill_opacity = 1;
	}
};

void read(string svgFileName, vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list);


#endif