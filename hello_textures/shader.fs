#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// 纹理采样器分配一个位置值 
// 可以设置多个纹理。  一个纹理位置称为纹理单元
// 默认是0，自动激活的

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float percent;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), percent);
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}

