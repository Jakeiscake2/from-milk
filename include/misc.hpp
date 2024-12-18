#pragma once
#include "global.hpp"
#include "misc.hpp"

extern void displayToScreen(std::string);
extern void resetScreen();
extern void checkUnplugged();

extern float getAvg(std::vector<double> vals);
extern float reduce0To360(float angle);
extern float reduce360To360(float angle);
extern float reduce180To180(float angle);
extern float sgn(float val);

extern void debugFunc(void *param);