
#include <stdint.h>

// --- Definições de Registradores Comuns da AM335x (BeagleBone Black) ---
// Endereços base dos módulos.

// Módulos de Clock (CM_PER para periféricos, CM_WKUP para módulos de wake-up)
#define CM_PER_BASE_ADDR        0x44E00000
#define CM_WKUP_BASE_ADDR       0x44E00400

#define CM_PER_GPIO1_CLKCTRL    (*(volatile uint32_t *)(CM_PER_BASE_ADDR + 0xAC))
#define CM_WKUP_GPIO0_CLKCTRL   (*(volatile uint32_t *)(CM_WKUP_BASE_ADDR + 0x8)) // GPIO0 está no domínio WKUP
#define CM_PER_UART0_CLKCTRL    (*(volatile uint32_t *)(CM_PER_BASE_ADDR + 0xB4))

// Módulo de Controle (Pin Muxing)
#define CONTROL_MODULE_BASE_ADDR 0x44E10000

// Offsets de Pin Muxing (P8 e P9 headers)
// Mode 0: UART, Mode 7: GPIO. PULLUP/DOWN e RCVR_EN são importantes.
// Lembre-se: 0x07 = GPIO Mode 7, Sem Pull, Receiver Disabled (para Saídas)
//            0x27 = GPIO Mode 7, Pull-Up Habilitado, Receiver Enabled (para Entradas)
#define CM_CONF_UART0_TXD_OFFSET    0x97C // P9_24
#define CM_CONF_UART0_RXD_OFFSET    0x978 // P9_26

#define CM_CONF_GPIO1_17_OFFSET     0x844 // P9_23 (LED_EXT1)
#define CM_CONF_GPIO1_15_OFFSET     0x83C // P9_15 (LED_EXT2)
#define CM_CONF_GPIO1_21_OFFSET     0x854 // User LED0 (LED_INT)

#define CM_CONF_GPIO1_28_OFFSET     0x870 // P9_12 (BTN1)
#define CM_CONF_GPIO0_27_OFFSET     0x80C // P8_17 (BTN2)
#define CM_CONF_GPIO1_16_OFFSET     0x840 // P9_16 (BTN3)

// Registradores GPIO0
#define GPIO0_BASE_ADDR          0x44E07000
#define GPIO0_OE                 (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x134))
#define GPIO0_DATAIN             (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x138))
#define GPIO0_SETDATAOUT         (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x194))
#define GPIO0_CLEARDATAOUT       (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x190))
#define GPIO0_IRQSTATUS_0        (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x2C))
#define GPIO0_IRQSTATUS_SET_0    (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x34))
#define GPIO0_RISINGDETECT       (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x140))
#define GPIO0_FALLINGDETECT      (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x14c))
#define GPIO0_DEBOUNCENABLE      (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x150))
#define GPIO0_DEBOUNCINGTIME     (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x154))
#define GPIO0_IRQSTATUS_CLR_0    (*(volatile uint32_t *)(GPIO0_BASE_ADDR + 0x38)) // Necessário para limpar as interrupções globais

// Registradores GPIO1
#define GPIO1_BASE_ADDR          0x4804C000
#define GPIO1_OE                 (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x134))
#define GPIO1_DATAOUT            (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x13C)) // Usado para ler o estado atual das saídas
#define GPIO1_DATAIN             (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x138))
#define GPIO1_SETDATAOUT         (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x194))
#define GPIO1_CLEARDATAOUT       (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x190))
#define GPIO1_IRQSTATUS_0        (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x2C))
#define GPIO1_IRQSTATUS_SET_0    (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x34))
#define GPIO1_RISINGDETECT       (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x140))
#define GPIO1_FALLINGDETECT      (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x14c))
#define GPIO1_DEBOUNCENABLE      (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x150))
#define GPIO1_DEBOUNCINGTIME     (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x154))
#define GPIO1_IRQSTATUS_CLR_0    (*(volatile uint32_t *)(GPIO1_BASE_ADDR + 0x38)) // Necessário para limpar as interrupções globais

// Registradores UART0
#define UART0_BASE_ADDR          0x44E09000
#define UART0_RHR                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x00)) // Receive Holding Register
#define UART0_THR                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x00)) // Transmit Holding Register
#define UART0_DLL                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x00)) // Divisor Latch Low (DLAB=1)
#define UART0_DLH                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x04)) // Divisor Latch High (DLAB=1)
#define UART0_FCR                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x08)) // FIFO Control Register
#define UART0_LCR                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x0C)) // Line Control Register
#define UART0_LSR                (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x14)) // Line Status Register
#define UART0_MDR1               (*(volatile uint32_t *)(UART0_BASE_ADDR + 0x20)) // Mode Definition Register 1

