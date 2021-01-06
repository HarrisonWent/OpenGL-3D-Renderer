#version 450

uniform sampler2D texture_Diffuse;
uniform sampler2D texture_Normal;

//uniform vec3 FragLightColor;
//uniform vec3 FragLightPos;
uniform vec3 FragCamPos;

in vec2 FragTextureCoord;
out vec4 frag_colour;

in vec3 FragNormal;
in vec3 FragPos;
in mat3 TBN;

uniform vec3 PointLight_Colours[2];
uniform vec3 PointLight_Positions[2];

vec3 CalculatePointLight(vec3 PointColour, vec3 PointPosition)//colour not yet used
{
	//Normal map
	vec3 normal = normalize(FragNormal * texture(texture_Normal,FragTextureCoord).rgb);
	vec3 norm_light = normalize(normalize(PointPosition)-FragPos);
	float diffuse_value = max(dot(normal, norm_light), 0.0);

    //Specular	
	float specularStrength = 2.0;
	vec3 viewDir = normalize(normalize(FragCamPos) - FragPos);
	vec3 reflectDir = reflect(-norm_light,normal);
	float spec = pow(max(dot(normal,reflectDir),0.0),32.0);
	vec3 specular = vec3(specularStrength * spec);
    
	//Distance attenuation for point light
	float dist = length(PointPosition - FragPos);
	float attenuation = 1.0 / (1.0 + 0.09 * dist + 
  			    0.032 * (dist * dist));
	
	return PointColour*(diffuse_value + specular) * attenuation;
};

void main() 
{
	//Ambient
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * vec3(1,1,1);

	//Point lights
	vec3 Combined = vec3(0.0);
	for(int i = 0; i < 2;i++)
	{
		Combined+=CalculatePointLight(PointLight_Colours[i],PointLight_Positions[i]);
	}

	//With
	frag_colour = vec4(texture2D(texture_Diffuse,FragTextureCoord).rgb *(Combined+ambient),1.0);
};


//(old code )
//Normal 
//    vec3 norm_light = normalize(FragLightPos-FragPos);
//    vec3 normal = (texture(texture_Normal,FragTextureCoord).rgb);
//	normal = normalize(normal * 2.0-1.0);
//	normal = normalize(TBN * normal);
//	float diffuse_value = max(dot(normal, norm_light), 0.0);

//		//Normal map
//	vec3 normal = normalize(FragNormal * texture(texture_Normal,FragTextureCoord).rgb);
//	vec3 norm_light = normalize(normalize(FragLightPos)-FragPos);
//	float diffuse_value = max(dot(normal, norm_light), 0.0);
//
//    //Specular	
//	float specularStrength = 2.0;
//	vec3 viewDir = normalize(normalize(FragCamPos) - FragPos);
//	vec3 reflectDir = reflect(-norm_light,normal);
//	float spec = pow(max(dot(normal,reflectDir),0.0),32.0);
//	vec3 specular = vec3(specularStrength * spec);
//    
//	//Distance attenuation for point light
//	float dist = length(FragLightPos - FragPos);
//	float attenuation = 1.0 / (1.0 + 0.09 * dist + 
//  			    0.032 * (dist * dist));   

	//Without light Attenuation
//frag_colour = vec4(texture2D(texture_Diffuse,FragTextureCoord).rgb * (diffuse_value+ambient+specular),1.0);
	