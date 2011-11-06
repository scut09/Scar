
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

	// 切线向量，副法线，法线向量，组成切线坐标系
	vec4 tangent = gl_MultiTexCoord1.xyz;
	vec4 binormal = gl_MultiTexCoord2.xyz;
	vec4 normal = gl_Normal;


	// 计算散射光
	//vec4 N = normalize( TransMatrix * vec4( vec3(1,1,-1)*gl_Normal, 0.0));
	
	//LightDirection = vec3(gl_Vertex.xyz - CameraPos.xyz);
	// 计算切线坐标系下的光照方向
	vec4 L = vec4( LightDirection, 0.0 );
	LLightInTangentCoord.x = dot( L, tangent );
	LLightInTangentCoord.y = dot( L, binormal );
	LLightInTangentCoord.z = dot( L, normal );

	HLightInTangentCoord = vec4(0.0);

	// 得到纹理坐标
	gl_TexCoord[0] = gl_MultiTexCoord0;
}