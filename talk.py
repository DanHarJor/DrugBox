#talk.py
import os
import serial
import binascii as bi
import time
#only works if only one usb plugged in. Ports of all devices are included in the string. 
port = os.popen('python3 -m serial.tools.list_ports').read()
print(port[0:12])
ser = serial.Serial("/dev/ttyUSB0",baudrate = 57600, timeout = 2)
#ser = serial.Serial(port[0:12],baudrate = 57600, timeout = 30)

def speak(data, q):
	qu = bytes(q, 'UTF-8')
	ser.write(qu)

	da = bytes(data, 'UTF-8')
	ser.write(da)

	ser.write(bytes('$', 'UTF-8'))

def listen ():
        ts = time.time()
        tf = time.time()

        r = 0
        i = 0
        ch = ""
        fin = bytes('$', 'UTF-8')
        while (ser.in_waiting == 0 and tf-ts <= 10):
            a=1
            tf = time.time()
#adds 5 second wait before giving up on listen.	
        if tf-ts >= 10:
            r = fin
            ch = 0#return int 0 if nothing was heard within 5sec
        while r != fin:
            r = ser.read()
            if r != fin:
                r = r.decode('UTF-8')
                ch = ch + r
        return ch

def recieved():
        if (listen() == "rec"):
            return 1
        else: 
            return 0
def serMT():
    while (ser.in_waiting != 0):
        ser.read()