// --- Definições do Advanced Interrupt Controller (AINTC) ---
#define AINTC_BASE_ADDR         0x48200000
#define AINTC_SYSCONFIG         (*(volatile uint32_t *)(AINTC_BASE_ADDR + 0x10))
#define AINTC_IDLEST            (*(volatile uint32_t *)(AINTC_BASE_ADDR + 0x14))
#define AINTC_ILR_BASE          (AINTC_BASE_ADDR + 0x100) // Base para registradores de nível (IRQs 0-127)
#define AINTC_MIR_BASE          (AINTC_BASE_ADDR + 0x84)  // Mask Set/Clear Registers
#define AINTC_MIR_CLEAR(n)      (*(volatile uint32_t *)(AINTC_MIR_BASE + (n * 0x20))) // IRQ Enable (Clear mask)
#define AINTC_MIR_SET(n)        (*(volatile uint32_t *)(AINTC_MIR_BASE + 0x4 + (n * 0x20))) // IRQ Disable (Set mask)
#define AINTC_CMR_BASE          (AINTC_BASE_ADDR + 0x400) // Base para Channel Map Registers
#define AINTC_SICR              (*(volatile uint32_t *)(AINTC_BASE_ADDR + 0x20)) // Software Interrupt Clear Register
#define AINTC_EISR              (*(volatile uint32_t *)(AINTC_BASE_ADDR + 0x24)) // Enable Interrupt Set Register
#define AINTC_EOIR              (*(volatile uint32_t *)(AINTC_BASE_ADDR + 0x48)) // End Of Interrupt Register
#define AINTC_ITR_BASE          (AINTC_BASE_ADDR + 0x0C) // Interrupt Test Register (status das IRQs)
#define AINTC_ISR_BASE          (AINTC_BASE_ADDR + 0x28) // Interrupt Status Register (IRQ status)
#define AINTC_IRCP_BASE         (AINTC_BASE_ADDR + 0xC0) // Interrupt Controller Registers for CPU (Priority)
#define AINTC_ILR(n)            (*(volatile uint32_t *)(AINTC_ILR_BASE + (n * 0x4))) // Interrupt Level Register

// IDs de Interrupção para GPIOs (verifique no TRM da AM335x)
#define GPIO0_IRQ_ID            96
#define GPIO1_IRQ_ID            98

// --- Definições de LEDs e Botões ---
// LEDs Externos:
#define LED_EXT1_GPIO1_17       (1 << 17) // Conectado ao pino P9_23
#define LED_EXT2_GPIO1_15       (1 << 15) // Conectado ao pino P9_15

// LED Interno (User LED0 na BeagleBone Black)
#define LED_INT_GPIO1_21        (1 << 21) // Mapeia para o LED0 na placa

// Botões:
#define BTN1_GPIO1_28           (1 << 28) // Conectado ao pino P9_12
#define BTN2_GPIO0_27           (1 << 27) // Conectado ao pino P8_17 (ATENÇÃO: GPIO0)
#define BTN3_GPIO1_16           (1 << 16) // Conectado ao pino P9_16

// --- Variáveis Globais de Estado ---
volatile uint8_t led_ext1_blinking = 0;
volatile uint8_t led_ext2_blinking = 0;
volatile uint8_t led_int_blinking = 0;

volatile uint32_t led_ext1_last_toggle_time = 0;
volatile uint32_t led_ext2_last_toggle_time = 0;
volatile uint32_t led_int_last_toggle_time = 0;

volatile uint32_t current_time_ms = 0; // Contador de tempo para pisca-pisca

// --- Protótipos de Funções ---
void delay_ms(unsigned int ms);
void uartInit(void);
void uartPutChar(char c);
void uartPutString(const char *str);
char uartGetChar(void);
void gpioInit(void);
void aintcInit(void);
void enable_irq(uint32_t irq_id);
void showMenu(void);
void handleCommand(char cmd);
void gpio_irq_handler(void); // Novo manipulador para interrupções GPIO
void ISR_Handler(void); // Manipulador de interrupção principal

// --- Funções de Utilitário ---

// Atraso simples (busy-wait). Este atraso é aproximado e depende da frequência do CPU.
// Ajuste o valor "2000" para calibrar 1ms no seu ambiente.
void delay_ms(unsigned int ms) {
    for (volatile unsigned int i = 0; i < ms * 2000; i++);
}

