#version 120
uniform sampler2D tDiffuse; 
uniform sampler2D tPosition;
uniform sampler2D tNormals;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 lightAtt;

void main( void )
{ 
	vec4 image		= texture2D( tDiffuse, gl_TexCoord[0].xy );
	vec4 position	= texture2D( tPosition, gl_TexCoord[0].xy );
	vec4 normal		= texture2D( tNormals, gl_TexCoord[0].xy );


	vec4 light		= vec4(lightPosition,0);
	vec4 lightDir	= light - position;
	float dist		= length(lightDir);
	float att		= 1000/(lightAtt[0]+lightAtt[1]*dist+lightAtt[2]*dist*dist);

	normal			= normalize(normal);
	lightDir		= normalize(lightDir);
	
	vec4 eyeDir		= normalize(-position);
	vec4 HalfVector = normalize(lightDir+eyeDir);

	gl_FragColor	= att * vec4(lightColor,1.0) * (max(dot(normal,lightDir),0) * image + pow(max( dot(normal,HalfVector), 0.0), 80)*0.2  );

}
