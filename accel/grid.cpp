#include "grid.h"

namespace Orchid
{
    void Box::Init()
    {
        Total.bl={300,300,300};
        Total.tr={0,0,0};
        aabbox=new AABBox[8];
        array.resize(8);
    }
    void Box::Dividebox()
    {
        //bl min,tr max
        
        Vector3d bl=Total.bl;
        Vector3d tr=Total.tr;
        
        Vector3d mid=(tr-bl)/2.0;
        Vector3d n_bl(0,0,0);
        Vector3d n_tr(0,0,0);
        
        int id=0;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    n_bl={bl.x()+i*mid.x(),bl.y()+j*mid.y(),bl.z()+k*mid.z()};
                    n_tr=n_bl+mid;
                    aabbox[id].bl=n_bl;
                    aabbox[id].tr=n_tr;
                    id++;
                }
            }
        }
    }
    int Box::getid(Vector3d &p){
        Vector3d mid=(Total.tr+Total.bl)/2;
        int a=(p.x()>mid.x())? 1:0;
        int b=(p.y()>mid.y())? 1:0;
        int c=(p.z()>mid.z())? 1:0;
        return a*4+b*2+c;
    }
    void Box::Grid(int id, Vector3d &p0, Vector3d &p1, Vector3d &p2)
    {
        int t0=getid(p0);
        int t1=getid(p1);
        int t2=getid(p2);
        t2=(t0==t2)? -1:t2;
        t2=(t1==t2)? -1:t2;
        t1=(t0==t1)? -1:t1;
        array[t0].push_back(id);
        if(t1!=-1) array[t1].push_back(id);
        if(t2!=-1) array[t2].push_back(id);
    }
    AABBox Box::getbox(int i){
        return aabbox[i];
    }
    
}
