#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 u_viewPos;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

uniform int no_pointLights;
#define MAX_POINT_LIGHTS 20

uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // Material stuff
    vec3 mat_diffuse = vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 mat_specular = vec3(texture(material.texture_specular1, TexCoords));

    // Ambient
    vec3 ambient = mat_diffuse * pointLight.ambient;

    // Diffuse
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = mat_diffuse * diff * pointLight.diffuse;

    // Specular;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = mat_specular * spec * pointLight.specular;

    // Distance attenuation
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 res = (ambient + diffuse + specular) * attenuation;

    return res;
}

void main() {    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < no_pointLights; i++)
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    
    float gamma = 2.2;
    FragColor = vec4(pow(result, vec3(1.0/gamma)), 1.0);
}