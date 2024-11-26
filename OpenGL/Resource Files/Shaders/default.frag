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

// Spotlight light structure
struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
    vec3 position;
    float inner;
    float outer;
}; 

// PointLight light structure
struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
}; 



uniform DirectionalLight dirLight;  
uniform SpotLight spotLight;        
uniform PointLight pointLight;      

uniform vec3 viewPos;              // View position
in vec3 FragPos;                   // Fragment position in world space
in vec3 Normal;                    // Normal vector in world space

/*
//Shadows
uniform sampler2D shadowMap;
in FragPosLightSpace;


float ShadowCalculation(vec4 fragPosLightSpace){

     // Perform perspective divide
     vec3 ProjCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
     ProjCoords = ProjCoords * 0.5 + 0.5;

     // Get closest depth value from shadow map
     float closestDepth = texture(shadowMap, ProjCoords.xy).r;

     // Current Depth
     float currentDepth = ProjCoords.z;

     // Shadow Calculation
     float shadow = currentDepth > closestDepth + 0.005 ? 1.0 : 0.0;         // Bias to prevent bias artifacts

     return shadow;
}
*/

vec3 DirectLightCalc() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    vec3 viewDir = normalize(viewPos - FragPos);     // View direction


    // Calculate ambient, diffuse, and specular components
    vec3 ambient = dirLight.ambient;
    vec3 diffuse = dirLight.diffuse * max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 specular = dirLight.specular * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    //vec3 specular = CalculateSpecular(dirLight.specular, normal, lightDir, viewDir);

    //Shadow
    //float Shadow = ShadowCalculation(FragPosLightSpace);


    // Combine the lighting components with the input color
    //return  (ambient +  ( 1.0 - shadow) * (specular + diffuse));
      return  (ambient + (specular + diffuse));
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



vec3 PointLightCalc() {

    float constant = 1.0f;
    float linear = 0.7f;
    float quadratic = 1.0f;


    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(-pointLight.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (constant + 
                               linear * distance + 
                               quadratic * (distance * distance));

    vec3 ambient = pointLight.ambient;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Shininess = 32
    vec3 specular = pointLight.specular * spec;

    return ambient + (diffuse ) * attenuation;
}



void main()
{
    // Calculate the lighting using DirectLight function
    vec3 color2 = DirectLightCalc();

 
    // Final output color with the calculated lighting
    FragColor = vec4(color2 * aColor, 1.0);

}
