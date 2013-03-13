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

/*TODO:

?DA FARE? Cambiare formato G-Buffer:
	-1) INT   8  bit RGB : Colore				Alpha : Spec power
	-2) FLOAT 16 bit RGB : Normale				Alpha : Spec mult
	-3) FLOAT 32 bit	 : Profondità

IN PROGRESS: Primitivi e relative intersezioni:
	-cRay
	-cAABox
	-cFrustum
	-cSphere

Aggiustare pipeline deferred rendering:
	rendere cDeferredRenderer autonoma

TILED DEFERRED RENDERING:
	la cpu divide lo schermo in tiles
	per ognuno calcola le luci che lo influenzano
	tramite intersezione frustum sfera
	manda le luci allo shader lightpass

Possibile formato voxel:
short voxeldata;	2 byte


	
*/