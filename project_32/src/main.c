#include <REGX52.H>
void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
while(xms){
		i = 2;
		j = 239;
			do
			{
				while (--j);
			} while (--i);
		xms--;
}
	
}
void main(){

	while(1){{
		if(P3_1 == 0){
			Delay(20);//消除按下的抖动
			while(P3_1==0);//判断是否松手，若未松手，则一直循环
			Delay(20);//消除松手的抖动
			P2_0 = ~P2_0;//按位取反，若灯亮则熄灭，若熄灭则点亮
		}
	}
}
}