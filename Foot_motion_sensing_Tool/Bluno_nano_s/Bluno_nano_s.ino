#include <JY901.h>

//IIC总线挂载多个JY901
//注意：SCL和SDA接4.7k上拉电阻
//时间：2020.9.28
//满手16传感器，左手从0x60-0x6C,右手从0x70-0x7C
//

#include <Wire.h>
#include <JY901.h>

//#define DEVADR 0x60//左手设备首地址
//#define DEVADR 0x78//右手设备首地址
//#define DEVNUM  1 //设备数量

/*
Test on Uno R3.
JY901    UnoR3
SDA <---> SDA
SCL <---> SCL
*/

void setup() 
{
  Serial.begin(9600,SERIAL_8N1);//波特率为9600
} 
void loop() 
{

  //循环获取多个设备的数据

    getData(0X76,1);
    getData(0X78,2);
    getData(0X79,3);
    getData(0X7A,4);

  
//  Serial.println();
}
void getData(unsigned char devAdr,unsigned char devNum)
{
  
  JY901.StartIIC(devAdr);//该库重载了IIC初始化StartIIC函数，设置设备地址

  JY901.GetAcc(); //输出三轴加速度
  Serial.print(devNum);Serial.print("a");
  Serial.print((float)JY901.stcAcc.a[0]/32768*16);Serial.print("$");
  Serial.print((float)JY901.stcAcc.a[1]/32768*16);Serial.print("$");
  Serial.print((float)JY901.stcAcc.a[2]/32768*16);Serial.print("$");
  
  JY901.GetGyro();  //输出三轴角速度
  Serial.print(devNum);Serial.print("v");
  Serial.print((float)JY901.stcGyro.w[0]/32768*2000);Serial.print("$");
  Serial.print((float)JY901.stcGyro.w[1]/32768*2000);Serial.print("$");
  Serial.print((float)JY901.stcGyro.w[2]/32768*2000);Serial.print("$");
  
  JY901.GetAngle(); //输出三轴姿态角
  Serial.print(devNum);Serial.print("p");
  Serial.print((int)((float)JY901.stcAngle.Angle[0]/32768*180));Serial.print("$");//x
  Serial.print((int)((float)JY901.stcAngle.Angle[1]/32768*180));Serial.print("$");//y
  Serial.print((int)((float)JY901.stcAngle.Angle[2]/32768*180));Serial.print("$");//z

  delay(10);  //利用delay（）函数确定采样率，单位为ms，10ms时采样率约为100Hz，采样率过高可能导致卡顿
 
}
