#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"

#include "graphics/context.h"
#include "graphics/renderer.h"
#include "objects/mesh.h"
#include "objects/box.h"

#define width 1024
#define height 768

using namespace std ;

int main(int argc, char** argv)
{
    string filename = "suzanne.obj";

    if (argc > 1)
    {
        filename = string(argv[1]);
    }

    Renderer renderer;
    Context context(renderer);
    if (!context.init(width, height, "obj viewer", 4))
    {
        cerr << "Impossible d'initialiser le contexte OpenGL." << endl;
        return 0;
    }

    //Mesh obj(filename);
    Box obj(20, 50, 20);

    obj.rotate(glm::vec3(3.1415 / 2.0, 0, 0)); // 90 degrés

    Shader shdr1("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader shdr2("shaders/gris.vert", "shaders/couleur3D.frag");

    while (context.eventLoop())
    {
        context.clean();
        obj.setShader(&shdr2);
        renderer.draw(obj); 
        obj.setShader(&shdr1);
        renderer.draw(obj, GL_LINE); 
        context.show();
        obj.rotate(glm::vec3(0,0.02,0));

        usleep(50000);
    }

    return 0;
}
