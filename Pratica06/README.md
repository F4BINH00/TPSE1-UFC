# ⏱️ Prática 06 – GPIO e Timers

## Objetivo

Utilizar temporizadores de hardware para gerar eventos periódicos através de interrupções, eliminando delays bloqueantes.

---

## Hardware Utilizado

* BeagleBone Black
* LEDs
* Push Buttons

---

## Funcionalidades

* Configuração do DMTimer.
* Geração de interrupções periódicas.
* Controle de LEDs.
* Integração entre Timer e GPIO.

---

## Estrutura dos Arquivos

```text
main.c
timer.c
interrupt.c
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
2. Carregue o programa.
3. Observe os LEDs sendo controlados pelo Timer.

---

## Conceitos Abordados

* DMTimer
* Overflow
* Temporização
* Interrupções periódicas
* Delay não bloqueante
* Sincronização de eventos
