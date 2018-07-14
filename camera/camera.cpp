#include "camera.h"

namespace Orchid
{
	Camera::Camera
	(
		Vector3d position, Vector3d target, Vector3d up,
		int width, int height,
		double nearPalneDistance, double fov
	) :	_position{ position },
		_up{ up },
		_imageW{ width },
		_imageH{ height },
		_nearPlaneDistance{ nearPalneDistance }
	{
		_cameraVerticalFOV = fov *PI / 180.0f;
		_aspectRatio = (double)_imageW / _imageH;
		_cameraFwd = (target - _position).normalized();
		_cameraRight = _up.cross(_cameraFwd).normalized();
		_cameraUp = _cameraFwd.cross(_cameraRight).normalized()*(-1);///???
		_cameraHorizFOV = _cameraVerticalFOV *_aspectRatio;
		_windowTop = tan(_cameraVerticalFOV / 2.0f)*_nearPlaneDistance;
		_windowRight = tan(_cameraHorizFOV / 2.0f)*_nearPlaneDistance;
	}

	Ray Camera::get_ray(int x, int y, bool jitter, unsigned short * Xi)
	{
//        if(!jitter){
//            double rotiax=(-0.5*_imageW+x)/_imageW;
//            double rotiay=(-0.5*_imageH+y)/_imageH;
//            Vector3d direction=rotiax*_cameraRight+rotiay*_cameraUp;
//            return Ray(_position,direction.normalized());
//        }
        Vector3d unit_rand={erand48(Xi),erand48(Xi),0};
        double rotiax=(-0.5*_imageW+unit_rand.x()+x)/(double)_imageW;
        double rotiay=(-0.5*_imageH+unit_rand.y()+y)/(double)_imageH;
//        double rotiax = 2*(unit_rand.x()+(double)x)/(double)_imageW-1.0;
//        double rotiay = 2*(unit_rand.y()+(double)y)/(double)_imageH-1.0;
        Vector3d direction=rotiax*_windowRight*_cameraRight + rotiay*_cameraUp*_windowTop+_cameraFwd*_nearPlaneDistance;
        return Ray(_position,direction.normalized());
	}

}
