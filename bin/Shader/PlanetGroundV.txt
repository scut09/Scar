uniform mat4 WorldViewProj;
uniform vec3 AbsPos;
uniform mat4 InvWorld;
uniform mat4 TransWorld;
uniform mat4 TransMatrix;

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main(void)
{
	gl_Position = WorldViewProj * gl_Vertex;

	vec3 LightDirection = vec3( -1.0, 0.0, 0.0 ); //uniform vec3 SunPosition;
	LightDirection =  vec3(0.0, 0.0, 0.0) - AbsPos;

	// 计算散射光
	vec4 N = normalize( TransMatrix * vec4(gl_Normal, 0.0));
	vec4 L = vec4( LightDirection, 0.0 );
	
	// 规范化光的方向向量 
	L = normalize( L );
	float NdotL = dot(N, L);
	DiffLight = vec4(max(0.0, NdotL));

	// 计算全局光
	AmbiLight = vec4(0.05);

	// 计算总光照
	Light = DiffLight * 0.5  + AmbiLight;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}