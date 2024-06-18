
# Sistema de Controle de bargraph via Potenciômetro

Este código implementa um sistema onde a quantidade de LEDs acesos  no bargraph é controlada pelo valor lido de um potenciômetro.

## Funcionalidade

- Quando o sistema é inicializado, ele configura o microcontrolador e inicializa o ADC para ler o valor do potenciômetro.
- A leitura do potenciômetro é feita periodicamente usando interrupções do ADC.
- Com base na leitura do potenciômetro, o código calcula quantos LEDs devem estar acesos de um total de 10 LEDs.
- Os LEDs são controlados através de pinos GPIO do microcontrolador.
- A função `desligaLeds()` é responsável por desligar todos os LEDs.
- A função `HAL_ADC_ConvCpltCallback()` é chamada sempre que a conversão ADC é concluída, atualizando o estado dos LEDs com base no valor lido do potenciômetro.

## Configuração do Hardware

- O sistema utiliza pinos específicos dos GPIOs (GPIOA e GPIOB) para controlar os LEDs.
- Um único ADC (ADC1) é usado para realizar a leitura do potenciômetro.

## Observações

- A calibração do ADC (`HAL_ADCEx_Calibration_Start(&hadc1)`) é realizada durante a inicialização para garantir leituras precisas.
- O sistema opera em um loop infinito onde a leitura do potenciômetro é contínua.
