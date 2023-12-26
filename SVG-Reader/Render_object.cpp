#include "Object.h"

VOID line::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
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
    graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
    graphics.Restore(save);
}

void line::get_max(float& max_width, float& max_height) {
    if (start.x > max_width)
        max_width = start.x;
    else if (end.x > max_width)
        max_width = end.x;
    if (start.y > max_height)
        max_width = start.y;
    else if (end.y > max_height)
        max_width = end.y;
}

VOID rectangle::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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
    graphics.Restore(save);
}

void rectangle::get_max(float& max_width, float& max_height) {
    if (max_width > start.x + width)
        max_width = start.x + width;
    if (max_height > start.y + height)
        max_height = start.y + height;
}

VOID circle::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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

void circle::get_max(float& max_width, float& max_height) {
    if (max_width > start.x + r)
        max_width = start.x + r;
    if (max_height > start.y + r)
        max_height = start.y + r;
}

VOID ellipse::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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

void ellipse::get_max(float& max_width, float& max_height) {
    if (max_width > start.x + rx)
        max_width = start.x + rx;
    if (max_height > start.y + ry)
        max_height = start.y + ry;
}

VOID polygon::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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

void polygon::get_max(float& max_width, float& max_height) {
    for (int i = 0; i < p.size(); i++) {
        if (p[i].x > max_width)
            max_width = p[i].x;
        if (p[i].y > max_height)
            max_height = p[i].y;
    }
}

VOID polyline::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
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

void polyline::get_max(float& max_width, float& max_height) {
    for (int i = 0; i < p.size(); i++) {
        if (p[i].x > max_width)
            max_width = p[i].x;
        if (p[i].y > max_height)
            max_height = p[i].y;
    }
}

VOID text::draw(Graphics& graphics, defs def) {
    for (int i = 0; i < text_.length(); i++) {
        if (text_[i] == '\n') {
            text_[i] = ' ';
        }
        if (text_[i] == ' ' && text_[i + 1] == ' ') {
            text_.erase(i, 1);
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
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    wstring wFontFamily = converter.from_bytes(font_family);

    FontFamily fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, static_cast<REAL>(font_size), italic ? FontStyleItalic : FontStyleRegular, UnitPixel);

    StringFormat stringFormat; // Tạo một biến StringFormat
    if (text_anchor == "middle") {
        stringFormat.SetAlignment(StringAlignmentCenter); // Căn giữa
    }
    else if (text_anchor == "end") {
        stringFormat.SetAlignment(StringAlignmentFar); // Căn giữa phải
        rate = 0.15;
    }
    else
    {
        stringFormat.SetAlignment(StringAlignmentNear); // Căn giữa trái
        rate = -0.15;
    }
    PointF pointF(static_cast<REAL>(start.x + dx + rate * font_size), static_cast<REAL>(start.y + dy - 0.9 * font_size));
    // Create a GraphicsPath
    GraphicsPath path;

    // Add the string to the path
    const wstring wstr = wstring(text_.begin(), text_.end());
    path.AddString(wstr.c_str(), -1, &fontFamily, italic ? FontStyleItalic : FontStyleRegular, static_cast<REAL>(font_size), pointF, &stringFormat);

    // Create a solid brush for filling
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    // Fill the path with the solid brush
    graphics.FillPath(&fillBrush, &path);
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}

void text::get_max(float& max_width, float& max_height) {
    if (max_width > start.x + text_.length())
        max_width = start.x + text_.length();
    if (max_height > start.y - font_size)
        max_height = start.y - font_size;
}

void path::read_single_point(string data, int& index, point& p) {
    string n1 = "0", n2 = "0";
    bool s1 = false, s2 = false, accept = false;
    bool negative1 = false, negative2 = false;
    while (true) {
        if ((data[index] > '9' || data[index] < '0') && data[index] != '.') {
            if (s1 == true) {
                s1 = false;
                accept = true;
            }
            if (s2 == true) {
                p.x = stof(n1);
                p.y = stof(n2);
                if (negative1)
                    p.x *= -1;
                if (negative2)
                    p.y *= -1;
                return;
            }
        }
        else if (data[index] <= '9' && data[index] >= '0' && s1 == false && s2 == false && accept == false) {
            n1 += data[index];
            if (data[index - 1] == '-') {
                negative1 = true;
            }
            s1 = true;
            index++;
            continue;
        }
        else if (data[index] <= '9' && data[index] >= '0' && s1 == false && accept == true) {
            n2 += data[index];
            s2 = true;
            if (data[index - 1] == '-') {
                negative2 = true;
            }
            index++;
            continue;
        }
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
            if (s1) {
                n1 += data[index];
            }
            if (s2) {
                n2 += data[index];
            }
        }
        index++;
    }
}

