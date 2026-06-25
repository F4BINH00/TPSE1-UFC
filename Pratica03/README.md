# 🔘 Prática 03 – GPIO como Entrada (Input)

## Objetivo

Implementar a leitura de botões utilizando GPIOs configurados como entrada, permitindo detectar estados lógicos provenientes do circuito externo.

---

## Hardware Utilizado

* BeagleBone Black
* Push Buttons
* Resistores Pull-Down
* Protoboard

---

## Funcionalidades

* Configuração de GPIO como entrada.
* Leitura do registrador `GPIO_DATAIN`.
* Detecção de pressionamento dos botões.
* Utilização de resistores Pull-Down para evitar estados flutuantes.

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
2. Faça o boot na BeagleBone Black.
3. Pressione os botões conectados.
4. Observe a resposta do sistema.

---

## Conceitos Abordados

* GPIO Input
* Pull-Up e Pull-Down
* Leitura de registradores
* Interface homem-hardware
* Debouncing (conceito)
* Leitura digital
