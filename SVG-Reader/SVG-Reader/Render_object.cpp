#include "Object.h"
//Visitor interface _ concrete visitors _ general shape's classes & methods
//path specific functions
void path::read_single_point(string data, int& index, point& p) {
    string n1 = "0", n2 = "0";
    bool s1 = false, s2 = false, accept = false;
    bool negative1 = false, negative2 = false;
    while (true) {
        if ((data[index] > '9' || data[index] < '0') && data[index] != '.') {
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
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
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

float path::read_single_point(string data, int& index) {
    string n = "0";
    bool s = false;
    bool negative = false;
    while (true) {
        if (data[index] == '-' && data[index + 1] <= '9' && data[index + 1] >= '0') {
            negative = true;
        }
        if (data[index] > '9' || data[index] < '0' && data[index] != '.') {
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
        if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
            n += data[index];
        }
        index++;
    }
}

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