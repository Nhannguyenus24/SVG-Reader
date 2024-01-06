#include"Path.h"
//read path function
void read_path(string name, string value, Path* path) {
    if (name == "d") {
        path->data = value;
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            path->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            path->stroke_id = value.substr(5, value.length() - 6);
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
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            path->fill_id = value.substr(5, value.length() - 6);
        }
        else
            path->fill_color = read_RGB(value);
    }
    else if (name == "transform") {
        read_transform(value, path->trans);
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
            read_path(str1, str2, path);
        }
    }
}

//draw path functions
void Path::read_single_point(string data, int& index, point& p) {
    string n1 = "0", n2 = "0";
    bool s1 = false, s2 = false, accept = false;
    bool negative1 = false, negative2 = false;
    while (true) {
        //check if the index is out of range
        if ((data[index] > '9' || data[index] < '0') && data[index] != '.' && data[index] != 'e') {
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
        else if (data[index] == '.' && s1 == false && s2 == false && accept == false) {
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
        else if (data[index] == '.' && s1 == true && n1.find('.') != string::npos) {
            n2 += data[index];
            s2 = true;
            if (data[index - 1] == '-') {
                negative2 = true;
            }
            index++;
            s1 = false;
            accept = true;
            continue;
        }
        else if (data[index] == '.' && s1 == false && accept == true && s2 == false) {
            n2 += data[index];
            s2 = true;
            if (data[index - 1] == '-') {
                negative2 = true;
            }
            index++;
            s1 = false;
            accept = true;
            continue;
        }
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.' || data[index] == 'e') {
            if (s1) {
                if (data[index] == 'e') {
                    n1 += data[index];
                    n1 += data[index + 1];
                    index += 2;
                    continue;
                }
                n1 += data[index];
            }
            if (s2) {
                if (data[index] == 'e') {
                    n2 += data[index];
                    n2 += data[index + 1];
                    index += 2;
                    continue;
                }
                if (data[index] == '.' && n2.find('.') != string::npos) {
                    p.x = stof(n1);
                    p.y = stof(n2);
                    if (negative1)
                        p.x *= -1;
                    if (negative2)
                        p.y *= -1;
                    return;
                }
                else
                    n2 += data[index];
            }
        }
        index++;
    }
}

float Path::read_single_point(string data, int& index) {
    string n = "0";
    bool s = false;
    bool negative = false;
    while (true) {
        if (data[index] == '-' && data[index + 1] <= '9' && data[index + 1] >= '0' && n == "0") {
            negative = true;
        }
        if ((data[index] > '9' || data[index] < '0') && data[index] != '.' && data[index] != 'e') {
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
            if (data[index - 1] == '-') {
                negative = true;
            }
            index++;
            continue;
        }
        else if (data[index] == '.' && s == false) {
            n += data[index];
            if (data[index - 1] == '-') {
                negative = true;
            }
            s = true;
            index++;
            continue;
        }
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.' || data[index] == 'e') {
            if (data[index] == 'e') {
                n += data[index];
                n += data[index + 1];
                index += 2;
                continue;
            }
            n += data[index];
        }
        index++;
    }
}

