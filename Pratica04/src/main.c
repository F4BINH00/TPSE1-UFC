#include "hw_types.h"
#include "soc_AM335x.h"

// Registradores do AINTC (Controlador de Interrupções)
#define INTC_MIR_CLEAR3      0x00E8   // Desmascara IRQs 96–127 (banco 3)
#define INTC_SIR_IRQ         0x0040   // Identifica o número da IRQ pendente
#define INTC_CONTROL         0x0048   // Sinaliza fim da interrupção

// Registradores do GPIO
#define GPIO_OE             0x134     // Define direção (0 = saída, 1 = entrada)
#define GPIO_IRQSTATUS_0    0x2C      // Status de IRQ pendente (limpa com 1)
#define GPIO_RISINGDETECT   0x148     // Ativa detecção de borda de subida
#define GPIO_SETDATAOUT     0x194     // Escreve 1 para ligar pino
#define GPIO_CLEARDATAOUT   0x190     // Escreve 1 para desligar pino
#define GPIO_IRQSTATUS_SET_0 0x34     // Seta o pino como habilitado para IRQ

// LEDs (conectados ao GPIO1)
#define LED1 21
#define LED2 22
#define LED3 23
#define LED4 24

// Botões
#define BTN1 28 // GPIO1_28 → IRQ 98
#define BTN2 27 // GPIO0_27 → IRQ 96

#define DELAY_TIME 100000000

// Variáveis globais controlando o modo de operação
volatile int modo_fixo = 0;
volatile int modo_piscar = 0;

// Função de atraso (delay)
void delay(unsigned int count) {
    volatile unsigned int i;
    for (i = 0; i < count; i++);
}

// Desativa o watchdog timer
void disable_watchdog() {
    while (HWREG(0x44E35034) != 0);
    HWREG(0x44E35048) = 0xAAAA;
    while (HWREG(0x44E35034) != 0);
    HWREG(0x44E35048) = 0x5555;
    while (HWREG(0x44E35034) != 0);
}

// Liga os clocks dos módulos GPIO0 e GPIO1
void habilita_clock_gpios() {
    HWREG(SOC_CM_PER_REGS + 0xAC) |= 0x2; // Habilita clock para GPIO1
    HWREG(SOC_CM_PER_REGS + 0xA8) |= 0x2; // Habilita clock para GPIO0
}

// Configura pinos dos LEDs como saída
void configura_leds_saida() {
    unsigned int reg = HWREG(SOC_GPIO_1_REGS + GPIO_OE);
    reg &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4)); // Clear bits = saída
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) = reg;
}

// Configura pinos dos botões como entrada
void configura_botoes_entrada() {
    unsigned int reg;

    reg = HWREG(SOC_GPIO_1_REGS + GPIO_OE);
    reg |= (1 << BTN1); // Seta bit = entrada
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) = reg;

    reg = HWREG(SOC_GPIO_0_REGS + GPIO_OE);
    reg |= (1 << BTN2);
    HWREG(SOC_GPIO_0_REGS + GPIO_OE) = reg;
}

// Ativa interrupções por borda de subida nos botões
void habilita_irq_botoes() {
    // BTN1 → GPIO1
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= (1 << BTN1);      // Ativa detecção
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) |= (1 << BTN1);   // Habilita IRQ

    // BTN2 → GPIO0
    HWREG(SOC_GPIO_0_REGS + GPIO_RISINGDETECT) |= (1 << BTN2);
    HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_SET_0) |= (1 << BTN2);
}

// Configura GPIOs (LEDs e botões)
void config_gpio() {
    habilita_clock_gpios();
    configura_leds_saida();
    configura_botoes_entrada();
    habilita_irq_botoes();
}

// Configura o controlador de interrupções (AINTC)
void config_aintc() {
    // Libera (desmascara) as IRQs 96 e 98 (banco 3)
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR3) |= 
        (1 << (98 - 96)) | (1 << (96 - 96));
}

// Função chamada no loop principal para verificar interrupções
void verifica_interrupcoes() {
    unsigned int irq_num = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ); // Qual IRQ ocorreu?

    if (irq_num == 98) { // BTN1
        if (HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) & (1 << BTN1)) {
            modo_fixo = !modo_fixo;    // Alterna modo fixo
            modo_piscar = 0;           // Desativa piscar
            HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << BTN1); // Reseta IRQ
        }
    } else if (irq_num == 96) { // BTN2
        if (HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) & (1 << BTN2)) {
            modo_piscar = !modo_piscar; // Alterna modo piscar
            modo_fixo = 0;              // Desativa fixo
            HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) = (1 << BTN2); // Reseta IRQ
        }
    }

    // Sinaliza ao AINTC que o tratamento terminou
    HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
}

// Liga todos os LEDs de uma vez
void liga_todos_leds() {
    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = 
        (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
}

// Desliga todos os LEDs
void desliga_todos_leds() {
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = 
        (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
}

// Pisca os LEDs um por vez, em sequência
void pisca_leds() {
    for (int i = LED1; i <= LED4; i++) {
        HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << i);
        delay(DELAY_TIME);
        HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << i);
    }
}

// Função principal
int main(void) {
    disable_watchdog();   // Desativa watchdog
    config_gpio();        // Configura GPIOs
    config_aintc();       // Configura interrupções

    // OBS: IRQ global já deve estar habilitada no start.s

    while (1) {
        if (modo_fixo) {
            liga_todos_leds();   // Acende todos os LEDs
        } else if (modo_piscar) {
            pisca_leds();        // Pisca LEDs sequencialmente
        } else {
            desliga_todos_leds(); // Nenhum modo → LEDs apagados
        }
    }
    return 0;
}
