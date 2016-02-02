#include "context.h"
#include "renderer.h"
#include "glm/glm.hpp"

int main(int argc, char** argv)
{
	Renderer renderer;
	Context context(renderer);

    context.init(1024, 768, "Jeu de voitures trop de ouf !!!", 0);
    while (context.eventLoop())
    {
        context.clean();
        context.show();
    }

    return 0;
}
