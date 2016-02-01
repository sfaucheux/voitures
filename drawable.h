#ifndef Drawable_H
#define Drawable_H

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

#ifdef __LINUX__
    #include <unistd.h>
#endif // __LINUX__

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <iostream>
//#include "Shader.h"

class Drawable
{
    public:
        Drawable() ;
        //Drawable(std::vector<float> textures, Shader* shader, std::string nomTexture);
        virtual ~Drawable();

        /*void SetVertices(std::vector<float> vertices);
        void SetCouleurs(std::vector<float> couleurs);
        void SetTextures(std::vector<float> textures);
        void SetNomTexture(std::string nom);
        void SetShader(Shader *shader);
        void SetModel(glm::mat4 model) ;


        const std::vector<float>& GetVertices() const;
        const std::vector<float>& GetCouleurs() const;
        const std::vector<float>& GetTextures() const;
        const glm::mat4& GetModel() const;

        std::string GetNomTexture() const;
        const Shader* GetShader() const;
        GLuint GetIdVAO() const;
        GLuint GetIdVBO() const;
        int GetVerticesNumber() const;

        void Tourner(glm::vec3 axe, float angle);
        void Translater(glm::vec3 translation);
        void Homothetie(glm::vec3 homothetie) ;

		void Charger(std::vector<float> &vertices, std::vector<float> &couleurs);
        void MiseAJour(const std::vector<float> &donnees, int decalage);*/


    protected:

        GLuint m_idVAO;
        GLuint m_idVBO;

        std::vector<float> m_vertices;
        std::vector<float> m_couleurs;
        std::vector<float> m_textures;
        //Shader* m_shader;
        std::string m_nomTexture;
        int m_verticesNumber;
        glm::mat4 m_model;
};

#endif
