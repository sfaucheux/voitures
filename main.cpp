#include "context.h"
#include "renderer.h"
#include "pmesh.h"
#include "glm/glm.hpp"

int main(int argc, char** argv)
{
    Renderer renderer;
	Context context(renderer);
    if (!context.init(1024, 768, "Jeu de voitures trop de ouf !!!", 0))
        exit(EXIT_FAILURE);

    PMesh* obj = new PMesh();
    obj->loadObject("cube.obj");

    Drawable drw;
    drw.load(obj->getVertices(), obj->getIndices());

    Shader shdr("shaders/couleur3D.vert", "shaders/couleur3D.frag");
    drw.setShader(&shdr);

    while (context.eventLoop())
    {
        context.clean();
        renderer.draw(drw);
        context.show();
    }

    return 0;
}