// --- Funções UART ---

// Inicializa a UART0 para comunicação serial (115200 baud, 8N1)
void uartInit(void) {

    // Configurar Pin Muxing para UART0_TXD e UART0_RXD
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_UART0_TXD_OFFSET)) = 0x00; // P9_24 (UART0_TXD): Mode 0 (UART), sem pull-up/down, receiver desabilitado
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_UART0_RXD_OFFSET)) = 0x20; // P9_26 (UART0_RXD): Mode 0 (UART), pull-up habilitado, receiver habilitado

    // Configurar registradores da UART0
    UART0_LCR |= (1 << 7); // Habilitar DLAB (Divisor Latch Access Bit)
    UART0_DLL = 26;        // Baud Rate 115200 bps com 48MHz clock (Divisor = 26)
    UART0_DLH = 0;
    UART0_LCR &= ~(1 << 7); // Desabilitar DLAB
    UART0_LCR = (3 << 0);   // 8-bit data, no parity, 1 stop bit (8N1)
    UART0_FCR = (1 << 0);   // Habilitar FIFO
    UART0_MDR1 = 0x0;       // Modo UART16x
}

// Envia um caractere via UART0
void uartPutChar(char c) {
    while (!(UART0_LSR & (1 << 5))); // Espera THR vazio
    UART0_THR = c;
}

// Envia uma string via UART0
void uartPutString(const char *str) {
    while (*str) {
        uartPutChar(*str++);
    }
}

// Lê um caractere via UART0
char uartGetChar(void) {
    while (!(UART0_LSR & (1 << 0))); // Espera dados disponíveis
    return (char)(UART0_RHR);
}

// --- Funções GPIO ---

// Inicializa os módulos GPIO e configura LEDs/Botões
void gpioInit(void) {
    // Habilitar clocks para GPIO0 e GPIO1
    CM_PER_GPIO1_CLKCTRL = 0x2;  // Habilita clock para GPIO1 (domínio PER)

    // Aguarda a ativação dos clocks
    while ((CM_PER_GPIO1_CLKCTRL & 0x2) == 0x0);

    // Configurar Pin Muxing para LEDs e Botões (Modo 7 para GPIO)
    // Para saídas (LEDs): 0x07
    // Para entradas (Botões): 0x27 (pull-up habilitado)
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO1_17_OFFSET)) = 0x07; // P9_23 (LED_EXT1)
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO1_15_OFFSET)) = 0x07; // P9_15 (LED_EXT2)
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO1_21_OFFSET)) = 0x07; // User LED0 (LED_INT)

    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO1_28_OFFSET)) = 0x27; // P9_12 (BTN1)
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO0_27_OFFSET)) = 0x27; // P8_17 (BTN2)
    (*(volatile uint32_t *)(CONTROL_MODULE_BASE_ADDR + CM_CONF_GPIO1_16_OFFSET)) = 0x27; // P9_16 (BTN3)

    // Configura LEDs como saída
    GPIO1_OE &= ~(LED_EXT1_GPIO1_17 | LED_EXT2_GPIO1_15 | LED_INT_GPIO1_21);

    // Configura botões como entrada
    GPIO1_OE |= BTN1_GPIO1_28 | BTN3_GPIO1_16;
    GPIO0_OE |= BTN2_GPIO0_27;

    // Configura e habilita o debounce de hardware para os botões
    // GPIO1_DEBOUNCINGTIME = 644; // ~20ms
    // GPIO0_DEBOUNCINGTIME = 644;

    // GPIO1_DEBOUNCENABLE = BTN1_GPIO1_28 | BTN3_GPIO1_16;
    // GPIO0_DEBOUNCENABLE = BTN2_GPIO0_27;

    // Configura a detecção de borda para interrupções (Falling Edge para botões active-low)
    GPIO1_FALLINGDETECT |= BTN1_GPIO1_28 | BTN3_GPIO1_16;
    GPIO0_FALLINGDETECT |= BTN2_GPIO0_27;

    // Limpa quaisquer flags de interrupção pendentes antes de habilitar
    // GPIO1_IRQSTATUS_0 = 0xFFFFFFFF; // Limpa todas as flags
    // GPIO0_IRQSTATUS_0 = 0xFFFFFFFF; // Limpa todas as flags

    // Ativa as interrupções para os botões dentro dos módulos GPIO.
    GPIO1_IRQSTATUS_SET_0 = BTN1_GPIO1_28 | BTN3_GPIO1_16;
    GPIO0_IRQSTATUS_SET_0 = BTN2_GPIO0_27;
}

