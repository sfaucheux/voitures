#include "pobject.h"

class PBox : public PObject
{
    public:
        PBox(float width, float height, float depth);
    private:
        float m_width;
        float m_height;
        float m_depth;
};
