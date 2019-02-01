#include "grids.h"

Grids::Grids()
{
    row = 0;
    col = 0;
    mat = 0;
}

Grids::Grids(int r, int c)
{
    row = r;
    col = c;
    mat = 0;
}

Grids::Grids(int r, int c, double **m)
{
    row = r;
    col = c;
    mat = m;
}

Grids::~Grids()
{
    mat=0;
    row=0;
    col=0;
}

void Grids::Mul_Mat(Grids* m1, Grids* m2, Grids* m3)
{
    int i=0,j=0,p=0;
//    double sum=0;
    if (m1->col != m2->row) {
        cout<<"\n行、列数不匹配!";
        exit(0);
    }
    m3->row=m1->row;
    m3->col=m2->col;
    m3->mat=new double*[m1->row];
    if (NULL==m3->mat) {
        cout<<"ERROR!\n";
        exit(0);
    }
    for (i=0;i<m3->row;i++) {
        m3->mat[i]=new double[m3->col];
        for (j=0;j<m3->col;j++) {
            for (m3->mat[i][j]=0,p=0;p<m1->col;p++) {
                m3->mat[i][j]+=m1->mat[i][p]*m2->mat[p][j];
            }
        }
    }
}

void Grids::Inv_Mat(Grids* m1, Grids* m2)
{
    int i,j,n,*is,*js,k;
    double d,p;
    if(m1->row!=m1->col) {
        cout<<"ERROR! 必须是方阵才能求逆!\n";
        exit(1);
    }
    m2->mat=new double*[m1->row];//申请行指针数组
    if(NULL==m2->mat){
        cout<<"ERROR! 申请内存出错!\n";
        exit(1);
    }
    for (i=0;i<m1->row;i++) {
        m2->mat[i]=new double[m1->col];//申请行
        for (j=0;j<m1->col;j++)
            m2->mat[i][j]=m1->mat[i][j];
    }
    n=m1->row;
    m2->row=m1->row;
    m2->col=m1->col;
    is=new int[n];
    js=new int[n];
    if (NULL==is || NULL==js){
        cout<<"ERROR! 申请内存出错!\n";
        exit(1);
    }
    for (k=0;k<=n-1;k++){ //全选主元
        d=0.000;
        for (i=k;i<=n-1;i++){
            for (j=k;j<=n-1;j++){
                p=fabs(m2->mat[i][j]);
                if (p>d){
                    d=p;
                    is[k]=i;
                    js[k]=j;
                }
            }
        }
        if(1.0==d+1.0){
            delete []is;
            delete []js;
            cout<<"ERROR ! 矩阵求逆出错!\n";
            exit(1);
        }
        if(is[k]!=k){ /*行交换*/
            for (j=0;j<=n-1;j++){
                p=m2->mat[k][j];
                m2->mat[k][j]=m2->mat[is[k]][j];
                m2->mat[is[k]][j]=p;
            }
        }
        if(js[k] != k) { /*列交换*/
            for (i=0;i<=n-1;i++) {
                p=m2->mat[i][k];
                m2->mat[i][k]=m2->mat[i][js[k]];
                m2->mat[i][js[k]]=p;
            }
        }
        m2->mat[k][k]=1/m2->mat[k][k];
        for (j=0;j<=n-1;j++){
            if (j != k){
                m2->mat[k][j]=m2->mat[k][j]*m2->mat[k][k];
            }
        }
        for (i=0;i<=n-1;i++){
            if(i!=k){
                for (j=0;j<=n-1;j++){
                    if(j!=k){
                        m2->mat[i][j]=m2->mat[i][j]-m2->mat[i][k]*m2->mat[k][j];
                    }
                }
            }
        }
        for (i=0;i<=n-1;i++){
            if (i!=k){
                m2->mat[i][k]=-m2->mat[i][k]*m2->mat[k][k];
            }
        }
    }
    for (k=n-1;k>=0;k--){
        if (js[k]!=k){
            for (j=0;j<=n-1;j++){
                p=m2->mat[k][j];
                m2->mat[k][j]=m2->mat[js[k]][j];
                m2->mat[js[k]][j]=p;
            }
        }
        if (is[k] != k){
            for (i=0;i<=n-1;i++){
                p=m2->mat[i][k];
                m2->mat[i][k]=m2->mat[i][is[k]];
                m2->mat[i][is[k]]=p;
            }
        }
    }
    delete []is;
    delete []js;
}

