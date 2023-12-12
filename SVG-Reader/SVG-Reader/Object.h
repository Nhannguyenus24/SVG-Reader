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
#include <regex>
#include <unordered_map>
#include "framework.h"
using namespace std;
using namespace Gdiplus;
using namespace rapidxml;
#pragma comment (lib,"Gdiplus.lib")
//convert to visitor design pattern
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

//forwards declaration
class shape;
class line;
class rectangle;
class ellipse;
class circle;
class polygon;
class polyline;
class text;
class path;

//visitor design pattern
class ShapeVisitor {
public:
	virtual void visit(line* l) = 0;
	virtual void visit(rectangle* r) = 0;
	virtual void visit(ellipse* e) = 0;
	virtual void visit(circle* c) = 0;
	virtual void visit(polygon* p) = 0;
	virtual void visit(polyline* p) = 0;
	virtual void visit(text* t) = 0;
	virtual void visit(path* p) = 0;
};

//shape interface
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
	virtual void accept(ShapeVisitor* v) = 0;
};


class line : public shape {
public:
	point end;
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class rectangle : public shape {
public:
	float width, height;
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class ellipse : public shape {
public:
	float rx, ry; // bán kính chiều ngang, dọc
	ellipse() {
		rx = ry = 0;
	}
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class circle : public shape {
public:
	point center;
	float r; // bán kính 
	circle() {
		r = 0;
	}
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class polygon : public shape {
public:
	vector<point> p;
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class polyline : public shape{
public:
	vector<point> p;
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
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
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
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
	void accept(ShapeVisitor* v) override {
		v->visit(this);
	}
};

class group {
public:
	unordered_map<string, string> attributes;
	void traversal_group(rapidxml::xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes);
};

class DrawVisitor : public ShapeVisitor {
public:
	void visit(line* l, Graphics& graphics) override{//draw line
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(l->stroke_opacity * 255), l->stroke_color.red, l->stroke_color.green, l->stroke_color.blue), static_cast<REAL>(l->stroke_width));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++){
            if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
        graphics.Restore(save);
    }

	void visit(rectangle* r, Graphics& graphics) override {//draw rectangle
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(r->stroke_opacity * 255), r->stroke_color.red, r->stroke_color.green, r->stroke_color.blue), static_cast<REAL>(r->stroke_width));
        SolidBrush fillBrush(Color(static_cast<int>(r->fill_opacity * 255), r->fill_color.red, r->fill_color.green, r->fill_color.blue));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        graphics.FillRectangle(&fillBrush, start.x, start.y, width, height);
        if (stroke_width != 0)
            graphics.DrawRectangle(&pen, start.x, start.y, width, height);
    }

	void visit(ellipse* e, Graphics& graphics) override{//draw ellipse
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(e->stroke_opacity * 255), e->stroke_color.red, e->stroke_color.green, e->stroke_color.blue), static_cast<REAL>(e->stroke_width));
        SolidBrush fillBrush(Color(static_cast<int>(e->fill_opacity * 255), e->fill_color.red, e->fill_color.green, e->fill_color.blue));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        graphics.FillEllipse(&fillBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
        if (stroke_width != 0)
            graphics.DrawEllipse(&pen, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
        graphics.Restore(save);
    }

	void visit(circle* c, Graphics& graphics) override{//draw circle
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(c->stroke_opacity * 255), c->stroke_color.red, c->stroke_color.green, c->stroke_color.blue), static_cast<REAL>(c->stroke_width));
        SolidBrush fillBrush(Color(static_cast<int>(c->fill_opacity * 255), c->fill_color.red, c->fill_color.green, c->fill_color.blue));
        int index = 0;
            for (int i = 0; i < trans.types.size(); i++) {
                if (trans.types[i] == "translate")
                    graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
                if (trans.types[i] == "rotate")
                    graphics.RotateTransform(trans.values[index]);
                if (trans.types[i] == "scale")
                    graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
                index += 2;
                if (trans.types[i] == "rotate")
                    index--;
            }
        graphics.FillEllipse(&fillBrush, start.x - r, start.y - r, 2 * r, 2 * r);
        if (stroke_width != 0)
            graphics.DrawEllipse(&pen, start.x - r, start.y - r, 2 * r, 2 * r);
        graphics.Restore(save);
    }

	void visit(polygon* p, Graphics& graphics) override{//draw polygon
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(p->stroke_opacity * 255), p->stroke_color.red, p->stroke_color.green, p->stroke_color.blue), static_cast<REAL>(p->stroke_width));
        SolidBrush fillBrush(Color(static_cast<int>(p->fill_opacity * 255), p->fill_color.red, p->fill_color.green, p->fill_color.blue));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        Point* point = new Point[p.size()];
        for (int i = 0; i < p.size(); i++) {
            point[i] = Point(p[i].x, p[i].y);
        }
        graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);
        if (stroke_width != 0)
            graphics.DrawPolygon(&pen, point, static_cast<int>(p.size()));
        delete[] point;
        graphics.Restore(save);
    }

	void visit(polyline* p, Graphics& graphics) override{//draw polyline
        GraphicsState save = graphics.Save();
        Pen pen(Color(static_cast<int>(p->stroke_opacity * 255), p->stroke_color.red, p->stroke_color.green, p->stroke_color.blue), static_cast<REAL>(p->stroke_width));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        Point* point = new Point[p.size()];
        for (int i = 0; i < p.size(); i++) {
            point[i] = Point(p[i].x, p[i].y);
        }
        SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
        graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);
        if (stroke_width != 0)
            graphics.DrawLines(&pen, point, static_cast<int>(p.size()));
        delete[] point;
        graphics.Restore(save);
    }

	void visit(text* t, Graphics& graphics) override{//draw text
        for (int i = 0; i < t->text_.length(); i++) {
            if (t->text_[i] == '\n') {
                t->text_[i] = ' ';
            }
            if (t->text_[i] == ' ' && t->text_[i + 1] == ' ') {
                t->text_.erase(i, 1);
                i--;
            }
        }
        float rate = 0;
        GraphicsState save = graphics.Save();
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }
        wstring_convert<codecvt_utf8<wchar_t>> converter;//convert utf8 to utf16
        wstring wFontFamily = converter.from_bytes(t->font_family);
        FontFamily fontFamily(wFontFamily.c_str());
        Font font(&fontFamily, static_cast<REAL>(t->font_size), t->italic ? FontStyleItalic : FontStyleRegular, UnitPixel);
        StringFormat stringFormat; // Tạo một biến StringFormat
        if (t->text_anchor == "middle") {
            stringFormat.SetAlignment(StringAlignmentCenter); // Căn giữa
        }
        else if (t->text_anchor == "end") {
            stringFormat.SetAlignment(StringAlignmentFar); // Căn giữa phải
            rate = 0.15;
        }
        else
        {
            stringFormat.SetAlignment(StringAlignmentNear); // Căn giữa trái
            rate = -0.15;
        }
        PointF pointF(static_cast<REAL>(t->start.x + t->dx + rate * t->font_size), static_cast<REAL>(t->start.y + t->dy - 0.9 * t->font_size));
        
        // Create a GraphicsPath
        GraphicsPath path;
        // Add the string to the path
        const wstring wstr = wstring(t->text_.begin(), t->text_.end());
        path.AddString(wstr.c_str(), -1, &fontFamily, t->italic ? FontStyleItalic : FontStyleRegular, static_cast<REAL>(t->font_size), pointF, &stringFormat);
        // Create a solid brush for filling
        SolidBrush fillBrush(Color(static_cast<int>(t->fill_opacity * 255), t->fill_color.red, t->fill_color.green, t->fill_color.blue));
        Pen pen(Color(static_cast<int>(t->stroke_opacity * 255), t->stroke_color.red, t->stroke_color.green, t->stroke_color.blue), static_cast<REAL>(t->stroke_width));
        // Fill the path with the solid brush
        graphics.FillPath(&fillBrush, &path);
        if (t->stroke_width != 0)
            graphics.DrawPath(&pen, &path);
        graphics.Restore(save);
    }
	void visit(path* p, Graphics& graphics) override{//draw path
        GraphicsState save = graphics.Save();
        SolidBrush fillBrush(Color(static_cast<int>(p->fill_opacity * 255), p->fill_color.red, p->fill_color.green, p->fill_color.blue));
        Pen pen(Color(static_cast<int>(p->stroke_opacity * 255), p->stroke_color.red, p->stroke_color.green, p->stroke_color.blue), static_cast<REAL>(p->stroke_width));
        int index = 0;
        for (int i = 0; i < trans.types.size(); i++) {
            if (trans.types[i] == "translate")
                graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
            if (trans.types[i] == "rotate")
                graphics.RotateTransform(trans.values[index]);
            if (trans.types[i] == "scale")
                graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
            index += 2;
            if (trans.types[i] == "rotate")
                index--;
        }

        // Create a GraphicsPath
        GraphicsPath path;
        point current_point;
        point start_point;
        point d1, d2, d;
        bool first_point = true;
        index = 0;
        float single_type;
        char last_command = ' ';
        while (index < p->data.length()) {
            if (p->data[index] == 'z' || p->data[index] == 'Z') {//close path
                index++;
                path.CloseFigure();
                start_point.x = current_point.x;
                start_point.y = current_point.y;
                last_command = 'z';
            }
            else if (p->data[index] == 'm') {//move to
                read_single_point(p->data, index, d);
                if (first_point) {
                    first_point = false;
                    start_point.x = d.x, start_point.y = d.y;
                    current_point.x = d.x, current_point.y = d.y;
                    path.StartFigure();

                    last_command = 'm';
                }
                else {
                    current_point.x += d.x;
                    current_point.y += d.y;

                    last_command = 'm';
                }
            }
            else if (p->data[index] == 'M') {
                read_single_point(p->data, index, d);
                if (first_point) {
                    first_point = false;
                    start_point.x = d.x, start_point.y = d.y;
                    current_point.x = d.x, current_point.y = d.y;
                    path.StartFigure();
                    last_command = 'M';
                }
                else {
                    current_point.x = d.x;
                    current_point.y = d.y;
                    last_command = 'M';
                }
            }
            else if (p->data[index] == 'l') {
                command_l:
                    read_single_point(p->data, index, d);
                    path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
                    current_point.x += d.x;
                    current_point.y += d.y;
                    last_command = 'l';
            }
            else if (p->data[index] == 'L') {
                command_L:
                    read_single_point(p->data, index, d);
                    path.AddLine(current_point.x, current_point.y, d.x, d.y);
                    current_point.x = d.x;
                    current_point.y = d.y
                    last_command = 'L';
            }
            else if (p->data[index] == 'h') {
                command_h:
                    single_type = read_single_point(p->data, index);
                    path.AddLine(current_point.x, current_point.y, current_point.x + single_type, current_point.y);
                    current_point.x += single_type;
                    last_command = 'h';
            }
            else if (p->data[index] == 'H') {
                command_H:
                    single_type = read_single_point(p->data, index);
                    path.AddLine(current_point.x, current_point.y, single_type, current_point.y);
                    current_point.x = single_type;
                    last_command = 'H';
            }
            else if (p->data[index] == 'v') {
                command_v:
                    single_type = read_single_point(p->data, index);
                    path.AddLine(current_point.x, current_point.y, current_point.x, current_point.y + single_type);
                    current_point.y += single_type;
                    last_command = 'v';
            }
            else if (p->data[index] == 'V') {
                command_V:
                    single_type = read_single_point(p->data, index);
                    path.AddLine(current_point.x, current_point.y, current_point.x, single_type);
                    current_point.y = single_type;
                    last_command = 'V';
            }
            else if (p->data[index] == 'c') {
                command_c:
                    read_single_point(p->data, ++index, d1);
                    read_single_point(p->data, ++index, d2);
                    read_single_point(p->data, ++index, d);
                    path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d2.x, current_point.y + d2.y, current_point.x + d.x, current_point.y + d.y);
                    current_point.x += d.x;
                    current_point.y += d.y;
                    last_command = 'c';
            }
            else if (p->data[index] == 'C') {
                command_C:
                    read_single_point(p->data, ++index, d1);
                    read_single_point(p->data, ++index, d2);
                    read_single_point(p->data, ++index, d);
                    path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d2.x, d2.y, d.x, d.y);
                    current_point.x = d.x;
                    current_point.y = d.y;
                    last_command = 'C';
            }
            else if (p->data[index] <= '9' && p->data[index] >= '0') {
                index--;
                switch (last_command) {
                case 'm':
                    read_single_point(p->data, index, d);
                    path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
                    current_point.x += d.x;
                    current_point.y += d.y;
                    break;

                case 'M':
                    read_single_point(p->data, index, d);
                    path.AddLine(current_point.x, current_point.y, d.x, d.y);
                    current_point.x = d.x;
                    current_point.y = d.y;
                    break;
                case 'c':
                    goto command_c;
                    break;
                case 'C':
                    goto command_C;
                    break;
                case 'L':
                    goto command_L;
                case 'l':
                    goto command_l;
                    break;
                case 'h':
                    goto command_h;
                    break;
                case 'H':
                    goto command_H;
                    break;
                case 'v':
                    goto command_v;
                    break;
                case 'V':
                    goto command_V;
                    break;
                }
            }
            else {
                index++;
            }
         }

         //process linecap
        if (p->linecap == "round") {
            pen.SetStartCap(LineCapRound);
            pen.SetEndCap(LineCapRound);
        }
        else if (p->linecap == "square") {
            pen.SetStartCap(LineCapSquare);
            pen.SetEndCap(LineCapSquare);
        }
        else {
            pen.SetStartCap(LineCapFlat);
            pen.SetEndCap(LineCapFlat);
        }

        //process linejoin
        if (p->linejoin == "round") {
            pen.SetLineJoin(LineJoinRound);
        }
        else if (p->linejoin == "bevel") {
            pen.SetLineJoin(LineJoinBevel);
        }
        else {
            pen.SetLineJoin(LineJoinMiter);
        }

        graphics.FillPath(&fillBrush, &path);
        if (stroke_width != 0)
            graphics.DrawPath(&pen, &path);
        graphics.Restore(save);
    }
};

