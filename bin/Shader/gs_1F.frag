
uniform sampler2D TextureL0; //Diff
uniform sampler2D TextureL1; //Ngs
uniform sampler2D TextureL2; //

varying vec4 DiffLight;
varying vec4 AmbiLight;
varying vec4 Light;

varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;

void main()
{
	vec4 Skin = texture2D( TextureL0, vec2(gl_TexCoord[0]));
	vec4 Ngs = texture2D( TextureL1, vec2(gl_TexCoord[0]));

	// lookup normal from normal map, move from [0,1] to  [-1, 1] range, normalize
	vec3 normal = 2.0 * Ngs.agb - vec3(1.0);
	normal = normalize (normal);
	
	// compute diffuse lighting
	float lamberFactor= max (dot(lightVec, normal), 0.0) ;
	vec4 diffuseMaterial;
	vec4 diffuseLight;
  
	// compute ambient
	vec4 ambientLight = vec4(0.4);	
	diffuseMaterial = Skin;
	diffuseLight  = vec4(0.6);
		 
	// 全局光+漫反射光
	gl_FragColor =	diffuseMaterial * diffuseLight * lamberFactor + ambientLight * diffuseMaterial;

	// 添加空间站灯光
	if(Skin.a > 0.9)
		gl_FragColor +=  vec4(0.5, 0.5, 0.8, 0.5);
	else
		gl_FragColor += Skin.a * vec4(4.156863, 6.941176, 10, 1);
}