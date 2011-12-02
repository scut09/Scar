uniform sampler2D TextureL0; 
uniform sampler2D TextureL1; 
uniform sampler2D TextureL2; 

uniform float Alpha;
uniform float Speed;

void main(void) 
{

	vec2 tempCord = vec2(gl_TexCoord[0]);
	tempCord.y = tempCord.y + Speed;

	if( tempCord.y >= 1.0 ) 
		tempCord.y -= 1.0;

	vec4 Texture = texture2D( TextureL0, tempCord );
	gl_FragColor = Texture * Alpha;
}