#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "../core/common.h"
#include "../math/vector3d.h"
#include "../objects/shape.h"
#include <random>

namespace Orchid
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 1);
    namespace helper
    {
        void calcLocalCoords(const Vector3d& w, Vector3d* u, Vector3d* v) {
            Vector3d up={0,1,0};
            *u=w.cross(up);
            *v=(*u).cross(w);
            *u=(*u).normalized();
            *v=(*v).normalized();
        }
    }
    namespace sampler
    {
        void onHemisphere(const Vector3d& normal, Vector3d* direction, double &r1, double &r2)
        {
            const double PI=3.14;
            double radius=sqrt(r1);
            double theta=2*PI*r2;
            double x=radius*cos(theta);
            double y=radius*sin(theta);
            double z=sqrt(1-r1);
            Vector3d loc_x;
            Vector3d loc_y;
            Vector3d loc_z;
            helper::calcLocalCoords(normal,&loc_x,&loc_y);
            loc_z=loc_x.cross(loc_y);
            loc_z=loc_z.normalized();
            *direction={loc_x.x()*x+loc_y.x()*y+loc_z.x()*z,
                loc_x.y()*x+loc_y.y()*y+loc_z.y()*z,
                loc_x.z()*x+loc_y.z()*y+loc_z.z()*z};
            
            
        }
        
        void onTriangle(const Triangle& tri, Vector3d* position, Vector3d* normal, double r1, double r2)
        {
            
        }
        
    }
}
