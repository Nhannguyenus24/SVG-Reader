#include"BaseComponent.h"
string trim(string str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
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
            if (s[i - 1] <= '9' && s[i - 1] >= '0' && ((s[i + 1] <= '9' && s[i + 1] >= '0') || s[i + 1] == '-' || s[i + 1] == '.') && s[i] != '.') {
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
    if (s[0] == '-' && s[1] == '.') {
        s.insert(1, "0");
    }
    if (s[s.length() - 1] == '%') {
        string str = s.substr(0, s.length() - 1);
        return stof(str) / 100;
    }
    return stof(s);
}

//read color funtion
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

//read point function
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