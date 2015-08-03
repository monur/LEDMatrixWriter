 # Convert any char to 8X8 LED char and send it via Serial port to Arduino
import serial
import LEDNumbers
import LEDSymbols

def writeSerial(symbolArray):
	ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
        ser.open()
        ser.write(''.join(map(str, symbolArray)))
	ser.flush()
        ser.close()

def writeNumber(num):
	writeSerial(LEDNumbers.numbers[num-1])

#writeNumber(14)

def writeSymbol(symbolName):
	writeSerial(LEDSymbols.symbols[symbolName])
