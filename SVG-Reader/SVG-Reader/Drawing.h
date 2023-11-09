#ifndef DRAWING_H
#define DRAWING_H
#include "framework.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include <vector>
#include <locale>  // Để sử dụng wstring_convert và codecvt_utf8
#include <codecvt> // Để sử dụng codecvt_utf8
#include "Object.h"
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

struct Drawing {
	vector<line> line_list;
	vector<rectangle> rect_list;
	vector<circle> cir_list;
	vector<ellipse> ellip_list;
	//vector<polygon> polyg_list;
	//vector<polyline> polyl_list;
	//vector<text> text_list;
	string file_name;
	float rotate; // 0 - 90 - 180 - 270 - 360
	HDC hdc;

	Drawing(string file_svg_name, HDC hdc);

	VOID DrawLine(HDC hdc, int sx, int sy, int ex, int ey, float alpha, int red, int green, int blue, int strokeWidth);

	VOID DrawRectangle(HDC hdc, int x, int y, int width, int height, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

	VOID DrawCircle(HDC hdc, int  x, int y, int r, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

	VOID DrawEllipse(HDC hdc, int cx, int cy, int rx, int ry, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

	VOID DrawPolygon(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

	VOID DrawPolyline(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

	VOID DrawText(HDC hdc, int x, int y, string text, float f_alpha, int f_red, int f_green, int f_blue, int strokeWidth, string font_family, bool italic);

	VOID mainDrawing();
};
#endif //DRAWING_H