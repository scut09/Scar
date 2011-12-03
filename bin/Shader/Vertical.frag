uniform sampler2D TextureL0;
uniform sampler2D TextureL1;
uniform vec3 CameraDir;

void main()
{
	//Çó½Ç¶È
	vec2 dir = CameraDir.yz;
	float PI = 3.1415926;
	float DPI = 2*PI;
	float rad;
	float temp = dir.y / sqrt(pow(dir.x,2) + pow(dir.y,2));
	temp = asin( temp );
	if (dir.x > 0)
	{
		if(dir.y > 0)
		{
			rad = temp;
		}
		else
		{
			rad = DPI + temp;
		}
	}
	else
	{
		rad = PI - temp;
	}
	rad = rad - 0.5 * PI;
    vec4 Skin = texture2D( TextureL0, (vec2(gl_TexCoord[0]) + vec2(0, rad/PI) - vec2(0, 0.5)) * vec2( 1.0, 0.5 ));
	//vec4 Skin = texture2D( TextureL0, (vec2(gl_TexCoord[0])) * vec2(1.0, 0.5));
	vec4 Alpha = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	gl_FragColor = Skin * Alpha;
} 