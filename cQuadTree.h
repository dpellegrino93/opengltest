#ifndef CQUADTREE_H
#define CQUADTREE_H
/*
#include "main.h"
#include "sVertex-sTexCoord.h"
#include <vector>



class cQuadTreeNode
{
private:
	bool isLeaf;
	cQuadTreeNode* Parent;
	cQuadTreeNode* Child[4];			// 0---1	
	cVec3 Center;						// |   |
	float Radius;						// 2---3
	int Depth;
	cQuadTreeNode(){};

public:

	
	cQuadTreeNode(int depth, cVec3 center, float radius)
	{
		Child[0] = Child[1] = Child[2] = Child[3] = NULL;
		Depth = depth;
		if(Depth==0) isLeaf=true;
		else		 isLeaf=false;
		Center = center;
		Radius = radius;
	}

	bool CreateChildNode(short index)
	{
		if(Depth > 0)
		{
			if(index == 0)
				Child[0] = new cQuadTreeNode(Depth-1 , cVec3(Center.X-Radius, Center.Y, Center.Z-Radius) , Radius);	
			else if (index == 1)
				Child[1] = new cQuadTreeNode(Depth-1 , cVec3(Center.X+Radius, Center.Y, Center.Z-Radius) , Radius);
			else if (index == 2)
				Child[2] = new cQuadTreeNode(Depth-1 , cVec3(Center.X-Radius, Center.Y, Center.Z+Radius) , Radius);
			else if (index == 3)
				Child[3] = new cQuadTreeNode(Depth-1 , cVec3(Center.X+Radius, Center.Y, Center.Z+Radius) , Radius);
			else 
				return 0;

			return 1;
		}
		else
			return 0;
	}


};



class cQuadTree
{
private:
	cQuadTreeNode Root;
	cVec3 Center;
	float Radius;
	int maxDepth;

public:

	cQuadTree(){};
	cQuadTree( int maxdepth, cVec3 center, float radius)
	{
		Center = center;
		Radius = radius;
		maxDepth = maxdepth;
		Root = cQuadTreeNode(maxDepth, Center, Radius);
	}


};
*/


#endif

