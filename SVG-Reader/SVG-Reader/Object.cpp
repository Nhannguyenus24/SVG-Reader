#include "Object.h"


color readRGB(string value) {
    color colour;
    stringstream ss(value);
    string temp = "";
    getline(ss, temp, '(');
    getline(ss, temp, ',');
    colour.red = stoi(temp);
    getline(ss, temp, ',');
    colour.green = stoi(temp);
    getline(ss, temp, ')');
    colour.blue = stoi(temp);
    return colour;
}

void readLine(string name, string value, line& line) {
    if (name == "stroke-opacity") {
        line.strokeColor.alpha = stof(value);
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
        rect.fillColor.alpha = stof(value);
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
    else if (name == "stroke-opacity") {
        rect.strokeColor.alpha = stof(value);
    }
    if (rect.strokeColor.alpha == 0)
        rect.strokeColor.alpha = 1;
}

void readEllipse(string name, string value, ellipse& elli) {
    if (name == "fill-opacity") {
        elli.fillColor.alpha = stof(value);
    }
    else if (name == "stroke-opacity") {
        elli.strokeColor.alpha = stof(value);
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
        cir.fillColor.alpha = stof(value);
    }
    else if (name == "stroke-opacity") {
        cir.strokeColor.alpha = stof(value);
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

void read(string svgFileName, vector<line>& line_list, vector<rectangle>& rect_list, vector<ellipse>& elli_list, vector<circle>& cir_list) {
    ifstream file(svgFileName);
    if (!file.is_open()) {
        cerr << "Không thể mở tệp " << svgFileName << endl;
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
            line line;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readLine(attribute->name(), attribute->value(), line);
            }
            line_list.push_back(line);
        }
        else if (name == "rect") {
            rectangle rect;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readRectangle(attribute->name(), attribute->value(), rect);
            }
            rect_list.push_back(rect);
        }
        else if (name == "ellipse") {
            ellipse elli;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readEllipse(attribute->name(), attribute->value(), elli);
            }
            elli_list.push_back(elli);
        }
        else if (name == "circle") {
            circle cir;

            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                cout << "Attribute name: " << attribute->name() << ", Value: " << attribute->value() << endl;
                readCircle(attribute->name(), attribute->value(), cir);
            }
            cir_list.push_back(cir);
        }
    }
}
