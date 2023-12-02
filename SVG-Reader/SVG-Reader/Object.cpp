#include "Object.h"

//======================================= Reading area================================================================

color readRGB(string value) {
    color colour;
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {

        stringstream ss(value);
        string temp = "";
        getline(ss, temp, '(');
        getline(ss, temp, ',');
        colour.red = stof(temp);
        getline(ss, temp, ',');
        colour.green = stof(temp);
        getline(ss, temp, ')');
        colour.blue = stof(temp);
    }
    else {
        ifstream file("rgb.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string buffer, name, rgb;
                getline(ss, buffer, '"');
                getline(ss, name, '"');
                if (name == value) {
                    getline(ss, buffer, '(');
                    ss >> colour.red;
                    ss >> buffer;
                    ss >> colour.green;
                    ss >> buffer;
                    ss >> colour.blue;
                    break;
                }
                else {
                    getline(ss, buffer, '}');
                }
            }
        }
        file.close();
    }
    return colour;
}

bool check(char a) {
    if (a <= 'Z' && a >= 'A')
        return true;
    if (a <= 'z' && a >= 'a')
        return true;
    if (a <= '9' && a >= '0')
        return true;
    if (a == '(' || a == ')')
        return true;
    return false;
}
void remove_space(string& s) {
    for (int i = 1; i < s.length() - 1; i++) {
        if (!check(s[i])) {
            if (s[i - 1] <= '9' && s[i - 1] >= '0' && s[i + 1] <= '9' && s[i + 1] >= '0' && s[i] != '.') {
                s[i] = ',';
                continue;
            }
            else if (s[i] != '.') {
                s.erase(i, 1);
                i--;
            }
        }
    }
}

void readTransform(string value, point& translate, float& rotate, float& scale_x, float& scale_y) {
    string temp;
    string vessel1 = "", vessel2 = "";
    bool change = true;
    remove_space(value);
    //value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
    if (value.find("translate") != string::npos)
    {
        stringstream ss(value.substr(value.find("translate") + 10));
        getline(ss, temp, ',');
        translate.x = stof(temp);
        getline(ss, temp, ')');
        translate.y = stof(temp);
    }
    if (value.find("rotate") != string::npos)
    {
        stringstream ss(value.substr(value.find("rotate") + 7));
        getline(ss, temp, ')');
        rotate = stof(temp);
    }
    if (value.find("scale") != string::npos) {
        stringstream ss(value.substr(value.find("scale") + 6));
        getline(ss, temp, ')');
        for (int i = 0; i < temp.length(); i++) {
            if (temp[i] == ',') {
                change = false;
                continue;
			}
            if (change) {
				vessel1 += temp[i];
			}
            else {
				vessel2 += temp[i];
			}
		}
        if (vessel2.length() == 0)
            scale_x = scale_y = stof(vessel1);
        else {
            scale_x = stof(vessel1);
			scale_y = stof(vessel2);
        }
    }
}

vector<point> readPoints(string value) {
    vector<point> points;

    // Xóa khoảng trắng ở đầu và cuối chuỗi
    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");

    // Kiểm tra và loại bỏ dấu cách đầu tiên nếu có
    if (!value.empty() && value[0] == ' ') {
        value = value.substr(1);
    }

    // Kiểm tra và loại bỏ dấu cách cuối cùng nếu có
    if (!value.empty() && value.back() == ' ') {
        value = value.substr(0, value.size() - 1);
    }

    stringstream ss(value);
    string temp = "";
    string pointStr;
    while (getline(ss, pointStr, ' ')) {
        point p;
        stringstream pointStream(pointStr);
        getline(pointStream, pointStr, ',');
        p.x = stof(pointStr);
        getline(pointStream, pointStr, ',');
        p.y = stof(pointStr);
        points.push_back(p);
    }
    return points;
}

