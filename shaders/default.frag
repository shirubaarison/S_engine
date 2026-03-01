#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;

void main()
{
  vec4 albedo;
  albedo = texture(texture_diffuse, TexCoords);

  vec3 specularColor;
  specularColor = texture(texture_specular, TexCoords).rgb;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - crntPos);
  vec3 viewDir = normalize(camPos - crntPos);

  vec3 ambient = min(material.ambient, 0.4) * lightColor.rgb;

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor.rgb;

  vec3 specular = vec3(0.0);
  if (diff > 0.0) {
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));
    specular = spec * specularColor * lightColor.rgb;

    specular = min(specular, vec3(1.0));
  }

  vec3 result = (ambient + diffuse + specular) * albedo.rgb;

  FragColor = vec4(result, albedo.a);
}
