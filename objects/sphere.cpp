#include "sphere.h"
namespace  Orchid
{
	Sphere::Sphere(Vector3d position, double radius, Material material)

	{
		_position = position;
		_radius = radius;
		_material = material;
	}
	ObjectIntersection Sphere::getIntersection(const Ray & ray)
	{
        ObjectIntersection object;
        Vector3d loc=ray.origin();
        Vector3d dir=ray.direction();
        double a=dir.dot(dir);
        double b=2.0*dir.dot(loc-_position);
        double c=(loc-_position).dot(loc-_position)-_radius*_radius;
        double delt=b*b-4*a*c;
        double t0,t1;
        if(delt>=0){
            t0=0.5*(-b-sqrt(delt));
            t1=0.5*(-b+sqrt(delt));
            if(t0>0 || t1>0){
                t0=t0>0? t0 :(t1>0 ? t1 : 0);
                object._hit=true;
                Vector3d hitpt=loc+dir*t0;
                object._material=_material;
                object._normal=(hitpt-_position).normalized();
//                    std::cout<<(hitpt-_position).normalized()<<std::endl;
                object._u=t0;
                return object;
            }
        }
		return ObjectIntersection(0, 0, Vector3d(0.0), Material(DIFF));

	}
}
