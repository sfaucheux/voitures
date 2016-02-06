#version 150 core 
#
in vec2 coordTexture;
uniform sampler2D tex;
out vec4 out_Color;

// Fonction main

void main()
{
    out_Color = texture(tex, coordTexture);

    //On affiche du gris si pas de texture.
    //Affiche aussi du gris pour les textures quand le point vaut (0,0).
    if(coordTexture == vec2(0,0))
        out_Color = vec4(0.1,0.1,0.1,0.1);
}
