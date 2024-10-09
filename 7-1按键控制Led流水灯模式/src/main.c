#include "REGX52.H"
#include "Timer0.h"
#include "Key.h"
#include "INTRINS.H"

unsigned char KeyNum,LedMod;
void Timer0_Init(){
    /*
    //开启定时器1模式，
    首先将高位定时器全部归零即 0000，
    然后低位定时器的gate=0，C/T=0表示无外部时钟，
    为开启模式一，将M1=0，M0=1，即0001，转换为16进制即0x01)
    */
//TMOD = 0x01;
    TMOD = TMOD&0xF0; //把TMOD的低四位清零，高四位不变 ,&1111 0000
    TMOD = TMOD|0x01; //把TMOD的最低位置1，高四位不变，|0000 0001
    /*
    //将标志位清零
    定时器T0溢出标志，
    当T0开始计数并溢出时，由硬件置 "1" TF0，表示向cpu申请中断）
    */
    TF0 = 0;
    /*
    //开启计数器
    由于无外部中断，INT0=0，所有需要将gate置0，
    此时定时器由TR0全权控制）
    */
    TR0 = 1;
    /*
    两个定时/计数器分别用来记录高位与低位，且均为8位，最大为65535
    TH0表示高位，TL0表示低位
    所以高于2的八次方的数(即256)放在TH0，低于2的八次方的数放在TL0
    此程序从64535（65535 - 64535 = 1000）开始，即初值为64535
    每隔1000us（即1ms）申请一次中断
    */
    TH0 = 64535/256;//高位
    TL0 = 64535%256;//低位
    //打开中断通路
    ET0 = 1;//允许中断
    EA = 1;//允许总中断
    PT0 = 0;//中断优先级为0
}
void Timer0_Routine() interrupt 1{
    static unsigned int T0count;
    TH0 = 64535/256;//高位
    TL0 = 64535%256;//低位
    T0count++;
    if(T0count >= 1000){T0count = 0;P2_0 = ~P2_0;}
}
void main(){
    Timer0Init();
    while(1){
        KeyNum = Key();
        if(KeyNum){
            if(KeyNum == 1) P2_1 = ~P2_1;
            if(KeyNum == 2) P2_2 = ~P2_2;
            if(KeyNum == 3) P2_3 = ~P2_3;
            if(KeyNum == 4) P2_4 = ~P2_4;
        }
    }
}