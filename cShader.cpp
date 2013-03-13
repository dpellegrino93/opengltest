#include "cShader.h"
using namespace std;


char* LeggiFile(const char *Filename) 
{
    char* Text;
    printf("- Caricamento file '%s' ...\n", Filename); 
    if (Filename != NULL) 
	{
        FILE *file = fopen(Filename, "rt");
        
        if (file != NULL) 
		{
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) 
			{
                Text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(Text, sizeof(char), count, file);
                Text[count] = '\0';
            }
            fclose(file);
        }
    }
	else
	{
		printf("\t*File '%s' non trovato.\n", Filename);
		return NULL;
	}
    return Text;
}


void validateShader(GLuint shader, const char* file = 0) 
{
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;
    
    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
        cerr << "Shader" << shader << " (" << (file?file:"") << ") compile error: " << buffer << endl;
    }
}

void validateProgram(GLuint program) 
{
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;
    
    memset(buffer, 0, BUFFER_SIZE);
    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
    if (length > 0)
        cerr << "Program " << program << " link error: " << buffer << endl;
    
    glValidateProgram(program);
    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE)
        cerr << "Error validating shader " << program << endl;
}



void cShader::Init(const char* fileVP, const char* fileFP)
{
	mShaderVP = glCreateShader(GL_VERTEX_SHADER);
	mShaderFP = glCreateShader(GL_FRAGMENT_SHADER);

	const char* TestoVP = LeggiFile(fileVP);
	const char* TestoFP = LeggiFile(fileFP);

	if (TestoVP == NULL || TestoFP == NULL) 
	{
        printf("\t*Errore nel caricamento degli shader.\n");
        return;
    }

	glShaderSource(mShaderVP, 1, &TestoVP, 0);
    glShaderSource(mShaderFP, 1, &TestoFP, 0);
	glCompileShader(mShaderVP);
	validateShader(mShaderVP, fileVP);
    glCompileShader(mShaderFP);
	validateShader(mShaderFP, fileFP);
	mShaderID = glCreateProgram();
    glAttachShader(mShaderID, mShaderFP);
    glAttachShader(mShaderID, mShaderVP);
    glLinkProgram(mShaderID);
	validateProgram(mShaderID);

}

unsigned int cShader::GetID()
{
	return mShaderID;
}


void cShader::Bind()
{
	glUseProgram(mShaderID);
}

void cShader::Unbind()
{
	glUseProgram(0);
}