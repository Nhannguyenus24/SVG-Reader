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

void readTransform(std::string value, point& translate, float& rotate, float& scale_x, float& scale_y) {
    std::istringstream ss(value);

    std::string token;
    while (ss >> token) {
        if (token == "translate") {
            ss >> translate.x;
            ss.ignore(); // Ignore the comma
            ss >> translate.y;
        }
        else if (token == "rotate") {
            ss >> rotate;
        }
        else if (token == "scale") {
            ss >> scale_x;
            if (ss.peek() == ',') {
                ss.ignore(); // Ignore the comma
                ss >> scale_y;
            }
            else {
                scale_y = scale_x;
            }
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
    PointF pointF(static_cast<REAL>(start.x), static_cast<REAL>(start.y - font_size));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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