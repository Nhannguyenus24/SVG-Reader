//Shapes_Reader.cpp contains functions to read Shape hierarchy from SVG file.
#include"Shapes.h"
void read_line(string name, string value, line* line) {
    if (name == "stroke-opacity") {
        line->stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            line->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            line->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            line->stroke_color = read_RGB(value);
            if (line->stroke_width == 0)
                line->stroke_width = 1;
        }
    }
    else if (name == "x1") {
        line->start.x = stof(value);
    }
    else if (name == "y1") {
        line->start.y = stof(value);
    }
    else if (name == "x2") {
        line->end.x = stof(value);
    }
    else if (name == "y2") {
        line->end.y = stof(value);
    }
    else if (name == "stroke-width") {
        line->stroke_width = stof(value);
    }
    else if (name == "transform") {
        read_transform(value, line->trans);
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_line(str1, str2, line);
        }
    }
}

void read_rectangle(string name, string value, rectangle* rect) {
    if (name == "fill-opacity") {
        rect->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        rect->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            rect->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            rect->fill_id = value.substr(5, value.length() - 6);
        }
        else
            rect->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            rect->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            rect->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            rect->stroke_color = read_RGB(value);
            if (rect->stroke_width == 0)
                rect->stroke_width = 1;
        }
    }
    else if (name == "x") {
        rect->start.x = stof(value);
    }
    else if (name == "y") {
        rect->start.y = stof(value);
    }
    else if (name == "width") {
        if (value[value.length() - 1] == 't')
            value = value.substr(0, value.length() - 2);
        rect->width = stof(value);
    }
    else if (name == "height") {
        if (value[value.length() - 1] == 't')
            value = value.substr(0, value.length() - 2);
        rect->height = stof(value);
    }
    else if (name == "stroke-width") {
        rect->stroke_width = stof(value);
    }
    else if (name == "transform") {
        read_transform(value, rect->trans);
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_rectangle(str1, str2, rect);
        }
    }
}

void read_ellipse(string name, string value, ellipse* elli) {
    if (name == "fill-opacity") {
        elli->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        elli->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            elli->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            elli->fill_id = value.substr(5, value.length() - 6);
        }
        else
            elli->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            elli->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            elli->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            elli->stroke_color = read_RGB(value);
            if (elli->stroke_width == 0)
                elli->stroke_width = 1;
        }
    }
    else if (name == "cx") {
        elli->start.x = stof(value);
    }
    else if (name == "cy") {
        elli->start.y = stof(value);
    }
    else if (name == "rx") {
        elli->rx = stof(value);
    }
    else if (name == "ry") {
        elli->ry = stof(value);
    }
    else if (name == "stroke-width") {
        elli->stroke_width = stof(value);
    }
    else if (name == "transform") {
        read_transform(value, elli->trans);
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_ellipse(str1, str2, elli);
        }
    }
}

void read_circle(string name, string value, circle* cir) {
    if (name == "fill-opacity") {
        cir->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        cir->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            cir->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            cir->fill_id = value.substr(5, value.length() - 6);
        }
        else
            cir->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            cir->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            cir->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            cir->stroke_color = read_RGB(value);
            if (cir->stroke_width == 0)
                cir->stroke_width = 1;
        }
    }
    else if (name == "cx") {
        cir->start.x = stof(value);
    }
    else if (name == "cy") {
        cir->start.y = stof(value);
    }
    else if (name == "r") {
        cir->r = stof(value);
    }
    else if (name == "stroke-width") {
        cir->stroke_width = stof(value);
    }
    else if (name == "transform") {
        read_transform(value, cir->trans);
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_circle(str1, str2, cir);
        }
    }
}

void read_polygon(string name, string value, polygon* polygon) {
    if (name == "fill-opacity") {
        polygon->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polygon->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            polygon->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polygon->fill_id = value.substr(5, value.length() - 6);
        }
        else
            polygon->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polygon->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polygon->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            polygon->stroke_color = read_RGB(value);
            if (polygon->stroke_width == 0)
                polygon->stroke_width = 1;
        }
    }
    else if (name == "stroke-width") {
        polygon->stroke_width = stof(value);
    }
    else if (name == "points") {
        polygon->p = read_points(value);
    }
    else if (name == "transform") {
        string s = value;
        read_transform(value, polygon->trans);
    }
    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_polygon(str1, str2, polygon);
        }
    }
}

void read_polyline(string name, string value, polyline* polyline) {
    if (name == "fill-opacity") {
        polyline->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polyline->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            polyline->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polyline->fill_id = value.substr(5, value.length() - 6);
        }
        else
            polyline->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polyline->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polyline->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            polyline->stroke_color = read_RGB(value);
            if (polyline->stroke_width == 0)
                polyline->stroke_width = 1;
        }
    }
    else if (name == "stroke-width") {
        polyline->stroke_width = stof(value);
    }
    else if (name == "points") {
        polyline->p = read_points(value);
    }
    else if (name == "transform") {
        read_transform(value, polyline->trans);
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_polyline(str1, str2, polyline);
        }
    }
}

void read_text(string name, string value, text* text) {
    if (name == "x") {
        text->start.x = stof(value);
    }
    else if (name == "y") {
        text->start.y = stof(value);
    }
    else if (name == "font-size") {
        text->font_size = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            text->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            text->fill_id = value.substr(5, value.length() - 6);
        }
        else
            text->fill_color = read_RGB(value);
    }
    else if (name == "fill-opacity") {
        text->fill_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            text->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            text->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            text->stroke_color = read_RGB(value);
            if (text->stroke_width == 0)
                text->stroke_width = 1;
        }
    }
    else if (name == "stroke-opacity") {
        text->stroke_opacity = stof(value);
    }
    else if (name == "font-family") {
        text->font_family = value;
    }
    else if (name == "transform") {
        read_transform(value, text->trans);
    }
    else if (name == "dx") {
        text->dx = stof(value);
    }
    else if (name == "dy") {
        text->dy = stof(value);
    }
    else if (name == "text-anchor") {
        text->text_anchor = value;
    }

    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_text(str1, str2, text);
        }
    }
}
