#version 120
varying vec3 normals;
varying vec4 position;


void main( void )
{
	gl_Position		= gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0]	= gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
	normals			= normalize( gl_NormalMatrix * gl_Normal);
	position		= gl_ModelViewMatrix * gl_Vertex;

}
