#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#include "graphics/context.h"
#include "graphics/renderer.h"
#include "physic/pworld.h"

#define width 1024
#define height 768

using namespace std ;

void drawObjectWithEdges(Object& obj, Shader* shdr1, Shader* shdr2, Renderer& renderer)
{
    obj.setShader(shdr2);
    renderer.draw(obj); 
    obj.setShader(shdr1);
    renderer.draw(obj, GL_LINE); 
}

int main(int argc, char** argv)
{
    /*
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

    PWorld world(glm::vec3(0,0,-10)) ;
    //Mesh obj(filename);
    Sphere sphere1(10);
    Sphere sphere2(10);
    Sphere sphere3(10);
    Sphere sphere4(10);
    sphere1.getPObject()->setVelocity(glm::vec3(0,20,8));
    sphere4.getPObject()->setVelocity(glm::vec3(0,1,5));
    sphere2.getPObject()->setVelocity(glm::vec3(1,0,8));
    sphere3.getPObject()->setVelocity(glm::vec3(0,3,8));

    sphere1.getPObject()->setAngularVelocity(glm::vec3(-2,10,0));
    sphere4.getPObject()->setAngularVelocity(glm::vec3(1,0,10));
    sphere3.getPObject()->setAngularVelocity(glm::vec3(8,0,2));
    sphere2.getPObject()->setAngularVelocity(glm::vec3(1,0,0));

    sphere3.getPObject()->setStatic(false);
    //sphere4.getPObject()->setStatic(true);
    //sphere1.getPObject()->setStatic(true);
    world.addObject(sphere4.getPObject());
    world.addObject(sphere3.getPObject());
    world.addObject(sphere1.getPObject());
    world.addObject(sphere2.getPObject());

    sphere1.translate(glm::vec3(1, -40, 0));
    sphere2.translate(glm::vec3(6, 15, 30));
    sphere3.translate(glm::vec3(2, 0, 0));
    sphere4.translate(glm::vec3(3, -20, 35));

    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    Shader grayShdr("shaders/gris.vert", "shaders/couleur3D.frag");

    while (context.eventLoop())
    {
        //usleep(1000);
        world.update(context.getFrametime());
        sphere4.sync();
        sphere1.sync();
        sphere2.sync();
        sphere3.sync();
        context.clean();
        drawObjectWithEdges(sphere4, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere1, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere2, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere3, &greenShdr, &grayShdr, renderer);
        context.show();

        //cout << 1/context.getFrametime() << "\x1B[F"  << endl ;;
        //cout << sphere4.getPObject()->getAngularVelocity().x << ", " << sphere4.getPObject()->getAngularVelocity().y << ", " << sphere4.getPObject()->getAngularVelocity().z << "\x1B[F" << endl;
        //cout << "norme : " << l2Norm(sphere4.getPObject()->getAngularVelocity()) << endl ;
    }

    return 0;
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

    PWorld world(glm::vec3(0,0,-9.81)) ;
    //Mesh obj(filename);
    Box box(20, 50, 30);
    Sphere sphere(20);
    //world.addObject(obj.getPObject());

    box.translate(glm::vec3(0, 45, 0));
    box.rotate(glm::vec3(2.8, 0.5, 1.3));

    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    Shader grayShdr("shaders/gris.vert", "shaders/couleur3D.frag");

    while (context.eventLoop())
    {
        //world.update(0.05);
        context.clean();
        if (box.getPObject()->collide(sphere.getPObject()))
        {
            drawObjectWithEdges(box, &redShdr, &grayShdr, renderer);
            drawObjectWithEdges(sphere, &redShdr, &grayShdr, renderer);
        }
        else
        {
            drawObjectWithEdges(box, &greenShdr, &grayShdr, renderer);
            drawObjectWithEdges(sphere, &greenShdr, &grayShdr, renderer);
        }
        context.show();

        if (context.keyIsPressed(GLFW_KEY_W))
            sphere.translate(glm::vec3(-1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_S))
            sphere.translate(glm::vec3(1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_A))
            sphere.translate(glm::vec3(0, 1, 0));
        if (context.keyIsPressed(GLFW_KEY_D))
            sphere.translate(glm::vec3(0, -1, 0));
        if (context.keyIsPressed(GLFW_KEY_R))
            sphere.translate(glm::vec3(0, 0, -1));
        if (context.keyIsPressed(GLFW_KEY_F))
            sphere.translate(glm::vec3(0, 0, 1));
        if (context.keyIsPressed(GLFW_KEY_V))
            box.rotate(glm::vec3(0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_B))
            box.rotate(glm::vec3(0, 0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_N))
            box.rotate(glm::vec3(0, 0, 0.01));
        if (context.keyIsPressed(GLFW_KEY_G))
            box.rotate(glm::vec3(-0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_H))
            box.rotate(glm::vec3(0, -0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_J))
            box.rotate(glm::vec3(0, 0, -0.01));

        cout << box.getPObject()->getRotation().x << ", " << box.getPObject()->getRotation().y << ", " << box.getPObject()->getRotation().z << "\x1B[F" << endl;

        usleep(50000);
    }*/

    return 0;

}
