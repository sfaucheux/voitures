#version 130
#define PI 3.14159

in vec3 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 color;
out vec2 coordTexture;

void main()
{
    vec4 obj = model * vec4(in_Vertex, 1.0);

    gl_Position = projection * view * obj;

    //color = in_Color;
    color=vec3(0.3,0.3,0.3);
    coordTexture = in_TexCoord0;

}
