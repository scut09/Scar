
uniform mat4 WorldViewProj;
vec3 LightDirection = vec3( -1.0, 0.0, 0.0 ); //uniform vec3 SunPosition;
uniform mat4 TransMatrix;
uniform vec3 AbsPos;
uniform vec3 CameraPos;


varying vec4 LLightInTangentCoord;
varying vec4 HLightInTangentCoord;


void main()
{
	gl_Position = WorldViewProj * ( vec4( 1,1,-1,1 ) * gl_Vertex );

	// ���������������ߣ����������������������ϵ
	vec4 tangent = gl_MultiTexCoord1.xyz;
	vec4 binormal = gl_MultiTexCoord2.xyz;
	vec4 normal = gl_Normal;


	// ����ɢ���
	//vec4 N = normalize( TransMatrix * vec4( vec3(1,1,-1)*gl_Normal, 0.0));
	
	//LightDirection = vec3(gl_Vertex.xyz - CameraPos.xyz);
	// ������������ϵ�µĹ��շ���
	vec4 L = vec4( LightDirection, 0.0 );
	LLightInTangentCoord.x = dot( L, tangent );
	LLightInTangentCoord.y = dot( L, binormal );
	LLightInTangentCoord.z = dot( L, normal );

	HLightInTangentCoord = vec4(0.0);

	// �õ���������
	gl_TexCoord[0] = gl_MultiTexCoord0;
}