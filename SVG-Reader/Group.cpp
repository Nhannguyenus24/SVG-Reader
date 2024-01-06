//Group.cpp contains the function read_file to read the svg file and return the shapes in the file
#include"Group.h"
vector<shape*> read_file(string file_name, float& max_width, float& max_height, defs& def, viewBox& vb) {
    vector<shape*> shapes;
    ifstream file(file_name);
    // Read and save the content of the file to a buffer as vector<char>
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0'); // adding null character at the end

    // Declaring document object
    xml_document<> doc;

    // Analyzing the buffer
    doc.parse<0>(&buffer[0]);

    // Get the root node of the XML file
    xml_node<>* root = doc.first_node("svg");
    // Get the attributes of the root node
    for (xml_attribute<>* attribute = root->first_attribute(); attribute; attribute = attribute->next_attribute()) {
        string attribute_name = attribute->name();
        string attribute_value = attribute->value();
        if (attribute_name == "viewBox") {
            vb.setViewBoxAttribute(attribute_value);
        }
        else if (attribute_name == "width") {
            if (attribute_value[attribute_value.length() - 1] == 'x')
                attribute_value = attribute_value.substr(0, attribute_value.length() - 2);
            vb.width = stof(attribute_value);
        }
        else if (attribute_name == "height") {
            if (attribute_value[attribute_value.length() - 1] == 'x')
                attribute_value = attribute_value.substr(0, attribute_value.length() - 2);
            vb.height = stof(attribute_value);
        }
    }
    max_width = 0, max_height = 0;
    //suppose that the default group is the whole svg image
    group g;
    g.traversal_group(root, max_width, max_height, shapes, def);
    for (int i = 0; i < def.rg_list.size(); i++) {
        if (def.rg_list[i].xlink_href != "") {
            string id = def.rg_list[i].xlink_href.substr(1);
            for (int j = 0; j < def.lg_list.size(); j++) {
                if (def.lg_list[j].id == id) {
                    def.rg_list[i].stop_list = def.lg_list[j].stop_list;
                    break;
                }
            }
        }
    }
    return shapes;
}

