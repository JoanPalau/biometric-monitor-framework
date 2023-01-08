import paho.mqtt.client as mqtt
from collections import Counter



def most_common(lst):
    data = Counter(lst)
    return data.most_common(1)[0][0]

class MQTTVisualizer:

    def __init__(self):
        self.client = mqtt.Client()
        # The callback for when the client receives a CONNACK response from the server.

        self.accelerometer_predictions = []
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.intensity = {
            'rest': 0,
            'walking': 1,
            'run': 1,
            'erratic': 2,
            'falling': 2,
        }

    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))

        # Subscribing in on_connect() means that if we lose the connection and
        # reconnect then subscriptions will be renewed.
        client.subscribe("sensor/#")

    # The callback for when a PUBLISH message is received from the server.
    def on_message(self, client, userdata, msg):
        if msg.topic == "sensor/accelerometer":
            try:
                payload = msg.payload.decode()
            except Exception:
                return
            value = 30
            # print(msg.topic, payload)
            payload = payload.split('\t')
            if len(payload) < 4: return
            x, y, z, pred = payload
            self.accelerometer_predictions.append(pred)
            if len(self.accelerometer_predictions) > value:
                self.accelerometer_predictions = self.accelerometer_predictions[:-value]
            pred = most_common(self.accelerometer_predictions)
            intensity = self.intensity[pred]
            for topic, val in [
                ('x', x),
                ('y', y),
                ('z', z),
                ('prediction', intensity),
            ]:
                print(val, topic)
                self.client.publish(f'visualizer/accelerometer/{topic}', val)
            
            import random
            r = random.randint(20, 40)
            print('Heart', r)
            self.client.publish(f'sensor/heart', r)
    
    def main(self):
        self.client.connect("localhost", 1883, 60)

        # Blocking call that processes network traffic, dispatches callbacks and
        # handles reconnecting.
        # Other loop*() functions are available that give a threaded interface and a
        # manual interface.
        self.client.loop_forever()

if __name__ == '__main__':
    visualizer = MQTTVisualizer()
    visualizer.main()