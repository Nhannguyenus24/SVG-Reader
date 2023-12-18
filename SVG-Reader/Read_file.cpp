#include "Object.h"

//======================================= Reading area================================================================

color read_RGB(string value) {
    color colour;
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {

        stringstream ss(value);
        string temp = "";
        getline(ss, temp, '(');
        getline(ss, temp, ',');
        if (stof(temp) > 255)
            temp = "255";
        colour.red = stof(temp);
        getline(ss, temp, ',');
        if (stof(temp) > 255)
            temp = "255";
        colour.green = stof(temp);
        getline(ss, temp, ')');
        if (stof(temp) > 255)
            temp = "255";
        colour.blue = stof(temp);
    }
    else if (value[0] == '#') {
        unsigned int hexValue;
        if (value.length() == 4) {
			char a1 = value[1], a2 = value[2], a3 = value[3];
            value = "#" + string(1, a1) + string(1, a1) + string(1, a2) + string(1, a2) + string(1, a3) + string(1, a3);
		}   
        istringstream(value.substr(1)) >> hex >> hexValue;

        colour.red = (hexValue >> 16) & 0xFF;
        colour.green = (hexValue >> 8) & 0xFF;
        colour.blue = hexValue & 0xFF;
    }
    else {
        for (int i = 0; i < value.length(); i++) {
            if (value[i] >= 'A' && value[i] <= 'Z') {
				value[i] += 32; 
			}
		}
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
            if (s[i - 1] <= '9' && s[i - 1] >= '0' && ((s[i + 1] <= '9' && s[i + 1] >= '0') || s[i + 1] == '-') && s[i] != '.') {
                s[i] = ',';
                continue;
            }
            else if (s[i] != '.' && s[i] != '-') {
                s.erase(i, 1);
                i--;
            }
        }
    }
}

float clarifyFloat(string s) {
    if (s[0] == '.') {
        s.insert(0, "0");
    }
    return stof(s);
}

void readStop(string name, string value, stop* stop) {
    if (name == "stop-color") {
        stop->stop_color = read_RGB(value);
    }
    else if (name == "stop-opacity") {
        stop->stop_opacity = clarifyFloat(value);
    }
    else if (name == "offset") {
        stop->offset = clarifyFloat(value);
    }
}

void readLinearGradient(string name, string value, linearGradient* lg) {
    if (name == "id") {
        lg->id = value;
    }
    else if (name == "x1") {
        lg->start.x = stof(value);
    }
    else if (name == "x2") {
        lg->end.x = stof(value);
    }
    else if (name == "y1") {
        lg->start.y = stof(value);
    }
    else if (name == "y2") {
        lg->end.y = stof(value);
    }
    else if (name == "gradientTransform") {
        //read_transform(value, lg->trans);
    }
    else if (name == "gradientUnits") {
        lg->units = value;
    }
}

void readRadialGradient(string name, string value, radialGradient* rg) {
    if (name == "id") {
        rg->id = value;
    }
    else if (name == "cx") {
        rg->center.x = stof(value);
    }
    else if (name == "cy") {
        rg->center.y = stof(value);
    }
    else if (name == "r") {
        rg->r = stof(value);
    }
    else if (name == "xlink:href") {
        rg->xlink_href = value;
    }
    else if (name == "gradientTransform") {
        //read_transform(value, rg->trans);
    }
    else if (name == "gradientUnits") {
        rg->units = value;
    }
    else if (name == "fx") {
        rg->fx = stof(value);
    }
    else if (name == "fy") {
        rg->fy = stof(value);
    }
}


