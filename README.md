# ESP32 LoRa Remote Industrial Sensor Node

A battery-aware ESP32 sensor node that samples industrial/environmental data, packages it into a compact CRC-protected binary frame, transmits it over LoRa, waits for an acknowledgement, and enters deep sleep until the next measurement window.

> **Hardware status:** This repository is a portable ESP-IDF reference implementation. The default sensor path is deterministic simulation so the complete software protocol can be developed and tested before attaching physical sensors and an SX1276/SX1278 module.

## Why this project matters

This project focuses on a common embedded constraint: a remote node has limited energy and an unreliable long-range link. The firmware therefore treats **sampling, packet integrity, retries, fault reporting, and sleep scheduling** as first-class design concerns.

## Features

- ESP32 + ESP-IDF / FreeRTOS
- SX1276/SX1278 LoRa abstraction over SPI
- Temperature/humidity sensor abstraction over I²C
- Battery-voltage monitoring abstraction over ADC
- Compact binary telemetry frame
- CRC-16 integrity check
- Sequence number and node ID
- ACK/retry state machine
- Packet-loss and retry counters
- Battery/sensor fault flags
- Configurable sample period
- Deep-sleep scheduling
- Wake-cause reporting
- UART gateway/diagnostic output
- Sensor simulation mode
- PC-side Python packet decoder

## System architecture

```
+-------------------+
| Temp/Humidity     |
| Sensor (I2C)      |
+---------+---------+
          |
+---------v---------+      +------------------+
| Sensor Abstraction|      | Battery ADC      |
+---------+---------+      +--------+---------+
          |                          |
          +------------+-------------+
                       v
              +----------------+
              | Measurement    |
              | Builder        |
              +-------+--------+
                      |
                      v
              +----------------+
              | Packet Encoder |
              | + CRC-16       |
              +-------+--------+
                      |
                      v
              +----------------+
              | LoRa Driver    |
              | SPI / SX127x    |
              +-------+--------+
                      |
                 ACK / RETRY
                      |
                      v
              +----------------+
              | Deep Sleep     |
              +----------------+
```

## Telemetry frame

| Field | Size | Description |
|---|---:|---|
| Version | 1 B | Protocol version |
| Node ID | 2 B | Unique logical node |
| Sequence | 4 B | Monotonic packet counter |
| Temperature | 2 B | °C × 100 |
| Humidity | 2 B | %RH × 100 |
| Battery | 2 B | mV |
| Status flags | 2 B | Fault/state bitmap |
| CRC-16 | 2 B | CCITT-style payload integrity |

The packet format is deliberately fixed-width so it can be decoded on small gateways without JSON overhead.

## Node state machine

```text
BOOT
  |
SAMPLE
  |
PACKETIZE
  |
TRANSMIT ----timeout----> RETRY
  |                         |
  +-------- ACK <-----------+
              |
           SLEEP
              |
            WAKE
```

A maximum retry count prevents a failed link from keeping the node awake indefinitely.

## Build

Install ESP-IDF 5.x, then:

```bash
idf.py set-target esp32
idf.py build
idf.py flash monitor
```

The default build uses simulated measurements. Integrate the real sensor and SX127x driver implementations through the interfaces under `main/include/`.

## Example telemetry

```text
NODE=0x1201 SEQ=42 TEMP=31.25C HUM=58.40% BAT=3710mV FLAGS=0x0000
TX=OK ACK=YES RETRIES=0
NEXT_WAKE=60s
```

## Project structure

```text
main/
├── app_main.c
├── include/
│   ├── packet.h
│   ├── sensor_if.h
│   ├── lora_if.h
│   ├── node_config.h
│   ├── power_manager.h
│   └── diagnostics.h
└── src/
    ├── packet.c
    ├── sensor_if.c
    ├── lora_if.c
    ├── node_config.c
    ├── power_manager.c
    └── diagnostics.c
gateway/
└── decode_packet.py
docs/
├── architecture.md
├── packet_protocol.md
└── test_plan.md
test/
└── packet_test.c
```

## Hardware integration

Recommended development hardware:

- ESP32 development board
- SX1276/SX1278 LoRa module
- BME280/SHT31-class temperature/humidity sensor
- Battery voltage divider / appropriately scaled ADC source
- USB-UART development connection

For battery-powered deployments, validate the divider current, regulator quiescent current, sleep current, radio duty cycle, and antenna configuration before claiming battery-life results.

## Validation status

Software protocol/unit tests can be run without radio hardware. **LoRa range, packet-loss rate, sleep current, sensor accuracy, and battery life are not claimed until measured on the selected hardware.**

## License

MIT
