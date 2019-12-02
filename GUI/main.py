# Author: Ruben Jungius
# Project: IO - GUI Groundstation
# Organization: EPFL Rocket Team, Lausanne

import serial
import sys

try:  # Open config
    config = open('config.txt', 'r')
except Exception as e:
    print(e)
    sys.exit()

for line in config:  # Initialize program from config
    if line.strip().startswith('#') or line.strip().startswith('\n'):
        continue
    if line.strip().startswith('Serial Port:'):
        port = line.replace('Serial Port:', '').replace('\n', '').strip()
        try:
            s = serial.Serial(port)
            print('[Serial] Connection on Port ' + port)
        except Exception as e:
            print(e)
            sys.exit()
    if line.strip().startswith('Baudrate:'):
        try:
            baud = int(line.replace('Baudrate:', '').replace('\n', '').strip())
            s.baudrate = baud
        except Exception as e:
            print(e)
            sys.exit()
    if line.strip().startswith('Excel Path:'):
        path = line.replace('Excel Path:', '').replace('\n', '').strip()
        if path != '' and not path.endswith('\\'):
            path = path + '\\'
        try:
            outfile = open(path + 'data.txt', 'w+')
            print('[Excel] Sucess creating Excel file '
                  + 'in current directory' if path == '' else
                  '[Excel] Sucess creating Excel file at ' + path)
        except Exception as e:
            print(e)
            sys.exit()

while s.inWaiting:
    data = s.readline()
    print(data)
    try:
        value = int(data)
        print(value)
        outfile.write(str(value) + '\n')
        if value == 300:
            break
    except Exception as e:
        print(e)
outfile.close()
s.close()
