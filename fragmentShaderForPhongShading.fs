#version 330 core
out vec4 FragColor;


struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};



struct PointLight {                    //Point Light
    vec3 position;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float Kc;  // attenuation factors
    float Kl;  // attenuation factors
    float Kq;  // attenuation factors
};

struct DirectionalLight {              //Directional Light
    vec3 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct SpotLight {                    //Spot Light
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float Kc;
    float Kl;
    float Kq;
};



#define NR_POINT_LIGHTS 2
#define NR_SPOT_LIGHTS 2


uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight[NR_SPOT_LIGHTS];


uniform Material material;
uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;//Viewer position

uniform bool lightingOn;
uniform bool dark;

in vec3 Normal;
in vec3 FragPos;

//Functions prototypes
vec4 CalcDirLight(Material material, DirectionalLight light, vec3 normal, vec3 fragPos);
vec4 CalcPointLight(Material material, PointLight light, vec3 normal, vec3 fragPos);
vec4 CalcSpotLight(Material material, SpotLight light, vec3 normal, vec3 fragPos);


void main()
{

    //Point Light
    vec4 pointL;
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
         pointL += CalcPointLight(material, pointLight[i], Normal, FragPos);    
    }

    //Directional Light Calculation
    vec4 dirL = CalcDirLight(material, directionalLight, Normal, FragPos);


    //Spot Light
    vec4 spotL;
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    {
         spotL += CalcSpotLight(material, spotLight[i], Normal, FragPos);    
    }

    //Aggregate all result

    vec4 result = dirL + pointL + spotL;

    if(!lightingOn)
    {
        result = material.ambient;
    }
    if(dark)
    {
        result = vec4(0.0f);
    }

    FragColor = result;
}


vec4 CalcPointLight(Material material, PointLight light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);//L
    vec3 norm = normalize(normal);//N
    vec3 viewDir = normalize(viewPos - fragPos);//V
    vec3 reflectDir = reflect(-lightDir, norm);//R

   

    //obj distance from light source
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.Kc + light.Kl * distance + light.Kq * (distance * distance));


    //ambient
    vec4 ambient = light.ambient * material.ambient;
    ambient *= attenuation;

    //diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse);
    diffuse *= attenuation;
    

    //specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = light.specular * (spec * material.specular);
    specular *= attenuation;

    return (ambient + diffuse + specular );
}

vec4 CalcDirLight(Material material, DirectionalLight light, vec3 normal, vec3 fragPos)
{
    vec3 norm = normalize(normal);//N
    vec3 lightDir = normalize(-light.direction);//L
    vec3 viewDir = normalize(viewPos - fragPos);//V
    vec3 reflectDir = reflect(-lightDir, norm);//R

    //ambient
    vec4 ambient = light.ambient * material.ambient;
    
    //diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse);
    
    //specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = light.specular * (spec * material.specular);

    return (ambient + diffuse + specular);
}



vec4 CalcSpotLight(Material material, SpotLight light, vec3 normal, vec3 fragPos)
{
    vec3 norm = normalize(normal);//N
    vec3 lightDir = normalize(light.position - fragPos);//L
    vec3 viewDir = normalize(viewPos - fragPos);//V
    vec3 reflectDir = reflect(-lightDir, norm);//R
    

    //distance
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.Kc + light.Kl * distance + light.Kq * (distance * distance));

    //Ambient
    vec4 ambient = light.ambient * material.ambient;
    ambient *= attenuation;

    //Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (diff * material.diffuse);
    diffuse *= attenuation;

    //Specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = light.specular * (spec * material.specular);
    specular *= attenuation;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}