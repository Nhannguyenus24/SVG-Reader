//Shapes_Render.cpp contains the definitions of the methods of Shape class hierarchy to render the shapes on the graphics object.
#include"Shapes.h"
//in terms of holding Gradient, all the information of radial gradient is passed as linear gradient to process
VOID line::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
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
    graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
    graphics.Restore(save);
}

VOID rectangle::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    int index = 0;
    //apply transformations
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
    //apply gradient
    if (fill_id != "") {
        for (int i = 0; i < def.lg_list.size(); i++) {
            if (fill_id == def.lg_list[i].id) {
                float* points = def.lg_list[i].get_point_list();
                Color* colors = def.lg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.lg_list[i].start.x, def.lg_list[i].start.y), PointF(def.lg_list[i].end.x, def.lg_list[i].end.y), colors[0], colors[def.lg_list[i].stop_list.size() - 1]);
                apply_transform(linGrBrush, def.lg_list[i].trans);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i].stop_list.size());
                graphics.FillRectangle(&linGrBrush, start.x, start.y, width, height);
                delete[] points;
                delete[] colors;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillRectangle(&linGrBrush, start.x, start.y, width, height);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillRectangle(&fillBrush, start.x, start.y, width, height);
    }
    if (stroke_width != 0)
        graphics.DrawRectangle(&pen, start.x, start.y, width, height);
    graphics.Restore(save);
}

VOID circle::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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
    if (fill_id != "") {
        for (int i = 0; i < def.lg_list.size(); i++) {
            if (fill_id == def.lg_list[i].id) {
                float* points = def.lg_list[i].get_point_list();
                Color* colors = def.lg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.lg_list[i].start.x, def.lg_list[i].start.y), PointF(def.lg_list[i].end.x, def.lg_list[i].end.y), colors[0], colors[def.lg_list[i].stop_list.size() - 1]);
                apply_transform(linGrBrush, def.lg_list[i].trans);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i].stop_list.size());
                graphics.FillEllipse(&linGrBrush, start.x - r, start.y - r, 2 * r, 2 * r);
                delete[] points;
                delete[] colors;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillEllipse(&linGrBrush, start.x - r, start.y - r, 2 * r, 2 * r);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillEllipse(&fillBrush, start.x - r, start.y - r, 2 * r, 2 * r);
    }
    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - r, start.y - r, 2 * r, 2 * r);
    graphics.Restore(save);
}


VOID ellipse::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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
    if (fill_id != "") {
        for (int i = 0; i < def.lg_list.size(); i++) {
            if (fill_id == def.lg_list[i].id) {
                float* points = def.lg_list[i].get_point_list();
                Color* colors = def.lg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.lg_list[i].start.x, def.lg_list[i].start.y), PointF(def.lg_list[i].end.x, def.lg_list[i].end.y), colors[0], colors[def.lg_list[i].stop_list.size() - 1]);
                apply_transform(linGrBrush, def.lg_list[i].trans);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i].stop_list.size());
                graphics.FillEllipse(&linGrBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
                delete[] points;
                delete[] colors;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillEllipse(&linGrBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillEllipse(&fillBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
    }
    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
    graphics.Restore(save);
}


VOID polygon::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
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
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
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
                graphics.FillPolygon(&linGrBrush, point, static_cast<int>(p.size()), FillModeWinding);
                delete[] points;
                delete[] colors;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillPolygon(&linGrBrush, point, static_cast<int>(p.size()), FillModeWinding);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);
    }
    if (stroke_width != 0)
        graphics.DrawPolygon(&pen, point, static_cast<int>(p.size()));
    delete[] point;
    graphics.Restore(save);
}


VOID polyline::draw(Graphics& graphics, defs def) {
    GraphicsState save = graphics.Save();
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
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    if (fill_id != "") {
        for (int i = 0; i < def.lg_list.size(); i++) {
            if (fill_id == def.lg_list[i].id) {
                float* points = def.lg_list[i].get_point_list();
                Color* colors = def.lg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.lg_list[i].start.x, def.lg_list[i].start.y), PointF(def.lg_list[i].end.x, def.lg_list[i].end.y), colors[0], colors[def.lg_list[i].stop_list.size() - 1]);
                apply_transform(linGrBrush, def.lg_list[i].trans);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                linGrBrush.SetInterpolationColors(colors, points, def.lg_list[i].stop_list.size());
                graphics.FillPolygon(&linGrBrush, point, static_cast<int>(p.size()), FillModeWinding);
                delete[] points;
                delete[] colors;
                break;
            }
        }
        for (int i = 0; i < def.rg_list.size(); i++) {
            if (fill_id == def.rg_list[i].id) {
                float* points = def.rg_list[i].get_point_list();
                Color* colors = def.rg_list[i].get_color_list();
                LinearGradientBrush linGrBrush(PointF(def.rg_list[i].center.x - def.rg_list[i].r, def.rg_list[i].center.y - def.rg_list[i].r), PointF(def.rg_list[i].center.x + def.rg_list[i].r, def.rg_list[i].center.y + def.rg_list[i].r), colors[0], colors[def.rg_list[i].stop_list.size() - 1]);
                linGrBrush.SetWrapMode(WrapModeTileFlipXY);
                apply_transform(linGrBrush, def.rg_list[i].trans);
                graphics.FillPolygon(&linGrBrush, point, static_cast<int>(p.size()), FillModeWinding);
                delete[] points;
                delete[] colors;
                break;
            }
        }
    }
    else {
        graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);
    }
    if (stroke_width != 0)
        graphics.DrawLines(&pen, point, static_cast<int>(p.size()));
    delete[] point;
    graphics.Restore(save);
}


VOID text::draw(Graphics& graphics, defs def) {
    for (int i = 0; i < text_.length(); i++) {
        if (text_[i] == '\n') {
            text_[i] = ' ';
        }
        if (text_[i] == ' ' && text_[i + 1] == ' ') {
            text_.erase(i, 1);
            i--;
        }
    }
    float rate = 0;
    GraphicsState save = graphics.Save();
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
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    wstring wFontFamily = converter.from_bytes(font_family);

    FontFamily fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, static_cast<REAL>(font_size), italic ? FontStyleItalic : FontStyleRegular, UnitPixel);

    StringFormat stringFormat; // Create a StringFormat object with the each line of text, and the block
    if (text_anchor == "middle") {
        stringFormat.SetAlignment(StringAlignmentCenter); // Center alignment
    }
    else if (text_anchor == "end") {
        stringFormat.SetAlignment(StringAlignmentFar); // Right and center alignment
        rate = 0.15;
    }
    else
    {
        stringFormat.SetAlignment(StringAlignmentNear); // Left and center alignment
        rate = -0.15;
    }
    PointF pointF(static_cast<REAL>(start.x + dx + rate * font_size), static_cast<REAL>(start.y + dy - 0.9 * font_size));
    // Create a GraphicsPath
    GraphicsPath path;

    // Add the string to the path
    const wstring wstr = wstring(text_.begin(), text_.end());
    path.AddString(wstr.c_str(), -1, &fontFamily, italic ? FontStyleItalic : FontStyleRegular, static_cast<REAL>(font_size), pointF, &stringFormat);

    // Create a solid brush for filling
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    // Fill the path with the solid brush
    graphics.FillPath(&fillBrush, &path);
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}