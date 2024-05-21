# Integrando display 7 segmentos no Franzininho C0.

Neste projeto estamos controlando um display 7 segmento por meio de 2 botoes, sendo um para incremento e outro para decremento. 


## Material Necessário

- 1 Franzininho C0
- 1 display 7 segmento
- 1 resistor 300 ohms
- 2 botoes


## Funções criadas para o display

```
void numero(uint32_t a, uint32_t b,uint32_t c,uint32_t d,uint32_t e, uint32_t f, uint32_t g){
	HAL_GPIO_WritePin(GPIOA, A_Pin, a);
	HAL_GPIO_WritePin(GPIOA, B_Pin, b);
	HAL_GPIO_WritePin(GPIOA, C_Pin, c);
	HAL_GPIO_WritePin(GPIOA, D_Pin, d);
	HAL_GPIO_WritePin(GPIOA, E_Pin, e);
	HAL_GPIO_WritePin(GPIOA, F_Pin, f);
	HAL_GPIO_WritePin(GPIOA, G_Pin, g);
}

void atualizaDisplay(int valor)
{
    // Configurações dos segmentos para cada dígito de 0 a 9
    switch(valor)
    {
        case 0: numero(1, 1, 1, 1, 1, 1, 0); break;
        case 1: numero(0, 1, 1, 0, 0, 0, 0); break;
        case 2: numero(1, 1, 0, 1, 1, 0, 1); break;
        case 3: numero(1, 1, 1, 1, 0, 0, 1); break;
        case 4: numero(0, 1, 1, 0, 0, 1, 1); break;
        case 5: numero(1, 0, 1, 1, 0, 1, 1); break;
        case 6: numero(1, 0, 1, 1, 1, 1, 1); break;
        case 7: numero(1, 1, 1, 0, 0, 0, 0); break;
        case 8: numero(1, 1, 1, 1, 1, 1, 1); break;
        case 9: numero(1, 1, 1, 1, 0, 1, 1); break;
    }
}


```