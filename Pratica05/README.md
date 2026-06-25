# 💻 Prática 05 – Comunicação Serial (UART)

## Objetivo

Implementar uma interface serial utilizando UART para controlar periféricos da BeagleBone Black através de comandos enviados pelo computador.

---

## Hardware Utilizado

* BeagleBone Black
* Cabo USB Serial
* Terminal Minicom

---

## Funcionalidades

* Configuração da UART0.
* Comunicação serial.
* Menu interativo.
* Controle de LEDs por comandos.
* Recepção e transmissão de caracteres.

---

## Estrutura dos Arquivos

```text
main.c
uart.c
uart.h
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
2. Carregue na placa.
3. Abra o Minicom.
4. Utilize o menu apresentado para controlar os LEDs.

---

## Conceitos Abordados

* UART
* Baud Rate
* Comunicação Serial
* Buffer de recepção
* Interface Homem-Máquina
* Entrada e saída serial
