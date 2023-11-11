#include "Drawing.h"

Drawing::Drawing(string file_svg_name, HDC hdc) : file_name(file_svg_name), hdc(hdc) {
    rotate = 0;
    line_list = {};
    rect_list = {};
    cir_list = {};
    ellip_list = {};
    //polyg_list = {};
    //polyl_list = {};
    //text_list = {};
}

VOID Drawing::DrawLine(HDC hdc, int sx, int sy, int ex, int ey, float alpha, int red, int green, int blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(alpha * 255), red, green, blue), static_cast<REAL>(strokeWidth));
    graphics.DrawLine(&pen, sx, sy, ex, ey);
    graphics.ResetTransform();
}

VOID Drawing::DrawRectangle(HDC hdc, int x, int y, int width, int height, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillRectangle(&fillBrush, x, y, width, height);
    graphics.DrawRectangle(&pen, x, y, width, height);
    graphics.ResetTransform();
}

VOID Drawing::DrawCircle(HDC hdc, int  x, int y, int r, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillEllipse(&fillBrush, x - r, y - r, 2 * r, 2 * r);
    graphics.DrawEllipse(&pen, x - r, y - r, 2 * r, 2 * r);
    graphics.ResetTransform();
}

VOID Drawing::DrawEllipse(HDC hdc, int cx, int cy, int rx, int ry, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));


    graphics.FillEllipse(&fillBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.ResetTransform();
}

VOID Drawing::DrawPolygon(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {

    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    Point* p = new Point[xP.size()];
    for (int i = 0; i < xP.size(); i++) {
        p[i] = Point(xP[i], yP[i]);
    }
    graphics.FillPolygon(&fillBrush, p, static_cast<int>(xP.size()));
    graphics.DrawPolygon(&pen, p, static_cast<int>(xP.size()));
    graphics.ResetTransform();
    delete[] p;
}

VOID Drawing::DrawPolyline(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));

    Point* points = new Point[xP.size()];
    for (int i = 0; i < xP.size(); i++) {
        points[i].X = xP[i];
        points[i].Y = yP[i];
    }

    graphics.DrawLines(&pen, points, static_cast<int>(xP.size()));

    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));
    graphics.FillPolygon(&fillBrush, points, static_cast<int>(xP.size()));
    graphics.ResetTransform();
    delete[] points;
}

VOID Drawing::DrawText(HDC hdc, int x, int y, string text, float f_alpha, int f_red, int f_green, int f_blue, int strokeWidth, string font_family, bool italic) {
    Graphics graphics(hdc);
    graphics.RotateTransform(rotate);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wFontFamily = converter.from_bytes(font_family);

    FontFamily  fontFamily(wFontFamily.c_str());
    INT fontStyle = FontStyleRegular;
    if (italic) {
        fontStyle |= FontStyleItalic;
    }

    Font font(&fontFamily, strokeWidth, static_cast<FontStyle>(fontStyle), UnitPixel);

    PointF pointF(static_cast<REAL>(x), static_cast<REAL>(y));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    const wstring wstr = wstring(text.begin(), text.end());
    graphics.DrawString(wstr.c_str(), -1, &font, pointF, &fillBrush);
    graphics.ResetTransform();
}

VOID Drawing::mainDrawing() {
    read(file_name, line_list, rect_list, ellip_list, cir_list);
    if (rotate != 0) {
        // transform vector
    }
    Graphics graphics(hdc);
   for (const auto& rect : rect_list) {
       
        DrawRectangle(hdc, rect.start.x, rect.start.y, rect.width, rect.height, rect.fillColor.alpha, rect.fillColor.red, rect.fillColor.green, rect.fillColor.blue, rect.strokeColor.alpha, rect.strokeColor.red, rect.strokeColor.green, rect.strokeColor.blue, rect.strokeWidth);
    }
    for (const auto& line : line_list) {
        DrawLine(hdc, line.start.x, line.start.y, line.end.x, line.end.y, line.strokeColor.alpha, line.strokeColor.red, line.strokeColor.green, line.strokeColor.blue, line.strokeWidth);
    }

    for (const auto& rect : rect_list) {
        DrawRectangle(hdc, rect.start.x, rect.start.y, rect.width, rect.height, rect.fillColor.alpha, rect.fillColor.red, rect.fillColor.green, rect.fillColor.blue, rect.strokeColor.alpha, rect.strokeColor.red, rect.strokeColor.green, rect.strokeColor.blue, rect.strokeWidth);
    }

    for (const auto& circle : cir_list) {
        DrawCircle(hdc, circle.center.x, circle.center.y, circle.r, circle.fillColor.alpha, circle.fillColor.red, circle.fillColor.green, circle.fillColor.blue, circle.strokeColor.alpha, circle.strokeColor.red, circle.strokeColor.green, circle.strokeColor.blue, circle.strokeWidth);
    }

    for (const auto& ellipse : ellip_list) {
        DrawEllipse(hdc, ellipse.center.x, ellipse.center.y, ellipse.rx, ellipse.ry, ellipse.fillColor.alpha, ellipse.fillColor.red, ellipse.fillColor.green, ellipse.fillColor.blue, ellipse.strokeColor.alpha, ellipse.strokeColor.red, ellipse.strokeColor.green, ellipse.strokeColor.blue, ellipse.strokeWidth);
    }

    //for (const auto& polygon : polyg_list) {
    //    DrawPolygon(hdc, polygon.xP, polygon.yP, polygon.fillColor.alpha, polygon.fillColor.red, polygon.fillColor.green, polygon.fillColor.blue, polygon.strokeColor.alpha, polygon.strokeColor.red, polygon.strokeColor.green, polygon.s_blue, polygon.strokeWidth);
    //}

    //for (const auto& polyline : polyl_list) {
    //    DrawPolyline(hdc, polyline.xP, polyline.yP, polyline.fillColor.alpha, polyline.fillColor.red, polyline.fillColor.green, polyline.fillColor.blue, polyline.s_alpha, polyline.s_red, polyline.s_green, polyline.s_blue, polyline.strokeWidth);
    //}

    //for (const auto& text : text_list) {
    //    DrawText(hdc, text.x, text.y, text.text, text.f_alpha, text.f_red, text.f_green, text.f_blue, text.strokeWidth, text.font_family, text.italic);
    //}
}
