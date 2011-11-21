
uniform mat4 WorldViewProj;
uniform vec3 SunNormal;
uniform mat4 TransMatrix;
uniform vec3 AbsPos;
uniform vec3 CameraPos;

varying vec4 DiffLight;
varying vec4 NewDiff;
varying float NdotVtoC;
varying vec4 High;
varying vec4 Low;

void main(void)
{
	//高光
	High = vec4(1.5);
	//色调
	Low = vec4( 0.8, 0.85, 0.9, 1.0 );

	gl_Position = WorldViewProj * gl_Vertex;
	
	// 计算散射光
	vec3 LightDirection = SunNormal;
	vec4 N = normalize( TransMatrix * vec4(gl_Normal, 0.0));
	vec4 L = vec4( LightDirection, 0.0 );
	float NdotL = dot(N, L);
	DiffLight = vec4( max( NdotL, 0.0) );

	// 计算顶点到镜头的方向向量
	vec4 Vertex = TransMatrix * gl_Vertex;
	vec4 VtoC = normalize(vec4(CameraPos, 0.0) - Vertex);
	// 计算方向向量与法线的夹角，只有大于90度时才渲染
	NdotVtoC = dot(N, VtoC);

	// 计算摄像机向量与大气层夹角
	vec4 E = normalize(vec4( (AbsPos - CameraPos), 0.0 ));
	float NdotE = dot(N, E);

	NewDiff = vec4(max((NdotL + NdotE), -1.0)) + vec4(1.0);
}
