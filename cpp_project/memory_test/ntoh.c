#include <stdio.h>                                                 

int main(void)                                                     
{                                                                  
    char j = 128, j2=1;                                                  
    printf("%02X = %016X =%02x\n", (unsigned char) (j),  (long long)j,j2);             
    char i = 0;                                                    
    for (i = 0; i < 8; i++)                                        
    {                                                              
        int num = (j << 8) | (i);                                  
        j++;                                                       
        printf("%04X = %04x = %d\n", (unsigned int)num, num, num); 
    }                                                              
    return(0);                                                     
}     
