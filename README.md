# 💻 Técnicas de Programação para Sistemas Embarcados I (TPSE I)

Este repositório reúne as práticas desenvolvidas na disciplina de **Técnicas de Programação para Sistemas Embarcados I (TPSE I)**, ofertada pela **Universidade Federal do Ceará (UFC) – Campus Quixadá**, durante o semestre **2025.1**.

O objetivo da disciplina é o desenvolvimento de aplicações **bare-metal** para a **BeagleBone Black (AM335x)**, explorando a arquitetura **ARM Cortex-A8**, programação em linguagem C, manipulação direta de registradores de hardware, periféricos embarcados e gerenciamento de interrupções.

---

## 🚀 Conteúdo do Repositório

### 📁 Prática 01 – Configuração do Ambiente

* Instalação da ARM GNU Toolchain;
* Configuração da interface de rede;
* Configuração do servidor TFTP;
* Acesso serial utilizando o **Minicom**;
* Boot da BeagleBone Black via **U-Boot**.

### 📁 Prática 02 – GPIO como Saída

* Configuração de GPIOs como saída;
* Controle de LEDs utilizando acesso direto aos registradores.

### 📁 Prática 03 – GPIO como Entrada

* Configuração de GPIOs como entrada;
* Leitura de botões e chaves;
* Utilização de resistores **Pull-Down**.

### 📁 Prática 04 – Interrupções Externas

* Configuração de interrupções em GPIO;
* Tratamento assíncrono de eventos;
* Implementação de rotinas de serviço de interrupção (ISR).

### 📁 Prática 05 – Comunicação Serial (UART)

* Configuração da UART;
* Comunicação entre a BeagleBone Black e o computador;
* Interface via terminal serial.

### 📁 Prática 06 – GPIO + Timers

* Configuração de Timers;
* Integração entre GPIO e interrupções temporizadas;
* Controle de LEDs e botões utilizando interrupções.

### 📁 Prática 07 – Real Time Clock (RTC)

* Configuração do RTC do AM335x;
* Geração de interrupções periódicas;
* Aplicações baseadas em temporização.

---

## 🛠️ Tecnologias Utilizadas

* Linguagem **C**
* Assembly ARM
* Desenvolvimento **Bare-Metal**
* BeagleBone Black (AM335x)
* ARM Cortex-A8
* ARM GNU Toolchain
* U-Boot
* Minicom
* TFTP

---

## 📥 Como Clonar o Projeto

Clone o repositório utilizando:

```bash
git clone https://github.com/F4BINH00/TPSE1-UFC.git
```

Em seguida, acesse a pasta desejada correspondente à prática que deseja executar.

Cada diretório contém:

* Código-fonte;
* Arquivos de suporte;
* Documentação específica da prática.

---

## 📚 Objetivos de Aprendizagem

Ao longo das práticas são explorados conceitos como:

* Desenvolvimento Bare-Metal;
* Manipulação de registradores de hardware;
* Controle de GPIO;
* Comunicação UART;
* Timers;
* RTC;
* Tratamento de interrupções;
* Arquitetura ARM Cortex-A8;
* Programação de Sistemas Embarcados.

---

## 👨‍💻 Autor

**Fábio Rodrigues Borges Filho**

Graduando em Engenharia de Computação
Universidade Federal do Ceará (UFC) – Campus Quixadá

GitHub: https://github.com/F4BINH00

---

> Repositório desenvolvido para fins acadêmicos na disciplina de **Técnicas de Programação para Sistemas Embarcados I (TPSE I)**.