// --- Funções AINTC (Advanced Interrupt Controller) ---

// Inicializa o AINTC
void aintcInit(void) {
    // Resetar o AINTC
    // AINTC_SYSCONFIG |= (1 << 1); // SRST bit
    // while (!(AINTC_SYSCONFIG & (1 << 0))); // Espera o reset completar (IDLEST bit 0)

    // // Modo normal de operação
    // AINTC_SYSCONFIG &= ~(1 << 1); // Clear SRST
    // AINTC_SYSCONFIG |= (1 << 0);  // Smartidle para IDLEST (opcional, mas boa prática)

    // Mapear interrupções para o canal 0 (maior prioridade)
    // GPIO0 (IRQ 62) e GPIO1 (IRQ 63)
    // O valor 0 << 2 significa canal 0
    // AINTC_ILR(GPIO0_IRQ_ID) = (0 << 2);
    // AINTC_ILR(GPIO1_IRQ_ID) = (0 << 2);

    // Desmascarar as interrupções para os GPIOs
    enable_irq(GPIO0_IRQ_ID);
    enable_irq(GPIO1_IRQ_ID);
}

// Habilita uma IRQ específica no AINTC
void enable_irq(uint32_t irq_id) {
    uint32_t reg_offset = irq_id / 32;
    uint32_t bit_offset = irq_id % 32;
    AINTC_MIR_CLEAR(reg_offset) = (1 << bit_offset);
}

// --- Manipuladores de Interrupção ---

// Manipulador de interrupção específico para GPIOs
void gpio_irq_handler(void) {
    uint32_t gpio0_status = GPIO0_IRQSTATUS_0;
    uint32_t gpio1_status = GPIO1_IRQSTATUS_0;

    // Botão 1 (P9_12 - GPIO1_28): Controla LED_EXT1
    if (gpio1_status & BTN1_GPIO1_28) {
        GPIO1_IRQSTATUS_0 = BTN1_GPIO1_28; // Limpa a flag no módulo GPIO
        led_ext1_blinking = !led_ext1_blinking; // Toggle estado de pisca
        if (led_ext1_blinking) {
            GPIO1_SETDATAOUT = LED_EXT1_GPIO1_17;
            uartPutString("\nBTN1 pressionado: LED_EXT1 (P9_23) PISCANDO!\n\r");
        } else {
            GPIO1_CLEARDATAOUT = LED_EXT1_GPIO1_17; // Desliga o LED se parar de piscar
            uartPutString("\nBTN1 pressionado: LED_EXT1 (P9_23) PAROU de piscar.\n\r");
        }
        //showMenu();
    }

    // Botão 2 (P8_17 - GPIO0_27): Controla LED_INT
    if (gpio0_status & BTN2_GPIO0_27) {
        GPIO0_IRQSTATUS_0 = BTN2_GPIO0_27; // Limpa a flag no módulo GPIO
        led_int_blinking = !led_int_blinking; // Toggle estado de pisca
        if (led_int_blinking) {
            GPIO1_SETDATAOUT = LED_INT_GPIO1_21;
            uartPutString("\nBTN2 pressionado: LED_INT (User LED0) PISCANDO!\n\r");
        } else {
            GPIO1_CLEARDATAOUT = LED_INT_GPIO1_21; // Desliga o LED
            uartPutString("\nBTN2 pressionado: LED_INT (User LED0) PAROU de piscar.\n\r");
        }
        //showMenu();
    }

    // Botão 3 (P9_16 - GPIO1_16): Controla LED_EXT2
    if (gpio1_status & BTN3_GPIO1_16) {
        GPIO1_IRQSTATUS_0 = BTN3_GPIO1_16; // Limpa a flag no módulo GPIO
        led_ext2_blinking = !led_ext2_blinking; // Toggle estado de pisca
        if (led_ext2_blinking) {
            GPIO1_SETDATAOUT = LED_EXT2_GPIO1_15;
            uartPutString("\nBTN3 pressionado: LED_EXT2 (P9_15) PISCANDO!\n\r");
        } else {
            GPIO1_CLEARDATAOUT = LED_EXT2_GPIO1_15; // Desliga o LED
            uartPutString("\nBTN3 pressionado: LED_EXT2 (P9_15) PAROU de piscar.\n\r");
        }
        //showMenu();
    }
}

