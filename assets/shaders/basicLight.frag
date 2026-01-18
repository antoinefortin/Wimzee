#version 330 core

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 uColor;
/*

    DIRECTIOHNAL LIGHT for now
*/
void main() {

    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diff = max(dot(normalize(vNormal), lightDir), 0.2);
    vec4 debug = vec4(1.0);
    //FragColor = vec4(uColor * diff, 1.0);
    FragColor = debug;
}