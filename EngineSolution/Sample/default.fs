#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D myTexture;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//FragColor = texture2D(diffuse, TexCoord0.xy) * vec4(R_ambient, 1);
	//gl_FragColor = texture2D(myTexture, TexCoord.xy);
	FragColor = texture(myTexture, TexCoord);
	//FragColor = texture2D(vec3(0,0,0), TexCoord.xy) * vec4(vec3(0.5f,.05f,0.5f),1);
}