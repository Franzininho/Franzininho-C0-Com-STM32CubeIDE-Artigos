
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

## Codigo leitura dht
```
void dht11(uint16_t *temperatura, uint16_t *umidade)
{
	//Variáveis para execução de cálculos da função.
	uint16_t tempcalc, umidcalc;

	//Configurações para seleção da direção do Pino 'dht11' como saída digital:
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = dht_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(dht_GPIO_Port, &GPIO_InitStruct);

	//Sinal em nivel lógico 0 - Conforme Datasheet.
	HAL_GPIO_WritePin(dht_GPIO_Port, dht_Pin, GPIO_PIN_RESET);

	//Tempo mínimo de 18ms - Conforme Datasheet.
	HAL_Delay(20); //Configura para 20ms

	//Sinal em nivel lógico 1 - Conforme Datasheet.
	HAL_GPIO_WritePin(dht_GPIO_Port, dht_Pin, GPIO_PIN_SET);

	//Configurações para seleção da direção do Pino 'dht11' como entrada digital:
	GPIO_InitStruct.Pin = dht_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(dht_GPIO_Port, &GPIO_InitStruct);

	//Lógica Principal:
	//Seta contador Timer 3 para 0.
	__HAL_TIM_SET_COUNTER(&htim3, 0);

	//Variáveis Auxiliares.
	uint16_t ler[2];
	uint16_t dados[42];
	uint8_t bits[40];
	uint16_t temph = 0;
	uint16_t umidh = 0;

	//Lógica Para Captura do Tempo Alto dos Dados.
	for(int i = 0; i < 42; i++)
	{
	    while(HAL_GPIO_ReadPin(dht_GPIO_Port, dht_Pin) == GPIO_PIN_RESET);
	    ler[0] = __HAL_TIM_GET_COUNTER(&htim3);
		while(HAL_GPIO_ReadPin(dht_GPIO_Port, dht_Pin) == GPIO_PIN_SET);
		ler[1] = __HAL_TIM_GET_COUNTER(&htim3);
		dados[i] = ler[1] - ler[0];
	}

	//Definindo bits conforme tempos do datasheet.
	for(int i = 0; i < 40; i++)
	{
	    if((dados[i+2] >=20) && (dados[i+2] <=32))
	    {
		    bits[i] = 0;
	    }
	    else if((dados[i+2] >=65) && (dados[i+2] <=75))
	    {
		    bits[i] = 1;
	    }
	}

	//Cálculo da temperatura e umidade determinado pelos bits.
	for(int i = 0; i < 8; i++)
	{
	    temph += bits[i+16] << (7 - i);
	    umidh += bits[i] << (7 - i);
	}

	//Atribuição dos valores calculados nas variáveis
	tempcalc = temph;
	umidcalc = umidh;
	*temperatura = tempcalc;
	*umidade = umidcalc;
}
```

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
