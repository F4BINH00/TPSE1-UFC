#include "hw_types.h"
#include "soc_AM335x.h"

// --- Definições de Hardware ---
// Endereços base
#define GPIO1_BASE              (SOC_GPIO_1_REGS)
#define CM_PER_BASE             (SOC_CM_PER_REGS)
#define CONTROL_MODULE_BASE     (SOC_CONTROL_REGS)

// Offsets de registradores do GPIO
#define GPIO_OE                 (0x134)
#define GPIO_DATAIN             (0x138)
#define GPIO_SETDATAOUT         (0x194)
#define GPIO_CLEARDATAOUT       (0x190)

// Offset de clock do GPIO10
#define CM_PER_GPIO1_CLKCTRL    (0xAC)
#define MODULE_ENABLE           (0x2)

// --- Definições de Pinos e MUX ---
// Pinos de Botão
#define BOTAO_MODO_PIN_MUX      (0x878) // P9_12
#define BOTAO_MODO_MASCARA      (1 << 28)

#define BOTAO_EXTRA_PIN_MUX     (0x844) // P9_23
#define BOTAO_EXTRA_MASCARA     (1 << 17)

// Pino do LED Externo
#define LED_EXTERNO_PIN_MUX     (0x840) // P9_15
#define LED_EXTERNO_MASCARA     (1 << 16)

// Pinos dos LEDs da Placa
#define LED_USR0_PIN_MUX        (0x854)
#define LED_USR0_MASCARA        (1 << 21)
#define LED_USR1_PIN_MUX        (0x858)
#define LED_USR1_MASCARA        (1 << 22)
#define LED_USR2_PIN_MUX        (0x85C)
#define LED_USR2_MASCARA        (1 << 23)
#define LED_USR3_PIN_MUX        (0x860)
#define LED_USR3_MASCARA        (1 << 24)

#define LEDS_USR_MASCARA_TODOS (LED_USR0_MASCARA | LED_USR1_MASCARA | LED_USR2_MASCARA | LED_USR3_MASCARA)

// Configuração de msetenv app "setenv autoload no;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 app.bin;echo *Booting to BareMetal *;go 0x80000000"odo dos pinos
#define MODO_GPIO_SAIDA         (0x0F) // GPIO, Pull-up/down desabilitado
#define MODO_GPIO_ENTRADA_PD    (0x2F) // GPIO, com Pull-down habilitado

// --- Constantes de Software ---
#define TEMPO_ATRASO_PADRAO     (400000)
#define TEMPO_DEBOUNCE          (20000)
// NOVO: Constante dedicada para a velocidade do scanner
#define TEMPO_ATRASO_SCANNER    (450000) 

// Enum com 4 modos de operação
typedef enum {
    MODO_SCANNER,
    MODO_CONVERGENTE,
    MODO_BATIMENTO,
    MODO_BARRA_DE_CARGA,
    MODO_CONTAGEM // Agora com valor 4, para ciclar os modos
} ModoOperacao;

// --- Funções de Baixo Nível (Inline) ---
static inline void gpioSet(unsigned int mascara) { HWREG(GPIO1_BASE + GPIO_SETDATAOUT) = mascara; }
static inline void gpioClear(unsigned int mascara) { HWREG(GPIO1_BASE + GPIO_CLEARDATAOUT) = mascara; }
static inline int gpioRead(unsigned int mascara) { return (HWREG(GPIO1_BASE + GPIO_DATAIN) & mascara); }
static inline void esperar(volatile unsigned int tempo) { while(tempo--); }

// --- Funções de Configuração ---
void configurarPinos(void) {
    HWREG(CM_PER_BASE + CM_PER_GPIO1_CLKCTRL) |= MODULE_ENABLE;
    HWREG(CONTROL_MODULE_BASE + BOTAO_MODO_PIN_MUX)  = MODO_GPIO_ENTRADA_PD;
    HWREG(CONTROL_MODULE_BASE + BOTAO_EXTRA_PIN_MUX) = MODO_GPIO_ENTRADA_PD;
    HWREG(CONTROL_MODULE_BASE + LED_EXTERNO_PIN_MUX) = MODO_GPIO_SAIDA;
    HWREG(CONTROL_MODULE_BASE + LED_USR0_PIN_MUX)    = MODO_GPIO_SAIDA;
    HWREG(CONTROL_MODULE_BASE + LED_USR1_PIN_MUX)    = MODO_GPIO_SAIDA;
    HWREG(CONTROL_MODULE_BASE + LED_USR2_PIN_MUX)    = MODO_GPIO_SAIDA;
    HWREG(CONTROL_MODULE_BASE + LED_USR3_PIN_MUX)    = MODO_GPIO_SAIDA;
    unsigned int direcao_original = HWREG(GPIO1_BASE + GPIO_OE);
    unsigned int direcao_nova = (direcao_original & ~(LEDS_USR_MASCARA_TODOS | LED_EXTERNO_MASCARA)) | (BOTAO_MODO_MASCARA | BOTAO_EXTRA_MASCARA);
    HWREG(GPIO1_BASE + GPIO_OE) = direcao_nova;
    gpioClear(LEDS_USR_MASCARA_TODOS | LED_EXTERNO_MASCARA);
}

