//Path.h contains the class Path which inherits from shape and the function read_path
#ifndef PATH_H
#define PATH_H
#include"Shapes.h"
class Path : public shape {
public:
	string data;
	string linecap, linejoin;
	Path() {
		linecap = "butt";
		linejoin = "miter";
	}
	void read_single_point(string data, int& index, point& p);
	float read_single_point(string data, int& index);
	void draw(Graphics& graphics, defs def) override;
};

//read path function
void read_path(string name, string value, Path* path);
#endif // !PATH_H


