
uniform mat4 WorldViewProj;
vec3 LightDirection = vec3( -1.0, 0.0, 0.0 ); //uniform vec3 SunPosition;
uniform mat4 TransMatrix;
uniform vec3 AbsPos;
uniform vec3 CameraPos;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;

void main()
{
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	vec3 tangent = gl_MultiTexCoord1.xyz;
	vec3 binormal = gl_MultiTexCoord2.xyz;
	
	// Building the matrix Eye Space -> Tangent Space
	vec3 n = -normalize((TransMatrix * vec4(gl_NormalMatrix * gl_Normal, 0)).xyz);
	vec3 t = -normalize((TransMatrix * vec4(gl_NormalMatrix * tangent, 0)).xyz);
	vec3 b = -normalize((TransMatrix * vec4(gl_NormalMatrix * binormal, 0)).xyz);

	gl_Position = (WorldViewProj * gl_Vertex);
	vec3 lightDir = normalize(LightDirection);
		
		
	// transform light and half angle vectors by tangent basis
	vec3 v;
	v.x = dot (lightDir, t);
	v.y = dot (lightDir, b);
	v.z = dot (lightDir, n);
	lightVec = normalize (v);
}