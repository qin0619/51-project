#include "REGX52.H"

void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
while(xms--){
    i = 12;
        j = 169;
        do
        {
            while (--j);
        } while (--i);
}
	
}
void main(){
    unsigned char LEDNum = 0;//八位用来表示一个临时寄存器，0000 0000
    while(1){
        if(P3_1 == 0){
            Delay(20);
            while (P3_1 == 0);
            Delay(20);
            LEDNum++;// 0000 0001
            P2 = ~LEDNum; //1111 1110
        }
    }

}