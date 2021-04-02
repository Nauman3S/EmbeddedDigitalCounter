#sudo pip3 install paho-mqtt
#sudo apt-get install python-spidev python3-spidev
import threading
import time
import serial
from datetime import datetime
from RFIDReader import *
import json

serialData=""
activePlayer=""
activePlayerData=['','','','','','','','']
def setActivePlayerData(apd):
    global activePlayerData
    activePlayerData=apd
def getActivePlayerData():
    global activePlayerData
    return activePlayerData
def setSerialData(sd):
    global serialData
    serialData=sd
def getSerialData():
    global serialData
    return serialData

def setActivePlayer(ap):
    global activePlayer
    serialData=ap
def getActivePlayer():
    global activePlayer
    return activePlayer

class SerialThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
    def run(self, *args):
        global setSerialData
        print( self._args )
        ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
        ser.flush()
        while 1:
            #print( self._args )
            line = ser.readline()
            print(line)
            setSerialData(line)
            time.sleep(1)
        self._target(*self._args)

class MQTTThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.connect("broker.hivemq.com", 1883, 60)
        self.client.subscribe("edc-monitor/playerExistance")
        self.client.loop_start()
    def getTimestamp(self):
        now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        return(str(now))
    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))
    def on_message(self, client, userdata, msg):
        global getActivePlayer, getActivePlayerData, getSerialData
        print(msg.topic+" "+str(msg.payload))
        if(msg.topic=="edc-monitor/playerExistance"):
            activePl=getActivePlayer()
            if(str(msg.payload!="null")):
                #setActivePlayer(str(msg.payload))
                self.client.publish('edc-monitor/setActive',activePl)
                activPList=json.loads(str(msg.payload))
                tmin30=int(getActivePlayerData()[2])
                tmout30=int(getActivePlayerData()[3])
                tmind=int(getActivePlayerData()[4])
                tmoutday=int(getActivePlayerData()[5])
                sd=getSerialData()
                if(len(sd)>2):
                    sdData=sd.split(';')
                    plData=getTimestamp()+';'+getActivePlayer()+';'+str(int(sdData[0])+tmin30)+';'+str(int(sdData[1])+tmout30)+';'+str(int(sdData[0])+tmin30)+';'+str(int(sdData[1])+tmout30+';1')
                    self.client.publish('edc-monitor/createNew',plData)


            else:
                plData=getTimestamp()+';'+getActivePlayer()+';0;0;0;0;0'
                self.client.publish('edc-monitor/createNew',plData)

    def run(self, *args):
        global getSerialData, getActivePlayer

        print( self._args )
        while 1:
            #print( self._args, getSerialData() )
            activeP=getActivePlayer()
            if(activeP!=""):
                self.client.publish('edc-monitor/playerExists',activeP())
            
            time.sleep(self._args[1])
        self._target(*self._args)


class RFIDThread(threading.Thread):
    def __init__(self, target, *args):
        global initRFIDReader
        super().__init__(target=target, args=args)
        initRFIDReader()
        
    
    def run(self, *args):
        global initRFIDReader,setActivePlayer

        print( self._args )
        while 1:
            #print(self._args, getSerialData())
            cardData=readCard()
            if(cardData!='null'):
                setActivePlayer(cardData)

            time.sleep(0.5)
        self._target(*self._args)
class FuncThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
    def run(self, *args):
        print( self._args )
        while 1:
            print( self._args )
            time.sleep(self._args[1])
        self._target(*self._args)

def testThreading(say=''):
  print("I'm a thread %s" % say)

t = RFIDThread(testThreading, 'RFIDThread',1)
t2 = MQTTThread(testThreading, 'MQTTThread',2)
t3 = SerialThread(testThreading, 'SerialThread',2.5)
t.start()
t2.start()
t3.start()