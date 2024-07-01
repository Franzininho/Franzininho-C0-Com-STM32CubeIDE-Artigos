
# Monitoramento de Temperatura e Umidade com DHT11 e Franzininho C0 e Exibição em Display OLED

## Visão Geral

Este projeto demonstra como ler dados de temperatura e umidade de um sensor DHT11 usando um microcontrolador STM32. Os dados do sensor são exibidos em um display OLED utilizando o driver SSD1306.

## Requisitos

- Microcontrolador STM32 (configurado com STM32CubeIDE)
- Sensor de Temperatura e Umidade DHT11
- Display OLED SSD1306
- Bibliotecas HAL para STM32
- STM32CubeMX para inicialização de periféricos (opcional)

## Configuração

1. **Conexões de Hardware:**
   - Conecte o sensor DHT11 ao pino GPIO configurado no código (`dht_Pin`).
   - Conecte o display OLED SSD1306 via I2C.
   - Garanta que o Timer 3 esteja configurado corretamente para medições de tempo.

2. **Configuração de Software:**
   - Importe o projeto para o STM32CubeIDE.
   - Verifique se as bibliotecas HAL e o driver SSD1306 estão incluídos.
   - Compile e programe o firmware para sua placa STM32.

## Uso

1. Carregue o firmware compilado para sua placa STM32.
2. Após a inicialização, o STM32 lerá continuamente os dados do sensor DHT11.
3. As leituras de temperatura e umidade serão exibidas no display OLED.
4. O display é atualizado a cada 5 segundos com novos dados do sensor.

## Notas

- **Temporizações:** Garanta que as temporizações no loop de captura de dados do DHT11 (`função dht11`) estejam precisas conforme o datasheet do DHT11.
- **Display:** Ajuste a formatação e posição da tela OLED conforme necessário na função `Display_Data`.


## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo LICENSE para mais detalhes.
