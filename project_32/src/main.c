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
			Delay(20);//�������µĶ���
			while(P3_1==0);//�ж��Ƿ����֣���δ���֣���һֱѭ��
			Delay(20);//�������ֵĶ���
			P2_0 = ~P2_0;//��λȡ������������Ϩ����Ϩ�������
		}
	}
}
}