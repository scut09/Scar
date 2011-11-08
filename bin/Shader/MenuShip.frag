uniform sampler2D TextureL0; //Skin

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	gl_FragColor = Skin * Light;
	gl_FragColor += Skin.a * vec4( 3.975904, 6.686747, 10, 1 );
}