#include "pobject.h"
#include "drawable.h"

class Object
{
	public:
		Object();
		virtual ~Object();

		void loadObject(

		void rotate(glm::vec3 axis, float angle);
		void translate(glm::vec3 t);
		void homothetie(glm::vec3 h);
	private:
		PObject physMesh;
		Drawable graphMesh;
};
