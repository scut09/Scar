uniform mat4 WorldViewProj;
uniform vec3 SunNormal;

void main()
{	
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	gl_Position = WorldViewProj * gl_Vertex;
}