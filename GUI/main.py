# Author: Ruben Jungius
# Project: IO - GUI Groundstation
# Organization: EPFL Rocket Team, Lausanne

import serial
import sys
from openpyxl import Workbook

def purge(string):
    value = ''
    output = []
    for char in string.decode("utf-8"):
        if char.isspace():
            if value:
                try:
                    output.append(int(value))
                    value = ''
                except Exception:
                    print("Error in DataFormat\n")
                    value = ''
        else:
            value += char
    return output

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
            # sys.exit()
    if line.strip().startswith('Baudrate:'):
        try:
            baud = int(line.replace('Baudrate:', '').replace('\n', '').strip())
            s.baudrate = baud
        except Exception as e:
            print(e)
            # sys.exit()
    if line.strip().startswith('Excel Path:'):
        path = line.replace('Excel Path:', '').replace('\n', '').strip()
        if path != '' and not path.endswith('\\'):
            path = path + '\\'
        try:
            # outfile = open(path + 'data.txt', 'w+')
            wb = Workbook()
            ws = wb.active
            # ws.title = 'LaunchData'
            print('[Excel] Sucess creating Excel file '
                  + 'in current directory' if path == '' else
                  '[Excel] Success creating Excel file at ' + path)
        except Exception as e:
            print(e)
            sys.exit()
    if line.strip().startswith('NB_DATA:'):
        try:
            NB_DATA = int(line.replace('NB_DATA:', '').replace('\n', '').strip())
        except Exception as e:
            print(e)
            sys.exit()

# data = [0]*NB_DATA
while s.inWaiting:
    try:
        data = purge(s.readline())
        print('Added: {}\n'.format(data))
        ws.append(data)
        wb.save(path + 'launchData.xlsx')  # Saving works vorzüenah
    except Exception as e:
        print(e)

# identifier = s.readline()  # in case of lost data, resets
# print("identifier {}, new {}".format(identifier, purge(identifier, 1)))
# if purge(identifier) == -1:
