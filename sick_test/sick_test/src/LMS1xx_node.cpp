
#include <ros/ros.h>

#include <csignal>
#include <cstdio>
#include <LMS1xx/LMS1xx.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>

#include <vector>
#include <string>
#include <sstream>
#include <iostream> 

#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>


#include <sick_msgs/sick_range.h>




using namespace std;
#define DEG2RAD M_PI/180.0


sick_msgs::sick_range  sick_range_;
ros::Publisher sick_data_publisher_;

double pos_x = 0.0;
double pos_y = 0.5;
double theta = 0.0;
double R = 0.5;
double N = 541;
double Pi = 3.1415;
int angle111;
//double Pi=acos(-1.0); //定义Pi
#define scale 10

#define  width 400  
#define  height 400  

LMS1xx laser;
scanData data;

float maxValue=0.0;

typedef  float float32;


struct ObstacleField
{
    float32 angleResolution;
    int startAngle;
    int stopAngle;
    float32 safeRange;
    float32 warnRange;
    float32 maxRange;
};


struct ObstacleField obstacle_msg={0.5,0,180,1,0.5,0.0};//0~185 为120视角,这里是60度




void drawArc(double x,double y,double start_angle,double end_angle,double delta_angle,double radius,bool fill)
{
	if (fill)
	{
		glBegin(GL_TRIANGLE_FAN);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
	}

	for (double i=start_angle;i<=end_angle;i+=delta_angle)
	{
		double vx=x+radius * cos(i);
		double vy=y+radius*sin(i);
		glVertex2d(vx,vy);
	}
	glEnd();
}

void drawCircle(double x, double y, double radius,bool fill)
{
	drawArc(x,y,0,2*M_PI,DEG2RAD,radius,fill);
}

void drawpie(double x,double y,double start_angle,double end_angle,double delta_angle,double radius,bool fill)
{
	drawArc(x,y,start_angle,end_angle,delta_angle,radius,fill);
	if (fill)
	{
		glBegin(GL_TRIANGLE_FAN);
	}
	else
	{
		glBegin(GL_LINES);
	}
	glVertex2d(x,y);
	glVertex2d(x+radius*cos(start_angle),y+radius*sin(start_angle));
	if (!fill)
	{
		glVertex2d(x,y);
	}
	glVertex2d(x+radius*cos(end_angle),y+radius*sin(end_angle));
	 
	glEnd();
}

void drawLine(int angle,double Ttheta,float TmaxValue)
{
 	pos_x = cos((angle*0.5)*DEG2RAD+ Ttheta)*TmaxValue;
	pos_y = sin((angle*0.5)*DEG2RAD+ Ttheta)*TmaxValue;
    glVertex2f(0.0f, 0.0f);
    glVertex2f(pos_x/scale, pos_y/scale);
}

void drawCoordinate()
{
    /*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.5,0.0,0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.5, 0.0f, 0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();


    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.5f, 0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();


    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.5);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.0f, 0.5f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();

}
void Keyboard(int key, int x, int y) //键盘交互 
{ 
    if (key == GLUT_KEY_LEFT)  
    {    
      angle111+=30;
    }   
    if (key == GLUT_KEY_RIGHT)  
    {
      angle111-=30;
    }
    glutPostRedisplay();//重新调用绘制函数


}
  void mymouse(int button,int state,int x,int y) 
  {  
     if(state==GLUT_DOWN)     
     {          
       if(button==GLUT_LEFT_BUTTON)         
        {          
          glTranslatef(-0.5,0,0);//左移   
                    
        }          
        else if(button==GLUT_RIGHT_BUTTON)  
        {             
           glTranslatef(0.5,0,0);//右移  
           
        }           
        glutPostRedisplay();//重新调用绘制函数     
     }      
     return; 
  }

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
 
    glPointSize(2.0f);
    //drawCoordinate();
    //glTranslatef(0,0,0);
    //glRotatef(angle111,0,0,1); 

    glColor3f(1.0,0.0,0.0); 

    //glViewport(100, 100, 400, 400);
/*  
  //画笛卡尔坐标系    

   
    glBegin(GL_LINES);  
    glVertex2d(-width/2.0,0);  
    glVertex2d(width/2.0,0);  
    glEnd();  
    glBegin(GL_LINES);  
    glVertex2d(0,height/2.0);  
    glVertex2d(0,-height/2.0);  
    glEnd();  
*/
    //drawCircle(0,0,1.0,false);  

    drawArc(0,0,obstacle_msg.startAngle*DEG2RAD,obstacle_msg.stopAngle*DEG2RAD,DEG2RAD,obstacle_msg.warnRange/scale,false);  
    drawArc(0,0,obstacle_msg.startAngle*DEG2RAD,obstacle_msg.stopAngle*DEG2RAD,DEG2RAD,obstacle_msg.safeRange/scale,false);  


    glBegin(GL_LINES);  
    glColor3f(0.0f, 0.0f, 1.0f);
     //绘制边线
    drawLine(obstacle_msg.startAngle/obstacle_msg.angleResolution,theta,obstacle_msg.maxRange);
    drawLine(180,theta,obstacle_msg.maxRange);
    drawLine(obstacle_msg.stopAngle/obstacle_msg.angleResolution,theta,obstacle_msg.maxRange);
    glEnd();  

    glBegin(GL_POINTS);
    
    //绘制中心点  
   	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
  	glVertex2f(0.0f, 0.0f);
 
    for (int i = int(obstacle_msg.startAngle/obstacle_msg.angleResolution);
             i < int(obstacle_msg.stopAngle/obstacle_msg.angleResolution); i++)
    {
   
          float tempDist=data.dist1[i] * 0.001; 
        
		      pos_x =(cos((i*0.5) *DEG2RAD + theta)*tempDist);
		      pos_y =(sin((i*0.5) *DEG2RAD + theta)*tempDist);

        
          if(tempDist<obstacle_msg.warnRange)      glColor3f(0.0f, 1.0f, 0.0f);
          else if(tempDist<obstacle_msg.safeRange) glColor3f(1.0f, 1.0f, 0.0f); 
          else                                     glColor3f(1.0f, 1.0f, 1.0f);
		


		      glVertex2f(pos_x/scale, pos_y/scale);
          
          glBegin(GL_LINES);

          glVertex2f(0.0f,0.0f);
          glVertex2f(pos_x/scale, pos_y/scale);
          glEnd();
         
	} 

    glEnd();
    glFlush();
}


void checkObstacle(float Tdegree,float Tradius)
{
     if(Tradius<obstacle_msg.warnRange)         cout<<"the "<<Tdegree<< " degree is dangerous" <<endl;
     else if(Tradius<obstacle_msg.safeRange)    cout<<"the "<<Tdegree<< " degree is warnning"  <<endl;
     else                                       cout<<"the "<<Tdegree<< " degree is safety"    <<endl;
}

void myIdle(void)
{
      cout<<"Reading scan data."<<endl;
      if (laser.getScanData(&data))
       {
         maxValue=0.0;
        //  for (int i = int(obstacle_msg.startAngle/obstacle_msg.angleResolution);
        //          i < int(obstacle_msg.stopAngle/obstacle_msg.angleResolution); i++)
        for (int i = 0;i < 360;i++)
        {
   
          float tempDist=data.dist1[i]; 
            // if(i==180)    cout<<"the num "<< i<<" the value " << tempDist <<endl;
          cout<<"the num "<< i<<" the value " << tempDist <<endl;
          sick_range_.data[i]=tempDist;
          // if(tempDist>=maxValue) maxValue=tempDist;

       //   checkObstacle(i*0.5,tempDist);
          
	    }
      sick_data_publisher_.publish(sick_range_); 
      //  if(maxValue==0.0) maxValue=1.0;    
      //  obstacle_msg.maxRange=maxValue;
      //  cout<< "the max value"<<maxValue<<endl;
      }
      else
      {
        cout<<"Laser timed out on delivering scan, attempting to reinitialize."<<endl;
      }
      Display();
}