//function to read the attributes of the group node
void group::traversal_group(xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes, defs& def) {
    //handling null root
    if (!root)
		return;
    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        string name = node->name();
        // Get the attributes of the node by iterating over them and save them
        //get line attributes
        if (name == "line") {
            line* lin = new line();
            for (const auto& attribute : attributes) {
                read_line(attribute.first, attribute.second, lin);
            }

            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_line(attribute->name(), attribute->value(), lin);
            }
            shapes.push_back(lin);
        }
        //get rectangle attributes
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
            shapes.push_back(rect);
        }
        //get ellipse attributes
        else if (name == "ellipse") {
            ellipse* elli = new ellipse();
            for (const auto& attribute : attributes) {
                read_ellipse(attribute.first, attribute.second, elli);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_ellipse(attribute->name(), attribute->value(), elli);
            }
            shapes.push_back(elli);
        }
        //get circle attributes
        else if (name == "circle") {
            circle* cir = new circle();
            for (const auto& attribute : attributes) {
                read_circle(attribute.first, attribute.second, cir);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_circle(attribute->name(), attribute->value(), cir);
            }
            shapes.push_back(cir);
        }
        //get polygon attributes
        else if (name == "polygon") {
            polygon* polyg = new polygon();
            for (const auto& attribute : attributes) {
                read_polygon(attribute.first, attribute.second, polyg);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_polygon(attribute->name(), attribute->value(), polyg);
            }
            shapes.push_back(polyg);
        }
        //get polyline attributes
        else if (name == "polyline") {
            polyline* polyl = new polyline();
            for (const auto& attribute : attributes) {
                read_polyline(attribute.first, attribute.second, polyl);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_polyline(attribute->name(), attribute->value(), polyl);
            }
            shapes.push_back(polyl);
        }
        //get text attributes
        else if (name == "text") {
            text* tex = new text();
            for (const auto& attribute : attributes) {
                read_text(attribute.first, attribute.second, tex);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_text(attribute->name(), attribute->value(), tex);
            }
            tex->text_ = node->value();
            shapes.push_back(tex);
        }
        //get path attributes
        else if (name == "path") {
            Path* p = new Path();
            for (const auto& attribute : attributes) {
                read_path(attribute.first, attribute.second, p);
            }
            for (xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                read_path(attribute->name(), attribute->value(), p);
            }
            shapes.push_back(p);
        }
        //get group attributes
        else if (name == "g") {
            group new_group;
            for (const auto& attribute : this->attributes) {
                new_group.attributes[attribute.first] = attribute.second;
            }
            string transform = "transform";
            for (xml_attribute<>* attri = node->first_attribute(); attri; attri = attri->next_attribute()) {
                auto it = new_group.attributes.find(attri->name());
                if (it != new_group.attributes.end()) {

                    if (attri->name() == transform) { // bug when compare with "transform" instead of transform
                        new_group.attributes[attri->name()] = it->second + " " + attri->value();
                    }
                    else {
                        new_group.attributes[attri->name()] = attri->value();
                    }
                }
                else
                    new_group.attributes[attri->name()] = attri->value();
            }
            new_group.traversal_group(node, max_width, max_height, shapes, def);
        }
        //get defs attributes (contain linearGradient and radialGradient)
        else if (name == "defs") {
            for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
                string child_name = child->name();
                if (child_name == "linearGradient") {
                    linearGradient lg;
                    for (rapidxml::xml_attribute<>* attribute = child->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readLinearGradient(attribute->name(), attribute->value(), lg);
                    }
                    for (rapidxml::xml_node<>* grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                        string s = grandchild->name();
                        if (s == "stop") {
                            stop new_stop;
                            for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                                readStop(attribute->name(), attribute->value(), new_stop);
                            }
                            lg.stop_list.push_back(new_stop);
                        }
                    }
                    def.lg_list.push_back(lg);
                }
                else if (child_name == "radialGradient") {
                    radialGradient rg;
                    for (rapidxml::xml_attribute<>* attribute = child->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readRadialGradient(attribute->name(), attribute->value(), rg);
                    }
                    for (rapidxml::xml_node<>* grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                        string s = grandchild->name();
                        if (s == "stop") {
                            stop new_stop;
                            for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                                readStop(attribute->name(), attribute->value(), new_stop);
                            }
                            rg.stop_list.push_back(new_stop);
                        }
                    }
                    def.rg_list.push_back(rg);
                }

            }
        }
        //get linearGradient attributes
        else if (name == "linearGradient") {
            linearGradient lg;
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readLinearGradient(attribute->name(), attribute->value(), lg);
            }
            for (rapidxml::xml_node<>* grandchild = node->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                string s = grandchild->name();
                if (s == "stop") {
                    stop new_stop;
                    for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readStop(attribute->name(), attribute->value(), new_stop);
                    }
                    lg.stop_list.push_back(new_stop);
                }
            }
            def.lg_list.push_back(lg);
        }
        //get radialGradient attributes
        else if (name == "radialGradient") {
            radialGradient rg;
            for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                readRadialGradient(attribute->name(), attribute->value(), rg);
            }
            for (rapidxml::xml_node<>* grandchild = node->first_node(); grandchild; grandchild = grandchild->next_sibling()) {
                string s = grandchild->name();
                if (s == "stop") {
                    stop new_stop;
                    for (rapidxml::xml_attribute<>* attribute = grandchild->first_attribute(); attribute; attribute = attribute->next_attribute()) {
                        readStop(attribute->name(), attribute->value(), new_stop);
                    }
                    rg.stop_list.push_back(new_stop);
                }
            }
            def.rg_list.push_back(rg);
        }
    }
}

