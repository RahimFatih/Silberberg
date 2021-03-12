import imaplib
#import serial
import time
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
for p in ports:
    print(p)
    if "CH340" in p.description:
        print("This is an Arduino!")

ser = serial.Serial("COM18",9600)
time.sleep(5)
ser.write(b'T')
ser.write(b'K')
ser.close()