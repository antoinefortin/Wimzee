#version 330 core

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 uColor;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uLightIntensity;
uniform sampler2D uTexture;

/*

    DIRECTIOHNAL LIGHT for now
*/
void main() {


    // Texture shit...

    vec4 textureTexColor = texture(uTexture, vTexCoord);
    vec3 lightDir = normalize(uLightPos);
    float diff = max(dot(normalize(vNormal), lightDir), 0.2);
    vec3 lightContribution = uLightColor * uLightIntensity;
    vec3 diffuse = diff * uColor;
    FragColor = vec4(textureTexColor.xyz, 1.0);
    
}