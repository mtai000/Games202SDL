#version 430
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3  aNormalPosition;
layout(location = 2) in vec2  aTextureCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uLightMVP;

out vec3 vNormal;
out vec2 vTextureCoord;

void main(void) {

  vNormal = aNormalPosition;
  vTextureCoord = aTextureCoord;

  gl_Position = uLightMVP * vec4(aVertexPosition, 1.0);
}