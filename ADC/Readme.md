# Utilizando ADC: modo polling, interrupção e DAC

sistemas embarcados são dispositivos que interagem com o mundo real, e no mundo real a informação é “ analógica ” e não “ digital ”.

O sistema “mágico” capaz de tornar um valor analógico “compreensível” para um microcontrolador é denominado: ADC . Um conversor analógico-digital (ADC) é um dispositivo que converte um sinal analógico, como uma temperatura captada por um sensor, em um sinal digital.


## Hardware Necessário

- 1 Franzininho C0
- 1 potenciometro 10k


## Polling
```
// inicia leitura
HAL_ADC_Start (&hadc1);

// aguarda conversao seja concluida
HAL_ADC_PollForConversion (&hadc1, 1000 );

// ler valor analogico
uint32_t val = HAL_ADC_GetValue (&hadc1);

```
## Interrupçao
```
// inicia leitura adc no modo interrupção
HAL_ADC_Start_IT (&hadc1);

// no final da conversao chamada da interrupcao
void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef *hadc);

```
## DMA

```
// inicia a leitura no modo DMA
HAL_ADC_Start_DMA (&hadc1, buffer, BUFFER_SIZE);

// chama funcao de retorno de chamada de interrupção no final da conversao ADC
void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef *hadc);


```