float path::read_single_point(string data, int& index) {
    string n = "0";
    bool s = false;
    bool negative = false;
    while (true) {
        if (data[index] == '-' && data[index + 1] <= '9' && data[index + 1] >= '0') {
            negative = true;
        }
        if (data[index] > '9' || data[index] < '0' && data[index] != '.') {
            if (s == true) {
                float result = stof(n);
                if (negative)
                    result *= -1;
                return  result;
            }
        }
        else if (data[index] <= '9' && data[index] >= '0' && s == false) {
            n += data[index];
            s = true;
            index++;
            continue;
        }
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
            n += data[index];
        }
        index++;
    }
}

void path::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
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
    GraphicsPath path;
    point current_point;
    point start_point;
    point d1, d2, d, d3;
    bool first_point = true;
    index = 0;
    float single_type;
    char last_command = ' ';
    while (index < data.length()) {
        if (data[index] == 'z' || data[index] == 'Z') {
            index++;
            path.CloseFigure();
            start_point.x = current_point.x;
            start_point.y = current_point.y;
            last_command = 'z';
        }
        else if (data[index] == 'A') {

        }
        else if (data[index] == 'a') {

        }
        else if (data[index] == 'q') {
            command_q:
            read_single_point(data, ++index, d1);
            read_single_point(data, ++index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y +d1.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x+ d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'q';
        }
        else if (data[index] == 'Q') {
        command_Q:
            read_single_point(data, ++index, d1);
            read_single_point(data, ++index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d1.x, d1.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'Q';
        }
        else if (data[index] == 's') {
            command_s:
            read_single_point(data, ++index, d3);
            read_single_point(data, ++index, d);
            if (last_command == 'c' || last_command == 'C') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else if (last_command == 's' || last_command == 'S') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else {
                d1.x = current_point.x;
                d1.y = current_point.y;
            }
            path.AddBezier(current_point.x, current_point.y, d1.x,d1.y, current_point.x + d3.x, current_point.y + d3.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            d2.x = d3.x + current_point.x;
            d2.y = d3.y + current_point.y;
            last_command = 's';
        }
        else if (data[index] == 'S') {
            command_S:
            read_single_point(data, ++index, d3);
            read_single_point(data, ++index, d);
            if (last_command == 'c' || last_command == 'C') {
				d1.x = 2 * current_point.x - d2.x;
				d1.y = 2 * current_point.y - d2.y;
			}
            else if (last_command == 's' || last_command == 'S') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else {
				d1.x = current_point.x;
				d1.y = current_point.y;
			}
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d3.x, d3.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            d2.x = d3.x;
            d2.y = d3.y;
            last_command = 'S';
        }
        else if (data[index] == 'm') {
            read_single_point(data, index, d);
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
        else if (data[index] == 'M') {
            read_single_point(data, index, d);
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
        else if (data[index] == 'l') {
        command_l:
            read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'l';
        }
        else if (data[index] == 'L') {
        command_L:
            read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'L';
        }
        else if (data[index] == 'h') {
        command_h:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x + single_type, current_point.y);
            current_point.x += single_type;
            last_command = 'h';
        }
        else if (data[index] == 'H') {
        command_H:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, single_type, current_point.y);
            current_point.x = single_type;
            last_command = 'H';
        }
        else if (data[index] == 'v') {
        command_v:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, current_point.y + single_type);
            current_point.y += single_type;
            last_command = 'v';
        }
        else if (data[index] == 'V') {
        command_V:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, single_type);
            current_point.y = single_type;
            last_command = 'V';
        }
        else if (data[index] == 'c') {
        command_c:
            read_single_point(data, ++index, d1);
            read_single_point(data, ++index, d2);
            read_single_point(data, ++index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d2.x, current_point.y + d2.y, current_point.x + d.x, current_point.y + d.y);
            d2.x += current_point.x;
            d2.y += current_point.y;
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'c';
        }
        else if (data[index] == 'C') {
        command_C:
            read_single_point(data, ++index, d1);
            read_single_point(data, ++index, d2);
            read_single_point(data, ++index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d2.x, d2.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'C';
        }
        else if (data[index] <= '9' && data[index] >= '0') {
            index--;
            switch (last_command) {
            case 'm':
                read_single_point(data, index, d);
                path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
                current_point.x += d.x;
                current_point.y += d.y;
                break;

            case 'M':
                read_single_point(data, index, d);
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
            case 's':
                goto command_s;
                break;
            case 'S':
                goto command_S;
                break;
            case 'q':
                goto command_q;
				break;
            case 'Q':
				goto command_Q;
                break;
            }
        }
        else {
            index++;
        }
    }

    if (linecap == "round") {
         pen.SetStartCap(LineCapRound);
         pen.SetEndCap(LineCapRound);
     }
     else if (linecap == "square") {
         pen.SetStartCap(LineCapSquare);
         pen.SetEndCap(LineCapSquare);
     }
     else {
         pen.SetStartCap(LineCapFlat);
         pen.SetEndCap(LineCapFlat);
    }
     if (linejoin == "round") {
         pen.SetLineJoin(LineJoinRound);
     }
     else if (linejoin == "bevel") {
         pen.SetLineJoin(LineJoinBevel);
     }
     else {
         pen.SetLineJoin(LineJoinMiter);
     }
     graphics.FillPath(&fillBrush, &path);
     if (fill_id != "") {
         for (int i = 0; i < def.lg_list.size(); i++) {
             if (fill_id == def.lg_list[i]->id) {
                 float* points = new float[def.lg_list[i]->stop_list.size()];
                 Color* colors = new Color[def.lg_list[i]->stop_list.size()];
                 for (int j = 0; j < def.lg_list[i]->stop_list.size(); j++) {
                     points[j] = def.lg_list[i]->stop_list[j]->offset;
                     colors[j] = Color(static_cast<int>(def.lg_list[i]->stop_list[j]->stop_opacity * 255), def.lg_list[i]->stop_list[j]->stop_color.red, def.lg_list[i]->stop_list[j]->stop_color.green, def.lg_list[i]->stop_list[j]->stop_color.blue);
                 }
                 LinearGradientBrush linGrBrush(PointF(def.lg_list[i]->start.x, def.lg_list[i]->start.y), PointF(def.lg_list[i]->end.x, def.lg_list[i]->end.y), colors[0], colors[def.lg_list[i]->stop_list.size() - 1]);
                 linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i]->stop_list.size());
                 graphics.FillPath(&linGrBrush, &path);
                 break;
             }
         }
     }
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}

void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale) {
    PointF center(static_cast<REAL>((width / 2 + scroll_x) * scale), static_cast<REAL>((height / 2 + scroll_y) * scale));

    // Áp dụng các biến đổi
    Matrix transformMatrix;
    transformMatrix.Translate(scroll_x, scroll_y); // Dịch chuyển trước
    transformMatrix.Scale(scale, scale);           // Sau đó thay đổi tỷ lệ
    transformMatrix.RotateAt(angle, center);       // Cuối cùng, xoay tại trọng tâm

    graphics.SetTransform(&transformMatrix);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}