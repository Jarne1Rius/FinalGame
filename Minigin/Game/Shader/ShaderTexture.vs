#version 330 core
layout (location = 0) in vec2 vertex;

uniform mat4 modelSpace;
uniform mat4 projectionSpace;

void main()
{
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}