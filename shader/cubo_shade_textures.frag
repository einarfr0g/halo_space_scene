#version 410 core
in vec3 fragNormal;
in vec3 shadedcolor;
in vec2 texturecords;

out vec4 color;

uniform sampler2D texture0;

void main()
{
    color = texture(texture0, texturecords);
}
