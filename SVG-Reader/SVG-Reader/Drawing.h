#ifndef DRAWING_H
#define DRAWING_H
#include "framework.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
#include <vector>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID DrawLine(HDC hdc, int sx, int sy, int ex, int ey, float alpha, int red, int green, int blue, int strokeWidth);

VOID DrawRectangle(HDC hdc, int x, int y, int width, int height, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

VOID DrawCircle(HDC hdc, int  x, int y, int r, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

VOID DrawEllipse(HDC hdc, int cx, int cy, int rx, int ry, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

VOID DrawPolygon(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

VOID DrawPolyline(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth);

VOID DrawText(HDC hdc, int x, int y, string text, float f_alpha, int f_red, int f_green, int f_blue, int strokeWidth);

#endif //DRAWING_H