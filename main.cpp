#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"

#include "graphics/context.h"
#include "graphics/renderer.h"
#include "objects/mesh.h"
#include "objects/box.h"
#include "objects/sphere.h"
#include "physic/pworld.h"
#include "physic/pbox.h"

#define width 1024
#define height 768

using namespace std ;

void drawObjectWithEdges(Object& obj, Shader* shdr1, Shader* shdr2, Renderer& renderer)
{
    obj.getDrawable()->setShader(shdr2);
    renderer.draw(*obj.getDrawable()); 
    obj.getDrawable()->setShader(shdr1);
    renderer.draw(*obj.getDrawable(), GL_LINE); 
}

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

    PWorld world(glm::vec3(0,0,-9.81)) ;
    //Mesh obj(filename);
    Box box(20, 50, 30);
    Sphere sphere(20);
    //world.addObject(obj.getPObject());

//    box.getCoordinates().translate(glm::vec3(0, 45, 0));
//    box.getCoordinates().rotate(glm::vec3(2.8, 0.5, 1.3));

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
            sphere.getCoordinates().translate(glm::vec3(-1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_S))
            sphere.getCoordinates().translate(glm::vec3(1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_A))
            sphere.getCoordinates().translate(glm::vec3(0, 1, 0));
        if (context.keyIsPressed(GLFW_KEY_D))
            sphere.getCoordinates().translate(glm::vec3(0, -1, 0));
        if (context.keyIsPressed(GLFW_KEY_R))
            sphere.getCoordinates().translate(glm::vec3(0, 0, -1));
        if (context.keyIsPressed(GLFW_KEY_F))
            sphere.getCoordinates().translate(glm::vec3(0, 0, 1));
        if (context.keyIsPressed(GLFW_KEY_V))
            box.getCoordinates().rotate(glm::vec3(0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_B))
            box.getCoordinates().rotate(glm::vec3(0, 0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_N))
            box.getCoordinates().rotate(glm::vec3(0, 0, 0.01));
        if (context.keyIsPressed(GLFW_KEY_G))
            box.getCoordinates().rotate(glm::vec3(-0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_H))
            box.getCoordinates().rotate(glm::vec3(0, -0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_J))
            box.getCoordinates().rotate(glm::vec3(0, 0, -0.01));

        cout << box.getCoordinates().getRotation().x << ", " << box.getCoordinates().getRotation().y << ", " << box.getCoordinates().getRotation().z << "\x1B[F" << endl;

        usleep(50000);
    }

    return 0;
}
