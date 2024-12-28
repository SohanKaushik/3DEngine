#version 330 core

in vec3 aColor; 
in vec2 TexCoord;

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
    vec3 position;
    float inner;
    float outer;
}; 

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

// Uniforms
uniform DirectionalLight dirLight;
uniform SpotLight spotLight;
uniform PointLight pointLight;
uniform vec3 viewPos; 

uniform sampler2D shadowMap;  // Shadow map texture

// Inputs from vertex shader
in vec3 FragPos;                           // Fragment position in world space
in vec3 Normal;                 
in vec4 FragPosDirLightSpace;              // Fragment position in light space for shadow calculation



float ShadowCalculation() {
    // Perspective divide to get normalized device coordinates
    vec3 ProjCoords = FragPosDirLightSpace.xyz / FragPosDirLightSpace.w;
    ProjCoords = ProjCoords * 0.5 + 0.5; // Transform to [0, 1] range
    
    // Compare depth value from shadow map
    float closestDepth = texture(shadowMap, ProjCoords.xy).r;
    float currentDepth = ProjCoords.z;
    
    // Apply bias to avoid shadow acne
    return currentDepth > closestDepth + 0.0005 ? 1.0 : 0.0;
}


vec3 DirectLightCalc() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    vec3 viewDir = normalize(viewPos - FragPos);     // View direction


    // Calculate ambient, diffuse, and specular components
    vec3 ambient = dirLight.ambient;
    vec3 diffuse = dirLight.diffuse * max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 specular = dirLight.specular * pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);

    //Shadow
    float shadow = ShadowCalculation();


    // Combine the lighting components with the input color
    return ambient + (specular + diffuse) * (1- shadow);
      //return  (ambient + ( specular + diffuse) * aColor);
}


vec3 SpotLightCalc() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-spotLight.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Angle between lightDir and spotlight direction
    float theta = dot(lightDir, normalize(-spotLight.direction));
    
    // Calculate intensity within the cone
    float epsilon = spotLight.inner - spotLight.outer;
    float intensity = clamp((theta - spotLight.outer) / epsilon, 0.0, 1.0);

  
    vec3 ambient = spotLight.ambient;
    vec3 diffuse = spotLight.diffuse * max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);

    vec3 specular = spotLight.specular * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    // Combine lighting components
    return   ambient + (diffuse + specular) * intensity;
}



vec3 SolidLightCalc() {
    // Calculate light vector from fragment position to light position
    vec3 lightVec = pointLight.position - FragPos;
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightVec);
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDir, normal);

    // Ambient lighting (multiplied by the light's ambient color)
    vec3 ambient = pointLight.ambient;

    // Fresnel effect calculation
    float fresnelFactor = pow(max(dot(normal, -viewDirection), 0.0), 2.0) * 4; // Adjust exponent for subtle 
    vec3 fresnel = vec3(1.0, 1.0, 1.0) * fresnelFactor; // White edge highlights

    // Apply intensity attenuation to diffuse, specular, and Fresnel components
    vec3 finalFresnel = fresnel * 0.2;

    // Combine ambient, diffuse, specular, and Fresnel
    //return ambient + finalDiffuse  + finalFresnel;
     return  ambient + finalFresnel;
}


vec3 PointLightCalc() {
    // Calculate light vector from fragment position to light position
    vec3 lightVec = pointLight.position - FragPos;

    // Calculate the distance to the light
    float dist = length(lightVec);

    // Distance attenuation formula
    float a = 3.0f;
    float b = 0.7f;
    float inten = 1.0f / (a * dist * dist + b * dist + 3.0f);

    // Ambient lighting (multiplied by the light's ambient color)
    vec3 ambient = pointLight.ambient;

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, -lightDirection), 0.0f);
    vec3 diffuseColor = pointLight.diffuse * diffuse;

    // Specular lighting
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32.0);  // Shininess = 32
    vec3 specularColor = pointLight.specular * specAmount;
   
    return ambient + (diffuseColor) * inten * 10;
}


void main()
{
    // Calculate the lighting using DirectLight function
    vec3 color2 = DirectLightCalc();

 
    FragColor = vec4(color2 * aColor, 1.0);

}