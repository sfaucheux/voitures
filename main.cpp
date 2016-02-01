#include "context.h"
#include "renderer.h"

int main(int argc, char** argv)
{
	Renderer renderer;
	Context context(renderer);

    while (context.eventLoop())
    {
        context.clean();
        context.show();
    }

    return 0;
}