void Path::draw(Graphics& graphics, defs def) {
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
    point d1, d2, d, d3, r;
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
        command_A:
            read_single_point(data, index, r);
            float rotation = read_single_point(data, ++index);
            float large_arc = read_single_point(data, ++index);
            float sweep = read_single_point(data, ++index);
            read_single_point(data, ++index, d);
            float angle = rotation * 3.14159265358979323846 / 180.0f;
            float cos_angle = cos(angle);
            float sin_angle = sin(angle);
            float cons = cos_angle * cos_angle - (sin_angle * -sin_angle);
            d1.x = cons * (current_point.x - d.x) / 2.0f;
            d1.y = cons * (current_point.y - d.y) / 2.0f;
            float check_r = (d1.x * d1.x) / (r.x * r.x) + (d1.y * d1.y) / (r.y * r.y);
            if (check_r > 1.0f) {
                r.x *= sqrt(check_r);
                r.y *= sqrt(check_r);
            }
            int sign = (large_arc == sweep) ? -1 : 1;
            float num = abs(r.x * r.x * r.y * r.y - r.x * r.x * d1.y * d1.y - r.y * r.y * d1.x * d1.x);
            float den = r.x * r.x * d1.y * d1.y + r.y * r.y * d1.x * d1.x;
            d2.x = sign * sqrt(num / den) * r.x * d1.y / r.y;
            d2.y = sign * sqrt(num / den) * -r.y * d1.x / r.x;
            cons = cos_angle * cos_angle - (sin_angle * -sin_angle);
            d3.x = cons * d2.x + (current_point.x + d.x) / 2.0f;
            d3.y = cons * d2.y + (current_point.y + d.y) / 2.0f;
            float angle1 = atan2((d1.y - d2.y) / r.y, (d1.x - d2.x) / r.x);
            float angle2 = atan2((-d2.y - d1.y) / r.y, (-d2.x - d1.x) / r.x);
            float delta_angle = angle2 - angle1;
            if (sweep == 0 && delta_angle > 0) {
                delta_angle -= 2 * 3.14159265358979323846;
            }
            else if (sweep == 1 && delta_angle < 0) {
                delta_angle += 2 * 3.14159265358979323846;
            }
            path.AddArc(d3.x - r.x, d3.y - r.y, 2 * r.x, 2 * r.y, fmod((long double)(angle1 * 180.0f) / 3.14159265358979323846, 360), fmod((long double)(delta_angle * 180.0f) / 3.14159265358979323846, 360));
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'A';
        }
        else if (data[index] == 'a') {
        command_a:
            read_single_point(data, index, r);
            float rotation = read_single_point(data, ++index);
            float large_arc = read_single_point(data, ++index);
            float sweep = read_single_point(data, ++index);
            read_single_point(data, ++index, d);
            d.x += current_point.x;
            d.y += current_point.y;
            float angle = rotation * 3.14159265358979323846 / 180.0f;
            float cos_angle = cos(angle);
            float sin_angle = sin(angle);
            float cons = cos_angle * cos_angle - (sin_angle * -sin_angle);
            d1.x = cons * (current_point.x - d.x) / 2.0f;
            d1.y = cons * (current_point.y - d.y) / 2.0f;
            float check_r = (d1.x * d1.x) / (r.x * r.x) + (d1.y * d1.y) / (r.y * r.y);
            if (check_r > 1.0f) {
                r.x *= sqrt(check_r);
                r.y *= sqrt(check_r);
            }
            int sign = (large_arc == sweep) ? -1 : 1;
            float num = abs(r.x * r.x * r.y * r.y - r.x * r.x * d1.y * d1.y - r.y * r.y * d1.x * d1.x);
            float den = r.x * r.x * d1.y * d1.y + r.y * r.y * d1.x * d1.x;
            d2.x = sign * sqrt(num / den) * r.x * d1.y / r.y;
            d2.y = sign * sqrt(num / den) * -r.y * d1.x / r.x;
            cons = cos_angle * cos_angle - (sin_angle * -sin_angle);
            d3.x = cons * d2.x + (current_point.x + d.x) / 2.0f;
            d3.y = cons * d2.y + (current_point.y + d.y) / 2.0f;
            float angle1 = atan2((d1.y - d2.y) / r.y, (d1.x - d2.x) / r.x);
            float angle2 = atan2((-d2.y - d1.y) / r.y, (-d2.x - d1.x) / r.x);
            float delta_angle = angle2 - angle1;
            if (sweep == 0 && delta_angle > 0) {
                delta_angle -= 2 * 3.14159265358979323846;
            }
            else if (sweep == 1 && delta_angle < 0) {
                delta_angle += 2 * 3.14159265358979323846;
            }
            path.AddArc(d3.x - r.x, d3.y - r.y, 2 * r.x, 2 * r.y, fmod((long double)(angle1 * 180.0f) / 3.14159265358979323846, 360), fmod((long double)(delta_angle * 180.0f) / 3.14159265358979323846, 360));
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'a';
        }
        else if (data[index] == 'q') {
        command_q:
            read_single_point(data, index, d1);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'q';
        }
        else if (data[index] == 'Q') {
        command_Q:
            read_single_point(data, index, d1);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d1.x, d1.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'Q';
        }
        else if (data[index] == 's') {
        command_s:
            read_single_point(data, index, d3);
            read_single_point(data, index, d);
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
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, current_point.x + d3.x, current_point.y + d3.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            d2.x = d3.x + current_point.x;
            d2.y = d3.y + current_point.y;
            last_command = 's';
        }
        else if (data[index] == 'S') {
        command_S:
            read_single_point(data, index, d3);
            read_single_point(data, index, d);
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
            read_single_point(data, index, d1);
            read_single_point(data, index, d2);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d2.x, current_point.y + d2.y, current_point.x + d.x, current_point.y + d.y);
            d2.x += current_point.x;
            d2.y += current_point.y;
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'c';
        }
        else if (data[index] == 'C') {
        command_C:
            read_single_point(data, index, d1);
            read_single_point(data, index, d2);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d2.x, d2.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'C';
        }
        else if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
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
            case 'a':
                goto command_a;
                break;
            case 'A':
                goto command_A;
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
    if (fill_id != "") {
        for (int i = 0; i < def.lg_list.size(); i++) {
            if (fill_id == def.lg_list[i].id) {
                float* points = def.lg_list[i].get_point_list();
                Color* colors = def.lg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.lg_list[i].start.x, def.lg_list[i].start.y), PointF(def.lg_list[i].end.x, def.lg_list[i].end.y), colors[0], colors[def.lg_list[i].stop_list.size() - 1]);
                apply_transform(linGrBrush, def.lg_list[i].trans);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i].stop_list.size());
                graphics.FillPath(&linGrBrush, &path);
                delete[] points;
                delete[] colors;
                goto Draw;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.rg_list[i].stop_list.size());
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillPath(&linGrBrush, &path);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillPath(&fillBrush, &path);
    }
Draw:
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}
