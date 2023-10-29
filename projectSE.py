import serial
import requests

# Configure serial connection
ser =serial.Serial('COM1', 9600)

# Read RFID tag code from serial port
while True:
    data = ser.readline().decode('utf-8').rstrip()
    datastr= data.replace(" ", "")

    if data:
        print('RFID tag code:', datastr)

        # # Define the URL of the Node.js server
        url = f'http://192.168.249.194:3000/api/etudiantByRFID/{datastr}/Monday/9'
        #
        response = requests.get(url)
        #
        # # Print the response from the server
        # clear the input buffer
        print(response.text)
        
        ser.flush()

        if response.text == "1":
            ser.write("Success !".encode())
        else:
            ser.write("Fail !".encode())



