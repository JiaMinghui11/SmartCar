#include "camera.h"

uint8 threshold;    //图像动态阈值

/**
 * @brief       大津法计算动态阈值
 * @param       image
 * @param       col
 * @param       row
 * @return      void
 */
void OTUS(uint8 *image, uint16 col, uint16 row) 
{       
    uint16 x0 = 0;              //处理起始行
    uint16 y0 = 0;              //处理起始列
    uint16 x1 = MT9V03X_CSI_H;  //处理终止行
    uint16 y1 = MT9V03X_CSI_W;  //处理终止列
    uint16 dx = 2;              //行处理系数
    uint16 dy = 2;              //列处理系数
    
    float gmax = 0;             //最大类间方差
    float w0;                   //前景像素所占比例
    float w1;                   //背景像素所占比例
    float u0;                   //前景平均灰度值
    float u1;                   //背景平均灰度值
    float u;
    float w0_temp;
    float w1_temp;
    float u0_temp;
    float u1_temp;
    uint8 histogram[256] = {0};         //灰度直方图，下标-灰度值，保存内容为灰度值对应像素点总数
    uint8* data = image;                //指向像素数据的指针
    uint16 totalnum = col*row/dy/dx;    //整幅图像的大小 （所有像素点个数和）  (一行有col/dy点,一列有row/dx个点)
    
    //历遍( x0-x1 )整个灰度级,统计每个灰度值对应的像素点的个数
    for(int i = x0; i < x1; i += dx)       
    {
        for(int j = y0; j < y1; j += dy)
        {
            histogram[data[i*col+j]]++;
            u += data[i*col+j];         //全局灰度和    
        }
    }

    //以i为阈值计算并寻找最大类间方差对应的i
    for(int i=1; i < 254; i++)
    {
        w0=0;
        w1=0;
        u0=0;
        u1=0;
        w1_temp += histogram[i];        //背景像素和
        u1_temp += i * histogram[i];    //背景像素灰度值和
        u0_temp = u - u1_temp;          //前景像素灰度和
        w0_temp = totalnum - w1_temp;   //前景像素和
        u1 = u1_temp / w1_temp;         //背景平均灰度值
        w1 = w1_temp / totalnum;        //背景像素所占比例
        u0 = u0_temp / w0_temp;         //前景平均灰度值
        w0 = 1 - w1;                    //前景像素所占比例

        float g = (float)(w1 * w0 * (u0-u1) * (u0-u1));     //方差公式
        //float g=(float)(w0*w1*(u0-u1)*(u0-u1));    
        if(gmax<g)
        {
            gmax=g;
            threshold=i;
        } 
    }
}