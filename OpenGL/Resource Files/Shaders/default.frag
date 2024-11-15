#version 330 core

in vec3 aColor;  // Color passed from the vertex shader
out vec4 FragColor;


struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; uniform DirectionalLight dirLight;


uniform vec3 viewPos;
in vec3 FragPos;
in vec3 Normal;


vec3 CalculateAmbient() {
    return dirLight.ambient;
}

vec3 CalculateDiffuse(vec3 normal, vec3 lightDir) {
    float diff = max(dot(Normal, lightDir), 0.0);
    return diff * dirLight.diffuse;
}

vec3 CalculateSpecular(vec3 normal, vec3 lightDir, vec3 viewDir) {

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess = 32
    return spec * dirLight.specular;
}


vec3 DirectLight() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    vec3 viewDir = normalize(viewPos - FragPos);


    // Calculate components
    vec3 ambient = CalculateAmbient();
    vec3 diffuse = CalculateDiffuse(normal, lightDir);
    vec3 specular = CalculateSpecular(normal, lightDir, viewDir);

    // Combine results
    return aColor *  ambient + diffuse + specular;

}



void main()
{ 
      FragColor = vec4(DirectLight(), 1.0);                   // Set the final color output
    //FragColor =  vec4(0.0, 0.0, 0.0, 1.0); 
   // FragColor = vec4(CalculateDiffuse() * vec3(1.0, 0.5, 0.0), 1.0);
}