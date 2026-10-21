# STM32F4 Renode Lab

Learning project to understand Cortex-M4 execution, memory-mapped peripherals,
UART, debugging, and later FreeRTOS, without buying hardware for the initial stage.

## Status

**Milestone 0 — bring-up:** prepared; execution must be verified on the local
Windows Renode installation. The first binary is Renode's **official Contiki
demo**, **not** firmware written in this repository. A future milestone will
replace it with our own C application and FreeRTOS.

## Prerequisites

- Windows 10/11
- [Renode](https://github.com/renode/renode/releases) installed
- VS Code (optional for this initial demo)
- Internet for the first demo firmware download

## First run (GUI)

1. Launch **Renode** from the Windows Start menu.
2. In the **Renode Monitor**, execute the local script. Use `/` in the path and
   replace the example path with the full path to this repository:

   ```text
   i @C:/Users/YOUR_USER/Documents/stm32-renode-lab/scripts/stm32f4-lab.resc
   ```

   The script includes Renode's stock STM32F4 Discovery platform and stock
   Contiki demo; it opens the UART4 analyzer, starts a GDB server on port 3333,
   and starts the emulation.

3. Observe output in the **UART4 analyzer**. The first launch may need to
   download the demo ELF from the official Antmicro server.
4. Use the Renode Monitor for the experiments in [`docs/lab01.md`](docs/lab01.md).

If the path above doesn't work, try the official built-in demo directly:

```text
s @scripts/single-node/stm32f4_discovery.resc
```

This fallback does not run the custom script or open the GDB server.

## What is actually verified?

- [ ] Renode loads the STM32F4 platform
- [ ] The demo ELF loads and the Cortex-M4 runs
- [ ] UART4 produces output
- [ ] We can pause execution and examine the program counter
- [ ] We can inspect and modify an STM32F4 GPIO register

Tick the boxes **only after observing the result**. Do not claim the firmware
is our original creation.

## Repository layout

```text
scripts/      Renode monitor scripts (.resc)
docs/         Learning exercises and test evidence
firmware/     Our future C/FreeRTOS code
hardware/     Future KiCad schematic/PCB
 tests/       Future automated integration and regression tests
```

## Next milestones

- M1: Write our own bare-metal C firmware, cross-compile and debug in Renode.
- M2: Configure FreeRTOS tasks, queues and priorities.
- M3: Automated tests (Renode + Robot Framework, native C tests).
- M4: Design an expansion board in KiCad; validate real peripherals on a board.

## Sources

- [Official Renode demo guide](https://renode.readthedocs.io/en/latest/introduction/demo.html)
- [Official STM32F4 Discovery script](https://github.com/renode/renode/blob/master/scripts/single-node/stm32f4_discovery.resc)
- [Renode test guide](https://renode.readthedocs.io/en/latest/introduction/testing.html)
