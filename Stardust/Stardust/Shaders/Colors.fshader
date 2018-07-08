#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};
uniform Light light;
uniform Material material;

void main()
{
    // ambient

	float ambientStrength  = 0.1f;
	vec3 ambient  = light.ambient * material.ambient;

	// Diffuse
	vec3 directionTowardsLight = normalize(lightPos - FragPos);
	vec3 norm =  normalize(Normal);
	float diff = max(dot(directionTowardsLight, norm),0.0);
	vec3 diffuse  = light.diffuse * (diff * material.diffuse);

	//Specular
	float specularStrength = 0.8;
	vec3 refDir = reflect(-directionTowardsLight, norm);
	vec3 eyeDir = normalize(viewPos - FragPos);
	float spec = pow(max(dot(refDir,eyeDir),0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);  

	vec3 result =(ambient + diffuse + specular) * objectColor;
	FragColor = vec4 (result,1.0);
} 