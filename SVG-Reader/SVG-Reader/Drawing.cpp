#include "Drawing.h"

VOID DrawLine(HDC hdc, int sx, int sy, int ex, int ey, float alpha, int red, int green, int blue, int strokeWidth) {
    Graphics graphics(hdc);
    Pen pen(Color(static_cast<int>(alpha * 255), red, green, blue), static_cast<REAL>(strokeWidth));
    graphics.DrawLine(&pen, sx, sy, ex, ey);
}

VOID DrawRectangle(HDC hdc, int x, int y, int width, int height, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);

    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillRectangle(&fillBrush, x, y, width, height);
    graphics.DrawRectangle(&pen, x, y, width, height);
}

VOID DrawCircle(HDC hdc, int  x, int y, int r, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);

    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillEllipse(&fillBrush, x - r, y - r, 2 * r, 2 * r);
    graphics.DrawEllipse(&pen, x - r, y - r, 2 * r, 2 * r);
}

VOID DrawEllipse(HDC hdc, int cx, int cy, int rx, int ry, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);

    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));


    graphics.FillEllipse(&fillBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}

VOID DrawPolygon(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {

    Graphics graphics(hdc);

    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    Point* p = new Point[xP.size()];
    for (int i = 0; i < xP.size(); i++) {
        p[i] = Point(xP[i], yP[i]);
    }
    graphics.FillPolygon(&fillBrush, p, static_cast<int>(xP.size()));
    graphics.DrawPolygon(&pen, p, static_cast<int>(xP.size()));

    delete[] p;
}

VOID DrawPolyline(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);

    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));

    Point* points = new Point[xP.size()];
    for (int i = 0; i < xP.size(); i++) {
        points[i].X = xP[i];
        points[i].Y = yP[i];
    }

    graphics.DrawLines(&pen, points, static_cast<int>(xP.size()));

    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));
    graphics.FillPolygon(&fillBrush, points, static_cast<int>(xP.size()));

    delete[] points;
}

VOID DrawText(HDC hdc, int x, int y, string text, float f_alpha, int f_red, int f_green, int f_blue, int strokeWidth) {
    Graphics graphics(hdc);
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, strokeWidth, FontStyleRegular, UnitPixel);

    PointF      pointF(static_cast<REAL>(x), static_cast<REAL>(y));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));
    const wstring wstr = wstring(text.begin(), text.end());
    graphics.DrawString(wstr.c_str(), -1, &font, pointF, &fillBrush);
}