double** Grids::Surface_Fitting(Grids* m1, Grids* m2)
{  // m1为已知数组R,m2为自变量数组
    int i,j;
    double ipso=0.05;
    Grids *R=new Grids(m1->col+3,m1->col+3);
    R->mat=new double*[R->row];
    for(i=0;i<R->row;i++)
        R->mat[i]=new double[R->col];
    for(i=0;i<R->row;i++){
        for(j=0;j<R->col;j++){
            if(i<m1->col&&j<m1->col){
                if(i==j)
                    R->mat[i][j]=ipso;
                else
                    R->mat[i][j]=sqrt(pow(m1->mat[0][i] - m1->mat[0][j],2)+pow(m1->mat[1][i] - m1->mat[1][j],2));
            }
            if(i>=m1->col&&j<m1->col){
                if(i==m1->col)
                    R->mat[i][j]=1;
                else
                    R->mat[i][j]=m1->mat[i-m1->col-1][j];
            }
            if(i<m1->col&&j>=m1->col){
                if(j==m1->col)
                    R->mat[i][j]=1;
                else
                    R->mat[i][j]=m1->mat[j-(m1->col)-1][i];
            }
            if(i>=m1->col&&j>=m1->col){
                R->mat[i][j]=0;
            }
        }
    }

    Grids *z1=new Grids(m1->col+3,1);
    Grids *invm1=new Grids();
    Grids *F=new Grids();
    z1->mat=new double*[z1->row];
    for(i=0;i<z1->row;i++){
        z1->mat[i]=new double[z1->col];
        for(j=0;j<z1->col;j++){
            if(i<m1->col)
                z1->mat[i][j]=m1->mat[2][i];
            else
                z1->mat[i][j]=0;
        }
    }
    Inv_Mat(R, invm1);

    Mul_Mat(invm1, z1, F);

    Grids *z=new Grids();
    Grids *r=new Grids(m2->col,F->row);
    r->mat=new double*[r->row];
    for(i=0;i<r->row;i++)
        r->mat[i]=new double[r->col];
    for(i=0;i<r->row;i++){
        for(j=0;j<m1->col+3;j++){
            if(j<m1->col){
                double temp=sqrt(pow(m2->mat[0][i] - m1->mat[0][j],2)+pow(m2->mat[1][i] - m1->mat[1][j],2));
                r->mat[i][j]=temp*log(temp+ipso);
            }
            else{
                if(j==m1->col)
                    r->mat[i][j]=1;
                else
                    r->mat[i][j]=m2->mat[j-m1->col-1][i];
            }
        }
    }
/*    FF->mat=new double*[FF->row];
    for(i=0;i<FF->row;i++)
        FF->mat[i]=new double[FF->col];
    for(i=0;i<FF->row;i++){
        for(j=0;j<FF->col;j++){
            if(i<m2->col)
                FF->mat[i][j]=F->mat[i/4][j/4];
            else
                FF->mat[i][j]=F->mat[i-m2->col+m1->col][j];
        }
    }*/
    Mul_Mat(r, F, z);

    Grids *xyz=new Grids(m2->row+1,m2->col);
    xyz->mat=new double*[xyz->row];
    for(i=0;i<xyz->row;i++)
        xyz->mat[i]=new double[xyz->col];
    for(i=0;i<xyz->row;i++){
        for(j=0;j<xyz->col;j++){
            if(i<m2->row)
                xyz->mat[i][j]=m2->mat[i][j];
            else
                xyz->mat[i][j]=z->mat[j][0];
        }
    }
    for(i=0;i<R->row;i++)
        delete [] R->mat[i];
    delete [] R->mat;
    for(i=0;i<z1->row;i++)
        delete [] z1->mat[i];
    delete [] z1->mat;
    for(i=0;i<invm1->row;i++)
        delete [] invm1->mat[i];
    delete [] invm1->mat;
    for(i=0;i<F->row;i++)
        delete [] F->mat[i];
    delete [] F->mat;
    for(i=0;i<z->row;i++)
        delete [] z->mat[i];
    delete [] z->mat;
    for(i=0;i<r->row;i++)
        delete [] r->mat[i];
    delete [] r->mat;
    return xyz->mat;
}
