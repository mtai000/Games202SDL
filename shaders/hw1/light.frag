#version 430

uniform vec3 uLightColor;
in vec4 outVertexPosition;

out vec4 color;
void main(void){
    // color = outVertexPosition;
    color = vec4(uLightColor,1.0);
}