#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out float Height;

void main()
{
    FragPos =
        vec3(model * vec4(aPos, 1.0));

    Normal =
        normalize(aPos);

    Height = aPos.y;

    gl_Position =
        camMatrix *
        model *
        vec4(aPos, 1.0);
}