#include <stdint.h>

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830UL)
#define GPIOD_MODER (*(volatile uint32_t *)0x40020C00UL)
#define GPIOD_BSRR  (*(volatile uint32_t *)0x40020C18UL)

int main(void)
{
    // Enable clock for GPIOD
    RCC_AHB1ENR |= (1u << 3);

    // Configure PD12 as general-purpose output
    GPIOD_MODER = (GPIOD_MODER & ~(3u << 24)) | (1u << 24);

    // Set PD12 high
    GPIOD_BSRR = (1u << 12);

    while (1) {
        __asm__ volatile ("nop");
    }
}