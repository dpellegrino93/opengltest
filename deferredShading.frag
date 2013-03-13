#version 120
varying vec4		position;
varying vec3		normals;
uniform sampler2D	tDiffuse;

//Aggiungere normal mapping

void main( void )
{
	gl_FragData[0]		= vec4(texture2D(tDiffuse,gl_TexCoord[0].st).rgb, 0) + gl_Color;
	gl_FragData[1]		= position;
	gl_FragData[2]		= vec4(normals.xyz,0);
}
