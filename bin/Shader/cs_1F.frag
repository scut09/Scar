
uniform sampler2D TextureL0; //Diff

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));

	// 全局光+漫反射光
	gl_FragColor =	Skin * Light;
	// 添加空间站灯光
	gl_FragColor += Skin.a * vec4(4.156863, 6.941176, 10, 1);
}