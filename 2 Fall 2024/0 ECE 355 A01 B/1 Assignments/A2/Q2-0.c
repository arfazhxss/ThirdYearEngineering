/* Define all necessary Ports Addresses */
#define PAOUT (volatile unsigned char *) 0xFFFFFFF1
#define PADIR (volatile unsigned char *) 0xFFFFFFF2
#define PAIN (volatile unsigned char *) 0xFFFFFFF3
#define PBOUT (volatile unsigned char *) 0xFFFFFFF5
#define PBDIR (volatile unsigned char *) 0xFFFFFFF6
#define CNTM (volatile unsigned int *) 0xFFFFFFF8
#define CTCON (volatile unsigned char *) 0xFFFFFFF9
#define CTSTAT (volatile unsigned char *) 0xFFFFFFFD
#define IVECT (volatile unsigned int *) 0x20

/* Define variables */
interrupt void intserv();          /* ISR for port A */
unsigned char digit1 = 0;          /* Digit1 to be displayed */
unsigned char digit2 = 0;          /* Digit2 to be displayed */
unsigned char led = 0x01;          /* LED1 state: on (PB2), LED2 state: off (PB0) */

int main() {
    *PADIR = 0x78;                 /* Set Port A direction (PA7 input, PA6-PA3 output) */
    *PBDIR = 0xF5;                 /* Set Port B direction (PB0, PB2, PB4-7 outputs) */
    *CTCON = 0x02;                 /* Stop Timer */
    *IVECT = (unsigned int *) &intserv;  /* Set interrupt vector */
    asm("MoveControl PSR, #0x40");  /* CPU responds to IRQ */
    *CNTM = 100000000;             /* Initialize Timer */
    *CTCON = 0x11;                 /* Enable Timer interrupts and start counting */
    
    *PAOUT = 0x00;                 /* Initialize DIGIT1 */
    *PBOUT = led;                  /* Initiate LEDs and DIGIT2 on Port B */

    while (1) {
        while ((*PAIN & 0x80) != 0);  /* Wait until SW is pressed */
        while ((*PAIN & 0x80) == 0);  /* Wait until SW is released */
        
        if (led == 0x04) {          /* If LED1 (PB2) is on */
            led = 0x01;             /* Switch to LED2 (PB0) */
        } else {
            led = 0x04;             /* Switch to LED1 (PB2) */
        }
        *PBOUT = led;               /* Update LEDs on Port B */
    }

    exit(0);
}

interrupt void intserv() {
    *CTSTAT = 0x0;                 /* Clear "reached 0" flag */
    
    if (led == 0x04) {             /* If LED1 (PB2) is on */
        digit1 = (digit1 + 1) % 10;  /* Increment DIGIT1 */
        *PAOUT = (*PAOUT & 0x87) | (digit1 << 3);  /* Update DIGIT1 (PA3-PA6) */
    } else {
        digit2 = (digit2 + 1) % 10;  /* Increment DIGIT2 */
        *PBOUT = (*PBOUT & 0x0F) | (digit2 << 4);  /* Update DIGIT2 (PB4-PB7) */
    }
}
