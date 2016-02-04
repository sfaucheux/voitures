#include "texture.h"

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
    image<rgba_pixel> img(name);
    if(glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.get_width(), img.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &img.get_pixbuf());
    glBindTexture(GL_TEXTURE_2D, 0);
}
