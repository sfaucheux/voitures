#include <string>
#include <iostream>
#include <unistd.h>
#include <chrono>

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
    stack<const Node*> s;
    if(world.getPWorld().getOctree() != nullptr)
        s.push(world.getPWorld().getOctree());

    while(!s.empty())
    {
        const Node* node = s.top();
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
            AABB b = world.getPWorld().getPObject((*it))->getAABB();
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
    //obj.translate(glm::vec3(50, 0, 0));*/


    Object b1(Box(1200, 1200, 60));
    world.addObject(b1);
    Object b2(Box(1200, 1200, 60));
    world.addObject(b2);

    b1.getPObject()->setStatic(true);
    b2.getPObject()->setStatic(true);

    world.translateObject(b1, vec3(-600, -500, 0)); 
    world.rotateObject(b1, vec3(-0.25, 0.0, 0)); 
    world.translateObject(b2, vec3(-600 ,500, 0)); 
    world.rotateObject(b2, vec3(0.25 , 0.0, 0)); 

    for (int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0 ; j < 10 ; j++)
        {
            Object* s = new Object(Sphere(20));
            s->getPObject()->setVelocity(vec3(rand()%20 -20,rand()%20 -20,rand()%20 -20));
            world.addObject(*s);
            world.translateObject(*s, vec3(i*50 - 1000, j*50 , 400));

           /* Object* s = new Object(Box(20, 20, 20));
            s->getPObject()->setVelocity(vec3(rand()%20 -20,rand()%20 -20,rand()%20 -20));
            world.addObject(*s);
            world.translateObject(*s, vec3(i*50 - 1000, j*50 , 500));*/
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
        chrono::time_point<chrono::system_clock> begin, ph, aff, cl;
        begin = chrono::system_clock::now();

        world.getPWorld().update(context.getFrametime());

        ph = chrono::system_clock::now();

        context.clean();

        cl = chrono::system_clock::now();

        renderer.setDefaultShader(&grayShdr);
        world.getGWorld().draw(renderer);
        renderer.setDefaultShader(&greenShdr);
        world.getGWorld().draw(renderer, GL_LINE);
        //drawOctree(renderer, world);

        /*if(b1.getPObject()->getGeometry().collide(&b2.getPObject()->getGeometry()))
        {
            vector<tuple<vec3,vec3>> z = b1.getPObject()->getGeometry().collisionPoints(&b2.getPObject()->getGeometry());
            for(int i = 0 ; i < z.size() ; i++)
            {
                vec3 p = get<0>(z[i]);
                Object s(Sphere(2));
                s.getDrawable()->setShader(&redShdr);
                world.translateObject(s, p);
                renderer.draw(*s.getDrawable());
            }
        }*/
        context.show();/*
        if (context.keyIsPressed(GLFW_KEY_W))
            world.translateObject(b1,glm::vec3(-1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_S))
            world.translateObject(b1,glm::vec3(1, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_A))
            world.translateObject(b1,glm::vec3(0, 1, 0));
        if (context.keyIsPressed(GLFW_KEY_D))
            world.translateObject(b1,glm::vec3(0, -1, 0));
        if (context.keyIsPressed(GLFW_KEY_R))
            world.translateObject(b1,glm::vec3(0, 0, -1));
        if (context.keyIsPressed(GLFW_KEY_F))
            world.translateObject(b1,glm::vec3(0, 0, 1));
        if (context.keyIsPressed(GLFW_KEY_V))
            world.rotateObject(b1,glm::vec3(0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_B))
            world.rotateObject(b1,glm::vec3(0, 0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_N))
            world.rotateObject(b1,glm::vec3(0, 0, 0.01));
        if (context.keyIsPressed(GLFW_KEY_G))
            world.rotateObject(b1,glm::vec3(-0.01, 0, 0));
        if (context.keyIsPressed(GLFW_KEY_H))
            world.rotateObject(b1,glm::vec3(0, -0.01, 0));
        if (context.keyIsPressed(GLFW_KEY_J))
            world.rotateObject(b1,glm::vec3(0, 0, -0.01));*/
/*
        if(b1.getPObject()->getGeometry().collide(&b2.getPObject()->getGeometry()))
            cout << "collision" << endl ;
        else
            cout << "pas collision" << endl ;
      
        aff = chrono::system_clock::now();

        cout << "physique : " << 
            chrono::duration_cast<chrono::milliseconds>(ph-begin).count() << "ms" << endl;
        cout << "affichage : " << 
            chrono::duration_cast<chrono::milliseconds>(aff-cl).count() << "ms" << endl;
        cout << "clear : " << 
            chrono::duration_cast<chrono::milliseconds>(cl-ph).count() << "ms" << endl;
        cout << "FPS : " <<  1/context.getFrametime() << endl ; // "\x1B[F"  << endl ;;*/
    }

    return 0;

}
