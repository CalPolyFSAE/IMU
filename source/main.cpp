/* System */
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE18F16.h"
#include "fsl_debug_console.h"

/* BSP */
#include "System.h"
#include "gpio.h"
#include "spi.h"

/* Project */

#define SPIBUS 0
#define SPICSPORT gpio::PortB // CS pin is PTB0
#define SPICSPIN 0
#define SPIBAUD 500000UL

#define PINRESET gpio::PortA,0
#define PINBOOTN gpio::PortA,0
#define PINPS0 gpio::PortA,0
#define PINPS1 gpio::PortA,0
#define PINCLKSEL0 gpio::PortA,0
#define PINCLKSEL1 gpio::PortA,0
#define PINH_INTN gpio::PortA,0

using namespace BSP;

void spicallback(){

}


int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    //SysTick_Config(SYSTICK);
    
    // setup
    gpio::GPIO::ConstructStatic();
    gpio::GPIO& gpio = gpio::GPIO::StaticClass();

    gpio.clear(PINRESET);
    gpio.set(PINBOOTN);
    gpio.set(PINPS0);
    gpio.set(PINPS1);
    gpio.set(PINCLKSEL0);
    gpio.clear(PINCLKSEL1);
    gpio.in_dir(PINH_INTN);
    
    spi::spi_config spiconf;
    spiconf.callbacks[SPIBUS] = spicallback;
    spi::SPI::ConstructStatic(&spiconf);
    spi::SPI& spi = spi::SPI::StaticClass();

    spi::SPI::masterConfig mconf;
    mconf.baudRate = SPIBAUD;
    mconf.cpol = kLPSPI_ClockPolarityActiveLow;
    mconf.cphase = kLPSPI_ClockPhaseSecondEdge;
    mconf.csport = SPICSPORT;
    mconf.cspin = SPICSPIN;
    spi.initMaster(SPIBUS, &mconf);

    gpio.set(PINRESET);

    while(gpio.read(PINH_INTN);

    while(1){
    }
}

extern "C" {
void SysTick_Handler(void){

}
}
