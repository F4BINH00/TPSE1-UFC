# 🕒 Prática 07 – Real Time Clock (RTC)

## Objetivo

Configurar o RTC da BeagleBone Black para gerar interrupções periódicas e manter a contagem de tempo em tempo real.

---

## Hardware Utilizado

* BeagleBone Black
* Terminal Serial (UART)

---

## Funcionalidades

* Inicialização do RTC.
* Ajuste da data e hora.
* Geração de interrupções a cada segundo.
* Impressão do horário pela UART.

---

## Estrutura dos Arquivos

```text
main.c
rtc.c
uart.c
start.s
linker.ld
Makefile
```

---

## Como Compilar

```bash
make
```

---

## Como Executar

1. Compile o projeto.
2. Carregue na BeagleBone Black.
3. Abra o terminal serial.
4. Observe a atualização do horário em tempo real.

---

## Conceitos Abordados

* RTC
* Clock de hardware
* Osciladores
* Contagem de tempo
* Interrupções periódicas
* Sistemas embarcados em tempo real
