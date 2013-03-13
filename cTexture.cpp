#include "cTexture.h"

unsigned int cTexture::GetID()
{
	return mTextureID;
}

void cTexture::CreateFromPPM(char* Filename)
{
	printf("- Caricamento file texture '%s' ...\n", Filename);
	FILE* file;
	fopen_s(&file,Filename,"rb");
	if(file==NULL)
	{
		printf("\t*File '%s' non trovato.\n", Filename);
		return;
	}
	unsigned char* data;
	unsigned int Width, Height;
	char Riga[LINE];

	fgets(Riga,LINE,file);
	if(Riga[1] != '6') return;

	do{
		fgets(Riga,LINE,file);
	}while(Riga[0] == '#');

	sscanf_s(Riga,"%d %d",&Width,&Height);

	data = new unsigned char[Width*Height*3];
	fseek(file,sizeof(unsigned char),SEEK_CUR); 
	fread(data,sizeof(unsigned char),Width*Height*3,file);
	fclose(file);

	glGenTextures( 1, &mTextureID );
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	printf("\t*Dimensione:\t%dx%d\n",Width,Height);
	free(data);
	return;
}