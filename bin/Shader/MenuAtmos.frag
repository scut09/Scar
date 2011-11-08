
varying vec4 DiffLight;
varying float NdotVtoC;
varying vec4 High;
varying vec4 Low;

void main(void) 
{
	// 羽化边缘
	float factor;
	if (NdotVtoC > -0.18)
	{
		factor = -.3 * NdotVtoC;
	}
	else if (NdotVtoC > -0.26 )
	{
		factor = -.6 * NdotVtoC;
	}
	else
	{
		factor = 1 + 2*NdotVtoC;
	}

	//根据角度计算大气颜色
	vec4 Color = High * DiffLight + Low * (vec4(1) - DiffLight);

	// 根据光照条件和色调绘制大气圈
	gl_FragColor = Color * DiffLight * factor;

	//gl_FragColor = vec4(1) * NewDiff	
	//gl_FragColor = vec4(0.5);
}