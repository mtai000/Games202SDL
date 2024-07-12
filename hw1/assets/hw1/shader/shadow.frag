#version 430

// uniform vec3 uLightPos;
// uniform vec3 uCameraPos;

// in vec3 vNormal;
// in vec2 vTextureCoord;

in vec4 vPos;
out vec4 outColor;

vec4 pack (float depth) {
    //return vec4(1.0,0.0,0.0,1.0);
    // 使用rgba 4字节共32位来存储z值,1个字节精度为1/256
    const vec4 bitShift = vec4(1.0, 256.0, 256.0 * 256.0, 256.0 * 256.0 * 256.0);
    const vec4 bitMask = vec4(1.0/256.0, 1.0/256.0, 1.0/256.0, 0.0);
    // gl_FragCoord:片元的坐标,fract():返回数值的小数部分
    vec4 rgbaDepth = fract(depth * bitShift); //计算每个点的z值
    //return vec4(rgbaDepth.r,0,0,1);
    //return vec4((rgbaDepth - rgbaDepth.gbaa * bitMask).r,0,0,1);
    rgbaDepth -= rgbaDepth.gbaa * bitMask; 
    //Cut off the value which do not fit in 8 bits
    return rgbaDepth;
}

void main(){

  //gl_FragColor = vec4( 1.0, 0.0, 0.0, gl_FragCoord.z);
  //gl_FragColor = pack(gl_FragCoord.z);
  outColor = pack(gl_FragCoord.z);
  //outColor = gl_FragCoord;
}