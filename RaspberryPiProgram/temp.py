import threading
import time
import paho.mqtt.client as mqtt

import json
jstr='{"ID":6,"Timestamp":"1","PlayerID":"29","TMIN30":"/","TMOUT30":"2","TMIND":"/","TMOUTD":"2","ActiveStatus":"0"}'
aList = json.loads(jstr)
print(aList['ID'])
exit(0)
serialData="1"
def setSerialData(sd):
    global serialData
    serialData=sd
def getSerialData():
    global serialData
    return serialData

class SerialThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
    def run(self, *args):
        global setSerialData, getSerialData
        
        print( self._args )
        while 1:
            print( self._args )
            time.sleep(self._args[1])
            setSerialData(str(int(getSerialData())+1))

        self._target(*self._args)

class MQTTThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.connect("broker.hivemq.com", 1883, 60)
        self.client.loop_start()
    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))
    def on_message(self, client, userdata, msg):
        print(msg.topic+" "+str(msg.payload))
    def run(self, *args):
        global getSerialData

        print( self._args )
        while 1:
            print( self._args, getSerialData() )
            self.client.publish('serialD/d/d',getSerialData())
            
            time.sleep(self._args[1])
        self._target(*self._args)
class FuncThread(threading.Thread):
    def __init__(self, target, *args):
        super().__init__(target=target, args=args)
    def run(self, *args):
        global getSerialData

        print( self._args )
        while 1:
            print( self._args, getSerialData() )
            time.sleep(self._args[1])
        self._target(*self._args)

def testThreading(say=''):
  print("I'm a thread %s" % say)

t = FuncThread(testThreading, 'hi',1)
t2 = MQTTThread(testThreading, 'bye',2)
t3 = SerialThread(testThreading, 'kry',2.5)
t.start()
t2.start()
t3.start()