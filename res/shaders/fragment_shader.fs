#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;

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
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform int no_pointLights;
#define MAX_POINT_LIGHTS 20

uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // Ambient
    vec3 ambient = material.diffuse * pointLight.diffuse;

    // Diffuse
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * pointLight.diffuse;

    // Specular;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * pointLight.specular;

    // Distance attenuation
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 res = (ambient + diffuse + specular) * attenuation;

    return res;
}

void main() {    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < no_pointLights; i++)
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);

    vec4 objColor = texture(texture_diffuse1, TexCoords);
    
    FragColor = vec4(objColor * vec4(result, 1.0));
}