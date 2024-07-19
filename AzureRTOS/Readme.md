# Projeto ThreadX com STM32

## Descrição

Este projeto utiliza o RTOS (Real-Time Operating System) ThreadX em um microcontrolador STM32. Ele cria duas tarefas (`btn_status` e `led_status`) e uma fila (`queue_ptr`) para comunicação entre as tarefas. 

## Estrutura do Projeto

### Arquivos Principais

- `main.c`: Contém o código principal para inicialização periféricos
- `app_threadx.c`: Contém a implementação das tarefas e da fila.
- `app_threadx.h`: Cabeçalhos e declarações de funções e variáveis globais.

## Funcionalidade

#### `btn_status`

Esta tarefa lê o estado de um botão conectado ao pino GPIOA, GPIO_PIN_8 e envia uma mensagem para a fila `queue_ptr` sempre que o estado do botão muda.

**Protótipo:**
```c
VOID btn_status(ULONG initial_input);
```
#### `led_status`

Esta tarefa recebe mensagens da fila `queue_ptr` e aciona um LED conectado ao `LED_GPIO_Port` e `LED_Pin` com base nas mensagens recebidas. Também transmite mensagens pela UART para indicar o estado do LED.

**Protótipo:**
```c
VOID led_status(ULONG initial_input);
```

### Fila - `queue_ptr`

A fila é usada para passar mensagens entre as tarefas `btn_status` e `led_status`. A fila é criada com o seguinte código:

```c
tx_queue_create(&queue_ptr, "message_btn_status", TX_1_ULONG, queue_stack, QUEUE_STACK_SIZE);
```

**Parâmetros:**
- `queue_ptr`: Ponteiro para a fila.
- `"message_btn_status"`: Nome da fila.
- `TX_1_ULONG`: Tipo de mensagem (um ULONG).
- `queue_stack`: Array utilizado como armazenamento da fila.
- `QUEUE_STACK_SIZE`: Tamanho do array `queue_stack`.

### Tarefa -  tx_thread_create

A função tx_thread_create cria e inicializa uma nova thread (tarefa). É criada com o seguinte código:


```c
tx_thread_create(&btn_status_ptr, "btn_status", btn_status, 0, btn_status_stack, BTN_STATUS_STACK_SIZE, 15, 15, 1, TX_AUTO_START);
```
**Parâmetros:**
- `&btn_status_ptr`: Ponteiro para a estrutura da thread.
- `"btn_status"`: Nome da thread.
- `btn_status`: Ponteiro para a função da thread.
- `0`: Valor passado como argumento para a função da thread (não utilizado nesta implementação).
- `btn_status_stack`: Ponteiro para o stack da thread.
- `BTN_STATUS_STACK_SIZE`: Tamanho do stack da thread.
- `15`: Prioridade da thread (quanto menor o valor, maior a prioridade).
- `15`: Sub-prioridade da thread (em sistemas com preempção de múltiplos níveis, geralmente igual à prioridade principal).
- `1`: Time-slice para a thread (quantidade de ticks que a thread pode rodar antes de outra thread com a mesma prioridade ser executada).
- `TX_AUTO_START`: Opção de auto-start para a thread (a thread começa a rodar automaticamente após ser criada).

### Código Principal

A função `App_ThreadX_Init` inicializa a fila e as tarefas:

```c
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;

  tx_queue_create(&queue_ptr, "message_btn_status", TX_1_ULONG, queue_stack, QUEUE_STACK_SIZE);

  tx_thread_create(&btn_status_ptr, "btn_status", btn_status, 0, btn_status_stack, BTN_STATUS_STACK_SIZE, 15, 15, 1, TX_AUTO_START);
  tx_thread_create(&led_status_ptr, "led_status", led_status, 0, led_status_stack, LED_STATUS_STACK_SIZE, 15, 15, 1, TX_AUTO_START);

  return ret;
}
```