void readPolygon(string name, string value, polygon* polygon) {
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
		else
			polygon->fill_color = readRGB(value);
        polygon->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polygon->stroke_opacity = 0;
        }
		else
            polygon->stroke_color = readRGB(value);
    }
    else if (name == "stroke-width") {
        polygon->stroke_width = stof(value);
    }
    else if (name == "points") {
        polygon->p = readPoints(value);
    }
    else if (name == "transform") {
        readTransform(value, polygon->translate, polygon->rotate, polygon->scale_x, polygon->scale_y);
    }
}

void readPolyline(string name, string value, polyline* polyline) {
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
        else
            polyline->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			polyline->stroke_opacity = 0;
		}
		else
            polyline->stroke_color = readRGB(value);
    }
    else if (name == "stroke-width") {
        polyline->stroke_width = stof(value);
    }
    else if (name == "points") {
        polyline->p = readPoints(value);
    }
    else if (name == "transform") {
        readTransform(value, polyline->translate, polyline->rotate, polyline->scale_x, polyline->scale_y);
    }
}

void readText(string name, string value, text* text) {
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
		else
            text->fill_color = readRGB(value);
    }
    else if (name == "font-family") {
        text->font_family = value;
    }
    else if (name == "transform") {
        readTransform(value, text->translate, text->rotate, text->scale_x, text->scale_y);
    }
    else if (name == "dx") {
        text->dx = stof(value);
	}
    else if (name == "dy") {
		text->dy = stof(value);
	}
}

void readLine(string name, string value, line* line) {
    if (name == "stroke-opacity") {
        line->stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			line->stroke_opacity = 0;
		}
        else 
            line->stroke_color = readRGB(value);
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
        readTransform(value, line->translate, line->rotate, line->scale_x, line->scale_y);
    }
}

void readRectangle(string name, string value, rectangle* rect) {
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
        else 
            rect->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			rect->stroke_opacity = 0;
		}
		else
            rect->stroke_color = readRGB(value);
    }
    else if (name == "x") {
        rect->start.x = stof(value);
    }
    else if (name == "y") {
        rect->start.y = stof(value);
    }
    else if (name == "width") {
        rect->width = stof(value);
    }
    else if (name == "height") {
        rect->height = stof(value);
    }
    else if (name == "stroke-width") {
        rect->stroke_width = stof(value);
    }
    else if (name == "transform") {
        readTransform(value, rect->translate, rect->rotate, rect->scale_x, rect->scale_y);
    }
}

void readEllipse(string name, string value, ellipse* elli) {
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
		else
            elli->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            elli->stroke_opacity = 0;
        }
        else 
            elli->stroke_color = readRGB(value);
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
        readTransform(value, elli->translate, elli->rotate, elli->scale_x, elli->scale_y);
    }
}

void readCircle(string name, string value, circle* cir) {
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
		else 
			cir->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			cir->stroke_opacity = 0;
		}
		else
            cir->stroke_color = readRGB(value);
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
        readTransform(value, cir->translate, cir->rotate, cir->scale_x, cir->scale_y);
    }
}
void readPath(string name, string value, path* path) {
    if (name == "d") {
        path->data = value;
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			path->stroke_opacity = 0;
		}
		else
			path->stroke_color = readRGB(value);
    }
    else if (name == "stroke-width") {
        path->stroke_width = stoi(value);
    }
    else if (name == "stroke-linejoin") {
        path->linejoin = value;
    }
    else if (name == "stroke-linecap") {
        path->linecap = value;
    }
    else if (name == "fill-opacity") {
        path->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        path->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            path->fill_opacity = 0;
        }
        else
            path->fill_color = readRGB(value);
    }
}
vector<shape*> read_file(string file_name, float& max_width, float& max_height) {
    vector<shape*> shapes;
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Không thể mở tệp " << file_name << endl;
    }
    // Đọc nội dung của tệp vào một vector<char>
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0'); // Thêm ký tự kết thúc chuỗi

    // Khai báo một tài liệu XML để lưu trữ cấu trúc tệp SVG
    rapidxml::xml_document<> doc;

    // Phân tích nội dung tệp vào tài liệu XML
    doc.parse<0>(&buffer[0]);

    // Lấy nút gốc (root node) của tài liệu
    rapidxml::xml_node<>* root = doc.first_node("svg");
    max_width = 0, max_height = 0;
    group g;
    g.traversal_group(root, max_width, max_height, shapes);
    return shapes;
}

