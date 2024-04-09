#version 330 core
//in vec4 color;
in vec2 uv;
in vec3 normal;
in vec3 fragPos;


out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D sampler;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1;
    //vec3 ambient = ambientStrength * lightColor;
    //vec3 lightColor = vec3(1.0);
    vec4 Objcolor = texture(sampler, uv);

    vec3 ambient = ambientStrength * lightColor;
    //vec3 ambient = ambientStrength * lightColor;



    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;



    //specularStrength
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    //vec3 reflectDir = lightDir;

    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float spec1 = max(dot(viewDir, reflectDir), 0.0);
    //float spec = pow(spec1,32.0);  
    

    //float spec = spec1 * spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1;//* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1* spec1;  
    vec3 specular = specularStrength * spec1 * lightColor;

    vec3 temp = ambient + diffuse + specular;


    vec4 result = vec4(temp,1.0)*Objcolor;


    FragColor = result ;
} 