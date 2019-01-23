#ifndef INTERFACE_H
#define INTERFACE_H




typedef  struct{
     short int  z_speed;
     short int  y_speed;
     short int  x_speed;
}CarSpeedConfig;    



typedef  struct{
     short int  speed;
     short int  type;
     short int position;
}CarPositionConfig; 



typedef  struct{
     short int  m1_speed;
     short int  m2_speed;
     short int  m3_speed;
}CarSingleSpeedConfig; 





#endif 