void read_transform(string value,  multi_transform& tr) {
    string temp = value;
    string vessel1 = "", vessel2 = "";
    bool change = true;
    remove_space(value);
    //value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
    for (int i = 0; i < value.length() - 1; i++) {
        if (value[i] == 't' && value[i + 1] == 'r') {
            tr.types.push_back("translate");
            if (value.find("translate") != string::npos)
            {
                stringstream ss(value.substr(value.find("translate") + 10));
                getline(ss, temp, ',');
                tr.values.push_back(stof(temp));
                getline(ss, temp, ')');
                tr.values.push_back(stof(temp));
                value = value.substr(value.find("translate") + 10);
            }
		}
        else if (value[i] == 's' && value[i + 1] == 'c') {
            tr.types.push_back("scale");
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
                if (vessel2.length() == 0) {
                    tr.values.push_back(stof(vessel1));
                    tr.values.push_back(stof(vessel1));
                }
                else {
                    tr.values.push_back(stof(vessel1));
                    tr.values.push_back(stof(vessel2));
                }
                value = value.substr(value.find("scale") + 6);
            }
        }
        else if (value[i] == 'r' && value[i + 1] == 'o') {
            tr.types.push_back("rotate");
            if (value.find("rotate") != string::npos) {
				stringstream ss(value.substr(value.find("rotate") + 7));
				getline(ss, temp, ')');
				tr.values.push_back(stof(temp));
                value = value.substr(value.find("rotate") + 7);
			}
		}
    }
}

vector<point> read_points(string value) {
    vector<point> points;

    // Xóa khoảng trắng ở đầu và cuối chuỗi
    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");

    stringstream ss(value);
    string temp = "";
    string pointStr;
    while (getline(ss, pointStr, ' ')) {
        point p;
        if (pointStr.find(',') == string::npos) {
            p.x = stof(pointStr);
            getline(ss, pointStr, ' ');
            p.y = stof(pointStr);
            points.push_back(p);
        }
        else {
            stringstream pointStream(pointStr);
            getline(pointStream, pointStr, ',');
            p.x = stof(pointStr);
            getline(pointStream, pointStr, ',');
            p.y = stof(pointStr);
            points.push_back(p);
        }
    }

    return points;
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
		else
			polygon->fill_color = read_RGB(value);
        polygon->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polygon->stroke_opacity = 0;
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
        else
            polyline->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			polyline->stroke_opacity = 0;
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
}

void read_line(string name, string value, line* line) {
    if (name == "stroke-opacity") {
        line->stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			line->stroke_opacity = 0;
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
        else 
            rect->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			rect->stroke_opacity = 0;
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
		else
            elli->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            elli->stroke_opacity = 0;
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
		else 
			cir->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			cir->stroke_opacity = 0;
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
}
void read_path(string name, string value, path* path) {
    if (name == "d") {
        path->data = value;
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
			path->stroke_opacity = 0;
		}
        else {
            path->stroke_color = read_RGB(value);
            if (path->stroke_width == 0)
                path->stroke_width = 1;
        }
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
            path->fill_color = read_RGB(value);
    }
    else if (name == "transform") {
		read_transform(value, path->trans);
	}
}
vector<shape*> read_file(string file_name, float& max_width, float& max_height) {
    vector<shape*> shapes;
    ifstream file(file_name);
    // Đọc nội dung của tệp vào một vector<char>
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0'); // Thêm ký tự kết thúc chuỗi

    // Khai báo một tài liệu XML để lưu trữ cấu trúc tệp SVG
    xml_document<> doc;

    // Phân tích nội dung tệp vào tài liệu XML
    doc.parse<0>(&buffer[0]);

    // Lấy nút gốc (root node) của tài liệu
    xml_node<>* root = doc.first_node("svg");
    max_width = 0, max_height = 0;
    group g;
    g.traversal_group(root, max_width, max_height, shapes);
    return shapes;
}

