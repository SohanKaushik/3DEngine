#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {

    // Retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float SpecularStrength = texture(gAlbedoSpec, TexCoords).a;

    // Lighting calculations (Phong)
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = lightColor * spec * SpecularStrength;

    vec3 result = (diffuse + specular) * Albedo;
    FragColor = vec4(result, 1.0);
}
