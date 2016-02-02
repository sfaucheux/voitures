#include "shader.h"

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{
}

Shader::Shader(Shader const &shaderACopier)
{
    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;
    load();
}

Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}

Shader::~Shader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}

Shader& Shader::operator=(Shader const &srcShader)
{
    m_vertexSource = srcShader.m_vertexSource;
    m_fragmentSource = srcShader.m_fragmentSource;
    load();
    return *this;
}

bool Shader::load()
{
    // Destruction d'un éventuel ancien Shader
    if (glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);
    if (glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);
    if (glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);

    // Compilation des shaders
    if (!compileShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;
    if (!compileShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;

    // Création du programme
    m_programID = glCreateProgram();

    // Association des shaders
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

    // Verrouillage des entrées shader
    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");

    // Linkage du programme
    glLinkProgram(m_programID);

    // Vérification du linkage
    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);

    if (erreurLink != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);
        char* erreur = new char[tailleErreur + 1];

        // Récupération de l'erreur
        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        std::cout << erreur << std::endl;

        // Libération de la mémoire
        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    }
    else
    {
        return true;
    }
}

bool Shader::compileShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader
    shader = glCreateShader(type);

    // Vérification du shader
    if (shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    std::ifstream fichier(fichierSource.c_str());
    if (!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);

        return false;
    }

    std::string ligne;
    std::string codeSource;

    // Lecture
    while (getline(fichier, ligne))
        codeSource += ligne + '\n';
    fichier.close();

    // Récupération de la chaine C du code source
    const GLchar* chaineCodeSource = codeSource.c_str();

    // Envoi du code source au shader
    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compilation du shader
    glCompileShader(shader);

    // Vérification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

    if (erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);
        char* erreur = new char[tailleErreur + 1];

        // Récupération de l'erreur
        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';

        std::cout << erreur << std::endl;

        // Libération de la mémoire
        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }
    else
    {
        return true;
    }

}

GLuint Shader::getProgramID() const
{
    return m_programID;
}

bool Shader::operator==(Shader const& a)
{
    if (a.m_vertexSource == m_vertexSource && a.m_fragmentSource == m_fragmentSource)
        return true ;
    return false ;
}