void group::traversal_group(rapidxml::xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes) {
    for (rapidxml::xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        string name = node->name();
        if (name == "line") {
            line* lin = new line();
            for (const auto& attribute : attributes) {
				readLine(attribute.first, attribute.second, lin);
			}
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readLine(attribute->name(), attribute->value(), lin);
            }
            lin->get_max(max_width, max_height);
            shapes.push_back(lin);
        }
        else if (name == "rect") {
            rectangle* rect = new rectangle();
            for (const auto& attribute : attributes) {
                readRectangle(attribute.first, attribute.second, rect);
            }
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                string attribute_name = attribute->name();
                string attribute_value = attribute->value();
                readRectangle(attribute_name, attribute_value, rect);
            }
            rect->get_max(max_width, max_height);
            shapes.push_back(rect);
        }
        else if (name == "ellipse") {
            ellipse* elli = new ellipse();
            for (const auto& attribute : attributes) {
				readEllipse(attribute.first, attribute.second, elli);
			}
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readEllipse(attribute->name(), attribute->value(), elli);
            }
            elli->get_max(max_width, max_height);
            shapes.push_back(elli);
        }
        else if (name == "circle") {
            circle* cir = new circle();
            for (const auto& attribute : attributes) {
                readCircle(attribute.first, attribute.second, cir);
            }
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readCircle(attribute->name(), attribute->value(), cir);
            }
            cir->get_max(max_width, max_height);
            shapes.push_back(cir);
        }
        else if (name == "polygon") {
            polygon* polyg = new polygon();
            for (const auto& attribute : attributes) {
				readPolygon(attribute.first, attribute.second, polyg);
			}
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readPolygon(attribute->name(), attribute->value(), polyg);
            }
            polyg->get_max(max_width, max_height);
            shapes.push_back(polyg);
        }
        else if (name == "polyline") {
            polyline* polyl = new polyline();
            for (const auto& attribute : attributes) {
                readPolyline(attribute.first, attribute.second, polyl);
            }
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readPolyline(attribute->name(), attribute->value(), polyl);
            }
            polyl->get_max(max_width, max_height);
            shapes.push_back(polyl);
        }
        else if (name == "text") {
            text* tex = new text();
            for (const auto& attribute : attributes) {
				readText(attribute.first, attribute.second, tex);
			}
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readText(attribute->name(), attribute->value(), tex);
            }
            tex->text_ = node->value();
            tex->get_max(max_width, max_height);
            shapes.push_back(tex);
        }
        else if (name == "path") {
            path* p = new path();
            for (const auto& attribute : attributes) {
				readPath(attribute.first, attribute.second, p);
			}
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
				readPath(attribute->name(), attribute->value(), p);
			}
			p->get_max(max_width, max_height);
			shapes.push_back(p);
        }
        else if (name == "g") {
			group new_group;
            for (const auto& attribute : attributes) {
                new_group.attributes[attribute.first] = attribute.second;
            }
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
				new_group.attributes[attribute->name()] = attribute->value();
			}
			new_group.traversal_group(node, max_width, max_height, shapes);
		}
    }
}

//================================== Drawing area ==========================================================================================================

VOID line::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
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

VOID rectangle::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
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

VOID circle::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
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

VOID ellipse::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
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

VOID polygon::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }
    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()));
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

VOID polyline::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }

    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()));
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

