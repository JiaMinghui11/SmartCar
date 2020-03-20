#include "camera.h"
uint8 threshold;
void OTUS(uint8 *image,uint16 col, uint16 row,uint16 x0,uint16 y0,uint16 x1,uint16 y1,uint16 dx,uint16 dy) 
{       //(图像宽-140,图像高-120,起始行-0，起始列-0，终止行-120，终止列-140，处理行系数-2，处理列系数-2)   //threshold=OTUS_fenkuai(*image,MT9V032_W ,MT9V032_H,0,0,120,140,2,2);                                                                                                                    
    float  gmax=0;
    float w0;//=0; //前景像素所占比例
    float  w1;//=0; //背景像素所占比例
    float u0;//=0;//前景平均灰度值
    float u1;//=0; //背景平均灰度值
    float u;
    float w0_temp;
    float w1_temp;
    float u0_temp;
    float u1_temp;
    uint8 histogram[256]={0}; //灰度直方图，下标-灰度值，保存内容为灰度值对应像素点总数
    uint8* data = image; //指向像素数据的指针
    uint16 totalnum=col*row/dy/dx; //整幅图像的大小 （所有像素点个数和）  (一行有col/dy点,一列有row/dx个点)
    for(int i=x0;i<x1;i+=dx)  //历遍( x0-x1 )整个灰度级,统计每个灰度值对应的像素点的个数   
    {
        for(int j=y0;j<y1;j+=dy)
        {
            histogram[data[i*col+j]]++;
            u+=data[i*col+j];  //全局灰度和    
        }
    }
 
    //u=u/totalnum;//全局平均灰度
 
    /* for(int i=0;i<254;i++)
            u+=i*histogram[i];*/
 
    for(int i=1;i<254;i++)
    {
        w0=0;
        w1=0;
        u0=0;
        u1=0;
  
        w1_temp+=histogram[i]; //背景像素和
        u1_temp+=i*histogram[i]; //背景像素灰度值和
    
        /*for(int j=0;j<=i;j++)
        {
            w1+=histogram[j]; //背景像素和
            u1+=j*histogram[j]; //背景像素灰度值和
        }*/
        
        //if(w1==0) {continue;}  
        u0_temp=u-u1_temp; //前景像素灰度和
        w0_temp=totalnum-w1_temp;//前景像素和
  
        u1=u1_temp/w1_temp;          //背景平均灰度值
        w1=w1_temp/totalnum;     //背景像素所占比例
        u0=u0_temp/w0_temp;           //前景平均灰度值
        w0=1-w1;            //前景像素所占比例
  
        /*for(int k=i+1;k<254;k++)
        {
            w0+=histogram[k]; //前景像素和
            u0+=k*histogram[k]; //前景像素灰度值和
        }
        //if(w0==255) break;
        u0=u0/w0;
        w0=w0/totalnum;*/
  
        float g=(float)(w1*w0*(u0-u1)*(u0-u1)); //方差公式
        //float g=(float)(w0*w1*(u0-u1)*(u0-u1));
    
        if(gmax<g)
        {
            gmax=g;
            threshold=i;
        } 
    }
    //return threshold;
}