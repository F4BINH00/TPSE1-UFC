#define CM_PER_GPIO1_CLKCTRL  (*(volatile unsigned int*)0x44E000AC)
#define CM_RTC_RTC_CLKCTRL    (*(volatile unsigned int*)0x44E00800)
#define CM_RTC_CLKSTCTRL      (*(volatile unsigned int*)0x44E00804)

#define UART0_THR             (*(volatile unsigned int*)0x44E09000)
#define UART0_RHR             (*(volatile unsigned int*)0x44E09000)
#define UART0_LSR             (*(volatile unsigned int*)0x44E09014)

#define WDT_WSPR              (*(volatile unsigned int*)0x44E35048)
#define WDT_WWPS              (*(volatile unsigned int*)0x44E35034)

#define GPIO1_OE              (*(volatile unsigned int*)0x4804C134)
#define GPIO1_CLEARDATAOUT    (*(volatile unsigned int*)0x4804C190)
#define GPIO1_SETDATAOUT      (*(volatile unsigned int*)0x4804C194)

#define INTC_SIR_IRQ          (*(volatile unsigned int*)0x48200040)
#define INTC_CONTROL          (*(volatile unsigned int*)0x48200048)
#define INTC_MIR_CLEAR2       (*(volatile unsigned int*)0x482000C8)

#define SECONDS_REG           (*(volatile unsigned int*)0x44E3E000)
#define MINUTES_REG           (*(volatile unsigned int*)0x44E3E004)
#define HOURS_REG             (*(volatile unsigned int*)0x44E3E008)
#define RTC_CTRL_REG          (*(volatile unsigned int*)0x44E3E040)
#define RTC_STATUS_REG        (*(volatile unsigned int*)0x44E3E044)
#define RTC_INTERRUPTS_REG    (*(volatile unsigned int*)0x44E3E048)
#define RTC_OSC_REG           (*(volatile unsigned int*)0x44E3E054)
#define KICK0R                (*(volatile unsigned int*)0x44E3E06C)
#define KICK1R                (*(volatile unsigned int*)0x44E3E070)

/* ==============================================================================
 * PONTO DE DIFERENÇA: FUNÇÕES DE INTERAÇÃO COM O USUÁRIO
 * As funções a seguir (`put_str`, `put_ch`, `get_ch`, `read_two_digits`)
 * criam uma interface de texto para o usuário configurar o relógio.
 * ==============================================================================
 */
void disable_wdt(void){
  WDT_WSPR = 0xAAAA;
  while((WDT_WWPS & (1<<4)));
  WDT_WSPR = 0x5555;
  while((WDT_WWPS & (1<<4)));
}

void put_ch(unsigned char c){
  while(!(UART0_LSR & (1<<5)));
  UART0_THR = c;
}

void put_str(const char *str){
  while(*str){
    put_ch(*str++);
  }
}

unsigned char get_ch(void){
  while(!(UART0_LSR & (1<<0)));
  return (unsigned char)UART0_RHR;
}

unsigned int read_two_digits(void){
  unsigned int num = 0;
  unsigned char ch;

  ch = get_ch();
  put_ch(ch);
  num = (ch - '0') * 10;

  ch = get_ch();
  put_ch(ch);
  num += (ch - '0');

  return num;
}

void gpio_setup(void){
  CM_PER_GPIO1_CLKCTRL = 0x40002;
  GPIO1_OE &= ~(1<<21);
}

void ledOff(void){
  GPIO1_CLEARDATAOUT = (1<<21);
}

void ledOn(void){
  GPIO1_SETDATAOUT = (1<<21);
}

void print_time(void){
  unsigned char h = HOURS_REG;
  unsigned char m = MINUTES_REG;
  unsigned char s = SECONDS_REG;

  put_ch(0x30 + ((h >> 4) & 0x3));
  put_ch(0x30 + ((h >> 0) & 0xf));
  put_ch(':');
  put_ch(0x30 + ((m >> 4) & 0x7));
  put_ch(0x30 + ((m >> 0) & 0xf));
  put_ch(':');
  put_ch(0x30 + ((s >> 4) & 0x7));
  put_ch(0x30 + ((s >> 0) & 0xf));
  put_ch('\r');
}

int flg_led = 0;

void rtc_irq_handler(void){
  if (flg_led++ & 0x1)
    ledOn();
  else
    ledOff();

  print_time();
  /* PONTO DE DIFERENÇA: LIMPEZA DA FLAG DE INTERRUPÇÃO (CRÍTICO)
   * A linha abaixo informa ao hardware do RTC que a interrupção foi tratada,
   * permitindo que a próxima seja gerada. Não tê-la é um erro que faria a 
   * interrupção ocorrer apenas uma vez.
   */
  //Limpa a flag da interrupção do RTC para permitir a próxima
  RTC_STATUS_REG |= 0x4;
}

void IRQ_Handler(void){
  unsigned int irq_number = INTC_SIR_IRQ & 0x7f;
  if(irq_number == 75){
    rtc_irq_handler();
  }
  INTC_CONTROL = 1;
}

void rtc_setup(void){
  CM_RTC_CLKSTCTRL   = 0x2;
  CM_RTC_RTC_CLKCTRL = 0x2;

  KICK0R = 0x83E70B13;
  KICK1R = 0x95A4F1E0;

  RTC_OSC_REG = 0x48;

  RTC_INTERRUPTS_REG = 0x0;  // Desativa interrupções no início

  RTC_CTRL_REG &= ~0x01;  // Garante parado
  while(RTC_STATUS_REG & 0x01);

  RTC_CTRL_REG |= 0x01;  // Libera acesso
  while(RTC_STATUS_REG & 0x01);

  RTC_CTRL_REG &= ~0x01;  // Stop RTC para configurar
  while(RTC_STATUS_REG & 0x01);
}

/* ==============================================================================
 * PONTO DE DIFERENÇA: FUNÇÃO PARA AJUSTAR A HORA
 * Esta é a função principal para a interação com o usuário
 * ==============================================================================
 */
void set_rtc_time(void){
  put_str("\nDigite HORAS (00 a 23): ");
  unsigned int hh = read_two_digits();
  HOURS_REG = ((hh/10)<<4) | (hh%10);
  put_str("\r\n");
  put_str("Digite MINUTOS (00 a 59): ");
  unsigned int mm = read_two_digits();
  MINUTES_REG = ((mm/10)<<4) | (mm%10);
  put_str("\r\n");
  put_str("Digite SEGUNDOS (00 a 59): ");
  unsigned int ss = read_two_digits();
  SECONDS_REG = ((ss/10)<<4) | (ss%10);
  put_str("\n\r");
}

void rtc_start(void){
  RTC_INTERRUPTS_REG = 0x4; // Interrupção a cada segundo
  RTC_CTRL_REG |= 0x01;     // Inicia o RTC
  while(RTC_STATUS_REG & 0x01);

  INTC_MIR_CLEAR2 |= (1<<11); // Libera IRQ 75
}

int main(void){
  gpio_setup();
  rtc_setup();
  disable_wdt();

  put_str("\nHello Interrupt2!\n\r");

  set_rtc_time();
  rtc_start();

   /* PONTO DE DIFERENÇA: HABILITAÇÃO GLOBAL DE INTERRUPÇÕES (CRÍTICO)
   * O comando em assembly abaixo habilita o processador a responder aos
   * pedidos de interrupção. Sem ele, a rotina IRQ_Handler nunca seria executada.
   */
  __asm__ volatile("cpsie i");  // Habilita interrupções

  while(1);

  return 0;
}
