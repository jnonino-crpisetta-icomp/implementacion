/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xgpio.h"


/************************** Constant Definitions *****************************/

/*
 * The following constant is used to wait after an LED is turned on to make
 * sure that it is visible to the human eye.  This constant might need to be
 * tuned for faster or slower processor speeds.
 */
/*
 * The following constant is used to determine which channel of the GPIO is
 * used for the LED if there are 2 channels supported.
 */
#define LED_CHANNEL 1
#define SWTICH_CHANNEL 1

/************************** Variable Definitions *****************************/

/*
 * The following are declared globally so they are zeroed and so they are
 * easily accessible from a debugger
 *
 */

//Es necesario una instancia del driver por cada dispositivo

	XGpio leds; /* The Instance of the LEDs GPIO Driver */
	XGpio switchs;/* The Instance of the SWITCHs GPIO Driver */

/*****************************************************************************/
/**
* The purpose of this function is to illustrate how to use the GPIO level 1
* driver to turn on and off an LED.
*
* @return	XST_FAILURE to indicate that the GPIO Intialisation had failed.
* buen ejemplo en la sig pagina
*
*http://www.eng.iastate.edu/vie/courses/cpre488x_f05/Lab_Files/Lab_2/system.c
******************************************************************************/

int main(void)
{
	u32 Data;

	int Status;

	/*
	 * Initialize the LEDs GPIO driver
	 */
	Status = XGpio_Initialize(&leds, XPAR_LEDS_8BITS_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*
	 * Initialize the SWITCHs GPIO driver
	 */

	Status = XGpio_Initialize(&switchs, XPAR_DIP_SWITCHES_8BITS_DEVICE_ID);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
	/*
	 * Set the direction for all signals to be inputs except the
	 * LED output
	 * SWITCH input
	 */
	XGpio_SetDataDirection(&leds, LED_CHANNEL, 0x00);
	XGpio_SetDataDirection(&switchs, SWTICH_CHANNEL, 0xff);

	int d1;
	int d2;
	u32 salida;

	while(1){


		Data=XGpio_DiscreteRead(&switchs,SWTICH_CHANNEL);

		d1=0x0f & Data;//para quedarnos con los bits 0 al 3
		d2=(0xf0 & Data)/16; //para quedarnos con los bits 4 al 7
		salida=d1+d2;

		XGpio_DiscreteWrite(&leds, LED_CHANNEL,salida);

		//	for (Delay = 0; Delay < LED_DELAY; Delay++);

	}

	return XST_SUCCESS;
}

