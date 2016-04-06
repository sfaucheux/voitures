#include "gworld.h"
#include <chrono>
#include <iostream>
using namespace glm;
using namespace std;

GWorld::GWorld()
{
}

GWorld::~GWorld()
{
}

void GWorld::addObject(Drawable* obj)
{
    m_objects.push_back(obj);
}

void GWorld::translateObject(Drawable* obj, vec3 t)
{
    //obj->translate(t);   
}

void GWorld::draw(const Renderer& rdr, GLenum mode)
{

        chrono::time_point<chrono::system_clock> begin, end;
        begin = chrono::system_clock::now();
    for(auto it = m_objects.begin() ; it != m_objects.end() ; it++)
    {
        rdr.draw(**it, mode);
    }
        end = chrono::system_clock::now();
        /*
        cout << "boucle affichage : " << 
            chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;*/
}
