uniform sampler2D TextureL0;
uniform sampler2D TextureL1;
uniform float Col;
uniform float Row;
uniform float TotalCol;
uniform float TotalRow;

void main()
{
	float xoff = Col / TotalCol;
	float yoff = Row / TotalRow;
    vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]) / vec2( TotalCol, TotalRow) + vec2(xoff, yoff));
	//vec4 Alpha = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	gl_FragColor = Skin;
} 