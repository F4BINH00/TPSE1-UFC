# 💡 Prática 02 – GPIO como Saída (Output)

## Objetivo

Configurar os periféricos GPIO da BeagleBone Black como saída (Output), permitindo controlar LEDs através da manipulação direta dos registradores do processador AM335x.

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* LEDs
* Resistores
* Protoboard

---

## Funcionalidades

* Habilitação do clock do módulo GPIO.
* Configuração do multiplexador de pinos (PinMux).
* Configuração dos GPIOs como saída.
* Acionamento e desligamento de LEDs utilizando os registradores:

  * `GPIO_SETDATAOUT`
  * `GPIO_CLEARDATAOUT`

---

## Estrutura dos Arquivos

```text
main.c
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
2. Carregue o binário utilizando o U-Boot.
3. Execute na BeagleBone Black.
4. Observe o acionamento dos LEDs.

---

## Conceitos Abordados

* Programação Bare-Metal
* GPIO
* Manipulação direta de registradores
* Mapeamento de memória
* Clock Manager (CM_PER)
* Pin Multiplexing (PinMux)
* Operações atômicas em hardware
