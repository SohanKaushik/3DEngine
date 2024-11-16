#version 330 core

in vec3 aColor;  // Color passed from the vertex shader
out vec4 FragColor;

// Directional light structure
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

uniform DirectionalLight dirLight;  // Directional light
uniform vec3 viewPos;              // View position
in vec3 FragPos;                   // Fragment position in world space
in vec3 Normal;                    // Normal vector in world space

// Calculate the ambient light
vec3 CalculateAmbient() {
    return dirLight.ambient;
}

// Calculate the diffuse light
vec3 CalculateDiffuse(vec3 normal, vec3 lightDir) {
    float diff = max(dot(normal, lightDir), 0.0);
    return dirLight.diffuse * diff;
}

// Calculate the specular light
vec3 CalculateSpecular(vec3 normal, vec3 lightDir, vec3 viewDir) {
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);  // Shininess = 32
    return dirLight.specular * spec;
}

// Calculate the total lighting
vec3 DirectLight() {
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);  // Light direction
    vec3 viewDir = normalize(viewPos - FragPos);     // View direction

    // Calculate ambient, diffuse, and specular components
    vec3 ambient = CalculateAmbient();
    vec3 diffuse = CalculateDiffuse(normal, lightDir);
    vec3 specular = CalculateSpecular(normal, lightDir, viewDir);

    // Combine the lighting components with the input color
    return aColor * (ambient + diffuse + specular);
}

void main()
{
    // Calculate the lighting using DirectLight function
    vec3 color = DirectLight();

    // Final output color with the calculated lighting
    FragColor = vec4(color, 1.0);

}
