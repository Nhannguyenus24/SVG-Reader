//Gradient.cpp contains functions for reading and rendering gradients in detail.
#include"Gradient.h"
//read function
void readStop(string name, string value, stop& stop) {
    if (name == "stop-color") {
        stop.stop_color = read_RGB(value);
    }
    else if (name == "stop-opacity") {
        stop.stop_opacity = clarifyFloat(value);
    }
    else if (name == "offset") {
        stop.offset = clarifyFloat(value);
    }
}

void readLinearGradient(string name, string value, linearGradient& lg) {
    if (name == "id") {
        lg.id = value;
    }
    else if (name == "x1") {
        if (value[value.length() - 1] == '%') {
            lg.percentage = true;
            lg.start.x = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else {
            lg.start.x = stof(value);
        }
    }
    else if (name == "x2") {
        if (value[value.length() - 1] == '%') {
            lg.end.x = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else
            lg.end.x = stof(value);
    }
    else if (name == "y1") {
        if (value[value.length() - 1] == '%') {
            lg.start.y = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else
            lg.start.y = stof(value);
    }
    else if (name == "y2") {
        if (value[value.length() - 1] == '%') {
            lg.end.y = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else
            lg.end.y = stof(value);
    }
    else if (name == "gradientTransform") {
        read_transform(value, lg.trans);
    }
    else if (name == "gradientUnits") {
        lg.units = value;
    }
}

void readRadialGradient(string name, string value, radialGradient& rg) {
    if (name == "id") {
        rg.id = value;
    }
    else if (name == "cx") {
        rg.center.x = stof(value);
    }
    else if (name == "cy") {
        rg.center.y = stof(value);
    }
    else if (name == "r") {
        rg.r = stof(value);
    }
    else if (name == "xlink:href") {
        rg.xlink_href = value;
    }
    else if (name == "gradientTransform") {
        read_transform(value, rg.trans);
    }
    else if (name == "gradientUnits") {
        rg.units = value;
    }
    else if (name == "fx") {
        rg.fx = stof(value);
    }
    else if (name == "fy") {
        rg.fy = stof(value);
    }
}

//render gradient functions
float* Gradient::get_point_list() {
    int size = stop_list.size();
    if (stop_list[0].offset != 0) {
        size++;
    }
    if (stop_list[stop_list.size() - 1].offset != 1) {
        size++;
    }

    float* points = new float[size];
    if (stop_list[0].offset != 0) {
        points[0] = 0;
    }
    if (stop_list[stop_list.size() - 1].offset != 1) {
        points[size - 1] = 1.0f;
    }

    //get points
    for (int j = 0; j < stop_list.size(); j++) {
        if (stop_list[0].offset != 0) {
            points[j + 1] = stop_list[j].offset;
        }
        else
            points[j] = stop_list[j].offset;
    }
    return points;
}

//cast color list to Color* for render
Color* Gradient::get_color_list() {
    Color* colors = new Color[stop_list.size()];
    for (int j = 0; j < stop_list.size(); j++) {
        //
        colors[j] = Color(static_cast<float>(stop_list[j].stop_opacity * 255), stop_list[j].stop_color.red, stop_list[j].stop_color.green, stop_list[j].stop_color.blue);
    }
    return colors;
}