int main(int argc, char **argv)
{
  // laser data

  ros::init(argc, argv, "talker");


  ros::NodeHandle n;

  sick_data_publisher_= n.advertise<sick_msgs::sick_range>("/sick_range", 1000);


  scanCfg cfg;
  scanOutputRange outputRange;
  scanDataCfg dataCfg;

  // parameters
    std::string host="192.168.0.11";

    int port=2111;
   
    laser.connect(host, port);
    if (!laser.isConnected())
    {
      cout<<"Unable to connect, retrying."<<endl;;
   
      sleep(1);
      return 0;
    }

    cout<<"Logging in to laser.";
    laser.login();
    cfg = laser.getScanCfg();
    outputRange = laser.getScanOutputRange();

    if (cfg.scaningFrequency != 5000)
    {
      laser.disconnect();
      cout<<"Unable to get laser output range. Retrying."<<endl;;
      sleep(1);
      return 0;
    }

    cout<<"Connected to laser."<<endl;
    cout<<"Laser configuration: scaningFrequency"<<cfg.scaningFrequency<<endl;
    cout<<"Laser configuration: angleResolution"<<cfg.angleResolution<<endl;
    cout<<"Laser configuration: startAngle"<<cfg.startAngle<<endl;
    cout<<"Laser configuration: stopAngle"<<cfg.stopAngle<<endl;
    
    cout<<"Laser output range:angleResolution"<< outputRange.angleResolution<<endl;
    cout<<"Laser output range:startAngle"<< outputRange.startAngle<<endl;
    cout<<"Laser output range:stopAngle"<< outputRange.stopAngle<<endl;


    int angle_range = outputRange.stopAngle - outputRange.startAngle;
    int num_values = angle_range / outputRange.angleResolution ;    
    cout<<"Device resolution is  " << (double)outputRange.angleResolution / 10000.0 << " degrees."<<endl;
    cout<<"Device frequency is  " << (double)cfg.scaningFrequency / 100.0 << " Hz"<<endl;
    cout<<"angle range "<<(double)angle_range/ 10000.0<<endl;
    cout<<"num values "<<num_values<<endl;

    if (angle_range % outputRange.angleResolution == 0)
    {
      // Include endpoint
      ++num_values;
    }

   

    cout<<"num values1"<<num_values<<endl;

    dataCfg.outputChannel = 1;
    dataCfg.remission = true;
    dataCfg.resolution = 1;
    dataCfg.encoder = 0;
    dataCfg.position = false;
    dataCfg.deviceName = false;
    dataCfg.outputInterval = 1;

    cout<<"Setting scan data configuration."<<endl;
    laser.setScanDataCfg(dataCfg);
    cout<<"Starting measurements."<<endl;
    laser.startMeas();
    cout<<"Waiting for ready status."<<endl;


    status_t stat = laser.queryStatus();
    //  cout<<"Laser not read    "<<stat<<endl; 
    sleep(1);
    //  cout<<"Laser not read1   "<<stat<<endl; 
    if (stat != ready_for_measurement)
    {
      cout<<"Laser not ready. Retrying initialization."<<endl;
      laser.disconnect();
      sleep(1);
      return 0;
    }

    cout<<"Starting device."<<endl;
    laser.startDevice(); // Log out to properly re-enable system after config

    cout<<"Commanding continuous measurements."<<endl;
    laser.scanContinous(1);
    glutInit(&argc,argv);
   
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(width,height);
    glutCreateWindow("Three Window");
    //glOrtho(-5,5,-5,5,-1,1);//视野缩放 
    //glutMouseFunc(&mymouse);//调用鼠标响应函数
    //glutSpecialFunc(&Keyboard);//调用键盘回调函数
    glutDisplayFunc(&Display);
    glutIdleFunc(&myIdle);
    glutMainLoop();

    laser.scanContinous(0);
    laser.stopMeas();
    laser.disconnect();
 

    return 0;
}



