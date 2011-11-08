
uniform mat4 WorldViewProj;
vec3 LightDirection = vec3( -0.6, 1, 1.4 );
uniform mat4 TransMatrix;
uniform vec3 CameraPos;

varying vec4 DiffLight;
varying float NdotVtoC;
varying vec4 High;
varying vec4 Low;

void main(void) 
{
	//�߹�
	High = vec4(0.3, 0.4, 0.8, 1);
	//ɫ��
	Low = vec4( 0.1, 0.2, 0.4, 1 );

	gl_Position = WorldViewProj * gl_Vertex;
	
	// ����ɢ���
	vec4 N = normalize( TransMatrix * vec4(gl_Normal, 0.0));
	vec4 L = vec4( LightDirection, 0.0 );
	float NdotL = dot(N, L);
	DiffLight = vec4( max( NdotL, 0) );

	// ���㶥�㵽��ͷ�ķ�������
	vec4 Vertex = TransMatrix * gl_Vertex;
	vec4 VtoC = vec4( 0, 0, -1, 0 );
	// ���㷽�������뷨�ߵļнǣ�ֻ�д���90��ʱ����Ⱦ
	NdotVtoC = dot(N, VtoC);
}