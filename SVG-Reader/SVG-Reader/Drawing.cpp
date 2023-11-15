#include "Drawing.h"

Drawing::Drawing(string file_svg_name, HDC hdc) : file_name(file_svg_name), hdc(hdc) {
    rotate = 0;
    line_list = {};
    rect_list = {};
    cir_list = {};
    ellip_list = {};
    polyg_list = {};
    polyl_list = {};
    text_list = {};
    zoom_scale = 1;
}

VOID Drawing::DrawLine(HDC hdc, int sx, int sy, int ex, int ey, float alpha, int red, int green, int blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(static_cast<int>(alpha * 255), red, green, blue), static_cast<REAL>(strokeWidth));
    graphics.DrawLine(&pen, sx, sy, ex, ey);
}

VOID Drawing::DrawRectangle(HDC hdc, int x, int y, int width, int height, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillRectangle(&fillBrush, x, y, width, height);
    graphics.DrawRectangle(&pen, x, y, width, height);
}

VOID Drawing::DrawCircle(HDC hdc, int  x, int y, int r, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));

    graphics.FillEllipse(&fillBrush, x - r, y - r, 2 * r, 2 * r);
    graphics.DrawEllipse(&pen, x - r, y - r, 2 * r, 2 * r);
}

VOID Drawing::DrawEllipse(HDC hdc, int cx, int cy, int rx, int ry, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));


    graphics.FillEllipse(&fillBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}

VOID Drawing::DrawPolygon(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {

    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
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

VOID Drawing::DrawPolyline(HDC hdc, vector<int> xP, vector<int> yP, float f_alpha, int f_red, int f_green, int f_blue, float s_alpha, int s_red, int s_green, int s_blue, int strokeWidth) {
    Graphics graphics(hdc);
    graphics.ScaleTransform(zoom_scale, zoom_scale);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    Pen pen(Color(static_cast<int>(s_alpha * 255), s_red, s_green, s_blue), static_cast<REAL>(strokeWidth));

    Point* points = new Point[xP.size()];
    for (int i = 0; i < xP.size(); i++) {
        points[i].X = xP[i];
        points[i].Y = yP[i];
    }

    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));
    graphics.FillPolygon(&fillBrush, points, static_cast<int>(xP.size()));
    graphics.DrawLines(&pen, points, static_cast<int>(xP.size()));
    delete[] points;
}

VOID Drawing::DrawText(HDC hdc, int x, int y, string text, float f_alpha, int f_red, int f_green, int f_blue, int strokeWidth, string font_family, bool italic) {
    Graphics graphics(hdc);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wFontFamily = converter.from_bytes(font_family);

    FontFamily  fontFamily(wFontFamily.c_str());
    INT fontStyle = FontStyleRegular;
    if (italic) {
        fontStyle |= FontStyleItalic;
    }

    Font font(&fontFamily, strokeWidth, static_cast<FontStyle>(fontStyle), UnitPixel);

    // Tính kích thước văn bản
    RectF layoutRect;
    //graphics.MeasureString(text.c_str(), -1, &font, PointF(0, 0), &layoutRect);

    // Tính toán ma trận biến đổi
    Matrix transformMatrix;
    transformMatrix.Scale(zoom_scale, zoom_scale);
    transformMatrix.RotateAt(rotate, PointF(x + layoutRect.Width / 2, y + layoutRect.Height / 2));

    // Áp dụng ma trận biến đổi
    graphics.SetTransform(&transformMatrix);

    PointF pointF(static_cast<REAL>(x), static_cast<REAL>(y - strokeWidth));
    SolidBrush fillBrush(Color(static_cast<int>(f_alpha * 255), f_red, f_green, f_blue));
    const wstring wstr = wstring(text.begin(), text.end());
    graphics.DrawString(wstr.c_str(), -1, &font, pointF, &fillBrush);

    // Đặt lại ma trận biến đổi về trạng thái ban đầu
    graphics.ResetTransform();
}