// Manipulador de interrupção principal
// Este é o vetor de interrupções da CPU, chamado pelo start.s
void ISR_Handler(void) {
    //uartPutString("\nBTN3 pressionado: LED_EXT2 (P9_15) PAROU de piscar.\n\r");
    // Leitura do registrador de interrupção para identificar a IRQ ativa
    // O valor lido aqui é o ID da IRQ mais prioritária
    uint32_t irq_id = *(volatile uint32_t *)(AINTC_BASE_ADDR + 0x40) & 0x7f; // INTC_ILR_REG (current active IRQ)

    if (irq_id == GPIO0_IRQ_ID || irq_id == GPIO1_IRQ_ID) {
        gpio_irq_handler(); // Chama o manipulador específico para GPIO
    }
    // Adicionar outros manipuladores de IRQ conforme necessário

    // Sinaliza o fim da interrupção para o AINTC
    AINTC_EOIR = 0x0; // Escreve 0 para indicar "End Of Interrupt"
}

// --- Funções de Lógica do Programa ---

// Exibe o menu de opções no terminal UART
void showMenu(void) {
    uartPutString("\n\n===== MENU DE CONTROLE DE LEDS =====\n\r");
    uartPutString("  LED Externo 1 (P9_23) - Status: \n\r");
    uartPutString((GPIO1_DATAOUT & LED_EXT1_GPIO1_17) ? "LIGADO \n\r" : "DESLIGADO\n\r");
    uartPutString(led_ext1_blinking ? " (PISCANDO)\n\r" : "\n");

    uartPutString("  LED Externo 2 (P9_15) - Status: \n\r");
    uartPutString((GPIO1_DATAOUT & LED_EXT2_GPIO1_15) ? "LIGADO\n\r" : "DESLIGADO\n\r");
    uartPutString(led_ext2_blinking ? " (PISCANDO)\n\r" : "\n");

    uartPutString("  LED Interno (User LED0) - Status: \n\r");
    uartPutString((GPIO1_DATAOUT & LED_INT_GPIO1_21) ? "LIGADO \n\r" : "DESLIGADO\n\r");
    uartPutString(led_int_blinking ? " (PISCANDO)\n\r" : "\n");
    uartPutString("------------------------------------\n\r");
    uartPutString("  COMANDOS VIA TECLADO:\n\r");
    uartPutString("  a - Ligar LED_EXT1\n\r");
    uartPutString("  s - Desligar LED_EXT1\n\r");
    uartPutString("  d - Ligar LED_EXT2\n\r");
    uartPutString("  f - Desligar LED_EXT2\n\r");
    uartPutString("  g - Ligar LED_INT\n\r");
    uartPutString("  h - Desligar LED_INT\n\r");
    uartPutString("  1 - Ativar/Desativar PISCA LED_EXT1 (P9_23)\n\r");
    uartPutString("  2 - Ativar/Desativar PISCA LED_EXT2 (P9_15)\n\r");
    uartPutString("  3 - Ativar/Desativar PISCA LED_INT (User LED0)\n\r");
    uartPutString("  m - Mostrar Menu Novamente\n\r");
    uartPutString("------------------------------------\n\r");
    uartPutString("Pressione um BOTAO ou digite um comando: \n\r");
}

