# Author: Ruben Jungius
# Project: IO - GUI Groundstation
# Organization: EPFL Rocket Team, Lausanne

import serial
import sys

try:
    config = open('config.txt', 'r')
except Exception as e:
    print(e)
    sys.exit()

for line in config:
    if line.strip().startswith('#') or line.strip().startswith('\n'):
        continue
    if line.strip().startswith('Serial Port:'):
        port = line.replace('Serial Port:', '').replace('\n', '').strip()
        try:
            s = serial.Serial('COM5')
            print('[Serial] Connection on Port ' + port)
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

data = s.readline()
outfile.write(data.decode('utf-8').replace('\n', ''))
outfile.close()
