import imaplib
from serial import Serial
import time
import serial.tools.list_ports

abc=" ABCDEFGHIJKLMNOPQRSTUVWXYZ"

ports = list(serial.tools.list_ports.comports())
for p in ports:
    print(p)
    if "CH340" in p.description:
        print("This is an Arduino!")

ser = serial.Serial("COM18",9600)
time.sleep(5)
i=0
while True:
    ser.write(bytes(abc[i],'utf-8'))#x.encode('utf-8'))
    i=i+1
    if i==(len(abc)-1):
        i=0
    time.sleep(0)
ser.close()