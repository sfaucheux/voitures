#include "context.h"
#include "renderer.h"
#include "pmesh.h"
#include "glm/glm.hpp"
#include <unistd.h>

#define width 1024
#define height 768

using namespace std ;

int main(int argc, char** argv)
{
    Renderer renderer;
	Context context(renderer);
    if (!context.init(width, height, "Jeu de voitures trop de ouf !!!", 16))
    {
        cerr << "Impossible d'initialiser le contexte OpenGL." << endl ;
        return 0;
    }

    PMesh* obj = new PMesh();
    obj->loadObject("gun.obj");

    Drawable drw;
    drw.load(obj->getVertices(), obj->getIndices());
	drw.rotate(glm::vec3(1,0,0), 90);

    Shader shdr1("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader shdr2("shaders/gris.vert", "shaders/couleur3D.frag");

    while (context.eventLoop())
    {
        context.clean();
        drw.setShader(&shdr2);
        renderer.draw(drw); 
        drw.setShader(&shdr1);
        renderer.draw(drw, GL_LINE); 
        context.show();
		drw.rotate(glm::vec3(0,1,0), 0.01);
    }

    return 0;
}
