#include "OBJ.h"


void OBJModel::LoadOBJ(const char* Filename)
{
	printf("- Caricamento file modello '%s' ...\n",Filename);
	FILE* file;
	fopen_s(&file, Filename, "r");
	if (file==NULL)
	{
		printf("\t*File '%s' non trovato.\n", Filename);
		return;
	}
	char Riga[200];
	cVec3 TempPos;
	cVec3 TempNor;
	sTexCoord TempUV;
	OBJVertex TempVertDef[3];
	
	
	while(fgets(Riga,200,file)!=0)
	{
		if(Riga[0]=='v' && Riga[1] == ' ' && Riga[2] == ' ')
		{
			//Carica posizione vertici
			sscanf_s(Riga,"v  %f %f %f", &TempPos.X
									 , &TempPos.Y
									 , &TempPos.Z);
			inPosition.push_back(TempPos);
		}
		else if(Riga[0]=='v' && Riga[1] == 't' && Riga[2]==' ')
		{
			//Carica coordinate texture
			float W = 0;
			sscanf_s(Riga,"vt %f %f %f", &TempUV.U
							      , &TempUV.V, &W);
			inTexCoord.push_back(TempUV);
		}
		else if(Riga[0]=='v' && Riga[1] == 'n' && Riga[2]==' ')
		{
			//Carica Normali
			sscanf_s(Riga,"vn %f %f %f", &TempNor.X
									 , &TempNor.Y
									 , &TempNor.Z);
			inNormal.push_back(TempNor);
		}
		else if(Riga[0]=='f' && Riga[1]==' ')
		{
			//Carica definizioni vertici 3 alla volta
			sscanf_s(Riga,"f %d/%d/%d %d/%d/%d %d/%d/%d", &TempVertDef[0].Pos		//V1
													    , &TempVertDef[0].UV
													    , &TempVertDef[0].Nor
													    , &TempVertDef[1].Pos	//V2
													    , &TempVertDef[1].UV
													    , &TempVertDef[1].Nor
													    , &TempVertDef[2].Pos	//V3
													    , &TempVertDef[2].UV
													    , &TempVertDef[2].Nor  );
			inVertexDef.push_back(TempVertDef[0]);
			inVertexDef.push_back(TempVertDef[1]);
			inVertexDef.push_back(TempVertDef[2]);

		}
	}
	fclose(file);
	return;
};


bool OBJModel::CercaVerticeSimileMap( sVertex &Finito,
								std::map<sVertex,unsigned int> &MappaVerticiIndici,
								unsigned int &Risultato)
{
	std::map<sVertex,unsigned int>::iterator It = MappaVerticiIndici.find(Finito);
	if ( It == MappaVerticiIndici.end() )
	{
		return false;
    }
	else
	{
        Risultato = It->second;
        return true;
    }
}


int OBJModel::SetToMesh(cStaticMesh* Mesh)
{
	printf("\t*Calcolo indici...\n");
	unsigned int i;
	std::map<sVertex,unsigned int> MappaVerticiIndici;
        for ( i=0; i < inVertexDef.size(); i++ )
		{
                unsigned int Indice;
				sVertex Finito = sVertex(inPosition[inVertexDef[i].Pos-1], inNormal[inVertexDef[i].Nor-1], inTexCoord[inVertexDef[i].UV-1]);
                bool Trovato = CercaVerticeSimileMap(Finito, MappaVerticiIndici, Indice);
				

                if ( Trovato )
				{ 
                        outIndices.push_back( Indice );
                }
				else
				{ 
                        outVertices.push_back( inPosition[inVertexDef[i].Pos-1]);
                        outTexCoord.push_back( inTexCoord[inVertexDef[i].UV-1]);
                        outNormal.push_back( inNormal[inVertexDef[i].Nor-1]);
						unsigned int NuovoIndice = outVertices.size() - 1;
                        outIndices .push_back( NuovoIndice );
						sVertex nuovo = sVertex(inPosition[inVertexDef[i].Pos-1], inNormal[inVertexDef[i].Nor-1], inTexCoord[inVertexDef[i].UV-1]);
						outFiniti.push_back(nuovo);
                }
        }


	Mesh->SetData(outFiniti.data(), outFiniti.size(),	outIndices.data(), outIndices.size());
	
	int nFacce = outIndices.size()/3;

	printf("\t*Vertici :\t%d\n", outFiniti.size());
	printf("\t*Indici :\t%d\n", outIndices.size());
	printf("\t*Facce :\t%d\n", outIndices.size()/3);

	free(outFiniti.data());
	free(outIndices.data());
	free(inPosition.data());
	free(inTexCoord.data());
	free(inNormal.data());
	free(inVertexDef.data());
	free(outVertices.data());
	free(outTexCoord.data());
	free(outNormal.data());
	
	return nFacce;

}