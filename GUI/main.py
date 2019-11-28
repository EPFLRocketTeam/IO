# Author: Ruben Jungius
# Project: IO - GUI Groundstation
# Organization: EPFL Rocket Team

import serial

s = serial.Serial('COM5')
while True:
    data = s.read()
    print(data)
