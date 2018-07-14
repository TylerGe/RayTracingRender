#ifndef _GRID_
#define _GRID_
#include <cfloat>
#include <algorithm>

#include "../math/vector3d.h"
#include "../objects/triangle.h"
#include "aabbox.h"
namespace Orchid{
    class Box{
    private:
        
        AABBox *aabbox;
    public:
        AABBox Total;
        //bl min,tr max
        void Init();
        void Dividebox();
        void Grid(int i,Vector3d &p0,Vector3d &p1,Vector3d &p2);
        int getid(Vector3d &p);
        AABBox getbox(int i);
        std::vector<std::vector<int>> array;
    };
    
}


#endif
