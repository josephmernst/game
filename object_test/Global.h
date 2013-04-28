#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <vector>
#include "MainWindow.h"
using namespace std;
vector<double> screen_to_world(int x, int y, float depth);
bool gluInvertMatrix(const double m[16], double invOut[16]);
#endif
