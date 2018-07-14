#include "scene.h"
#include <random> 
#include "../sample/sampler.h"
namespace Orchid
{
	
	
	void Scene::add(Object * object)
	{
		_objects.push_back(object);
	}

	ObjectIntersection Scene::intersect(const Ray & ray)
	{
		ObjectIntersection isct = ObjectIntersection();
		ObjectIntersection temp;
		long size = _objects.size();

		for (int i = 0; i < size; i++)
		{
			temp = _objects.at((unsigned)i)->getIntersection(ray);
            
            
			if (temp._hit) {
				if (isct._u == 0 || temp._u < isct._u) isct = temp;
			}
		}
		return isct;
	}

	Vector3d Scene::trace_ray(const Ray & ray, int depth, unsigned short * Xi)
	{
        ObjectIntersection isct=intersect(ray);
        if(isct._hit){
            if(isct._material.getType()==EMIT){
//                std::cout<<"Sign"<<std::endl;
                return isct._material.get_emission();
            }
            if(depth>=4){
//                return Vector3d();
                return isct._material.get_colour();
            }
            double cos=isct._normal.dot(-ray.direction())/(isct._normal.norm()*ray.direction().norm());
            Vector3d location=ray.origin()+ray.direction()*isct._u;
            Ray re_ray=isct._material.get_reflected_ray(ray, location, isct._normal, Xi);
            depth++;
            Vector3d direct={25.0f,25.0f,25.0f};

            return cos*(isct._material.get_colour())*trace_ray(re_ray, depth, Xi);
        }
        
        return Vector3d(0, 0, 0);
	}




}
