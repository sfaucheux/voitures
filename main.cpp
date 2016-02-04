#include <string>
#include <iostream>

#include "glm/glm.hpp"

#include "context.h"
#include "renderer.h"
#include "object.h"
#include "pobject.h" // temporaire, pour la méthode 2. à enlever après les tests

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

    Object obj;
    obj.load(filename);

    // NB les rotations sont en radians

    // Méthode 1 : on appelle rotate sur l'Object
    // => le PObject ainsi que le Drawable sont tournés
    // ce qu'il faut faire dans le main
    obj.rotate(glm::vec3(3.1415 / 2.0, 0, 0)); // 90 degrés

    // Méthode 2 : on appelle rotate sur le PObject
    // puis on utilise Object::sync pour maj le Drawable
    // PWorld pourra appeler translate sur un PObject, et le main, sync
    /*PObject* pObj = obj.getPObject();
    pObj->rotate(glm::vec3(90,0,0));
    obj.sync();*/

    // On notera que l'on ne peut pas faire tourner que le Drawable,
    // le code suivant ne changera rien :
    /*Drawable drw = obj.getDrawable();
    drw.rotate(glm::vec3(1,0,0), 90);*/

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
        obj.rotate(glm::vec3(0,0.01,0));
        cout << "Rotation en y : " << obj.getPObject()->getRotation().y << " radians" << endl;
    }

    return 0;
}
