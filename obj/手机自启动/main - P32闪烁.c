#include <STC8G.H>

sbit LED1 = P3^3;
sbit LED2 = P3^2;



void Timer0_Init() {
    TMOD = 0x01;      // ???0????1(16???)
    TH0 = 0xD8;       // ?????(11.0592MHz?50ms????)^[11]^
    TL0 = 0xF0;
    ET0 = 1;          // ?????0??
    EA = 1;           // ??????
    TR0 = 1;          // ?????0
}

volatile unsigned int count = 0; // ????

void DelayMs(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++); 
}

void main() {
    //P3M0 &= ~0x08;
	  //P3M1 &= ~0x08;
    P3M0 |= 0x0f; P3M1 &= ~0x0f; 
	  LED1 = 1; 
	  LED2 = 1;
	  DelayMs(20000);
    LED1 = 0;          // ??????
    Timer0_Init();
    while(1);
}

// ???0??????
void Timer0_ISR() interrupt 1 {
    TH0 = 0xD8;       // ??????
    TL0 = 0xF0;
    if (++count >= 600) {  // 50ms*60=3?
        count = 0;
       LED2 = ~LED2;    // ??LED??
			 LED1 = 1;
    }
}
