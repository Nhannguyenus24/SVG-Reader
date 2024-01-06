#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"BaseComponent.h"
class multi_transform {
public:
	vector<string> types;
	vector<float> values;
};

//for transform image to fit the screen
void transform_image(Graphics& graphics, float angle, float width, float height, float scroll_x, float scroll_y, float scale);
void read_transform(string value, multi_transform& tr);
void apply_transform(LinearGradientBrush& lgbrush, multi_transform trans);
#endif // !TRANSFORM_H

