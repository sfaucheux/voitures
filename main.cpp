#include <string>
#include <iostream>
#include <unistd.h>

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#include "object.h"
#include "graphics/context.h"
#include "graphics/renderer.h"
#include "world.h"

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
    if (!context.init(width, height, "Jeu de voitures trop de ouf !!!", 4))
    {
        cerr << "Impossible d'initialiser le contexte OpenGL." << endl;
        return 0;
    }

    World world ;

    Object obj(Mesh(filename.c_str()));
    Object sphere1(Sphere(15));
    Object sphere2(Sphere(8));
    Object sphere3(Box(10, 60, 10));
    Object sphere4(Box(80, 60, 10));
    //sphere1.getPObject()->setVelocity(glm::vec3(0,20,8));
    //sphere4.getPObject()->setVelocity(glm::vec3(0,10,5));
    //sphere2.getPObject()->setVelocity(glm::vec3(1,0,8));
    //sphere3.getPObject()->setVelocity(glm::vec3(0,3,8));

    //sphere1.getPObject()->setAngularVelocity(glm::vec3(-2,10,0));
    //sphere4.getPObject()->setAngularVelocity(glm::vec3(1,0,10));
    sphere3.getPObject()->setAngularVelocity(glm::vec3(2,0,3));
    //sphere2.getPObject()->setAngularVelocity(glm::vec3(1,0,0));

    //sphere4.getPObject()->setStatic(true);
    //sphere4.getPObject()->setStatic(true);
    //sphere1.getPObject()->setStatic(true);
   

    world.translateObject(sphere1, glm::vec3(20, -20, 60));
    world.translateObject(sphere2, glm::vec3(0, 0, -20));
    world.translateObject(sphere3, glm::vec3(2, 40, 25));
    world.translateObject(sphere4, glm::vec3(3, 10, -40));
    world.rotateObject(sphere4, glm::vec3(-0.2,0,0));
    //obj.translate(glm::vec3(50, 0, 0));
    //
    cout << "Ajout du sol." << endl ;
    world.addObject(sphere4);
    world.getPWorld().getOctree().afficher(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la boite." << endl ;
    world.addObject(sphere3);
    world.getPWorld().getOctree().afficher(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la grande sphere." << endl;
    world.addObject(sphere1);
    world.getPWorld().getOctree().afficher(world.getPWorld().getOctree().getRoot());
    cout << "Ajout de la petite sphere." << endl ;
    world.addObject(sphere2);
    world.getPWorld().getOctree().afficher(world.getPWorld().getOctree().getRoot());

    Shader greenShdr("shaders/vert.vert", "shaders/couleur3D.frag");
    Shader redShdr("shaders/rouge.vert", "shaders/couleur3D.frag");
    Shader grayShdr("shaders/gris.vert", "shaders/texture.frag");
    Texture tex;
    tex.load("textures/mushroom.png");
    obj.getDrawable()->setTexture(&tex);

    while (context.eventLoop())
    {
        world.getPWorld().update(context.getFrametime());
        context.clean();
        drawObjectWithEdges(sphere4, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere1, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere2, &greenShdr, &grayShdr, renderer);
        drawObjectWithEdges(sphere3, &greenShdr, &grayShdr, renderer);

        //drawObjectWithEdges(obj, &greenShdr, &grayShdr, renderer);
       
        //Affichage de l'octree. 
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

        context.show();

        cout << "FPS : " <<  1/context.getFrametime() << "\x1B[F"  << endl ;;
        //cout << sphere4.getPObject()->getAngularVelocity().x << ", " << sphere4.getPObject()->getAngularVelocity().y << ", " << sphere4.getPObject()->getAngularVelocity().z << "\x1B[F" << endl;
        //cout << "norme : " << l2Norm(sphere4.getPObject()->getAngularVelocity()) << endl ;
    }

    return 0;

}
