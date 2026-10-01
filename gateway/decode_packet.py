#!/usr/bin/env python3
import struct, sys
FMT=">BH I h H H H H"; SIZE=struct.calcsize(FMT)
def crc16(data):
 crc=0xFFFF
 for b in data:
  crc^=b<<8
  for _ in range(8): crc=((crc<<1)^0x1021)&0xFFFF if crc&0x8000 else (crc<<1)&0xFFFF
 return crc
def decode(frame):
 if len(frame)!=SIZE: raise ValueError(f"expected {SIZE} bytes")
 body=frame[:-2]; rx=int.from_bytes(frame[-2:],"big")
 if crc16(body)!=rx: raise ValueError("CRC mismatch")
 v,node,seq,temp,hum,batt,flags,crc=struct.unpack(FMT,frame)
 return {"version":v,"node_id":f"0x{node:04X}","sequence":seq,"temperature_c":temp/100,"humidity_rh":hum/100,"battery_mv":batt,"flags":f"0x{flags:04X}"}
if __name__=="__main__":
 raw=bytes.fromhex(sys.argv[1]); print(decode(raw))