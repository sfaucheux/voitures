#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#include "object.h"
#include "graphics/context.h"
#include "graphics/renderer.h"
#include "world.h"
#include "stdlib.h"

#define width 1024
#define height 768

using namespace std;
using namespace glm;

void drawOctree(Renderer& renderer, World& world)
{
    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    stack<Node*> s;
    if(world.getPWorld().getOctree().getRoot() != nullptr)
        s.push(world.getPWorld().getOctree().getRoot());

    while(!s.empty())
    {
        Node* node = s.top();
        s.pop();
        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                s.push(node->getChildren()[i]);
            }
        }
        AABB a = node->getAABB();
        Object boite = Object(Box(a.getSize().x, a.getSize().y, a.getSize().z));

        boite.getDrawable()->setShader(&greenShdr);
        world.translateObject(boite, a.getPosition());
        renderer.draw(*boite.getDrawable(), GL_LINE); 
        //cout << "nombre d'objet dans le noeud : " << node->getObjects().size() + node->getObjectCount() << endl;
        for (auto it = node->getObjects().begin() ; it != node->getObjects().end() ; it++)
        {
            AABB b = (*it)->getAABB();
            Object b2 = Object(Box(b.getSize().x, b.getSize().y, b.getSize().z));

            b2.getDrawable()->setShader(&redShdr);
            world.translateObject(b2, b.getPosition());
            renderer.draw(*b2.getDrawable(), GL_LINE); 

        }

    }

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

    if (!context.init(width, height, "Jeu de voitures trop de ouf !!!", 4))
    {
        cerr << "Impossible d'initialiser le contexte OpenGL." << endl;
        return 0;
    }

    World world ;
/*
    Object obj(Mesh(filename.c_str()));
    Object sphere1(Sphere(15));
    Object sphere2(Sphere(8));
    Object sphere3(Box(10, 80, 10));
    Object sphere4(Box(80, 80, 20));


    sphere1.getPObject()->setVelocity(glm::vec3(0,20,8));
    sphere4.getPObject()->setVelocity(glm::vec3(0,10,5));
    sphere2.getPObject()->setVelocity(glm::vec3(1,0,8));
    sphere3.getPObject()->setVelocity(glm::vec3(0,3,8));

    sphere1.getPObject()->setAngularVelocity(glm::vec3(-2,10,0));
    sphere4.getPObject()->setAngularVelocity(glm::vec3(1,0,10));
    sphere3.getPObject()->setAngularVelocity(glm::vec3(2,1,8));
    sphere2.getPObject()->setAngularVelocity(glm::vec3(1,0,0));

    sphere4.getPObject()->setStatic(true);
    //sphere4.getPObject()->setStatic(true);
    //sphere1.getPObject()->setStatic(true);
   
    cout << "Ajout du sol." << endl ;
    world.addObject(sphere4);
    //world.getPWorld().getOctree().print(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la boite." << endl ;
    world.addObject(sphere3);
    //world.getPWorld().getOctree().print(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la grande sphere." << endl;
    world.addObject(sphere1);
    //world.getPWorld().getOctree().print(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la petite sphere." << endl ;
    world.addObject(sphere2);
    //world.getPWorld().getOctree().print(world.getPWorld().getOctree().getRoot());

    world.translateObject(sphere1, glm::vec3(10, -80, 60));
    world.translateObject(sphere2, glm::vec3(5, 20, -0));
    world.translateObject(sphere3, glm::vec3(10, 60, 65));
    world.translateObject(sphere4, glm::vec3(3, 20, -40));
    world.rotateObject(sphere4, glm::vec3(-0.2,0,0));
    //obj.translate(glm::vec3(50, 0, 0));
*/

    Object b1(Box(3000, 3000, 20));
    world.addObject(b1);
    Object b2(Box(3000, 3000, 20));
    world.addObject(b2);

    b1.getPObject()->setStatic(true);
    b2.getPObject()->setStatic(true);

    world.translateObject(b1, vec3(0, -1300, 0)); 
    world.rotateObject(b1, vec3(-0.4, 0.2, 0)); 
    world.translateObject(b2, vec3(0 ,1300, 0)); 
    world.rotateObject(b2, vec3(0.4 , 0.2, 0)); 

    for (int i = 0 ; i < 25 ; i++)
    {
        for(int j = 0 ; j < 25 ; j++)
        {
            Object* s = new Object(Sphere(20));
            s->getPObject()->setVelocity(vec3(rand()%200 -200,rand()%200 -200,rand()%200 -200));
            world.addObject(*s);
            world.translateObject(*s, vec3(i*50 - 1000, j*50 , 400));
        }
    }
    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    Shader grayShdr("shaders/gris.vert", "shaders/texture.frag");
    renderer.setDefaultShader(&grayShdr);

    Texture tex;
    tex.load("textures/mushroom.png");
    //obj.getDrawable()->setTexture(&tex);

    while (context.eventLoop())
    {
        world.getPWorld().update(context.getFrametime());
        context.clean();

        renderer.setDefaultShader(&grayShdr);
        world.getGWorld().draw(renderer);
        renderer.setDefaultShader(&greenShdr);
        world.getGWorld().draw(renderer, GL_LINE);
        
        //drawOctree(renderer, world);
        
        context.show();

        cout << "FPS : " <<  1/context.getFrametime() << "\x1B[F"  << endl ;;
    }

    return 0;

}