void group::traversal_group(xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes) {
    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        string name = node->name();
        if (name == "line") {
            line* lin = new line();
            for (const auto& attribute : attributes) {
				read_line(attribute.first, attribute.second, lin);
			}   
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_line(attribute->name(), attribute->value(), lin);
            }
            lin->get_max(max_width, max_height);
            shapes.push_back(lin);
        }
        else if (name == "rect") {
            rectangle* rect = new rectangle();
            for (const auto& attribute : attributes) {
                read_rectangle(attribute.first, attribute.second, rect);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                string attribute_name = attribute->name();
                string attribute_value = attribute->value();
                read_rectangle(attribute_name, attribute_value, rect);
            }
            rect->get_max(max_width, max_height);
            shapes.push_back(rect);
        }
        else if (name == "ellipse") {
            ellipse* elli = new ellipse();
            for (const auto& attribute : attributes) {
				read_ellipse(attribute.first, attribute.second, elli);
			}
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_ellipse(attribute->name(), attribute->value(), elli);
            }
            elli->get_max(max_width, max_height);
            shapes.push_back(elli);
        }
        else if (name == "circle") {
            circle* cir = new circle();
            for (const auto& attribute : attributes) {
                read_circle(attribute.first, attribute.second, cir);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_circle(attribute->name(), attribute->value(), cir);
            }
            cir->get_max(max_width, max_height);
            shapes.push_back(cir);
        }
        else if (name == "polygon") {
            polygon* polyg = new polygon();
            for (const auto& attribute : attributes) {
				read_polygon(attribute.first, attribute.second, polyg);
			}
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_polygon(attribute->name(), attribute->value(), polyg);
            }
            polyg->get_max(max_width, max_height);
            shapes.push_back(polyg);
        }
        else if (name == "polyline") {
            polyline* polyl = new polyline();
            for (const auto& attribute : attributes) {
                read_polyline(attribute.first, attribute.second, polyl);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_polyline(attribute->name(), attribute->value(), polyl);
            }
            polyl->get_max(max_width, max_height);
            shapes.push_back(polyl);
        }
        else if (name == "text") {
            text* tex = new text();
            for (const auto& attribute : attributes) {
				read_text(attribute.first, attribute.second, tex);
			}
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_text(attribute->name(), attribute->value(), tex);
            }
            tex->text_ = node->value();
            tex->get_max(max_width, max_height);
            shapes.push_back(tex);
        }
        else if (name == "path") {
            path* p = new path();
            for (const auto& attribute : attributes) {
				read_path(attribute.first, attribute.second, p);
			}
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
				read_path(attribute->name(), attribute->value(), p);
			}
			p->get_max(max_width, max_height);
			shapes.push_back(p);
        }
        else if (name == "g") {
            group new_group;
            for (const auto& attribute : this->attributes) {
                    new_group.attributes[attribute.first] = attribute.second;
            }
            string transform = "transform";
            for (xml_attribute<>* attri = node->first_attribute(); attri; attri = attri->next_attribute()) {
                auto it = new_group.attributes.find(attri->name());
                if (it != new_group.attributes.end()) {

                    if (attri->name() == transform){ // bug when compare with "transform" instead of transform
                        new_group.attributes[attri->name()] =  it->second + " " + attri->value();
                    }
                    else {
						new_group.attributes[attri->name()] = attri->value();
					}
				}
				else
				    new_group.attributes[attri->name()] = attri->value();
			}
			new_group.traversal_group(node, max_width, max_height, shapes);
		}
        else if (name == "defs") {
            defs new_defs;
            for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
                string child_name = child->name();
                if (child_name == "linearGradient") {
                    linearGradient* lg = new linearGradient;
                    for (rapidxml::xml_attribute<>* attribute = child->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readLinearGradient(attribute->name(), attribute->value(), lg);
                    }
                    for (rapidxml::xml_node<>* grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                        if (grandchild->name() == "stop") {
                            stop* new_stop = new stop;
                            for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                                readStop(attribute->name(), attribute->value(), new_stop);
                            }
                            lg->stop_list.push_back(new_stop);
                        }
                    }
                    new_defs.lg_list.push_back(lg);
                }
                else if (child_name == "radialGradient") {
                    radialGradient* rg = new radialGradient;
                    for (rapidxml::xml_attribute<>* attribute = child->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readRadialGradient(attribute->name(), attribute->value(), rg);
                    }
                    for (rapidxml::xml_node<>* grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                        if (grandchild->name() == "stop") {
                            stop* new_stop = new stop;
                            for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                                readStop(attribute->name(), attribute->value(), new_stop);
                            }
                            rg->stop_list.push_back(new_stop);
                        }
                    }
                    new_defs.rg_list.push_back(rg);
                }

            }
        }
    }
}

