#include "material.h"
//#include "../sample/sampler.h"

namespace Orchid
{
    
	Material::Material
	(MaterialType t, Vector3d colour, Vector3d emission, Texture texture)
		:_type{ t }
		, _colour{ colour }
		, _emission{ emission }
		, _texture{ texture }  //nead addd
	{

	}

	Material & Material::operator=(Material  m)
	{
		this->_type = m._type;
		this->_emission = m._emission;
		this->_texture = m._texture;
		this->_colour = m._colour;
		return *this;
	}

	Vector3d Material::get_colour_at(double u, double v) const
	{
		if (_texture.is_loaded())
			return _texture.get_pixel(u, v);
		return _colour;
	}

	Ray Material::get_reflected_ray
	(
		const Ray & r, 
		Vector3d & p, 
		const Vector3d & n,
		unsigned short * Xi
	) const
	{
        
        Vector3d direction;
        if(_type==SPEC){
            direction=r.direction()-n*(2*n.dot(r.direction()));
            return Ray(p,direction.normalized());
        }
        if(_type==DIFF){
            double r1=erand48(Xi);
            double r2=erand48(Xi);
            
            const double PI=3.14;
            double radius=sqrt(r1);
            double theta=2*PI*r2;
            double x=radius*cos(theta);
            double y=radius*sin(theta);
            double z=sqrt(1-r1);
            
            Vector3d w=n;
            Vector3d u=((abs(w.x())>.1 ?Vector3d(0,1):Vector3d(1)).cross(w)).normalized();
            Vector3d v=w.cross(u).normalized();
            Vector3d direction = (u*x + v*y + w*z).normalized();
            return Ray(p,direction);
        }
        return r;
	}
}
