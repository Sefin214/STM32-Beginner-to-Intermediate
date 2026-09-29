# STM32 Beginner to Intermediate
Hands-on STM32 projects covering fundamental to intermediate embedded-systems concepts using **C, STM32 HAL, STM32CubeMX, and STM32CubeIDE**.
This repository contains my practice assignments and implementations covering **GPIO, polling, interrupts, timers, PWM, UART, ADC, SPI, I2C, EEPROM, sensors, and peripheral integration.

## 🧠 About This Repository
This repository is a collection of STM32 peripheral assignments implemented as part of my learning journey from beginner to intermediate-level embedded development. The projects focus on understanding how STM32 peripherals work in practical applications rather than only studying them theoretically.

## 📂 Contents

Each assignment folder contains the question sheet and its corresponding STM32 implementation:

- `Guide.pdf` — Assignment/question sheet for the particular exercise.
- `.ioc` — STM32CubeMX configuration file containing MCU and peripheral configuration.
- `main.c` — Application code implementing the assignment.

The repository is organized so that the **assignment/question PDF and its corresponding implementation are kept together**.

---

## 📚 Assignments Covered

### 🔌 GPIO, Interrupts & Timers

The initial assignments cover the fundamentals of GPIO, polling, interrupts, timers, and PWM:

1. Blink an LED using HAL Write and Toggle APIs.
2. Read key presses using polling and toggle LEDs accordingly.
3. Repeat key-press handling using interrupts.
4. Blink LEDs using the system timer interrupt.
5. Blink LEDs sequentially using timer auto-reload interrupts.
6. Develop a pulse-width measurement timer logic for LED toggling.
7. Control LED intensity using PWM.

These exercises provide the foundation for understanding:

- GPIO configuration
- Polling-based programming
- Interrupt-driven programming
- Timer operation
- PWM generation
- LED control

---

### 📡 UART, Interrupt Priority & Timer Counter

The next set of assignments focuses on serial communication and combining multiple peripherals:

1. Continuously transfer a string through UART2 using polling and interrupt-based methods.
2. Implement UART2 loop operation using polling and interrupts, including carriage-return handling.
3. Print `Key Pressed` on the serial console when a user button is pressed, using USART and button interrupts with interrupt priority configuration.
4. Use a timer as a counter to count key presses and continuously display the count on the serial console.

These exercises help build an understanding of:

- UART communication
- UART polling
- UART interrupts
- External interrupts
- Interrupt priority
- Timer counter operation
- Serial debugging

---

### 🔧 UART, ADC, DAC, PWM, SPI & I2C

The later assignments extend the work into additional STM32 peripherals:

1. Print floating-point values through UART.
2. Demonstrate `printf` functionality through UART.
3. Read an analog value using ADC and a potentiometer.
4. Demonstrate DAC functionality by varying LED intensity.
5. Interface a buzzer and control it using I/O and PWM.
6. Interface an EEPROM using SPI.
7. Continuously transmit SHT21 temperature and relative-humidity measurements through UART.
8. Develop a UART menu-driven application for starting, displaying, and stopping temperature and humidity conversions.

These exercises introduce:

- ADC
- DAC
- PWM
- SPI
- I2C
- EEPROM interfacing
- Sensor interfacing
- UART-based application control

---

## 🌡️ UART Menu Application

The SHT21 menu-driven assignment uses the serial terminal to control temperature and humidity operations.

```text
Press 1 : Start temperature conversion
Press 2 : Display temperature value
Press 3 : Start Humidity conversion
Press 4 : Display humidity value
Press 5 : Stop Conversion


If you find this repository useful for learning STM32, feel free to explore the projects, modify the configurations, and experiment with the code.
Happy Embedded Coding :)

A typical project folder contains:

```text
Assignment/
├── *.ioc
└── main.c
