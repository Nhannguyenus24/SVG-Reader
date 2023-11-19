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
	color() {
		red = green = blue = 0;
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
	point translate;
	float rotate;
	float scale_x, scale_y;
	color stroke_color, fill_color;
	int stroke_width;
	float stroke_opacity, fill_opacity;
	shape() {
		stroke_width = 0;
		stroke_opacity = fill_opacity = 1;
		rotate = 0;
		scale_x = scale_y = 0;
	}
	virtual void draw(Graphics& graphics) = 0;
	virtual void get_max(int& max_width, int& max_height) = 0;
};


class line : public shape {
public:
	point end;
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class rectangle : public shape {
public:
	int width, height;
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class ellipse : public shape {
public:
	int rx, ry; // bán kính chiều ngang, dọc
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class circle : public shape {
public:
	point center;
	int r; // bán kính 
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class polygon : public shape {
public:
	vector<point> p;
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class polyline : public shape{
public:
	vector<point> p;
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
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
	void draw(Graphics& graphics) override;
	void get_max(int& max_width, int& max_height) override;
};

class group {
public:
	color stroke_color, fill_color;
	int stroke_width;
	float stroke_opacity, fill_opacity;
	point translate;
	int rotate;
	float scale_x, scale_y;
	group() {
		stroke_width = 0;
		stroke_opacity = fill_opacity = 1;
		rotate = 0;
		scale_x = scale_y = 0;
	}
};
vector<shape*> read_file(string file_name, int& max_width, int& max_height);
void transform_image(Graphics& graphics, float angle, int width, int height, int scroll_x, int scroll_y, float scale);

#endif