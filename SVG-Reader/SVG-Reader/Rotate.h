#ifndef ROTATE_H
#define ROTATE_H

#include <cmath>
#include <vector>
using namespace std;

void rotateRight(vector<int>& x, vector<int>& y, int& max_length, int& max_height);
void rotateLeft(vector<int>& x, vector<int>& y, int& max_length, int& max_height);
void rotateR(int& x, int& y, int max_height);
void rotateL(int& x, int& y, int max_length);

#endif