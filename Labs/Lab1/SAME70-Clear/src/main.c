/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO	PIOC
#define LED_PIO_ID	12     
#define LED_PIO_IDX	8      
#define LED_PIO_IDX_MASK	(1<<LED_PIO_IDX)

#define BUT_PIO	PIOA
#define BUT_PIO_ID	ID_PIOA
#define BUT_PIO_IDX	11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	pmc_enable_periph_clk(LED_PIO_ID);
	//Inicializa PC8 como saída
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	pio_set_input(BUT_PIO,BUT_PIO_IDX_MASK,PIO_DEFAULT);
	
	pio_pull_up(BUT_PIO,BUT_PIO_IDX_MASK,1);
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
		if(!pio_get(BUT_PIO,PIO_INPUT,BUT_PIO_IDX_MASK)){
			for(int i = 0; i<5; i++){
				pio_set(PIOC, LED_PIO_IDX_MASK);      // Coloca 1 no pino LED
				delay_ms(200);                        // Delay por software de 200 ms
				pio_clear(PIOC, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED
				delay_ms(200);
			}
		}
		
  }
  return 0;
}
