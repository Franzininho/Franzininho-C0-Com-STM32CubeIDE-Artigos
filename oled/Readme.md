# Utilizando display Oled com a Franzininho C0

Este código é um exemplo simples de como inicializar e usar um display SSD1306 com um microcontrolador utilizando a interface I2C. O código inclui bibliotecas necessárias, define variáveis privadas e contém um exemplo de bitmap para exibição no display.

## Descrição dos Arquivos

### Incluídos
- `main.h`
- `ssd1306.h`

### Variáveis Privadas
Declara uma variável para o handle do I2C:
```c
I2C_HandleTypeDef hi2c1;
```

### Bitmaps para Exibição
Dois bitmaps são definidos para exibição no display:
1. `garfield_128x64` - Bitmap do Garfield
2. `franzininho_128x64` - Bitmap do Franzininho


## Como Usar
1. Inclua os headers necessários:
    ```c
    #include "main.h"
    #include "ssd1306.h"
    ```
2. Inicialize o handle do I2C (`hi2c1`).
3. Use a biblioteca `ssd1306` para inicializar o display e enviar os bitmaps.

## Exemplo de Código

### Inicialização do I2C e Display
```c
HAL_I2C_Init(&hi2c1);

// Inicialização do Display SSD1306
ssd1306_Init();
```

### Exibição de Bitmap
Para exibir um dos bitmaps, use a função apropriada da biblioteca `ssd1306`:
```c
// Exibir Garfield
ssd1306_DrawBitmap(0, 0, garfield_128x64, 128, 64, White);
ssd1306_UpdateScreen();

// Exibir Franzininho
ssd1306_DrawBitmap(0, 0, franzininho_128x64, 128, 64, White);
ssd1306_UpdateScreen();
```

### Funções Principais
- `HAL_I2C_Init()` - Inicializa o periférico I2C.
- `ssd1306_Init()` - Inicializa o display SSD1306.
- `ssd1306_DrawBitmap(x, y, bitmap, w, h, color)` - Desenha um bitmap no display.
- `ssd1306_UpdateScreen()` - Atualiza o conteúdo do display.

## Notas
- Certifique-se de que o endereço I2C do display SSD1306 está correto no código.
- Este exemplo assume a biblioteca `ssd1306` que deve estar disponível e configurada corretamente para o seu hardware.

## Conclusão
Este é um guia básico para iniciar o uso de um display SSD1306 com um microcontrolador através da interface I2C. A partir deste exemplo, você pode expandir para adicionar funcionalidades adicionais conforme necessário.