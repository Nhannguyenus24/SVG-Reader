#include "Object.h"


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

void seperatePoints(vector<point> points, vector<int>& xP, vector<int>& yP) {
    for (int i = 0; i < points.size(); i++) {
        xP.push_back(points[i].x);
        yP.push_back(points[i].y);
    }
}

void readPolygon(string name, string value, polygon& polygon) {
    if (name == "fill-opacity") {
        polygon.fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polygon.stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        polygon.fillColor = readRGB(value);
    }
    else if (name == "stroke") {
        polygon.strokeColor = readRGB(value);
    }
    else if (name == "stroke-width") {
        polygon.strokeWidth = stoi(value);
    }
    else if (name == "points") {
        vector<point> points = readPoints(value);
        seperatePoints(points, polygon.xP, polygon.yP);
    }
}

void readPolyline(string name, string value, polyline& polyline) {
    if (name == "fill-opacity") {
        polyline.fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polyline.stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        polyline.fillColor = readRGB(value);
    }
    else if (name == "stroke") {
        polyline.strokeColor = readRGB(value);
    }
    else if (name == "stroke-width") {
        polyline.strokeWidth = stoi(value);
    }
    else if (name == "points") {
        vector<point> points = readPoints(value);
        seperatePoints(points, polyline.xP, polyline.yP);
    }
}

void readText(string name, string value, text& text) {
    if (name == "x") {
        text.x = stoi(value);
    }
    else if (name == "y") {
        text.y = stoi(value);
    }
    else if (name == "font-size") {
        text.font_size = stoi(value);
    }
    else if (name == "fill") {
        text.fillColor = readRGB(value);
    }
}

void readLine(string name, string value, line& line) {
    if (name == "stroke-opacity") {
        line.stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        line.strokeColor = readRGB(value);
    }
    else if (name == "x1") {
        line.start.x = stoi(value);
    }
    else if (name == "y1") {
        line.start.y = stoi(value);
    }
    else if (name == "x2") {
        line.end.x = stoi(value);
    }
    else if (name == "y2") {
        line.end.y = stoi(value);
    }
    else if (name == "stroke-width") {
        line.strokeWidth = stoi(value);
    }
    else if (name == "stroke") {
        line.strokeColor = readRGB(value);
    }
}

void readRectangle(string name, string value, rectangle& rect) {
    if (name == "fill-opacity") {
        rect.fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        rect.stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        rect.fillColor = readRGB(value);
    }
    else if (name == "stroke") {
        rect.strokeColor = readRGB(value);
    }
    else if (name == "x") {
        rect.start.x = stoi(value);
    }
    else if (name == "y") {
        rect.start.y = stoi(value);
    }
    else if (name == "width") {
        rect.width = stoi(value);
    }
    else if (name == "height") {
        rect.height = stoi(value);
    }
    else if (name == "stroke-width") {
        rect.strokeWidth = stoi(value);
    }
}

void readEllipse(string name, string value, ellipse& elli) {
    if (name == "fill-opacity") {
        elli.fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        elli.stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        elli.fillColor = readRGB(value);
    }
    else if (name == "stroke") {
        elli.strokeColor = readRGB(value);
    }
    else if (name == "cx") {
        elli.center.x = stoi(value);
    }
    else if (name == "cy") {
        elli.center.y = stoi(value);
    }
    else if (name == "rx") {
        elli.rx = stoi(value);
    }
    else if (name == "ry") {
        elli.ry = stoi(value);
    }
    else if (name == "stroke-width") {
        elli.strokeWidth = stoi(value);
    }
}

void readCircle(string name, string value, circle& cir) {
    if (name == "fill-opacity") {
        cir.fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        cir.stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        cir.fillColor = readRGB(value);
    }
    else if (name == "stroke") {
        cir.strokeColor = readRGB(value);
    }
    else if (name == "cx") {
        cir.center.x = stoi(value);
    }
    else if (name == "cy") {
        cir.center.y = stoi(value);
    }
    else if (name == "r") {
        cir.r = stoi(value);
    }
    else if (name == "stroke-width") {
        cir.strokeWidth = stoi(value);
    }
}

void read(string svgFileName, vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list, vector<polygon>& polyg_list, vector<polyline>& polyl_list, vector<text>& text_list) {
    ifstream file(svgFileName);
    if (!file.is_open()) {
        cerr << "Không thể mở tệp " << svgFileName << endl;
    }
    int ordi = 1;
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
            line line;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readLine(attribute->name(), attribute->value(), line);
            }
            line.ordinal = ordi;
            line_list.push_back(line);
        }
        else if (name == "rect") {
            rectangle rect;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                string attribute_name = attribute->name();
                string attribute_value = attribute->value();
                readRectangle(attribute_name, attribute_value, rect);
            }
            rect.ordinal = ordi;
            rect_list.push_back(rect);
        }
        else if (name == "ellipse") {
            ellipse elli;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readEllipse(attribute->name(), attribute->value(), elli);
            }
            elli.ordinal = ordi;
            elli_list.push_back(elli);
        }
        else if (name == "circle") {
            circle cir;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readCircle(attribute->name(), attribute->value(), cir);
            }
            cir.ordinal = ordi;
            cir_list.push_back(cir);
        }
        else if (name == "polygon") {
            polygon polyg;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readPolygon(attribute->name(), attribute->value(), polyg);
            }
            polyg.ordinal = ordi;
            polyg_list.push_back(polyg);
        }
        else if (name == "polyline") {
            polyline polyl;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readPolyline(attribute->name(), attribute->value(), polyl);
            }
            polyl.ordinal = ordi;
            polyl_list.push_back(polyl);
        }
        else if (name == "text") {
            text text;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readText(attribute->name(), attribute->value(), text);
            }
            text.text_ = node->value();
            text.ordinal = ordi;
            text_list.push_back(text);
        }
        ordi++;
    }
}
