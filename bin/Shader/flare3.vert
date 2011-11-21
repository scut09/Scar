uniform mat4 WorldViewProj;
uniform vec3 AbsPos;
uniform vec3 CameraPos;
uniform vec3 CameraDir;
void main()
{	
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	gl_Position = (WorldViewProj * gl_Vertex * vec4( .6, .5, 1.0, 1.0) );	
}