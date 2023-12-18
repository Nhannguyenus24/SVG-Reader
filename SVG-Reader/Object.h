﻿#ifndef OBJECT_H
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
#include <regex>
#include <unordered_map>
#include "framework.h"
using namespace std;
using namespace Gdiplus;
using namespace rapidxml;
#pragma comment (lib,"Gdiplus.lib")

class color {
public:
	int red, green, blue;
	color() {
		red = green = blue = 0;
	}
};

class point {
public:
	float x, y;
	point() {
		x = 0, y = 0;
	}
};

class multi_transform {
public:
	vector<string> types;
	vector<float> values;
};


class shape {
public:
	point start;
	color stroke_color, fill_color;
	float stroke_width;
	float stroke_opacity, fill_opacity;
	multi_transform trans;
	shape() {
		stroke_width = 0;
		stroke_opacity = fill_opacity = 1;
	}
	virtual void draw(Graphics& graphics) = 0;
	virtual void get_max(float& max_width, float& max_height) = 0;
};


class line : public shape {
public:
	point end;
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class rectangle : public shape {
public:
	float width, height;
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class ellipse : public shape {
public:
	float rx, ry; // bán kính chiều ngang, dọc
	ellipse() {
		rx = ry = 0;
	}
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class circle : public shape {
public:
	point center;
	float r; // bán kính 
	circle() {
		r = 0;
	}
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class polygon : public shape {
public:
	vector<point> p;
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class polyline : public shape{
public:
	vector<point> p;
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class text : public shape {
public:
	float font_size;
	string text_;
	string font_family;
	string text_anchor;
	bool italic;
	float dx, dy;
	text() {
		text_ = "";
		text_anchor = "start";
		font_family = "Times New Roman";
		italic = false;
		dx = dy = 0;

	}
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override;
};

class path : public shape {
public:
	string data;
	string linecap, linejoin;
	path() {
		linecap = "butt";
		linejoin = "miter";
	}
	void read_single_point(string data, int& index, point& p);
	float read_single_point(string data, int& index);
	void draw(Graphics& graphics) override;
	void get_max(float& max_width, float& max_height) override {
		return;
	}
};

class group {
public:
	unordered_map<string, string> attributes;
	void traversal_group(rapidxml::xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes);
};

class stop {
public:
	color stop_color;
	float offset;
	float stop_opacity;
	stop() {
		offset = 0;
		stop_opacity = 1;
	}
};

class gradient {
public:
	vector<stop*> stop_list;
	//virtual void draw(Graphics& graphics);
};

class linearGradient : public gradient {
public:
	string id;
	point start, end;
	multi_transform trans;
	string units;

	//void draw(Graphics& graphics);
};

class radialGradient : public gradient {
public:
	string id;
	point center;
	float r, fx, fy;
	multi_transform trans;
	string units, xlink_href;
	radialGradient() {
		r = fx = fy = 0;
	}

	//void draw(Graphics& graphics);
};





class defs {
public:
	vector<linearGradient*> lg_list;
	vector<radialGradient*> rg_list;
};

vector<shape*> read_file(string file_name, float& max_width, float& max_height);
void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale);

#endif