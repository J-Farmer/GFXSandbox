#version 330 core

in vec3 fragPos;
in vec3 Normal; 
in vec2 uv; 
 
out vec4 fragColor; 

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform int reverseNormals; 
uniform int attenuationType;

uniform sampler2D tex;
uniform sampler2D tex2; 

uniform sampler2D bump; 

float constant = 1.0f;
float linear = 0.0004f;
float quadratic = 0.032f;


void main()
{
	//vec4 col = mix(texture(tex, uv), texture(tex2, uv), 0.2);
	
	//vec4 col = vec4(objectColor, 1.0f); 
	
	vec4 col = vec4(texture(tex,uv)); 

	// Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
	vec3 norm; 
    // Diffuse 
	if(reverseNormals == 1)
	{
		norm = normalize(-Normal);
	}
	else
	{
		norm = normalize(Normal);
	}
	
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

	//Attenuation
	float distance = length(lightPos - fragPos);
	vec3 result; 
	
	if(attenuationType == 0)
	{
		float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));  
		  
		diffuse  *= attenuation;
		specular *= attenuation;
		
		result = (ambient + diffuse + specular) * col.rgb;
	}
	
	if(attenuationType == 1)
	{
		vec3 attenuation = lightColor * (1.0f / (1.0f + 0.0004 * (distance*distance))); 
		result = (ambient + attenuation * (diffuse + specular)) * col.rgb;
	}
				
    fragColor = vec4(result, 1.0f);
	 
}