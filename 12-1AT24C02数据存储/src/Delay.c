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
void Delayus()		//@11.0592MHz
{
	unsigned char i;
	i = 89;
	while (--i);
}