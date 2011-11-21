uniform sampler2D TextureL0;
uniform sampler2D TextureL1;

varying float NdotL;

void main()
{
	float factor = NdotL;
	if( NdotL > 1 )
	{
		factor = 1;
	}
	else if( NdotL < 0 )
	{
		factor = 0;
	}
	vec4 color = texture2D( TextureL0, vec2(gl_TexCoord[0]) );
	vec4 alpha = texture2D( TextureL1, vec2(gl_TexCoord[0]) );
	gl_FragColor = vec4( color.rgb, alpha.r ) * vec4( 1, 0.8, 0.7, 1.0 ) * 0.8;
	gl_FragColor *=  vec4( vec3( factor ), 1.0 );
	//gl_FragColor = flare * vec4( 1.0, 0.8, 0.7, 1.0 );
}