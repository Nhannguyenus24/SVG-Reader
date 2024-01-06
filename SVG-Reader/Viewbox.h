#ifndef VIEWBOX_H
#define VIEWBOX_H
#include "Transform.h"
class viewBox {
public:
	float width, height, min_x, min_y;
	float width_viewbox, height_viewbox;
	viewBox()
	{
		width = 800;
		height = 600;
		min_x = 0;
		min_y = 0;
	}
	void setViewBoxAttribute(const string& viewBoxStr) {
		istringstream iss(viewBoxStr);
		iss >> min_x >> min_y >> width_viewbox >> height_viewbox;
	}
};
#endif // !VIEWBOX_H