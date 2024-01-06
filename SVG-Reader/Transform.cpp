//Transform.cpp contain defintion of functions related to transform attribute
#include"Transform.h"
void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale) {
    PointF center(static_cast<REAL>((width / 2 + scroll_x) * scale), static_cast<REAL>((height / 2 + scroll_y) * scale));

    // Áp dụng các biến đổi
    Matrix transformMatrix;
    transformMatrix.Translate(scroll_x, scroll_y); // Dịch chuyển trước
    transformMatrix.Scale(scale, scale);           // Sau đó thay đổi tỷ lệ
    transformMatrix.RotateAt(angle, center);       // Cuối cùng, xoay tại trọng tâm

    graphics.SetTransform(&transformMatrix);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
}
void read_transform(string value, multi_transform& tr) {
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
                tr.values.push_back(clarifyFloat(temp));
                getline(ss, temp, ')');
                tr.values.push_back(clarifyFloat(temp));
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
                    tr.values.push_back(clarifyFloat(vessel1));
                    tr.values.push_back(clarifyFloat(vessel1));
                }
                else {
                    tr.values.push_back(clarifyFloat(vessel1));
                    tr.values.push_back(clarifyFloat(vessel2));
                }
                value = value.substr(value.find("scale") + 6);
            }
        }
        else if (value[i] == 'r' && value[i + 1] == 'o') {
            tr.types.push_back("rotate");
            if (value.find("rotate") != string::npos) {
                stringstream ss(value.substr(value.find("rotate") + 7));
                getline(ss, temp, ')');
                tr.values.push_back(clarifyFloat(temp));
                value = value.substr(value.find("rotate") + 7);
            }
        }
        else if (value[i] == 'm' && value[i + 1] == 'a' && value[i + 2] == 't') {
            tr.types.push_back("translate");
            tr.types.push_back("scale");
            tr.types.push_back("rotate");
            string temp1, temp2, temp3, temp4, temp5;
            stringstream ss(value);
            getline(ss, temp, '(');
            getline(ss, temp, ',');
            getline(ss, temp1, ',');
            getline(ss, temp2, ',');
            getline(ss, temp3, ',');
            getline(ss, temp4, ',');
            getline(ss, temp5, ')');
            tr.values.push_back(clarifyFloat(temp));
            tr.values.push_back(clarifyFloat(temp1));
            tr.values.push_back(clarifyFloat(temp2));
            tr.values.push_back(clarifyFloat(temp3));
            tr.values.push_back(clarifyFloat(temp4));
            tr.values.push_back(clarifyFloat(temp5));
            break;
        }
    }
}
void apply_transform(LinearGradientBrush& lgbrush, multi_transform trans) {
    int index = 0;
    if (trans.types.size() == 0)
        return;
    if (trans.types.size() == 3) {
        Matrix matrix(trans.values[0], trans.values[1], trans.values[2], trans.values[3], trans.values[4], trans.values[5]);
        lgbrush.MultiplyTransform(&matrix, MatrixOrderAppend);
        return;
    }
    if (trans.types[0] == "translate") {
        lgbrush.TranslateTransform(trans.values[index], trans.values[index + 1], MatrixOrderAppend);
        return;
    }
    if (trans.types[0] == "rotate") {
        lgbrush.RotateTransform(trans.values[index], MatrixOrderAppend);
        return;
    }
    if (trans.types[0] == "scale") {
        lgbrush.ScaleTransform(trans.values[index], MatrixOrderAppend);
        return;
    }
}