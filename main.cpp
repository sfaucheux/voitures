#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"

#include "graphics/context.h"
#include "graphics/renderer.h"
#include "objects/mesh.h"
#include "objects/box.h"
#include "physic/pworld.h"

#define width 1024
#define height 768

using namespace std ;

int main(int argc, char** argv)
{
    string filename = "van.obj";

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
    PWorld world(glm::vec3(0,0,-0.981));
    Mesh obj(filename);
    Box obj2(15,20,8);
    obj2.translate(glm::vec3(20,20,20));

    world.addObject(obj.getPObject());
    world.addObject(obj2.getPObject());
    obj.rotate(glm::vec3(3.1415 / 2.0, 10, 30)); // 90 degrés

    Texture tex ;
    tex.load("textures/mushroom.png");
    obj.setTexture(&tex);
    obj2.setTexture(&tex);
    Shader shdr1("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader shdr2("shaders/gris.vert", "shaders/texture.frag");

    while (context.eventLoop())
    {
        world.update(0.05);
        obj.sync();
        obj2.sync();
        context.clean();
        obj.setShader(&shdr2);
        obj2.setShader(&shdr2);
        renderer.draw(obj); 
        renderer.draw(obj2); 
        obj.setShader(&shdr1);
        obj2.setShader(&shdr1);
        renderer.draw(obj, GL_LINE); 
        renderer.draw(obj2, GL_LINE); 
        context.show();
        obj.rotate(glm::vec3(0,0.02,0));

        usleep(50000);
    }

    return 0;
}
