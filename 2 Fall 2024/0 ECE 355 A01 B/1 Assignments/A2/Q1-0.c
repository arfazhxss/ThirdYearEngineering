/* Define all necessary Ports addresses */
#define PAOUT   (volatile unsigned char *) 0xFFFFFFF1
#define PAIN    (volatile unsigned char *) 0xFFFFFFF2
#define PBOUT   (volatile unsigned char *) 0xFFFFFFF3
#define PBIN    (volatile unsigned char *) 0xFFFFFFF4
#define CNTM    (volatile unsigned int *) 0xFFFFFFF5
#define CTCON   (volatile unsigned char *) 0xFFFFFFF6
#define CTSTAT  (volatile unsigned char *) 0xFFFFFFF7
#define IVEVCT  (volatile unsigned int *) 0x20

/* Define variables */
unsigned char digit1 = 0;  /* DIGIT1 value */
unsigned char digit2 = 0;  /* DIGIT2 value */
unsigned char led = 0x40;  /* LED1 state (PA6) */

/* Interrupt Service Routine */
interrupt void intserv() {
    *CTSTAT = 0x0;          /* Clear "reached 0" flag */
    
    /* Decrement DIGIT1 or DIGIT2 based on LED state */
    if (led == 0x40) {   /* If LED1 is on (PA6) */
        digit1 = (digit1 + 9) % 10;   /* Decrement DIGIT1 (0 -> 9) */
        *PAOUT = (*PAOUT & 0xF0) | digit1;   /* Update PA0-PA3 with new DIGIT1 value */
    } else {             /* If LED2 is on (PA5) */
        digit2 = (digit2 + 9) % 10;   /* Decrement DIGIT2 (0 -> 9) */
        *PBOUT = (*PBOUT & 0x0F) | (digit2 << 4);   /* Update PB4-PB7 with new DIGIT2 value */
    }

}

int main() {
    /* Set Port A and B directions */
    *PAOUT = 0x7F;   /* Set PA0-3 as outputs for DIGIT1, PA5 for LED2, PA6 for LED1 */
    *PBOUT = 0xF0;   /* Set PB4-7 as outputs for DIGIT2, PB0 as input for SW */

    
    /* Initialize Timer */
    *CNTM = 100000000;       /* 100 MHz counter */
    *CTCON = 0x11;           /* Enable Timer interrupts */
    
    /* Set interrupt vector */
    *IVEVCT = (unsigned int *) &intserv;
    asm("MoveControl PSR,#0x40");  /* CPU responds to IRQ */

    /* Main loop */
    while (1) {
        /* Wait until SW is pressed and released */
        while ((*PBIN & 0x01) != 0);  /* Wait for press (PB0 = SW) */
        while ((*PBIN & 0x01) == 0);  /* Wait for release */
        
        /* Swap LED states and toggle between DIGIT1 and DIGIT2 */
        if (led == 0x40) {   /* If LED1 (PA6) is on */
            led = 0x20;      /* Switch to LED2 (PA5) */
        } else {
            led = 0x40;      /* Switch to LED1 (PA6) */
        }
        
        /* Update Port A with new LED state */
        *PAOUT = (*PAOUT & 0x9F) | led;   /* Update PA5 and PA6 */
    }
    
    return 0;
}
