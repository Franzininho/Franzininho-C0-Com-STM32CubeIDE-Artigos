
## Introdução

Este código contém funções para analisar e processar dados do GPS, especificamente a sentença GPGGA, e transmitir esses dados formatados via UART.

## Funções Principais

### analisarGPGGA

A função `analisarGPGGA` recebe uma sentença GPGGA do GPS e preenche uma estrutura de dados com informações relevantes, como latitude, longitude e altitude.

```c
void analisarGPGGA(char* sentenca, DadosGPS* dados)
```

### processarDadosGPS

A função `processarDadosGPS` verifica se a sentença recebida é do tipo GPGGA e, se for, chama a função `analisarGPGGA` para processar os dados e os formata para transmissão via UART.

```c
void processarDadosGPS(char* dadosGPS)
```

### HAL_UART_RxCpltCallback

O callback `HAL_UART_RxCpltCallback` é acionado quando um caractere é recebido pela UART. Ele coleta os caracteres recebidos até encontrar um caractere de nova linha (`\n`), indicando o final da sentença, então chama a função `processarDadosGPS`.

```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
```

## Utilização

Para utilizar este código, é necessário configurar e inicializar as interrupções UART adequadas para a recepção de dados do GPS.

## Licença

Este código está disponível sob a [licença MIT].
```
