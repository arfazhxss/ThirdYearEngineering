//Part 2
#define BIT0 0x0
#define BIT1 0x1
#define BIT2 0x2
#define BIT3 0x4
#define BIT4 0x8
#define BIT5 0x10
#define BIT6 0x20
#define BIT7 0x40

// IO ports
#define PCONT (volatile unsigned char *) 0xFFFFFFF7
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

#define SWITCH BIT7
#define DISPLAY_DIGIT1 0x78 // PORT A
#define DISPLAY_DIGIT2 0xF0 // PORT B
#define LED1 BIT2
#define LED2 BIT0

char digitValue1 = 0; // holds the value for 7-segment digit 1
char digitValue2 = 0; // holds the value for 7-segment digit 2
char portBValueTemp;  // temporary storage for port B value
char portAValueTemp;  // temporary storage for port A value

interrupt void timerISR(); // interrupt service routine
char counterEnabled = 0; // flag to enable counting
char isSwitchPressed = 0; // flag to track switch state

void main(){
    unsigned int timerReloadValue = 100000000; // interrupt every second @ 100MHz
    *CTCON = BIT1; // ensure the timer is stopped initially
    *CTCON &= ~BIT7; // set in counter mode
    *CNTM = timerReloadValue; // load the initial timer value

    // configure Port B outputs for digit2, LED1, and LED2
    *PBDIR |= DISPLAY_DIGIT2 + LED1 + LED2;

    // configure Port A outputs for digit1
    *PADIR |= DISPLAY_DIGIT1;
    // set Port A input for the switch
    *PADIR &= ~(SWITCH);

    // set interrupt vector to point to the timer ISR
    *IVECT = (unsigned int) &timerISR;

    // initialize the display to show 0 on both digits
    *PBOUT &= ~DISPLAY_DIGIT2; // clear digit2 on port B
    *PAOUT &= ~DISPLAY_DIGIT1; // clear digit1 on port A

    // initialize LEDs
    *PBOUT |= LED1;  // turn LED1 on
    *PBOUT &= ~LED2; // turn LED2 off

    // enable interrupts by setting PSR[6]
    asm("MoveControl PSR, #0x20");
    // enable Port A interrupt
    *PCONT |= BIT4;

    // start the timer
    *CTCON &= ~BIT1; // clear stop bit
    *CTCON |= BIT0; // start the timer

    char currentTimerValue = 0;
    while(1){
        while(((*CTSTAT & BIT0) == 0)){}; // wait for timer to complete its count

        // check if LED1 is on, increment digit1
        if((*PBOUT & LED1) == 1){
            digitValue1++; // increment digit 1
            digitValue1 = digitValue1 >= 10 ? 0 : digitValue1; // roll over if it reaches 10

            char tempA;
            tempA = digitValue1 << 3; // shift digit1 value by 3 bits
            portAValueTemp = *PAOUT;
            portAValueTemp &= ~DISPLAY_DIGIT1; // clear the digit1 display bits
            portAValueTemp |= tempA; // set the new value for digit1
            *PAOUT = portAValueTemp;  // update Port A output
        }
        
        // check if LED2 is on, increment digit2
        if((*PBOUT & LED2) == 1){
            digitValue2++; // increment digit 2
            digitValue2 = digitValue2 >= 10 ? 0 : digitValue2; // roll over if it reaches 10

            char tempB;
            tempB = digitValue2 << 4; // shift digit2 value by 4 bits
            portBValueTemp = *PBOUT;
            portBValueTemp &= ~DISPLAY_DIGIT2; // clear the digit2 display bits
            portBValueTemp |= tempB; // set the new value for digit2
            *PBOUT = portBValueTemp;  // update Port B output
        }
        
        // Counter will automatically reload based on the timer config (ref: page 398 of the textbook)
    }

    // if the switch is pressed, counting will be disabled (counterEnabled = 0)
}

// Timer interrupt service routine
interrupt void timerISR()
{
    // check if the switch is pressed
    if(((*PAIN & SWITCH) == 0) && !isSwitchPressed){
        isSwitchPressed = 1; // mark switch as pressed
    } else if(((*PAIN & SWITCH) != 0) && isSwitchPressed){
        isSwitchPressed = 0; // reset switch press flag

        char tempPortA;
        // toggle LED states based on current LED1 status
        if(*PAOUT & LED1 != 0){ // if LED1 is currently on
            tempPortA = *PAOUT;
            tempPortA |= LED2; // turn LED2 on
            tempPortA &= ~LED1; // turn LED1 off
            *PAOUT = tempPortA; // update Port A with the new LED states
        } else {
            tempPortA = *PAOUT;
            tempPortA |= LED1; // turn LED1 on
            tempPortA &= ~LED2; // turn LED2 off
            *PAOUT = tempPortA; // update Port A with the new LED states
        }
    }
}

