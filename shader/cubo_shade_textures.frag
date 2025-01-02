#version 410 core
in vec3 fragNormal;
in vec3 shadedcolor;
in vec2 texturecords;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, texturecords) * vec4(shadedcolor, 1.0);
}
