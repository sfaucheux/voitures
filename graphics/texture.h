#include <GL/glew.h>
#include <string>
#include <png++/png.hpp>
#include <iostream>
#include <istream>

class Texture
{
    public:
        Texture();
        GLuint getId() const;
        void load(std::string name);       
    private:
        GLuint m_id ;
};
