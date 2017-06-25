from flask import Flask
from flask import request
import requests
import serial
import thread

#ser = serial.Serial('/dev/ttyACM0', 9600) # raspberry port
ser = serial.Serial('/dev/tty.usbmodem1411', 9600)  # macbook port
app = Flask(__name__)
# ip = "192.168.1.20:5000"
#ip = "141.19.142.164:5000"
ip = "141.19.142.232:5000"


def sendUp():
    http = "http://" + ip + "/up"

    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
            return "success"
    except requests.exceptions.ConnectionError as e:
        print e


def sendDown():
    http = "http://" + ip + "/down"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendLeft():
    http = "http://" + ip + "/left"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendRight():
    http = "http://" + ip + "/right"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendStart():
    http = "http://" + ip + "/start"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendRotate():
    http = "http://" + ip + "/rotate"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendLifeLost():
    http = "http://" + ip + "/lifelost"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendWaiting():
    http = "http://" + ip + "/waiting"
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


def sendLab(data):
    http = "http://" + ip + "/lab?nr="+data
    print "data"+data
    try:
        resp = requests.get(http)
        if resp.status_code != 200:
            print "failed"
        else:
            print resp.text
    except requests.exceptions.ConnectionError as e:
        print e


@app.route("/up")
def up():
    ser.write("u")
    return "up"


@app.route("/down")
def down():
    ser.write("d")
    return "down"


@app.route("/left")
def left():
    ser.write("l")
    return "left"


@app.route("/right")
def right():
    ser.write("r")
    return "right"


@app.route("/start")
def start():
    ser.write("s")
    return "start"


@app.route("/rotate")
def rotate():
    ser.write("o")
    return "rotate"


@app.route("/player")
def player():
    ser.write("p")
    return "player"


@app.route("/watcher")
def watcher():
    ser.write("w")
    return "watcher"

@app.route("/lifelost")
def lifelost():
    ser.write("i")
    return "lifelost"

@app.route("/waiting")
def waiting():
    ser.write("a")
    return "waiting"


@app.route("/lab")
def lab():
    query_string = request.query_string
    ser.write(query_string[3:])
    return "lab"


def flaskThread():
    app.run(host='0.0.0.0')


if __name__ == '__main__':
    thread.start_new_thread(flaskThread, ())
    while 1:
        data = ser.read()
        print data
        if data == 'u':
            sendUp()
        elif data == 'd':
            sendDown()
        elif data == 'l':
            sendLeft()
        elif data == 'r':
            sendRight()
        elif data == 'w':
            sendWaiting();
        elif data == 's':
            sendStart()
        elif data == 'i':
            sendLifeLost()
        elif data == '0' or data == '1' or data == '2' or data == '3' or data == '4' or data == '5' or data == '6' or data == '7' or data == '8' or data == '9':
            sendLab(data)
