#include "texture.h"
#include <iostream>
#include <istream>

using namespace std;
using namespace png;

Texture::Texture() : m_id(0)
{
}

GLuint Texture::getId() const
{
    return m_id;
}
void Texture::load(string name)
{
    ifstream file(name);
    if(file.is_open())
    {
        reader<ifstream> read(file);
        bool rgb = false ; //(read.get_color_type() == color_type_rgb) ;
        image<rgba_pixel> img(name);

        if(glIsTexture(m_id) == GL_TRUE)
            glDeleteTextures(1, &m_id);

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, (rgb)? GL_RGB : GL_RGBA, img.get_width(), img.get_height(), 0, (rgb)? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, &img.get_pixbuf()[0]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier : " << name << endl ;
    }
}
