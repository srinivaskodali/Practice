#include <stdio.h>
int main() {
	//endianness needs to be taken care -srini
    unsigned int  ipAddress = 297720354;
    unsigned char octet[4]  = {0,0,0,0};
    for (int i=0; i<4; i++)
    {
        octet[i] = ( ipAddress >> (i*8) ) & 0xFF;
    }
    printf("%d.%d.%d.%d\n",octet[3],octet[2],octet[1],octet[0]);
}