class GetMaxVisitor : public ShapeVisitor {
public:
	void visit(line* l, float& max_width, float& max_height) override{
        if (l->start.x > max_width)
            max_width = l->start.x;
        else if (l->end.x > max_width)
            max_width = l->end.x;
        if (l->start.y > max_height)
            max_width = l->start.y;
        else if (l->end.y > max_height)
            max_width = l->end.y;
    }
    void visit(rectangle* r, float& max_width, float& max_height) override{
        if (max_width > r->start.x + r->width)
            max_width = r->start.x + r->width;
        if (max_height > r->start.y + r->height)
            max_height = r->start.y + r->height;
    }
    void visit(ellipse* e, float& max_width, float& max_height) override{
        if (max_width > e->start.x + e->rx)
            max_width = e->start.x + e->rx;
        if (max_height > e->start.y + e->ry)
            max_height = e->start.y + e->ry;
    }
    void visit(circle* c, float& max_width, float& max_height) override{
        if (max_width > c->start.x + c->r)
            max_width = c->start.x + c->r;
        if (max_height > c->start.y + c->r)
            max_height = c->start.y + c->r;
    }
    void visit(polygon* p, float& max_width, float& max_height) override{
        for (int i = 0; i < p->p.size(); i++) {
            if (p->p[i].x > max_width)
                max_width = p->p[i].x;
            if (p->p[i].y > max_height)
                max_height = p->p[i].y;
        }
    }
    void visit(polyline* p, float& max_width, float& max_height) override{
        for (int i = 0; i < p->p.size(); i++) {
            if (p->p[i].x > max_width)
                max_width = p->p[i].x;
            if (p->p[i].y > max_height)
                max_height = p->p[i].y;
        }
    }
    void visit(text* t, float& max_width, float& max_height) override{
        if (max_width > t->start.x + t->text_.length())
            max_width = t->start.x + t->text_.length();
        if (max_height > t->start.y - t->font_size)
            max_height = t->start.y - t->font_size;
    }
    void visit(path* p, float& max_width, float& max_height) override{
        return;
    }
};

vector<shape*> read_file(string file_name, float& max_width, float& max_height);
void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale);

#endif