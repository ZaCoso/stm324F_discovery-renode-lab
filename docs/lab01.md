# Lab 01: A Cortex-M4 really runs inside Renode

Goal: investigate a working STM32F4 Discovery demo **without hardware**.
All commands below are run in the Renode **Monitor**, not PowerShell.

## A. Boot

Run the `scripts/stm32f4-lab.resc` script as explained in the root README.
Check for output in **UART4**. **USART2 is not the UART used by this stock demo.**

## B. Observe the CPU

```text
pause
sysbus.cpu PC
sysbus.cpu Step
sysbus.cpu PC
```

`PC` is the program counter, the address of the next instruction. `Step`
executes one instruction when execution is paused. The second PC value should
normally differ from the first (branches and exceptions can affect the change).

To resume:

```text
start
```

## C. Look at a real memory-mapped peripheral (GPIOD)

Pause the emulation first:

```text
pause
sysbus ReadDoubleWord 0x40020C14
```

`0x40020C14` is STM32F4 **GPIOD_ODR**, the output data register.
On the Discovery board, PD12 is connected to the green LED.

Try setting and clearing the PD12 bit via the **BSRR register**:

```text
sysbus WriteDoubleWord 0x40020C18 0x00001000
sysbus ReadDoubleWord 0x40020C14
sysbus WriteDoubleWord 0x40020C18 0x10000000
sysbus ReadDoubleWord 0x40020C14
```

`0x00001000` sets PD12 (bit 12); `0x10000000` clears it (bit 28, the BSRR reset
half). You are altering **modeled peripheral registers**, not driving a
physical pin. Depending on the demo/peripheral configuration, the modeled
LED may also log a state change.

This is the first encounter with **memory-mapped I/O**. The C equivalent
would involve writing through a `volatile` pointer to the appropriate address,
but our own C firmware comes in Milestone 1.

## D. Evidence

Record the observations in `docs/observations.md` and optionally add a
screenshot showing UART output. Avoid publishing screenshots with personal
account information.

## E. If something fails

- Confirm **Renode** is installed, not just the downloaded installer.
- Verify that your local script path exists; Windows paths can use `/`.
- Try the built-in script alone: `s @scripts/single-node/stm32f4_discovery.resc`.
- The demo binary is downloaded on first run, so internet access is required.
- If Renode says a machine is already running, close and reopen it before
  replaying the initialization script.
