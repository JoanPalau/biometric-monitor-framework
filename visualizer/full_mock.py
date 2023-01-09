import random
import paho.mqtt.client as mqtt
import time

client = mqtt.Client()
client.connect("localhost", 1883, 60)

intensity = {
    'rest': 0,
    'walking': 1,
    'run': 1,
    'erratic': 2,
    'falling': 2,
}


while True:
    r = random.randint(20, 40)
    print('Heart', r)
    client.publish(f'sensor/heart', r)
    act = random.choice(list(intensity.keys()))
    r = f'0.0\t0.0\t0.0\t{act}'
    print('Accelerometer', r)
    client.publish(f'sensor/accelerometer', r)
    time.sleep(2)