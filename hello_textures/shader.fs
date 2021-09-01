#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// 纹理采样器分配一个位置值 
// 可以设置多个纹理。  一个纹理位置称为纹理单元
// 默认是0，自动激活的

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
}

