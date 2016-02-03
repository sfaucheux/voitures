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
    if (!context.init(width, height, "Jeu de voitures trop de ouf !!!", 0))
    {
        cerr << "Impossible d'initialiser le contexte OpenGL." << endl ;
        return 0;
    }

    PMesh* obj = new PMesh();
    obj->loadObject("cube.obj");

    Drawable drw;
    drw.load(obj->getVertices(), obj->getIndices());

    Shader shdr("shaders/couleur3D.vert", "shaders/couleur3D.frag");
    drw.setShader(&shdr);

    while (context.eventLoop())
    {
        context.clean();
        renderer.draw(drw, GL_LINE); 
        context.show();
    }

    return 0;
}
