#include <stdbool.h>

// CLOCKS
#define CM_PER_GPIO1_CLKCTRL   (*(volatile unsigned int*)0x44E000AC)
#define CM_PER_TIMER7_CLKCTRL  (*(volatile unsigned int*)0x44E0007C)

// GPIO1
#define GPIO1_OE               (*(volatile unsigned int*)0x4804C134)
#define GPIO1_DATAIN           (*(volatile unsigned int*)0x4804C138)
#define GPIO1_SETDATAOUT       (*(volatile unsigned int*)0x4804C194)
#define GPIO1_CLEARDATAOUT     (*(volatile unsigned int*)0x4804C190)
#define GPIO1_IRQSTATUS_0      (*(volatile unsigned int*)0x4804C02C)
#define GPIO1_IRQSTATUS_SET_0  (*(volatile unsigned int*)0x4804C034)
#define GPIO1_RISINGDETECT     (*(volatile unsigned int*)0x4804C148)

// INTC
#define INTC_SIR_IRQ           (*(volatile unsigned int*)0x48200040)
#define INTC_CONTROL           (*(volatile unsigned int*)0x48200048)
#define INTC_MIR_CLEAR2        (*(volatile unsigned int*)0x482000C8)
#define INTC_MIR_CLEAR3        (*(volatile unsigned int*)0x482000E8)

// TIMER7
#define DMTIMER7_TCLR          (*(volatile unsigned int*)0x4804A038)
#define DMTIMER7_TCRR          (*(volatile unsigned int*)0x4804A03C)
#define DMTIMER7_TWPS          (*(volatile unsigned int*)0x4804A048)
#define DMTIMER7_TSICR         (*(volatile unsigned int*)0x4804A054)
#define DMTIMER7_IRQSTATUS     (*(volatile unsigned int*)0x4804A028)
#define DMTIMER7_IRQENABLE_SET (*(volatile unsigned int*)0x4804A02C)
#define DMTIMER7_IRQENABLE_CLR (*(volatile unsigned int*)0x4804A030)

#define DMTimerWaitForWrite(reg) \
    if (DMTIMER7_TSICR & 0x4) while (DMTIMER7_TWPS & reg);

// WATCHDOG
void disable_watchdog() {
    while (*(volatile unsigned int*)0x44E35034 != 0);
    *(volatile unsigned int*)0x44E35048 = 0xAAAA;
    while (*(volatile unsigned int*)0x44E35034 != 0);
    *(volatile unsigned int*)0x44E35048 = 0x5555;
    while (*(volatile unsigned int*)0x44E35034 != 0);
}

// MAPEAMENTO GPIOs
#define LED1 13  // GPIO1_13 - P8_11
#define LED2 15  // GPIO1_15 - P8_15
#define LED3 17  // GPIO1_17 - P9_23

#define BTN_MENU      16 // GPIO1_16 - P9_15
#define BTN_SEQUENCIA 28 // GPIO1_28 - P9_12

#define TIMER_1MS_COUNT 0x5DC0
#define TIMER_OVERFLOW  0xFFFFFFFF

volatile int flag_timer = 0;
volatile int flag_gpio = 0;

int sequencia = 0;
unsigned int delay_ms = 500;

void gpioInit() {
    CM_PER_GPIO1_CLKCTRL |= 0x40002;

    // LEDs como saída
    GPIO1_OE &= ~(1 << LED1);
    GPIO1_OE &= ~(1 << LED2);
    GPIO1_OE &= ~(1 << LED3);

    // Botões como entrada
    GPIO1_OE |= (1 << BTN_MENU);
    GPIO1_OE |= (1 << BTN_SEQUENCIA);

    // Interrupção no botão GPIO1_28
    GPIO1_IRQSTATUS_SET_0 |= (1 << BTN_SEQUENCIA);
    GPIO1_RISINGDETECT     |= (1 << BTN_SEQUENCIA);

    // Libera interrupção 98 (GPIO1A)
    INTC_MIR_CLEAR3 |= (1 << 2);
}

void timerInit() {
    CM_PER_TIMER7_CLKCTRL |= 0x2;
    while ((CM_PER_TIMER7_CLKCTRL & 0x3) != 0x2);
    INTC_MIR_CLEAR2 |= (1 << 31); // IRQ 95
}

void timerStart(unsigned int ms) {
    unsigned int count = TIMER_OVERFLOW - (ms * TIMER_1MS_COUNT);
    DMTimerWaitForWrite(0x2);
    DMTIMER7_TCRR = count;
    flag_timer = 0;
    DMTIMER7_IRQENABLE_SET = 0x2;
    DMTIMER7_TCLR |= 0x1;
}

void timerStop() {
    DMTIMER7_IRQENABLE_CLR = 0x2;
    DMTIMER7_TCLR &= ~0x1;
}

void ledsOff() {
    GPIO1_CLEARDATAOUT |= (1 << LED1) | (1 << LED2) | (1 << LED3);
}

void ledsSequencia(int modo) {
    ledsOff();
    switch (modo) {
        case 0:
            GPIO1_SETDATAOUT |= (1 << LED1);
            break;
        case 1:
            GPIO1_SETDATAOUT |= (1 << LED2);
            break;
        case 2:
            GPIO1_SETDATAOUT |= (1 << LED3);
            break;
    }
}

void gpioIrqHandler() {
    GPIO1_IRQSTATUS_0 = (1 << BTN_SEQUENCIA); // limpa flag
    flag_gpio = 1;
}

void timerIrqHandler() {
    DMTIMER7_IRQSTATUS |= 0x2;
    flag_timer = 1;
    timerStop();
}

void ISR_Handler() {
    unsigned int irq = INTC_SIR_IRQ & 0x7F;
    if (irq == 95) timerIrqHandler();
    else if (irq == 98) gpioIrqHandler();
    INTC_CONTROL = 0x1;
}

int main() {
    disable_watchdog(); // Desativa Watchdog antes de tudo
    gpioInit();
    timerInit();

    while (1) {
        // Botão Menu (GPIO1_16) - polling
        if (!(GPIO1_DATAIN & (1 << BTN_MENU))) {
            delay_ms = (delay_ms == 500) ? 200 : 500;
            for (volatile int i = 0; i < 500000; i++); // debounce
        }

        // Botão Sequência (GPIO1_28) - interrupção
        if (flag_gpio) {
            sequencia = (sequencia + 1) % 3;
            flag_gpio = 0;
        }

        ledsSequencia(sequencia);
        timerStart(delay_ms);
        while (!flag_timer);
    }

    return 0;
}

