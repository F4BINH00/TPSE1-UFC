# ⏱️ Prática 06 – GPIO e Timers via Interrupção

## Objetivo

Utilizar o **DMTimer** da BeagleBone Black para gerar interrupções periódicas, permitindo o controle de GPIOs e a implementação de temporizações precisas sem o uso de delays bloqueantes.

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* LEDs
* Push Buttons

---

## Funcionalidades

* Configuração do DMTimer.
* Geração de interrupções periódicas por overflow.
* Controle de LEDs utilizando interrupções.
* Integração entre Timer e GPIO.
* Implementação de temporização não bloqueante.

---

## Estrutura dos Arquivos

```text
Pratica06/
├── bin/
│   └── spl.boot
├── inc/
│   ├── bbb_regs.h
│   └── hw_types.h
├── obj/
├── src/
│   ├── main.c
│   └── start.s
└── Makefile
```

### Descrição dos Diretórios

| Diretório/Arquivo | Descrição                                                                                                                                       |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| `src/`            | Contém o código-fonte da aplicação, incluindo a lógica principal e o código de inicialização do processador.                                    |
| `inc/`            | Arquivos de cabeçalho (`.h`) com definições dos registradores, constantes e periféricos da BeagleBone Black, além de tipos e macros auxiliares. |
| `obj/`            | Diretório onde são gerados os arquivos objeto (`.o`) durante a compilação.                                                                      |
| `bin/`            | Contém o arquivo final (`spl.boot`) utilizado para carregar a aplicação na BeagleBone Black.                                                    |
| `Makefile`        | Automatiza o processo de compilação, montagem, ligação e geração do arquivo correspondente.                                                     |

---

## Como Compilar

```bash
make
```

---

## Como Executar

1. Compile o projeto utilizando o `make`.
2. Carregue a aplicação na BeagleBone Black por meio do U-Boot.
3. Execute a aplicação.
4. Observe os LEDs sendo controlados pelas interrupções geradas pelo DMTimer.

---

## Conceitos Abordados

* DMTimer
* Interrupções periódicas
* Temporização em hardware
* GPIO
* Manipulação de registradores
* Programação Bare-Metal
* ARM Cortex-A8
* Sincronização de eventos
