//BaseComponent.h contains all libraries and define base class for all components: Color and Point
#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include <iostream>
#include "rapidxml.hpp" // RapidXML library for read XML file
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h> //for GDI+ library
#include <locale>  // for std::wstring_convert and codecvt_utf8
#include <codecvt> // for codecvt_utf8
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

//read functions
//support functions
string trim(string str);
bool check(char a);
void remove_space(string& s);
float clarifyFloat(string s);

//read color funtion
color read_RGB(string value);

//read point function
vector<point> read_points(string value);
#endif // !BASECOMPONENT_H