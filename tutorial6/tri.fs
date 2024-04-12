#version 330 core
//in vec4 color;
in vec2 uv;
in vec3 normal;
in vec3 fragPos;
in vec4 FragPosLightSpace;


out vec4 FragColor;


struct Light {
    vec3 position;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D sampler;
uniform sampler2D shadowMap;
uniform vec3 viewPos;
uniform Light light;


float ShadowCalculation(vec4 fragPosLightSpace){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main(){

    


    //ambient
    float ambientStrength = 0.2;

    vec4 Objcolor = texture(sampler, uv);
    vec3 ambient = light.ambient * lightColor;



    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse* diff * lightColor;


    //specularStrength
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    //calculate result
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));   


    //calculate shadow
    float shadow = ShadowCalculation(FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) ;    
    //ambient  *= attenuation; 
    //diffuse  *= attenuation;
    //specular *= attenuation;

    vec3 temp = ambient + diffuse + specular;
    vec4 result = vec4(temp,1.0)* Objcolor;


    FragColor = result ;
} 