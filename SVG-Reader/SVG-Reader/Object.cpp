#include "Object.h"
//======================================= Reading area================================================================

color readRGB(string value) {
    color colour;
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {

        stringstream ss(value);
        string temp = "";
        getline(ss, temp, '(');
        getline(ss, temp, ',');
        colour.red = stoi(temp);
        getline(ss, temp, ',');
        colour.green = stoi(temp);
        getline(ss, temp, ')');
        colour.blue = stoi(temp);
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

vector<point> readPoints(string value) {
    vector<point> points;
    stringstream ss(value);
    string temp = "";
    string pointStr;
    while (getline(ss, pointStr, ' ')) {
        point p;
        stringstream pointStream(pointStr);
        getline(pointStream, pointStr, ',');
        p.x = stoi(pointStr);
        getline(pointStream, pointStr, ',');
        p.y = stoi(pointStr);
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
        polygon->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        polygon->stroke_color = readRGB(value);
    }
    else if (name == "stroke-width") {
        polygon->stroke_width = stoi(value);
    }
    else if (name == "points") {
        polygon->p = readPoints(value);
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
        polyline->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        polyline->stroke_color = readRGB(value);
    }
    else if (name == "stroke-width") {
        polyline->stroke_width = stoi(value);
    }
    else if (name == "points") {
        polyline->p = readPoints(value);
    }
}

void readText(string name, string value, text* text) {
    if (name == "x") {
        text->start.x = stoi(value);
    }
    else if (name == "y") {
        text->start.y = stoi(value);
    }
    else if (name == "font-size") {
        text->font_size = stoi(value);
    }
    else if (name == "fill") {
        text->fill_color = readRGB(value);
    }
    else if (name == "font-family") {
        text->font_family = value;
    }
}

void readLine(string name, string value, line* line) {
    if (name == "stroke-opacity") {
        line->stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        line->stroke_color = readRGB(value);
    }
    else if (name == "x1") {
        line->start.x = stoi(value);
    }
    else if (name == "y1") {
        line->start.y = stoi(value);
    }
    else if (name == "x2") {
        line->end.x = stoi(value);
    }
    else if (name == "y2") {
        line->end.y = stoi(value);
    }
    else if (name == "stroke-width") {
        line->stroke_width = stoi(value);
    }
    else if (name == "stroke") {
        line->stroke_color = readRGB(value);
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
        rect->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        rect->stroke_color = readRGB(value);
    }
    else if (name == "x") {
        rect->start.x = stoi(value);
    }
    else if (name == "y") {
        rect->start.y = stoi(value);
    }
    else if (name == "width") {
        rect->width = stoi(value);
    }
    else if (name == "height") {
        rect->height = stoi(value);
    }
    else if (name == "stroke-width") {
        rect->stroke_width = stoi(value);
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
        elli->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        elli->stroke_color = readRGB(value);
    }
    else if (name == "cx") {
        elli->start.x = stoi(value);
    }
    else if (name == "cy") {
        elli->start.y = stoi(value);
    }
    else if (name == "rx") {
        elli->rx = stoi(value);
    }
    else if (name == "ry") {
        elli->ry = stoi(value);
    }
    else if (name == "stroke-width") {
        elli->stroke_width = stoi(value);
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
        cir->fill_color = readRGB(value);
    }
    else if (name == "stroke") {
        cir->stroke_color = readRGB(value);
    }
    else if (name == "cx") {
        cir->start.x = stoi(value);
    }
    else if (name == "cy") {
        cir->start.y = stoi(value);
    }
    else if (name == "r") {
        cir->r = stoi(value);
    }
    else if (name == "stroke-width") {
        cir->stroke_width = stoi(value);
    }
}

vector<shape*> read_file(string file_name) {
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


    for (rapidxml::xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        cout << "Node name: " << node->name() << endl;

        string name = node->name();
        if (name == "line") {
            line* lin = new line();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readLine(attribute->name(), attribute->value(), lin);
            }
            shapes.push_back(lin);
        }
        else if (name == "rect") {
            rectangle* rect = new rectangle();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                string attribute_name = attribute->name();
                string attribute_value = attribute->value();
                readRectangle(attribute_name, attribute_value, rect);
            }
            shapes.push_back(rect);
        }
        else if (name == "ellipse") {
            ellipse* elli = new ellipse();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readEllipse(attribute->name(), attribute->value(), elli);
            }
            shapes.push_back(elli);
        }
        else if (name == "circle") {
            circle* cir = new circle();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readCircle(attribute->name(), attribute->value(), cir);
            }
            shapes.push_back(cir);
        }
        else if (name == "polygon") {
            polygon* polyg = new polygon();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readPolygon(attribute->name(), attribute->value(), polyg);
            }
            shapes.push_back(polyg);
        }
        else if (name == "polyline") {
            polyline* polyl = new polyline();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readPolyline(attribute->name(), attribute->value(), polyl);
            }
            shapes.push_back(polyl);
        }
        else if (name == "text") {
            text* tex = new text();

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readText(attribute->name(), attribute->value(), tex);
            }
            tex->text_ = node->value();
            shapes.push_back(tex);
        }
    }
    return shapes;
}

//================================== Drawing area ==========================================================================================================

VOID line::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
}

VOID rectangle::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));

    graphics.FillRectangle(&fillBrush, start.x, start.y, width, height);
    if (stroke_width != 0)
        graphics.DrawRectangle(&pen, start.x, start.y, width, height);
}

VOID circle::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));

    graphics.FillEllipse(&fillBrush, start.x - r, start.y - r, 2 * r, 2 * r);
    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - r, start.y - r, 2 * r, 2 * r);
}

VOID ellipse::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));


    graphics.FillEllipse(&fillBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
}

VOID polygon::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));

    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }
    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()));
    if (stroke_width != 0)
        graphics.DrawPolygon(&pen, point, static_cast<int>(p.size()));
    delete[] point;
}

VOID polyline::draw(Graphics& graphics) {
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));

    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }

    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()));
    if (stroke_width != 0)
        graphics.DrawLines(&pen, point, static_cast<int>(p.size()));
    delete[] point;
}

VOID text::draw(Graphics& graphics) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wFontFamily = converter.from_bytes(font_family);
    FontFamily  fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, static_cast<REAL>(font_size), italic ? FontStyleItalic : FontStyleRegular, UnitPixel);
    PointF pointF(static_cast<REAL>(start.x), static_cast<REAL>(start.y - font_size));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    const wstring wstr = wstring(text_.begin(), text_.end());
    graphics.DrawString(wstr.c_str(), -1, &font, pointF, &fillBrush);
}

