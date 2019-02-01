#ifndef T3DMAP_H
#define T3DMAP_H


#include <grids.h>


class T3dMap
{

public :
    T3dMap();
    ~T3dMap();
    void initMap();
    void drawBaseLine();
    void drawMap();
    void setLineOrFill();
    void laserScanData(int *temp);
private :
    double getAver(double * arr)
    {
        double num=0;
        int n=3;//(int)(sizeof(arr)/sizeof(double))/3;
        for(int i=0;i<n;i++)
            num+=arr[3*i+2];
        return num/n;
    }

    void setColor(double z1,double z2,double z3);

 private:
    double **data;
    int M,N;
    int dip;
    double scale;
    bool showBaseLine;
    double max,min;
    bool LineMode;
    int len;
};



#endif // 3DMAP_H
