#include "quad.h"

namespace Orchid
{
	Quad::Quad(
		const Vector3d & a,
		const Vector3d & b,
		const Vector3d & c,
		const Vector3d & d,
		const Material & material)
		: _a{ a }
		, _b{ b }
		, _c{ c }
		, _d{ d }
		, _material{ material }
	{
	}
	ObjectIntersection Quad::getIntersection(const Ray & ray)
	{
        ObjectIntersection object;
        Vector3d loc=ray.origin();
        Vector3d dir=ray.direction();
        Vector3d s1=Vector3d::cross(dir,_c-_d);//dxe2
        Vector3d s2=Vector3d::cross(loc-_d,_a-_d);//sxe1
        double t=s2.dot(_c-_d)/s1.dot(_a-_d);//sxe1*e2/dxe2*e1
        double b1=s1.dot(loc-_d)/s1.dot(_a-_d);//dxe2*s/dxe2*e1
        double b2=s2.dot(dir)/s1.dot(_a-_d);//sxe1*d/dxe2*e1
//        std::cout<<t<<std::endl;
        if(t>=0 and b1>=0 and b2>=0 and (b1+b2)<=1){
            object._hit=true;
            object._material=_material;
            object._u=t;
            object._normal=(Vector3d::cross(_c-_d,_a-_d)).normalized();
            if(object._normal.dot(ray.direction())>0){
                object._normal=-object._normal;
            }
//            std::cout<<ray.origin()+t*ray.direction()<<std::endl;
            return object;
        }
        
        s1=Vector3d::cross(dir,_a-_b);
        s2=Vector3d::cross(loc-_b,_c-_b);
        t=s2.dot(_a-_b)/s1.dot(_c-_b);
        b1=s1.dot(loc-_b)/s1.dot(_c-_b);
        b2=s2.dot(dir)/s1.dot(_c-_b);
        if(t>=0 and b1>=0 and b2>=0 and (b1+b2)<=1){
            object._hit=true;
            object._material=_material;
            object._u=t;
            object._normal=(Vector3d::cross(_a-_b,_c-_b)).normalized();
            if(object._normal.dot(ray.direction())>0){
                object._normal=-object._normal;
            }
            return object;
        }
        
		return ObjectIntersection(false, 0.0, Vector3d(0), Material(DIFF,Vector3d(0.0)));
	}
}
