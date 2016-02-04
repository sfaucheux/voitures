#ifndef Object_H
#define Object_H

#include <string>

#include "../glm/glm.hpp"

#include "../graphics/shader.h"
#include "../graphics/drawable.h"
#include "../physic/pobject.h"
#include "mesh.h"

class Object
{
	public:
		Object();
		virtual ~Object();

        void setShader(Shader* shader);

        PObject* getPObject();
        Drawable const& getDrawable() const;
        const Shader* getShader() const;

		void load(std::string filename);
        void sync();
        void translate(glm::vec3 t);
        void rotate(glm::vec3 r);


	private:
		PObject m_pObj;
		Drawable m_gObj;
        Mesh m_mesh;

};

#endif
