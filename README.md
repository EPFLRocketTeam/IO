# IO
Here the github repository of the IO rocket of the EPFL Rocket TEAM

Please only save independant code of sensors in Sensors/ folder
The full source code will be stored in Embedded/ Software/

For each main code to work it must be in a folder with the same name that contains the corresponding sensor code. Eg. mainTX.ino must be located in a folder called mainTX which also contains BNO055.cpp, BNO055.h, BMP280.cpp, BMP280.h, LoRa_TX.cpp, LoRa_TX.h and Data.h.

By default LoRaTX will await a code sent via LoRaRX to begin recording and transmitting data.