// --- Funções de Lógica de Alto Nível ---
int detectarClique(unsigned int mascara_botao) {
    if (gpioRead(mascara_botao)) {
        esperar(TEMPO_DEBOUNCE);
        if (gpioRead(mascara_botao)) {
            while (gpioRead(mascara_botao));
            return 1;
        }
    }
    return 0;
}

void disable_watchdog(){
    //while(HWREG(0x44E35034) != 0);
    HWREG(0x44E335048) = 0xAAAA;
    while(HWREG(0x44E35034) != 0);
    HWREG(0x44E335048) = 0x5555;
    while(HWREG(0x44E35034) != 0);
}

// --- Padrões de LED ---
// PADRÃO 1: Scanner "Knight Rider"
void executarPadraoScanner(void) {
    // Da esquerda para a direita
    for (int i = 0; i < 4; i++) {
        if (gpioRead(BOTAO_MODO_MASCARA)) return;
        gpioSet(LED_USR0_MASCARA << i);
        esperar(TEMPO_ATRASO_SCANNER); // <-- MUDANÇA AQUI
        gpioClear(LED_USR0_MASCARA << i);
    }
    // Da direita para a esquerda (sem repetir os cantos)
    for (int i = 2; i > 0; i--) {
        if (gpioRead(BOTAO_MODO_MASCARA)) return;
        gpioSet(LED_USR0_MASCARA << i);
        esperar(TEMPO_ATRASO_SCANNER); // <-- MUDANÇA AQUI
        gpioClear(LED_USR0_MASCARA << i);
    }
}

// PADRÃO 2: Efeito Convergente/Divergente
void executarPadraoConvergente(void) {
    if (gpioRead(BOTAO_MODO_MASCARA)) return;
    const unsigned int mascaraExterna = LED_USR0_MASCARA | LED_USR3_MASCARA;
    const unsigned int mascaraInterna = LED_USR1_MASCARA | LED_USR2_MASCARA;
    gpioClear(LEDS_USR_MASCARA_TODOS);
    gpioSet(mascaraExterna);
    esperar(TEMPO_ATRASO_PADRAO);
    if (gpioRead(BOTAO_MODO_MASCARA)) return;
    gpioClear(LEDS_USR_MASCARA_TODOS);
    gpioSet(mascaraInterna);
    esperar(TEMPO_ATRASO_PADRAO);
}

// PADRÃO 3: Batimento Cardíaco
void executarPadraoBatimento(void) {
    if (gpioRead(BOTAO_MODO_MASCARA)) return;
    gpioSet(LEDS_USR_MASCARA_TODOS);
    esperar(TEMPO_ATRASO_PADRAO / 5);
    gpioClear(LEDS_USR_MASCARA_TODOS);
    esperar(TEMPO_ATRASO_PADRAO / 4);
    gpioSet(LEDS_USR_MASCARA_TODOS);
    esperar(TEMPO_ATRASO_PADRAO / 5);
    gpioClear(LEDS_USR_MASCARA_TODOS);
    esperar(TEMPO_ATRASO_PADRAO * 2);
}

// PADRÃO 4: Barra de Carga
void executarPadraoBarraDeCarga(void) {
    if (gpioRead(BOTAO_MODO_MASCARA)) return;
    for (int i = 0; i < 4; i++) {
        if (gpioRead(BOTAO_MODO_MASCARA)) { gpioClear(LEDS_USR_MASCARA_TODOS); return; }
        gpioSet(LED_USR0_MASCARA << i);
        esperar(TEMPO_ATRASO_PADRAO);
    }
    esperar(TEMPO_ATRASO_PADRAO);
    for (int i = 0; i < 4; i++) {
        if (gpioRead(BOTAO_MODO_MASCARA)) { gpioClear(LEDS_USR_MASCARA_TODOS); return; }
        gpioClear(LED_USR3_MASCARA >> i);
        esperar(TEMPO_ATRASO_PADRAO);
    }
    esperar(TEMPO_ATRASO_PADRAO);
}


// --- Função Principal (sem alterações) ---
int _main(void) {
    configurarPinos();
    //disable_watchdog();
    ModoOperacao modo_atual = MODO_SCANNER;
    int led_externo_ativo = 0;

    while (1) {
        if (detectarClique(BOTAO_MODO_MASCARA)) {
            modo_atual = (modo_atual + 1) % MODO_CONTAGEM;
            gpioClear(LEDS_USR_MASCARA_TODOS);
        }

        if (detectarClique(BOTAO_EXTRA_MASCARA)) {
            led_externo_ativo = !led_externo_ativo;
            if (led_externo_ativo) {
                gpioSet(LED_EXTERNO_MASCARA);
            } else {
                gpioClear(LED_EXTERNO_MASCARA);
            }
        }

        switch (modo_atual) {
            case MODO_SCANNER:
                executarPadraoScanner();
                break;
            case MODO_CONVERGENTE:
                executarPadraoConvergente();
                break;
            case MODO_BATIMENTO:
                executarPadraoBatimento();
                break;
            case MODO_BARRA_DE_CARGA:
                executarPadraoBarraDeCarga();
                break;
            default:
                modo_atual = MODO_SCANNER;
                break;
        }
    }
    return 0;
}
