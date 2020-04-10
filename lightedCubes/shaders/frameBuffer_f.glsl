#version 400

in vec2 texCoords;
out vec4 fragColor;

uniform sampler2D screenTex;
uniform sampler2D depthTex;  

float linDepth(vec2 uv)
{
	float f = 1000.0;
	float n = 0.1;
	float z = (2 * n) / (f + n - texture( depthTex, uv ).x * (f - n));
	
	return z;
}

vec3 depth()
{
	float v = pow(texture(depthTex, texCoords).x, 256);
	return vec3(v, v, v);
}

void main()
{
	vec3 col = texture(screenTex, texCoords).rgb;
	
	//vec3 color = texture(depthTex, texCoords).rgb; 
	
	float c = linDepth(texCoords); 
	
	vec3 color = vec3(c, c, c); 
	
	
	
	fragColor = vec4(c, c, c, 1.0f);
	
	//if(gl_FragCoord.x > 512)
	//	fragColor = vec4(depth(), 1.0f);
	//else
		fragColor = vec4(col, 1.0f);
		
}