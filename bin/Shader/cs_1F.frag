
uniform sampler2D TextureL0; //Diff

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));

	// ȫ�ֹ�+�������
	gl_FragColor =	Skin * Light;
	// ��ӿռ�վ�ƹ�
	gl_FragColor += Skin.a * vec4(4.156863, 6.941176, 10, 1);
}