import serial

s = serial.Serial('COM5')
while True:
    data = s.read()
    print(data)
