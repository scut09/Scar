uniform mat4 WorldViewProj;
uniform vec3 AbsPos;
uniform vec3 SunNormal;

varying float NdotL;
 
void main()
{	
	vec3 L = SunNormal;
	vec3 N = normalize( gl_Vertex.xyz );
	NdotL = dot( L, N ) + 0.65;
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	gl_Position = WorldViewProj * gl_Vertex;	
}