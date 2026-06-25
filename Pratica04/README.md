# ⚡ Prática 04 – Interrupções em GPIO

## Objetivo

Substituir o método de polling pelo tratamento de eventos utilizando interrupções externas, aumentando a eficiência da aplicação.

---

## Hardware Utilizado

* BeagleBone Black
* Push Buttons
* LEDs

---

## Funcionalidades

* Configuração do controlador de interrupções (AINTC).
* Configuração de interrupções por borda de subida.
* Implementação da ISR (Interrupt Service Routine).
* Limpeza das flags de interrupção.

---

## Estrutura dos Arquivos

```text
main.c
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
3. Pressione um botão.
4. A interrupção será executada imediatamente.

---

## Conceitos Abordados

* Interrupt Vector Table (IVT)
* AINTC
* ISR
* Eventos assíncronos
* Polling × Interrupções
* Latência de interrupção
