# ⚡ Prática 04 – Interrupções para GPIO

## Objetivo

Substituir o método de polling pelo tratamento de eventos assíncronos utilizando interrupções externas da BeagleBone Black, tornando a aplicação mais eficiente e responsiva.

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* LEDs
* Push Buttons

---

## Funcionalidades

* Configuração do controlador de interrupções (AINTC).
* Configuração de interrupções por borda de subida (Rising Edge).
* Implementação da ISR (Interrupt Service Routine).
* Tratamento e limpeza das flags de interrupção.
* Controle de GPIO por eventos assíncronos.

---

## Estrutura dos Arquivos

```text
Pratica04/
├── bin/
│   └── spl.boot
├── inc/
│   ├── bbb_regs.h
│   ├── CLOCK_MODULE_Registers.h
│   ├── CONTROL_MODULE_Registers.h
│   ├── delay.h
│   ├── hw_types.h
│   ├── ledConfig.h
│   ├── offsets.h
│   ├── PAD_CONTROL_Registers.h
│   ├── playPong.h
│   ├── putString.h
│   ├── regs.h
│   ├── soc_AM335x.h
│   └── uart.h
├── obj/
├── src/
│   ├── main.c
│   └── start.s
└── Makefile
```

### Descrição dos Diretórios

| Diretório/Arquivo | Descrição                                                                                                                                                                                                                              |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `src/`            | Contém o código-fonte da aplicação e o código de inicialização do processador.                                                                                                                                                         |
| `inc/`            | Reúne os arquivos de cabeçalho do projeto, contendo definições de registradores, endereços de memória, drivers auxiliares, funções de comunicação UART, controle de LEDs, temporização e demais componentes utilizados pela aplicação. |
| `obj/`            | Diretório onde são gerados os arquivos objeto (`.o`) durante a compilação.                                                                                                                                                             |
| `bin/`            | Contém o arquivo final (`spl.boot`) utilizado para carregar a aplicação na BeagleBone Black.                                                                                                                                           |
| `Makefile`        | Automatiza o processo de compilação, montagem, ligação e geração do arquivo final.                                                                                                                                                     |

---

## Como Compilar

```bash
make
```

---

## Como Executar

1. Compile o projeto utilizando o `make`.
2. Carregue a aplicação na BeagleBone Black por meio do U-Boot.
3. Execute o programa.
4. Pressione os botões para gerar interrupções e observe o comportamento dos LEDs e das mensagens exibidas pela UART.

---

## Conceitos Abordados

* GPIO
* Interrupções externas
* AINTC
* Interrupt Service Routine (ISR)
* Programação Bare-Metal
* ARM Cortex-A8
* Manipulação de registradores
* Comunicação UART
* Eventos assíncronos
