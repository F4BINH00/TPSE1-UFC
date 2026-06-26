# 💻 Prática 05 – Sistema com UART

## Objetivo

Desenvolver um sistema de comunicação serial utilizando a **UART0** da BeagleBone Black, permitindo a interação com o usuário por meio de um terminal serial para controlar periféricos e visualizar informações do sistema.

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* LEDs
* Push Buttons
* Computador com terminal serial (Minicom)

---

## Funcionalidades

* Configuração da UART0.
* Comunicação serial entre a BeagleBone Black e o computador.
* Implementação de um menu interativo no terminal.
* Controle de GPIOs por meio de comandos enviados via UART.
* Recepção e transmissão de caracteres.

---

## Estrutura dos Arquivos

```text
Pratica05/
├── bin/
│   └── spl.boot
├── inc/
│   ├── bbb_regs.h
│   ├── hw_types.h
│   └── soc_AM335x.h
├── obj/
├── src/
│   ├── main.c
│   └── start.s
└── Makefile
```

### Descrição dos Diretórios

| Diretório/Arquivo | Descrição                                                                                                                               |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| `src/`            | Contém o código-fonte da aplicação, incluindo a lógica principal e o código de inicialização do processador.                            |
| `inc/`            | Arquivos de cabeçalho (`.h`) com definições dos registradores, constantes, tipos de dados e endereços de memória específicos do AM335x. |
| `obj/`            | Diretório onde são gerados os arquivos objeto (`.o`) durante a compilação.                                                              |
| `bin/`            | Contém o arquivo final (`spl.boot`) utilizado para carregar a aplicação na BeagleBone Black.                                            |
| `Makefile`        | Automatiza o processo de compilação, montagem, ligação e geração do arquivo correspondente.                                             |

---

## Como Compilar

```bash
make
```

---

## Como Executar

1. Compile o projeto utilizando o `make`.
2. Carregue a aplicação na BeagleBone Black por meio do U-Boot.
3. Abra um terminal serial (como o Minicom).
4. Interaja com o menu exibido para enviar comandos e controlar os periféricos.

---

## Conceitos Abordados

* UART
* Comunicação Serial
* GPIO
* Manipulação de registradores
* Programação Bare-Metal
* ARM Cortex-A8
* Interface Homem-Máquina (HMI)
* Entrada e saída serial
