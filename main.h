#pragma once

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <exception>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include "cVec3.h"


#define PI      3.14159265358979323846
#define PId180	0.0174532925199432957692

#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define ABS(a)  (((a) >=  0)  ? (a) : (-a))
