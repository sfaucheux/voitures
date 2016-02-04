#version 150 core 
#
in vec2 coordTexture;
uniform sampler2D tex;
out vec4 out_Color;

// Fonction main

void main()
{
    out_Color = texture(tex, coordTexture);
}