VOID Drawing::mainDrawing() {
    read(file_name, line_list, rect_list, ellip_list, cir_list, polyg_list, polyl_list, text_list);
    int total_figures = line_list.size() + rect_list.size() + ellip_list.size() + cir_list.size() + polyg_list.size() + polyl_list.size() + text_list.size();
    if (rotate != 0) {
        // transform vector
        Rotate t(line_list, rect_list, ellip_list, cir_list, polyg_list, polyl_list, text_list);
        int time = abs(rotate / 90);
        for (int i = 0; i < time; i++) {
            if (rotate < 0) {
                if (i == 0) {
                    for (auto& obj : rect_list) {
                        obj.start.x += obj.width;
                    }
                    
                }
                else if (i == 1) {
                    for (auto& obj : rect_list) {
                        obj.start.x += obj.width;
                    }
                }
                else if (i == 2) {
                    for (auto& obj : rect_list) {
                        obj.start.x += obj.width;
                    }
                }
                t.mainRotateL(line_list, rect_list, ellip_list, cir_list, polyg_list, polyl_list, text_list);
            }
            else {
                if (i == 0) {
                    for (auto& obj : rect_list) {
                        obj.start.y += obj.height;
                    }
                }
                else if (i == 1) {
                    for (auto& obj : rect_list) {
                        obj.start.y += obj.height;
                    }
                }
                else if (i == 2) {
                    for (auto& obj : rect_list) {
                        obj.start.y += obj.height;
                    }
                }
                t.mainRotateR(line_list, rect_list, ellip_list, cir_list, polyg_list, polyl_list, text_list);
            }
        }
    }
    int l = 0, r = 0, e = 0, c = 0, pg = 0, pl = 0, t = 0;
    for (int i = 1; i <= total_figures; i++) {
        if (l < line_list.size() && line_list[l].ordinal == i) {
            DrawLine(hdc, line_list[l].start.x, line_list[l].start.y, line_list[l].end.x, line_list[l].end.y, line_list[l].stroke_opacity, line_list[l].strokeColor.red, line_list[l].strokeColor.green, line_list[l].strokeColor.blue, line_list[l].strokeWidth);
            l++;
        }
        else if (r < rect_list.size() && rect_list[r].ordinal == i) {
            DrawRectangle(hdc, rect_list[r].start.x, rect_list[r].start.y, rect_list[r].width, rect_list[r].height, rect_list[r].fill_opacity, rect_list[r].fillColor.red, rect_list[r].fillColor.green, rect_list[r].fillColor.blue, rect_list[r].stroke_opacity, rect_list[r].strokeColor.red, rect_list[r].strokeColor.green, rect_list[r].strokeColor.blue, rect_list[r].strokeWidth);
            r++;
        }
        else if (e < ellip_list.size() && ellip_list[e].ordinal == i) {
            DrawEllipse(hdc, ellip_list[e].center.x, ellip_list[e].center.y, ellip_list[e].rx, ellip_list[e].ry, ellip_list[l].fill_opacity, ellip_list[l].fillColor.red, ellip_list[l].fillColor.green, ellip_list[l].fillColor.blue, ellip_list[l].stroke_opacity, ellip_list[l].strokeColor.red, ellip_list[l].strokeColor.green, ellip_list[l].strokeColor.blue, ellip_list[l].strokeWidth);
            e++;
        }
        else if (c < cir_list.size() && cir_list[c].ordinal == i) {
            DrawCircle(hdc, cir_list[c].center.x, cir_list[c].center.y, cir_list[c].r, cir_list[c].fill_opacity, cir_list[c].fillColor.red, cir_list[c].fillColor.green, cir_list[c].fillColor.blue, cir_list[c].stroke_opacity, cir_list[c].strokeColor.red, cir_list[c].strokeColor.green, cir_list[c].strokeColor.blue, cir_list[c].strokeWidth);
            c++;
        }
        else if (pg < polyg_list.size() && polyg_list[pg].ordinal == i) {
            DrawPolygon(hdc, polyg_list[pg].xP, polyg_list[pg].yP, polyg_list[pg].fill_opacity, polyg_list[pg].fillColor.red, polyg_list[pg].fillColor.green, polyg_list[pg].fillColor.blue, polyg_list[pg].stroke_opacity, polyg_list[pg].strokeColor.red, polyg_list[pg].strokeColor.green, polyg_list[pg].strokeColor.blue, polyg_list[pg].strokeWidth);
            pg++;
        }
        else if (pl < polyl_list.size() && polyl_list[pl].ordinal == i) {
            DrawPolyline(hdc, polyl_list[pl].xP, polyl_list[pl].yP, polyl_list[pl].fill_opacity, polyl_list[pl].fillColor.red, polyl_list[pl].fillColor.green, polyl_list[pl].fillColor.blue, polyl_list[pl].stroke_opacity, polyl_list[pl].strokeColor.red, polyl_list[pl].strokeColor.green, polyl_list[pl].strokeColor.blue, polyl_list[pl].strokeWidth);
            pl++;
        }
        else if (t < text_list.size() && text_list[t].ordinal == i) {
            DrawText(hdc, text_list[t].x, text_list[t].y, text_list[t].text_, text_list[t].fill_opacity, text_list[t].fillColor.red, text_list[t].fillColor.green, text_list[t].fillColor.blue, text_list[t].font_size, text_list[t].font_family, text_list[t].italic);
            t++;
        }
    }
}
