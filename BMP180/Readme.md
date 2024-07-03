
# Monitoramento de Pressão Atmosférica com BMP180 e Franzininho C0 

## Visão Geral

Este projeto demonstra como ler dados de temperatura e pressao atmosferica de um sensor BMP199 usando um microcontrolador STM32. Os dados do sensor são exibidos pela Serial.

## Requisitos

- Microcontrolador STM32 (configurado com STM32CubeIDE)
- Sensor BMP180
- Bibliotecas HAL para STM32
- STM32CubeMX para inicialização de periféricos (opcional)

## Configuração

### Configuração de Software:
   - Importe o projeto para o STM32CubeIDE.
   - Verifique se as bibliotecas HAL e o driver sensor esta incluso
   - driver sensor encontrado aqui: https://github.com/eepj/stm32-bmp180
   - Compile e programe o firmware para sua placa STM32.

### Uso

1. Carregue o firmware compilado para sua placa STM32.
2. Após a inicialização, o STM32 lerá continuamente os dados do sensor DHT11.
3. As leituras serão exibidas na serial.
4. O display é atualizado a cada 5 segundos com novos dados do sensor.

### datasheet sensor
https://cdn.awsli.com.br/945/945993/arquivos/Datasheet-BMP180-DS000-09.pdf

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo LICENSE para mais detalhes.