// Trata um comando recebido via UART
void handleCommand(char cmd) {
    switch (cmd) {
        case 'a':
            GPIO1_SETDATAOUT = LED_EXT1_GPIO1_17;
            led_ext1_blinking = 1; // Desliga o pisca se ligar manualmente
            uartPutString("LED_EXT1 ligado.\n");
            break;
        case 's':
            GPIO1_CLEARDATAOUT = LED_EXT1_GPIO1_17;
            led_ext1_blinking = 0; // Desliga o pisca se desligar manualmente
            uartPutString("LED_EXT1 desligado.\n");
            break;
        case 'd':
            GPIO1_SETDATAOUT = LED_EXT2_GPIO1_15;
            led_ext2_blinking = 1;
            uartPutString("LED_EXT2 ligado.\n");
            break;
        case 'f':
            GPIO1_CLEARDATAOUT = LED_EXT2_GPIO1_15;
            led_ext2_blinking = 0;
            uartPutString("LED_EXT2 desligado.\n");
            break;
        case 'g':
            GPIO1_SETDATAOUT = LED_INT_GPIO1_21;
            led_int_blinking = 1;
            uartPutString("LED_INT ligado.\n");
            break;
        case 'h':
            GPIO1_CLEARDATAOUT = LED_INT_GPIO1_21;
            led_int_blinking = 0;
            uartPutString("LED_INT desligado.\n");
            break;
        case '1':
            led_ext1_blinking = 1^led_ext1_blinking;
            if(led_ext1_blinking){
                GPIO1_SETDATAOUT = LED_EXT1_GPIO1_17;
            }else{
                GPIO1_CLEARDATAOUT = LED_EXT1_GPIO1_17;
            }
            break;
        case '2':
            led_ext2_blinking = !led_ext2_blinking;
            if (led_ext2_blinking) uartPutString("LED_EXT2 (P9_15) - Pisca ATIVADO.\n");
            else { GPIO1_CLEARDATAOUT = LED_EXT2_GPIO1_15; uartPutString("LED_EXT2 (P9_15) - Pisca DESATIVADO.\n"); }
            break;
        case '3':
            led_int_blinking = !led_int_blinking;
            if (led_int_blinking) uartPutString("LED_INT (User LED0) - Pisca ATIVADO.\n");
            else { GPIO1_CLEARDATAOUT = LED_INT_GPIO1_21; uartPutString("LED_INT (User LED0) - Pisca DESATIVADO.\n"); }
            break;
        case 'm':
        case 'M':
            break; // O menu será exibido novamente no final da função
        default:
            uartPutString("Opcao invalida. Digite 'm' para o menu.\n");
            break;
    }
    showMenu();
}

// Função para atualizar o estado dos LEDs que estão piscando
void updateBlinkingLeds(void) {
    // Intervalo de pisca-pisca (em ms)
    const uint32_t BLINK_INTERVAL = 500; // Pisca a cada 500ms

    if (led_ext1_blinking && (current_time_ms - led_ext1_last_toggle_time >= BLINK_INTERVAL)) {
        if (GPIO1_DATAOUT & LED_EXT1_GPIO1_17) {
            GPIO1_CLEARDATAOUT = LED_EXT1_GPIO1_17;
        } else {
            GPIO1_SETDATAOUT = LED_EXT1_GPIO1_17;
        }
        led_ext1_last_toggle_time = current_time_ms;
    }

    if (led_ext2_blinking && (current_time_ms - led_ext2_last_toggle_time >= BLINK_INTERVAL)) {
        if (GPIO1_DATAOUT & LED_EXT2_GPIO1_15) {
            GPIO1_CLEARDATAOUT = LED_EXT2_GPIO1_15;
        } else {
            GPIO1_SETDATAOUT = LED_EXT2_GPIO1_15;
        }
        led_ext2_last_toggle_time = current_time_ms;
    }

    if (led_int_blinking && (current_time_ms - led_int_last_toggle_time >= BLINK_INTERVAL)) {
        if (GPIO1_DATAOUT & LED_INT_GPIO1_21) {
            GPIO1_CLEARDATAOUT = LED_INT_GPIO1_21;
        } else {
            GPIO1_SETDATAOUT = LED_INT_GPIO1_21;
        }
        led_int_last_toggle_time = current_time_ms;
    }
}

// --- Função Principal ---
int main(void) {
    // Inicializa todos os periféricos necessários
    uartInit();
    gpioInit();
    aintcInit(); // Inicializa o controlador de interrupções

    // Habilita as interrupções globais da CPU.
    // Esta linha é ARM-specific. Em um projeto real, estaria no start.s.
    // Aqui para garantir que as IRQs estejam habilitadas.
    __asm__ __volatile__("cpsie i"); // Enable IRQ (CPSR I-bit)

    uartPutString("Sistema de Controle de LEDs e Botoes - BBB\r\n");
    showMenu(); // Exibe o menu inicial ao usuário

    // Loop principal do programa
    while (1) {
        //GPIO1_SETDATAOUT = LED_EXT1_GPIO1_17 | LED_EXT2_GPIO1_15;
        
        //uartPutString("Sistema de Controle de LEDs e Botoes - BBB\r\n");
        //Atualiza o contador de tempo (simulado)
        current_time_ms += 10; // Incrementa o tempo a cada 10ms do delay

        // Atualiza o estado dos LEDs que devem piscar
        //updateBlinkingLeds();

        // Verifica se há dados disponíveis na UART para leitura (non-blocking)
        if (UART0_LSR & (1 << 0)) { // Verifica o bit 0 (DR - Data Ready) do Line Status Register
            char c = uartGetChar();
            handleCommand(c);
        }

        // Pequeno atraso para controlar a taxa do loop e a simulação de tempo
        delay_ms(10);
    }

    return 0;
}
