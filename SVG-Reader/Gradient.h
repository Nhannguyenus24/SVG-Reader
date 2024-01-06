#ifndef GRADIENT_H
#define GRADIENT_H
#include "Viewbox.h"
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

class Gradient {
public:
	vector<stop> stop_list;
	float* get_point_list();
	Color* get_color_list();
};

class linearGradient : public Gradient {
public:
	string id;
	point start, end;
	multi_transform trans;
	string units;
	bool percentage;
};

class radialGradient : public Gradient {
public:
	string id;
	point center;
	float r, fx, fy;
	multi_transform trans;
	string units, xlink_href;
	radialGradient() {
		r = fx = fy = 0;
		xlink_href = "";
	}
};

class defs {
public:
	vector<linearGradient> lg_list;
	vector<radialGradient> rg_list;
};

//read function
void readStop(string name, string value, stop& stop);
void readLinearGradient(string name, string value, linearGradient& lg);
void readRadialGradient(string name, string value, radialGradient& rg);
#endif // !GRADIENT_H