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
Pratica02/
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
4. Observe o acionamento dos LEDs conectados aos GPIOs configurados como saída.

---

## Conceitos Abordados

* GPIO como Saída (Output)
* Manipulação direta de registradores
* Clock Manager (CM_PER)
* Pin Multiplexing (PinMux)
* Operações atômicas em hardware
* Programação Bare-Metal
* ARM Cortex-A8
* Controle de periféricos
