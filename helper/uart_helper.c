#include "uart_helper.h"
#include "boards.h"

void uart_event_handle(app_uart_evt_t* p_event) {
	
	//static uint8_t data_array[UART_MAX_DATA_LEN];
	//static uint8_t index = 0;
	//uint32_t err_code;
	
	switch (p_event->evt_type)
	{
		case APP_UART_DATA_READY:
			break;
		
		case APP_UART_COMMUNICATION_ERROR:
			APP_ERROR_HANDLER(p_event->data.error_communication);
			break;
	
		case APP_UART_FIFO_ERROR:
			APP_ERROR_HANDLER(p_event->data.error_code);
			break;
		
		default:
			break;
	}
}

void uart_init(void) {
	uint32_t err_code;
	const app_uart_comm_params_t comm_params = 
	{
		RX_PIN_NUMBER,
		TX_PIN_NUMBER,
		RTS_PIN_NUMBER,
		CTS_PIN_NUMBER,
		APP_UART_FLOW_CONTROL_DISABLED,
		false,
		UART_BAUDRATE_BAUDRATE_Baud57600
	};
	
	APP_UART_FIFO_INIT(&comm_params,
											UART_RX_BUF_SIZE,
											UART_TX_BUF_SIZE,
											uart_event_handle,
											APP_IRQ_PRIORITY_LOWEST,
											err_code);
									
	APP_ERROR_CHECK(err_code);
}
