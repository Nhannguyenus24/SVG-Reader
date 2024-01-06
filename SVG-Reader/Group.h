#ifndef GROUP_H
#define GROUP_H
#include"Path.h"
class group {
public:
	unordered_map<string, string> attributes;
	void traversal_group(rapidxml::xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes, defs& def);
};

vector<shape*> read_file(string file_name, float& max_width, float& max_height, defs& def, viewBox& vb);
#endif // !GROUP_H



