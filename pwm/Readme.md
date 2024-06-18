### PROJETO PWM NO FRANZINHO C0

---

#### Descrição

Este projeto demonstra o controle de modulação por largura de pulso (PWM) de dois LEDs utilizando um microcontrolador STM32 e a biblioteca HAL. Os LEDs, conectados aos canais PWM do Timer 1, são ajustados para variar sua intensidade luminosa em direções opostas, criando um efeito visual.

---

#### Configuração

1. **Requisitos de Hardware**:
   - Microcontrolador STM32 (testado com série STM32F4).
   - LEDs conectados a pinos GPIO capazes de PWM (PB6 para LED1, PB7 para LED2).

2. **Requisitos de Software**:
   - STM32CubeMX para inicialização do projeto.
   - STM32CubeIDE ou IDE compatível para compilação e carregamento do código.

---

#### Instalação

1. Clone ou baixe o repositório para sua máquina local.
   

2. Abra o projeto no STM32CubeIDE.

3. Compile e carregue o projeto no microcontrolador STM32.

---

#### Uso

1. Ao executar o programa, os LEDs começarão a variar sua intensidade luminosa de forma alternada.

2. O LED1 aumentará gradualmente sua intensidade enquanto o LED2 diminui, e vice-versa.

3. Este efeito se repete continuamente, controlado pela função `atualiza_largura_puslo_LEDS`.

---

#### Licença

Este software está licenciado sob os termos que podem ser encontrados no arquivo LICENSE no diretório raiz deste componente de software. Se nenhum arquivo LICENSE acompanhar este software, ele é fornecido COMO ESTÁ.

