uniform mat4 WorldViewProj;
//uniform mat4 RotMat;
//uniform mat4 MyTransMat;
uniform vec3 CameraDir;
uniform vec2 MouseVec;

varying float offset;

void main()
{	
	gl_TexCoord[0] =  gl_MultiTexCoord0;
	//gl_Position = MyTransMat * gl_Vertex; //+ vec4(MouseVec * vec2(-30.0, 30.0), 0.0, 0.0);
	gl_Position = WorldViewProj * gl_Vertex + vec4(MouseVec * vec2(-30.0, 30.0), 0.0, 0.0);

	//Çó´¹Ö±½Ç¶È
	vec2 dir = CameraDir.yz;
	float rad;
	float PI = 3.1415926;
	float DPI = 2*PI;
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
	offset = rad / PI;
}