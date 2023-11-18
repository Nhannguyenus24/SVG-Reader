#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "rapidxml.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <locale>  // Để sử dụng wstring_convert và codecvt_utf8
#include <codecvt> // Để sử dụng codecvt_utf8
#include "Object.h"
#include <algorithm>
#include "framework.h"
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
using namespace rapidxml;


class color {
public:
	int red, green, blue;
	float opacity;
	color() {
		red = green = blue = 0;
		opacity = 1.0;
	}
};

class point {
public:
	int x, y;
	point() {
		x = 0, y = 0;
	}
};

class shape {
public:
	point start;
	color stroke_color, fill_color;
	int stroke_width;
	shape() {
		stroke_width = 0;
	}
	virtual void draw(Graphics graphics) = 0;
};


class line : public shape {
public:
	point end;
	void draw(Graphics graphics) override;
};

class rectangle : public shape {
public:
	int width, height;
	void draw(Graphics graphics) override;
};

class ellipse : public shape {
public:
	int rx, ry; // bán kính chiều ngang, dọc
	void draw(Graphics graphics) override;
};

class circle : public shape {
public:
	point center;
	int r; // bán kính 
	void draw(Graphics graphics) override;
};

class polygon : public shape {
public:
	vector<point> p;
	void draw(Graphics graphics) override;
};

class polyline : public shape{
public:
	vector<point> p;
	void draw(Graphics graphics) override;
};

class text : public shape {
public:
	int font_size;
	string text_;
	string font_family;
	bool italic;
	text() {
		text_ = "";
		font_family = "Times New Roman";
		italic = false;
	}
	void draw(Graphics graphics) override;
};

vector<shape*> read_file(string file_name);

#endif