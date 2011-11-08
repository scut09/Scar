
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
	//高光
	High = vec4(0.3, 0.4, 0.8, 1);
	//色调
	Low = vec4( 0.1, 0.2, 0.4, 1 );

	gl_Position = WorldViewProj * gl_Vertex;
	
	// 计算散射光
	vec4 N = normalize( TransMatrix * vec4(gl_Normal, 0.0));
	vec4 L = vec4( LightDirection, 0.0 );
	float NdotL = dot(N, L);
	DiffLight = vec4( max( NdotL, 0) );

	// 计算顶点到镜头的方向向量
	vec4 Vertex = TransMatrix * gl_Vertex;
	vec4 VtoC = vec4( 0, 0, -1, 0 );
	// 计算方向向量与法线的夹角，只有大于90度时才渲染
	NdotVtoC = dot(N, VtoC);
}