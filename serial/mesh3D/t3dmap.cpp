#include "t3dmap.h"
#include <GL/glu.h>


T3dMap::T3dMap()
{
        M=320;
        N=220;
        showBaseLine=true;
        LineMode=false;
        scale=20.0;
        dip=1;
        max=-1000;
        min=10000;
}

 T3dMap::~T3dMap()
 {

 }

void T3dMap::laserScanData(int *temp)
{
    len=5*6;
    int i,j;
    double** src=new double*[3];
    for(i=0;i<3;i++)
        src[i]=new double[len];
    for(i=0;i<5;i++)
    {//y
        for(j=0;j<6;j++)
        {//x
            src[0][i*6+j]=j*10;
            src[1][i*6+j]=i*10;
            src[2][i*6+j]=temp[i*6+j];
        }
    }

    Grids g1(3,len,src);
    double** des=new double*[2];
    for(i=0;i<2;i++)
        des[i]=new double[N*M];
    for(i=0;i<N;i++)
    {//y
        for(j=0;j<M;j++)
        {//x
            des[0][i*M+j]=j/2;
            des[1][i*M+j]=i/2;
        }
    }
    Grids g2(2,N*M,des);
    data=g1.Surface_Fitting(&g1,&g2);

    for(i=0;i<N;i++)
    {//height
        for(int j=0;j<M;j++)
        {//width
            data[0][i*M+j]*=2;
            data[1][i*M+j]*=2;
            data[2][i*M+j]/=5;

            if(max<data[2][i*M+j])
                max=data[2][i*M+j];
            if(min>data[2][i*M+j])
                min=data[2][i*M+j];
        }
    }
    printf("max=%lf,min=%lf\n",max,min);
}




void T3dMap::initMap()
{


    int temp[]={
        229,219,199,216,235,255,266,285,272,241,246,281,284,275,261,273,
        221,214,195,216,234,258,273,289,281,249,259,278,287,272,275,277,
        213,203,196,206,221,232,259,293,294,277,258,285,287,283,288,286,
        204,195,200,201,209,218,231,259,288,306,286,291,301,311,319,298,
        196,207,201,211,239,234,241,259,294,315,317,321,325,322,325,341,
        208,218,204,214,235,260,239,268,298,291,331,313,281,280,280,280,
        216,231,218,196,220,255,271,253,264,303,322,312,276,243,238,239,
        236,242,218,198,200,215,224,238,261,294,324,312,280,255,220,200,
        255,241,219,211,206,225,252,275,284,285,305,316,271,237,208,191,
        245,218,207,198,214,241,261,256,273,276,291,298,281,238,197,175,
        225,215,205,195,208,221,235,252,262,271,301,275,245,212,181,171
    };
    len=11*16;
    int i,j;
    double** src=new double*[3];
    for(i=0;i<3;i++)
        src[i]=new double[len];
    for(i=0;i<11;i++)
    {//y
        for(j=0;j<16;j++)
        {//x
            src[0][i*16+j]=j*10;
            src[1][i*16+j]=i*10;
            src[2][i*16+j]=temp[i*16+j];
        }
    }

    Grids g1(3,len,src);
    double** des=new double*[2];
    for(i=0;i<2;i++)
        des[i]=new double[N*M];
    for(i=0;i<N;i++)
    {//y
        for(j=0;j<M;j++)
        {//x
            des[0][i*M+j]=j/2;
            des[1][i*M+j]=i/2;
        }
    }
    Grids g2(2,N*M,des);
    data=g1.Surface_Fitting(&g1,&g2);

    for(i=0;i<N;i++)
    {//height
        for(int j=0;j<M;j++)
        {//width
            data[0][i*M+j]*=2;
            data[1][i*M+j]*=2;
            data[2][i*M+j]/=5;

            if(max<data[2][i*M+j])
                max=data[2][i*M+j];
            if(min>data[2][i*M+j])
                min=data[2][i*M+j];
        }
    }
    printf("max=%lf,min=%lf\n",max,min);
}
void T3dMap::drawBaseLine()
{
        glBegin(GL_LINES);
            glColor3f(1, 0, 0);
            glVertex2i(0,0);//x line
            glVertex2i(100,0);

            glColor3f(0, 1, 0);
            glVertex2i(0,0);//y line
            glVertex2i(0,100);

            glColor3f(0, 0, 1);
            glVertex3f(0,0,0);//
            glVertex3f(0,0,500);
        glEnd();
}

void T3dMap::setColor(double z1,double z2,double z3)
{
    float r,g,b;
    double temp=(max+min)/2;
    double aver=(z1+z2+z3)/3;
    /*printf("%lf  ",aver);*/
    if(aver>temp)
    {
        r=(aver-temp)/(temp-min);
        b=0;
    }else {
        r=0;
        b=(temp-aver)/(temp-min);
    }
    g=1-((abs(temp-aver))/(temp-min));
    glColor3f(r,g,b);
}


void T3dMap::setLineOrFill()
{
    LineMode=!LineMode;
}


void T3dMap::drawMap()
{

    showBaseLine=true;
//    LineMode=false;

    if(showBaseLine)
    {
        drawBaseLine();
    }
    if(LineMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else
     {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
     }
    glLineWidth(0.4f);
    for(int i=0;i<N-1;i++)
    {//height22

        for(int j=0;j<M-1;j++)
        {//width32
            glBegin(GL_TRIANGLE_FAN);
                int t=i*M+j;
                setColor(data[2][t],data[2][t+1],data[2][t+1+M]);

                glVertex3f(data[0][t],data[1][t],data[2][t]);
                glVertex3f(data[0][t+1],data[1][t+1],data[2][t+1]);
                glVertex3f(data[0][t+1+M],data[1][t+1+M],data[2][t+1+M]);
                setColor(data[2][t+M],data[2][t+1],data[2][t+1+M]);
                glVertex3f(data[0][t+M],data[1][t+M],data[2][t+M]);
            glEnd();
        }
    }
}
