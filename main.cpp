#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#include "object.h"
#include "graphics/context.h"
#include "graphics/renderer.h"
#include "physic/pworld.h"

#define width 1024
#define height 768

using namespace std;

void drawObjectWithEdges(Object& obj, Shader* shdr1, Shader* shdr2, Renderer& renderer)
{
    obj.getDrawable()->setShader(shdr2);
    renderer.draw(*obj.getDrawable()); 
    obj.getDrawable()->setShader(shdr1);
    renderer.draw(*obj.getDrawable(), GL_LINE); 
}

int main(int argc, char** argv)
{
    string filename = "cube_text.obj";

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

    PWorld world(glm::vec3(0,0,-10)) ;

    Object obj(Mesh(filename.c_str()));
    Object sphere1(Sphere(10));
    Object sphere2(Sphere(10));
    Object sphere3(Sphere(10));
    Object sphere4(Box(60, 60, 10));
    //sphere1.getPObject()->setVelocity(glm::vec3(0,20,8));
    //sphere4.getPObject()->setVelocity(glm::vec3(0,10,5));
    //sphere2.getPObject()->setVelocity(glm::vec3(1,0,8));
    //sphere3.getPObject()->setVelocity(glm::vec3(0,3,8));

    //sphere1.getPObject()->setAngularVelocity(glm::vec3(-2,10,0));
    //sphere4.getPObject()->setAngularVelocity(glm::vec3(1,0,10));
    //sphere3.getPObject()->setAngularVelocity(glm::vec3(8,0,2));
    //sphere2.getPObject()->setAngularVelocity(glm::vec3(1,0,0));

    sphere4.getPObject()->setStatic(true);
    //sphere4.getPObject()->setStatic(true);
    //sphere1.getPObject()->setStatic(true);
    world.addObject(sphere4.getPObject());
    world.addObject(sphere3.getPObject());
    world.addObject(sphere1.getPObject());
    world.addObject(sphere2.getPObject());

    sphere1.translate(glm::vec3(1, -40, 30));
    sphere2.translate(glm::vec3(0, 35, 20));
    sphere3.translate(glm::vec3(2, 60, 20));
    sphere4.translate(glm::vec3(3, 0, -40));
    sphere4.rotate(glm::vec3(-0.01,0,0));
    obj.translate(glm::vec3(50, 0, 0));

    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    Shader grayShdr("shaders/gris.vert", "shaders/texture.frag");
    Texture tex;
    tex.load("textures/mushroom.png");
    obj.getDrawable()->setTexture(&tex);

    while (context.eventLoop())
    {
        usleep(50000);
        world.update(context.getFrametime());
        context.clean();
        drawObjectWithEdges(sphere4, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere1, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere2, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere3, &greenShdr, &grayShdr, renderer);

        drawObjectWithEdges(obj, &greenShdr, &grayShdr, renderer);
        
        context.show();

        //cout << 1/context.getFrametime() << "\x1B[F"  << endl ;;
        //cout << sphere4.getPObject()->getAngularVelocity().x << ", " << sphere4.getPObject()->getAngularVelocity().y << ", " << sphere4.getPObject()->getAngularVelocity().z << "\x1B[F" << endl;
        //cout << "norme : " << l2Norm(sphere4.getPObject()->getAngularVelocity()) << endl ;
    }

    return 0;

}
