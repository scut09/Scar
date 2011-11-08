
uniform mat4 WorldViewProj;
vec3 LightDirection = vec3( -0.6, 1, 1.4 );
uniform mat4 InvWorld;
uniform mat4 TransWorld;
uniform mat4 TransMatrix;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main()
{
	gl_Position = WorldViewProj * gl_Vertex;


	// ����ɢ���
	vec4 N = normalize( TransMatrix * vec4(gl_Normal, 0.0));
	vec4 L = vec4( LightDirection, 0.0 );
	float NdotL = dot(N, L);
	DiffLight = vec4(max(0.0, NdotL));
	// ����ȫ�ֹ�
	AmbiLight = vec4(0.05);
	// �����ܹ���
	Light = DiffLight + AmbiLight;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}