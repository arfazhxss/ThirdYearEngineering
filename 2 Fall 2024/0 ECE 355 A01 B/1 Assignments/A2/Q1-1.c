//Part 1
#define BIT0 0x0
#define BIT1 0x1
#define BIT2 0x2
#define BIT3 0x4
#define BIT4 0x8
#define BIT5 0x10
#define BIT6 0x20
#define BIT7 0x40

#define switch BIT0
#define displayBitsB 0xF0 // PortB
#define displayBitsA 0x0F // PortA
#define LED1 BIT6
#define LED2 BIT5

// IO ports
// Port A
#define PAIN (volatile unsigned char *) 0xFFFFFFF0
#define PAOUT (volatile unsigned char * ) 0xFFFFFFF1
#define PADIR (volatile unsigned char *) 0xFFFFFFF2
// Port B
#define PBIN (volatile unsigned char *) 0xFFFFFFF3
#define PBOUT (volatile unsigned char * ) 0xFFFFFFF4
#define PBDIR (volatile unsigned char *) 0xFFFFFFF5

// timer 
#define CNTM (volatile unsigned int *) 0xFFFFFFD0 // initial timer value
#define CTCON (volatile unsigned char *) 0xFFFFFFD8 // timer control register 
#define CTSTAT (volatile unsigned char *) 0xFFFFFFD9 // timer status register
#define IVECT (volatile unsigned int *) (0x20) // interrupt vector address

char segmentDigitA = 0;  // 7-segment display digit A
char segmentDigitB = 0;  // 7-segment display digit B
char portBValSnapshot;   // temporary store for port B value
char portAValSnapshot;   // temporary store for port A value

void main(){
    unsigned int timerCount=100000000; // trigger interrupt every second @ 100MHz
    *CTCON = BIT1; // ensure timer is stopped initially
    *CTCON |= BIT7; // set timer mode
    *CNTM = timerCount; // load initial timer value

    // set PB0 as input (switch)
    *PBDIR &= ~switch;
    
    // configure Port B upper nibble (PB4-PB7) as output
    *PBDIR |= displayBitsB;
    // configure Port A lower nibble (PA0-PA3) as output
    *PADIR |= displayBitsA;
    
    // set PA5 and PA6 as LED output pins
    *PADIR |= LED1 | LED2;

    // initialize LEDs: turn LED1 on, turn LED2 off
    *PAOUT |= LED1; // LED1 is initially on
    *PAOUT &= ~LED2; // LED2 is initially off
    
    // set interrupt vector to timer ISR
    *IVECT = (unsigned int) &timerISR;
    
    // initialize display to show 0
    *PBOUT &= ~0xF0; // clear upper 4 bits of port B
    *PAOUT &= ~0x0F; // clear lower 4 bits of port A

    // enable interrupt by setting PSR[6]
    asm("MoveControl PSR, #0x20");
    
    // enable timer interrupt
    *CTCON |= BIT4;

    // start the timer
    *CTCON &= ~BIT1; // clear stop bit
    *CTCON |= BIT0; // set start bit

    while(1){
        // check if switch (PB0) is pressed
        if(~*PBIN & switch != 0){ 
            // wait until switch is released
            while(~*PBIN & switch != 0);
            // temporary store for updating LEDs
            char tempPortA = *PAOUT;
            // check if LED1 is currently on
            if(*PAOUT & LED1 != 0){ 
                // turn on LED2 and turn off LED1
                tempPortA |= LED2; // enable LED2
                tempPortA &= ~LED1; // disable LED1
                *PAOUT = tempPortA; // update PAOUT with new values
            } else {
                // turn on LED1 and turn off LED2
                tempPortA |= LED1; // enable LED1
                tempPortA &= ~LED2; // disable LED2
                *PAOUT = tempPortA; // update PAOUT with new values
            }
        }    
    }  
}

// Timer interrupt service routine
interrupt void timerISR()
{
    // check if LED1 is on, meaning we're decrementing digit A
    if(*PAOUT & LED1 != 0){ 
        // if digit A reaches 0, reset to 10
        segmentDigitA = segmentDigitA >= 0 ? 10 : segmentDigitA;
        segmentDigitA--; // decrement digit A
        
        // temporarily store the current value of port A
        portAValSnapshot = *PAOUT;
        // clear the 7-segment display portion of port A
        portAValSnapshot &= ~displayBitsA;
        // update display with the new value for digit A
        portAValSnapshot |= segmentDigitA;
        *PBOUT = portAValSnapshot;  // update the 7-segment display
    } else if(*PAOUT & LED2 != 0){ // if LED2 is on, decrement digit B
        segmentDigitB = segmentDigitB >= 0 ? 10 : segmentDigitB;
        segmentDigitB--; // decrement digit B

        char shiftedValue; 
        // shift the value of digit B to align with upper 4 bits
        shiftedValue = segmentDigitB << 4;
        
        // temporarily store the current value of port B
        portBValSnapshot = *PBOUT;
        // clear the upper nibble (7-segment display) portion of port B
        portBValSnapshot &= ~displayBitsB;
        // update display with new value for digit B
        portBValSnapshot |= shiftedValue;
        *PBOUT = portBValSnapshot;  // update the 7-segment display
    }
}

