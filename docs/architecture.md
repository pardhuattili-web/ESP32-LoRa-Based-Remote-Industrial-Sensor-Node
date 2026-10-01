# Architecture

The node runs a duty-cycled state machine:

```
WAKE -> SAMPLE -> PACKETIZE/CRC -> TRANSMIT -> ACK?
                                      |          |
                                      +--retry--+
                                         |
                                       SLEEP
```

Hardware boundaries:
- `sensor_if`: I2C sensors + ADC integration
- `packet`: fixed-width protocol + CRC-16
- `lora_if`: SX1276/SX1278 SPI/radio integration
- `power_manager`: RTC/deep-sleep policy
- `diagnostics`: UART observability

The repository keeps sensor/radio functions as reference shims so protocol behavior can be developed without claiming real RF or sensor validation.