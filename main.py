import serial
import datetime
import urllib3

ser = serial.Serial('COM9', 9600)
ser.flushInput()

baseurl = 'https://api.thingspeak.com/update?api_key='
API_key = 'W02E40J2V6KGPXKJ'
ID = 2407619

while True:

    try:
        ser_bytes = ser.readline()
        error_bytes = ser_bytes[0:4].decode("utf-8")
        now = datetime.datetime.now()
        now = now.strftime("%Y-%M-%D %H:%M:%S")
        data = ("'{}', {}\r\n".format(now, error_bytes))
        print(data)
        tsURL = ("{}&field1={}".format(
        baseurl, API_key, error_bytes))
        http = urllib3.PoolManager()
        tspeak = http.request('GET', tsURL)
        tspeak.status

    except:
        print("Keyboard Interrupt")
        break