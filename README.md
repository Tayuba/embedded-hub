# Embedded-Hub STM32 Bare-Metal Project

This project demonstrates low-level driver development for the STM32F407VHT6 without HAL.

### Structure
- `stm32_drivers/` → CubeIDE project
- `drivers/` → custom bare-metal drivers
- `tests/` → host-based unit tests
- `docs/` → documentation
- `.github/workflows/` → CI/CD automation

### Build
```bash
make -C stm32_drivers/Debug
