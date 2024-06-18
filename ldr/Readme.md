### Controle de Intensidade de LED com LDR

Este é um código simples para controle de intensidade de um LED utilizando um microcontrolador STM32 configurado com o STM32Cube.

#### Descrição
O código utiliza um sensor LDR (Light Dependent Resistor) para ler a intensidade de luz ambiente. Com base nessa leitura, ajusta a intensidade de um LED utilizando PWM (Pulse Width Modulation).

#### Hardware Necessário
- Microcontrolador STM32 com suporte ao STM32Cube
- Sensor LDR
- LED e resistor para controle de corrente
- Capacitor e resistores conforme necessário para filtragem e proteção

#### Configurações Iniciais
1. **HAL_Init():** Inicialização do Hardware Abstraction Layer.
2. **SystemClock_Config():** Configuração do clock do sistema.
3. **MX_GPIO_Init():** Inicialização dos pinos GPIO para LED e LDR.
4. **MX_ADC1_Init():** Inicialização do ADC para leitura do sensor LDR.
5. **MX_TIM1_Init():** Inicialização do timer TIM1 para geração de PWM.

#### Funcionamento do Loop Principal
- **Inicia PWM:** Inicia a saída PWM no canal específico (TIM_CHANNEL_3).
- **Loop Infinito:** O código entra em um loop infinito onde:
  - Inicia a conversão ADC para ler a tensão no sensor LDR.
  - Calcula a leitura do ADC.
  - Inverte a lógica do PWM: quanto maior a leitura do ADC (mais luz), menor o ciclo ativo do PWM (menor intensidade de luz no LED).
  - Atualiza a intensidade do LED ajustando o valor do comparador do timer (TIM1).

#### Lógica de Controle PWM
- A intensidade do LED é ajustada pela fórmula: `pwm = 1000 - ((leitura * 1000) / 4095)`.
- `leitura` é o valor lido do ADC, variando de 0 a 4095.
- `pwm` é o valor que determina o ciclo ativo do PWM, variando de 0 (sem luz) a 1000 (máxima luz).