VOID text::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wFontFamily = converter.from_bytes(font_family);
    FontFamily  fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, static_cast<REAL>(font_size), italic ? FontStyleItalic : FontStyleRegular, UnitPixel);
    PointF pointF(static_cast<REAL>(start.x + dx), static_cast<REAL>(start.y - font_size + dy));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
    const wstring wstr = wstring(text_.begin(), text_.end());
    graphics.DrawString(wstr.c_str(), -1, &font, pointF, &fillBrush);
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
        if (data[index] > '9' || data[index] < '0') {
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
        if (data[index] <= '9' && data[index] >= '0') {
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

float path::read_single_point(string data, int& index){
    string n = "0";
	bool s = false;
    bool negative = false;
    while (true) {
        if (data[index] == '-' && data[index + 1] <= '9' && data[index + 1] >= '0') {
			negative = true;
		}
        if (data[index] > '9' || data[index] < '0') {
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
        if (data[index] <= '9' && data[index] >= '0') {
			n += data[index];
		}
		index++;
	}
}

void path::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    graphics.TranslateTransform(translate.x, translate.y);
    graphics.RotateTransform(rotate);
    graphics.ScaleTransform(scale_x, scale_y);
    GraphicsPath path;
    point current_point;
    point start_point;
    point d1, d2, d;
    bool first_point = true;
    int index = 0;
    float single_type;
    char last_command;
    while (index < data.length()) {    
        if (data[index] == 'z' || data[index] == 'Z'){
			index++;
            path.AddLine(current_point.x, current_point.y, start_point.x, start_point.y);
            first_point = true;
            last_command = 'z';
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
			read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'l';
		}
        else if (data[index] == 'L') {
			read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, d.x, d.y);
			current_point.x = d.x;
			current_point.y = d.y;
			last_command = 'L';
		}
        else if (data[index] == 'h') {
			single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x + single_type, current_point.y);
            current_point.x += single_type;
            last_command = 'h';
		}
        else if (data[index] == 'H') {
			single_type = read_single_point(data, index);
			path.AddLine(current_point.x, current_point.y, single_type, current_point.y);
			current_point.x = single_type;
            last_command = 'H';
		}
        else if (data[index] == 'v') {
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, current_point.y + single_type);
			current_point.y += single_type;
            last_command = 'v';
		}
        else if (data[index] == 'V') {
			single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, single_type);
			current_point.y = single_type;
            last_command = 'V';
		}
        else if (data[index] == 'c') {
			read_single_point(data, ++index, d1);
			read_single_point(data, ++index, d2);
			read_single_point(data, ++index, d);
			
			path.AddBezier( current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d2.x, current_point.y + d2.y, current_point.x + d.x, current_point.y + d.y);
			current_point.x += d.x;
			current_point.y += d.y;
            last_command = 'c';
		}
        else if (data[index] == 'C') {
			read_single_point(data, ++index, d1);
			read_single_point(data, ++index, d2);
			read_single_point(data, ++index, d);
			path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d2.x, d2.y, d.x, d.y);
			current_point.x = d.x;
			current_point.y = d.y;
            last_command = 'C';
		}
        else if (data[index] <= '9' && data[index] >= '0') {
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
            }
        }
        else {
            index++;
        }
    }
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
   /* if (linecap == "round") {
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
   }*/
    graphics.FillPath(&fillBrush, &path);
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}

void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale) {

    // Lưu ý: Sử dụng REAL thay vì static_cast<REAL> để tránh lỗi chuyển đổi không mong muốn.

 // Tính toán tâm của ảnh sau khi áp dụng scroll và scale
    PointF center(static_cast<REAL>((width / 2 + scroll_x) * scale), static_cast<REAL>((height / 2 + scroll_y) * scale));

    // Áp dụng các biến đổi
    Matrix transformMatrix;
    transformMatrix.Translate(scroll_x, scroll_y); // Dịch chuyển trước
    transformMatrix.Scale(scale, scale);           // Sau đó thay đổi tỷ lệ
    transformMatrix.RotateAt(angle, center);       // Cuối cùng, xoay tại trọng tâm

    // Áp dụng ma trận biến đổi
    graphics.SetTransform(&transformMatrix);

    // Cài đặt các thuộc tính khác nếu cần
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}