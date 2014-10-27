// Hardware register definition file
#include "tm4c123ge6pm.h"

// Bit-specific addressing registers for the PF1, PF2 and PF3 pins
// Defined by the PortF register address base (0x40025000) plus
// the pins intended to be accessed (Pin1 = 0x08, Pin2 = 0x10, Pin3 = 0x20)
#define PF1_DATA (*((volatile unsigned long *)0x40025008))
#define PF2_DATA (*((volatile unsigned long *)0x40025010))
#define PF3_DATA (*((volatile unsigned long *)0x40025020))

// Simple macros to turn on and off each pin
#define PF1_ON 	PF1_DATA = 0x02;
#define PF1_OFF	PF1_DATA = 0x00;

#define PF2_ON  PF2_DATA = 0x02;
#define PF2_OFF PF2_DATA = 0x00;

#define PF3_ON  PF3_DATA = 0x02;
#define PF3_OFF PF3_DATA = 0x00;

// Function declaration
void PortF_Init(void);
void Delay(void);

int main(void)
{
    uint32_t i;
    
    PortF_Init();

    while(1) {

        // Turn on LED 
        PF1_ON

        // Wait some instruction cycles
        for (i = 0; i < 10; i++) {
            Delay();
        }

        // Turn off LED
        PF1_OFF

        // Wait some instruction cycles
        for (i = 0; i < 10; i++) {
            Delay();
        }
    }
}

void PortF_Init(void)
{
    volatile uint32_t delay;

  	SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  	delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  	GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0

  	// only PF0 needs to be unlocked, other bits can't be locked

  	GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  	GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  	GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  	GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  	GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  	GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0

	delay++;
}

void Delay(void)
{
	unsigned long volatile time;
  	time = 145448;  // 0.1sec
  	while(time) {
		time--;
  	}
}
