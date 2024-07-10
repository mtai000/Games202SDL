#version 430

uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightPos;
uniform vec3 uCameraPos;

uniform float uLightIntensity;

uniform int uTextureSample;
uniform sampler2D uSampler;

in vec2 vTextureCoord;
in vec3 vFragPos;
in vec3 vNormal;

out vec4 outcolor;

void main(void){
  vec3 colorKd;
  if(uTextureSample == 1)
  {
    colorKd = texture2D(uSampler, vTextureCoord).rgb;
    colorKd = pow(colorKd, vec3(2.2));
  }
  else
  {
    colorKd = uKd;
  }

  vec3 ambient = 0.05 * colorKd;
  vec3 lightDir = normalize(uLightPos - vFragPos);
  vec3 normal = normalize(vNormal);
  float diff = max(dot(lightDir,normal), 0.0);
  float light_atten_coff = uLightIntensity / length(uLightPos - vFragPos);
  vec3 diffuse = diff * light_atten_coff * colorKd;

  vec3 viewDir = normalize(uCameraPos - vFragPos);
  float spec = 0.0;
  vec3 reflectDir = reflect(-lightDir, normal);
  spec = pow (max(dot(viewDir, reflectDir), 0.0), 35.0);
  vec3 specular = uKs * light_atten_coff * spec;  

  outcolor = vec4(pow((ambient + diffuse + specular), vec3(1.0/2.2)), 1.0);
}