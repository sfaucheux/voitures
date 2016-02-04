#ifndef Shader_H
#define Shader_H

#include <string>
#include <GL/glew.h>

class Shader
{
    public:
        Shader();
        Shader(Shader const &srcShader);
        Shader(std::string vertexSource, std::string fragmentSource);
        ~Shader();

        Shader& operator=(Shader const &srcShader);

        bool load();
        bool compileShader(GLuint &shader, GLenum type, std::string const &fichierSource);
        GLuint getProgramID() const;
        bool operator==(Shader const& a);


    private:

        GLuint m_vertexID;
        GLuint m_fragmentID;
        GLuint m_programID;

        std::string m_vertexSource;
        std::string m_fragmentSource;

};

#endif
