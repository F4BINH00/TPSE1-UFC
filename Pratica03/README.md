# 🔘 Prática 03 – GPIO como Entrada (Input)

## Objetivo

Implementar a leitura de estados lógicos de dispositivos de entrada (Push Buttons) utilizando os GPIOs da BeagleBone Black configurados como entrada, permitindo a detecção de eventos externos.

---

## Hardware Utilizado

* BeagleBone Black (AM335x)
* Push Buttons
* Resistores Pull-Down
* Protoboard

---

## Funcionalidades

* Configuração dos GPIOs como entrada.
* Leitura do registrador `GPIO_DATAIN`.
* Detecção do estado lógico dos botões.
* Utilização de resistores Pull-Down para evitar estados flutuantes (Floating Inputs).

---

## Estrutura dos Arquivos

```text
Pratica03/
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
| `src/`            | Contém o código-fonte da aplicação e o código de inicialização do processador.                                                          |
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
3. Execute o programa.
4. Pressione os botões conectados aos GPIOs e observe a leitura dos estados lógicos.

---

## Conceitos Abordados

* GPIO como Entrada (Input)
* Manipulação de registradores
* Leitura de estados lógicos
* Resistores Pull-Up e Pull-Down
* Programação Bare-Metal
* ARM Cortex-A8
* Interface entre hardware e software
