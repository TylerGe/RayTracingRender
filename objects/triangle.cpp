#include "triangle.h"

namespace Orchid
{
	Triangle::Triangle()
	{

	}
	Triangle::Triangle(const Vector3d & p0, const Vector3d & p1, const Vector3d & p2, Material material)
	{
		_p0 = p0;
		_p1 = p1;
		_p2 = p2;
		_material = material;
	}
	Triangle::Triangle(const Triangle & tri)
	{
		this->operator=(tri);
	}
	Triangle::~Triangle()
	{
	}
	Triangle & Triangle::operator=(const Triangle & tri)
	{
		// TODO: insert return statement here
		this->_p0 = tri._p0;
		this->_p1 = tri._p1;
		this->_p2 = tri._p2;
		this->_material = tri._material;
		return *this;
	}
	Vector3d Triangle::gravity() const
	{
		return Vector3d();
	}
	AABBox Triangle::get_bounding_box()
	{
        AABBox box;
        double tempx,tempy,tempz;
        
        tempx=max3(_p0.x(),_p1.x(),_p2.x());
        tempy=max3(_p0.y(),_p1.y(),_p2.y());
        tempz=max3(_p0.z(),_p1.z(),_p2.z());
        Vector3d bl(tempx,tempy,tempz);
        tempx=min3(_p0.x(),_p1.x(),_p2.x());
        tempy=min3(_p0.y(),_p1.y(),_p2.y());
        tempz=min3(_p0.z(),_p1.z(),_p2.z());
        Vector3d tr(tempx,tempy,tempz);
        box.bl=bl;
        box.tr=tr;
		return box;
	}
	bool Triangle::triangleInBbox()
	{
		return false;
	}
	Vector3d Triangle::get(int id) const
	{
		Assertion(0 <= id && id <= 2, "ID must be between 0 and 2");
		if (0 == id)
			return _p0;
		if (1 == id)
			return _p1;
		if (2 == id)
			return _p2;
        return Vector3d(0);
        //my: change
	}
	Vector3d Triangle::normal() const
	{
        Vector3d p0p1=_p1-_p0;
        Vector3d p0p2=_p2-_p0;
        return Vector3d::cross(p0p2,p0p1).normalized();
        //my: change
	}
	ObjectIntersection Triangle::getIntersection(const Ray & ray)
	{
        ObjectIntersection object;
        Vector3d loc=ray.origin();
        Vector3d dir=ray.direction();
        Vector3d s1=Vector3d::cross(dir,_p2-_p0);//dxe2
        Vector3d s2=Vector3d::cross(loc-_p0,_p1-_p0);//sxe1
        double t=(s2.dot(_p2-_p0))/(s1.dot(_p1-_p0));//sxe1*e2/dxe2*e1
        double b1=(s1.dot(loc-_p0))/(s1.dot(_p1-_p0));//dxe2*s/dxe2*e1
        double b2=(s2.dot(dir))/(s1.dot(_p1-_p0));//sxe1*d/dxe2*e1
        //        std::cout<<t<<std::endl;
        if(t>=0 and b1>=0 and b2>=0 and (b1+b2)<=1){
//            std::cout<<"hit"<<std::endl;
            object._hit=true;
            object._material=_material;
            object._u=t;
            object._normal=(Vector3d::cross(_p2-_p0,_p1-_p0)).normalized();
            if(object._normal.dot(ray.direction())>0)
            {
                object._normal=-object._normal;
            }
            return object;
        }
		return ObjectIntersection(false, 0.0, Vector3d(0), Material(DIFF,Vector3d(0.0)));
	}
	double Triangle::area() const
	{
		const Vector3d e1 = _p1 - _p0;
		const Vector3d e2 = _p2 - _p0;
		return 0.5 * Vector3d::cross(e1, e2).norm();
	}
}
