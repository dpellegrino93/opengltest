#include "main.h"
#include "cVec3.h"
#include "sVertex-sTexCoord.h"
#include "cStaticMesh.h"
#include <vector>
#include <map>
#ifndef OBJ_H
#define OBJ_H


struct OBJVertex
{
	int Pos;
	int UV;
	int Nor;
	OBJVertex(){};
	OBJVertex(int inPosition, int inTexCoord, int normal)
	{
		Pos = inPosition;
		UV = inTexCoord;
		Nor = normal;
	};

	inline bool operator== (OBJVertex B)
	{
		return(Pos == B.Pos && UV == B.UV && Nor == B.Nor);
	}

	inline bool operator!= (OBJVertex B)
	{
		return(Pos != B.Pos || UV != B.UV || Nor != B.Nor);
	}


};


class OBJModel
{
private:
	std::vector<cVec3>			inPosition;			//Vettore posizioni vertici
	std::vector<sTexCoord>		inTexCoord;			//Vettore coordinate text vertici
	std::vector<cVec3>			inNormal;			//Vettore normali vertici
	std::vector<OBJVertex>		inVertexDef;

	std::vector<cVec3>			outVertices;
	std::vector<sTexCoord>		outTexCoord;		//Vettore coordinate text vertici
	std::vector<cVec3>			outNormal;			//Vettore normali vertici
	std::vector<unsigned int>   outIndices;
	std::vector<sVertex>		outFiniti;
public:
	OBJModel(){};
	bool CercaVerticeSimileMap( sVertex &Finito,
								std::map<sVertex,unsigned int> &MappaVerticiIndici,
								unsigned int &Risultato);
	void LoadOBJ(const char* Filename);	//SOLO LOADING IN OBJMODEL
	int SetToMesh(cStaticMesh* Mesh);	//SOLO CONVERSIONE INDICI E ASSEGNAZIONE

};


#endif