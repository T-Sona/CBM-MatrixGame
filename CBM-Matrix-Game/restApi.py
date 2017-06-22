from flask import Flask
import requests
import serial
import thread

# ser = serial.Serial('/dev/ttyACM0', 9600) --> raspberry port
ser = serial.Serial('/dev/tty.usbmodem1411', 9600)  # macbook port
app = Flask(__name__)
ip = "192.168.1.20:5000"


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


@app.route("/gameover")
def gameover():
    return "gameover"


def flaskThread():
    app.run(host='0.0.0.0')


if __name__ == '__main__':
    thread.start_new_thread(flaskThread, ())
    while 1:
        movement = ser.read()
        if movement == '1':
            sendUp()
        elif movement == '2':
            sendDown()
        elif movement == '3':
            sendLeft()
        elif movement == '4':
            sendRight()
