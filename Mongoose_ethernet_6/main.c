//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the EK-TM4C129EXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/emac.h"

#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/flash.h"

#include "driverlib/pin_map.h"

#include "mongoose.h"

#include "hal.h"
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************

uint32_t g_ui32SysClock;

void gpio_init()
{
    volatile uint32_t ui32Loop;
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 |  GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4 );



    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 |GPIO_PIN_1, 0xff);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,0xFF );

    // Delay for a bit.
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
    {
    }

    // Turn off the LED.
    //
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 |GPIO_PIN_1, 0x00);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,0x00 );

    //
    // Delay for a bit.
    //
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
    {
    }

}
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    // Loop while there are more characters to send.
    while(ui32Count--)
    {
        // Write the next character to the UART.
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

void uart_init(void)
{
    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
            SYSCTL_OSC_MAIN |
            SYSCTL_USE_PLL |
            SYSCTL_CFG_VCO_480), 120000000);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //  while(1)

    UARTSend((uint8_t *)"\033[2JEnter text: ", 16);


}

static volatile uint64_t s_ticks;  // Milliseconds since boot
void SysTick_Handler(void) {       // SyStick IRQ handler, triggered every 1ms
    s_ticks++;
}
uint64_t mg_millis(void) {  // Let Mongoose use our uptime function
    return s_ticks;           // Return number of milliseconds since boot
}

void
PinoutSet(bool bEthernet, bool bUSB)
{
    //
    // Enable all the GPIO peripherals.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

    //
    // PA0-1 are used for UART0.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // PB0-1/PD6/PL6-7 are used for USB.
    // PQ4 can be used as a power fault detect on this board but it is not
    // the hardware peripheral power fault input pin.
    //
    if(bUSB)
    {
        //        HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        //        HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xff;
        GPIOPinConfigure(GPIO_PD6_USB0EPEN);
        GPIOPinTypeUSBAnalog(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        GPIOPinTypeUSBDigital(GPIO_PORTD_BASE, GPIO_PIN_6);
        GPIOPinTypeUSBAnalog(GPIO_PORTL_BASE, GPIO_PIN_6 | GPIO_PIN_7);
        GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, GPIO_PIN_4);
    }
    else
    {
        //
        // Keep the default config for most pins used by USB.
        // Add a pull down to PD6 to turn off the TPS2052 switch
        //
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_6);
        GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA,
                         GPIO_PIN_TYPE_STD_WPD);

    }

    //
    // PF0/PF4 are used for Ethernet LEDs.
    //
    if(bEthernet)
    {
        //
        // this app wants to configure for ethernet LED function.
        //
        GPIOPinConfigure(GPIO_PF0_EN0LED0);
        GPIOPinConfigure(GPIO_PF4_EN0LED1);

        GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

    }
    else
    {

        //
        // This app does not want Ethernet LED function so configure as
        // standard outputs for LED driving.
        //
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

        //
        // Default the LEDs to OFF.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0);
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
                         GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);


    }

    //
    // PJ0 and J1 are used for user buttons
    //
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);

    //
    // PN0 and PN1 are used for USER LEDs.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1,
                     GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

    //
    // Default the LEDs to OFF.
    //
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
}

uint32_t ui32User0, ui32User1, ui32Loop, ui32SysClock;
uint8_t pui8MACAddr[6];
uint8_t ui8PHYAddr;




void ethernet_init()
{
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |    SYSCTL_USE_PLL |    SYSCTL_CFG_VCO_480), 120000000);
    //
    // Enable and reset the Ethernet modules.
    //
    PinoutSet(true, false);



    SysCtlPeripheralEnable(SYSCTL_PERIPH_EMAC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EPHY0);

    SysCtlPeripheralReset(SYSCTL_PERIPH_EMAC0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_EPHY0);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EMAC0))
    {
    }
    ui8PHYAddr = 0;
  //  EMACPHYConfigSet(EMAC0_BASE,(EMAC_PHY_TYPE_INTERNAL | EMAC_PHY_INT_MDIX_EN | EMAC_PHY_AN_100B_T_FULL_DUPLEX));

    // Initialize the MAC and set the DMA mode.
    //
    EMACReset(EMAC0_BASE);


    EMACTxEnable(EMAC0_BASE);
    EMACRxEnable(EMAC0_BASE);

    IntEnable(INT_EMAC0);
    EMACIntEnable(EMAC0_BASE, EMAC_INT_RECEIVE);


}

void get_macid()
{
    FlashUserGet(&ui32User0, &ui32User1);
    if((ui32User0 == 0xffffffff) || (ui32User1 == 0xffffffff))
    {
        //
        // We should never get here. This is an error if the MAC address has
        // not been programmed into the device. Exit the program.
        //
        while(1)
        {
        }
    }
    pui8MACAddr[0] = ((ui32User0 >> 0) & 0xff);
    pui8MACAddr[1] = ((ui32User0 >> 8) & 0xff);
    pui8MACAddr[2] = ((ui32User0 >> 16) & 0xff);
    pui8MACAddr[3] = ((ui32User1 >> 0) & 0xff);
    pui8MACAddr[4] = ((ui32User1 >> 8) & 0xff);
    pui8MACAddr[5] = ((ui32User1 >> 16) & 0xff);

}

static void timer_fn(void *arg) {
//  gpio_toggle(LED);                                      // Blink LED
  struct mg_tcpip_if *ifp = arg;                         // And show
  const char *names[] = {"down", "up", "req", "ready"};  // network stats
  MG_INFO(("Ethernet: %s, IP: %M, rx:%u, tx:%u, dr:%u, er:%u",
           names[ifp->state], mg_print_ip4, &ifp->ip, ifp->nrecv, ifp->nsent,
           ifp->ndrop, ifp->nerr));
}
#define BLINK_PERIOD_MS 1000  // LED blinking period in millis

int
main(void)
{

    gpio_init();

    uart_init();

    ethernet_init();
    //  MG_INFO(("Starting, CPU freq %g MHz", (double) SystemCoreClock / 1000000));

    struct mg_mgr mgr;        // Initialise
    mg_mgr_init(&mgr);        // Mongoose event manager
    mg_log_set(MG_LL_DEBUG);  // Set log level

    // Initialise Mongoose network stack

    get_macid();
    struct mg_tcpip_driver_tm4c_data driver_data = {.mdc_cr =
            1};  // See driver_tm4c.h
    struct mg_tcpip_if mif = {
                              .mac = pui8MACAddr,
                              // Uncomment below for static configuration:
                               .ip = mg_htonl(MG_U32(192, 168, 0, 223)),
                               .mask = mg_htonl(MG_U32(255, 255, 255, 0)),
                               .gw = mg_htonl(MG_U32(192, 168, 0, 1)),
                              .driver = &mg_tcpip_driver_tm4c,
                              .driver_data = &driver_data,
    };
    mg_tcpip_init(&mgr, &mif);
    mg_timer_add(&mgr, BLINK_PERIOD_MS, MG_TIMER_REPEAT, timer_fn, &mif);
    MG_INFO(("MAC: %M. Waiting for IP...", mg_print_mac, mif.mac));
    while (mif.state != MG_TCPIP_STATE_READY) {
      mg_mgr_poll(&mgr, 0);
    }
    MG_INFO(("Initialising application..."));

    MG_INFO(("Starting event loop"));
    for (;;) {
      mg_mgr_poll(&mgr, 0);
    }

    while(1)
    {
    }


}
