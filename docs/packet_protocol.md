# Packet Protocol

The telemetry payload is a fixed-width 17-byte frame.

| Bytes | Field |
|---|---|
| 0 | Protocol version |
| 1-2 | Node ID |
| 3-6 | Sequence number |
| 7-8 | Temperature, °C × 100 |
| 9-10 | Humidity, %RH × 100 |
| 11-12 | Battery, mV |
| 13-14 | Status flags |
| 15-16 | CRC-16 |

CRC uses polynomial `0x1021`, initial value `0xFFFF`, over bytes 0-14.

Suggested status flags:
- bit 0: sensor fault
- bit 1: low battery
- bit 2: radio fault
- bit 3: retry limit reached