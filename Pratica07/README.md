# 🕒 Prática 07 – Real Time Clock (RTC)

## Objetivo

Configurar o **Real Time Clock (RTC)** da BeagleBone Black para gerar interrupções periódicas, permitindo a atualização contínua do horário e sua exibição por meio da comunicação serial (UART).

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* Computador com terminal serial (Minicom)

---

## Funcionalidades

* Configuração e inicialização do RTC.
* Configuração da UART0 para comunicação serial.
* Geração de interrupções periódicas (1 Hz).
* Atualização e exibição do horário via terminal serial.

---

## Estrutura dos Arquivos

```text
Pratica07/
├── bin/
│   └── spl.boot
├── inc/
│   └── bbb_regs.h
├── obj/
├── src/
│   ├── main.c
│   └── start.s
└── Makefile
```

### Descrição dos Diretórios

| Diretório/Arquivo | Descrição                                                                                                    |
| ----------------- | ------------------------------------------------------------------------------------------------------------ |
| `src/`            | Contém o código-fonte da aplicação, incluindo a lógica principal e o código de inicialização do processador. |
| `inc/`            | Arquivos de cabeçalho (`.h`) com definições de registradores, constantes e periféricos da BeagleBone Black.  |
| `obj/`            | Diretório onde são gerados os arquivos objeto (`.o`) durante a compilação.                                   |
| `bin/`            | Contém o arquivo final (`spl.boot`) utilizado para carregar a aplicação na BeagleBone Black.                 |
| `Makefile`        | Automatiza o processo de compilação, montagem, ligação e geração do arquivo executável.                      |

## Como Compilar
```
make
```

---

## Como Executar

1. Compile o projeto utilizando o `make`.
2. Carregue a aplicação na BeagleBone Black por meio do U-Boot.
3. Abra um terminal serial (ex.: Minicom).
4. Execute a aplicação e acompanhe a atualização do horário em tempo real.

---

## Conceitos Abordados

* Real Time Clock (RTC)
* Comunicação Serial (UART)
* Tratamento de interrupções
* Registradores de hardware
* Programação Bare-Metal
* ARM Cortex-A8
* Sistemas embarcados em tempo real
