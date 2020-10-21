#version 330 core
	out vec4 FragColor;
	in vec3 ourColor;
	in vec2 TexCoord;
	uniform sampler2D texture1;
	uniform sampler2D texture2;
	uniform float mix_level;

	void main()
	{
		// vec2 popo;
		vec2 reverse = vec2(TexCoord.x * 1, TexCoord.y * 1);
		// if (TexCoord.x < 0.6 && TexCoord.x > 0.4 && TexCoord.y < 0.6 && TexCoord.y > 0.4 )
		// {
		FragColor = mix(texture(texture1, reverse), texture(texture2, TexCoord), mix_level);
		// }
		// else
		// {
			// FragColor = texture(texture2, TexCoord);
		// }
	}