# Test Plan

## Unit tests

- Encode/decode round-trip preserves all telemetry fields.
- Flipping one payload bit produces a CRC failure.
- Incorrect packet length is rejected.
- Retry count is bounded by the configured maximum.

## Integration tests

- Boot reports periodic-timer wake cause.
- Simulated sensor values produce deterministic telemetry.
- LoRa send/ACK follows the retry state machine.
- Deep sleep is armed with the configured interval.
- Gateway decoder rejects corrupted packets.

## Hardware validation still required

- SX1276/SX1278 SPI/radio configuration
- RF range and packet-loss measurements
- Antenna and local-band compliance
- Sensor calibration/accuracy
- Active and deep-sleep current measurements
- Battery-life characterization

No real-world RF range, current-draw, or battery-life figures are claimed until measured on the selected hardware.