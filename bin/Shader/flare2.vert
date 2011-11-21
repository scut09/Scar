uniform mat4 WorldViewProj;
uniform vec3 AbsPos;
uniform vec3 CameraPos;
uniform vec3 CameraDir;

varying float a;
 
void main()
{	
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	vec3 dir = normalize( AbsPos - CameraPos );
	a = dot( dir, CameraDir );
	a = ( a - 0.5 ) * 2;
	gl_Position = WorldViewProj * gl_Vertex;	
}