import requests
import json
import time

DEVICE_ID = "1202725242"# OneNET device_id->rpi5  API Key
API_KEY = "YJ=3hqMFW4oW1=ibQWOgR0NSEGY="
API_URL = f"http://api.heclouds.com/devices/{DEVICE_ID}/datapoints"# OneNET  API_URL  

def send_data_to_onenet(name, data):
    headers = {
        "api-key": API_KEY,
        "Content-Type": "application/json"
    }
    payload = {
        "datastreams": [
            {
                "id": name,
                "datapoints": [
                    {"value": data}    
                ]
            }
        ]
    }
    timeout_seconds = 0.5  #if time>500ms break
    try:
        response = requests.post(API_URL, headers=headers, data=json.dumps(payload), timeout=timeout_seconds)
    except requests.exceptions.Timeout: #if time>500ms break
        print(f"Failed to send {name} to OneNET within 500ms")        
'''
        if response.status_code == 200:
            print(f"{name} sent successfully to OneNET")
        else:
            print(f"Failed to send {name} to OneNET")
          

    except requests.exceptions.ConnectionError:#no link net 
        print("Failed to connect to the network")
    except Exception as e:# another error   
        print(f"Error: {e}")
'''
feeding=0
def fetch_data_from_onenet():
    headers = {
        "api-key": API_KEY,
    }
    response = requests.get(API_URL, headers=headers)
    if response.status_code == 200:
        data = response.json()
        for datastream in data["data"]["datastreams"]:
            datastream_id = datastream["id"]
            #           print all data            #
            '''
            datapoints = datastream["datapoints"]
            for datapoint in datapoints:
                value = datapoint["value"]
                timestamp = datapoint["at"]
                print(f"Datastream: {datastream_id}, Value: {value}, Timestamp: {timestamp}")
            '''
            global feeding  
            if datastream_id == "feeding":  
                datapoints = datastream["datapoints"]
                for datapoint in datapoints:
                    feeding = datapoint["value"]  
                   # print(f"Datastream: {datastream_id}, Value: {feeding}, Timestamp: {datapoint['at']}")
    else:
        print("Failed to fetch data from OneNET")
        
'''
def main():
    while True:
        data = 123          
        send_data_to_onenet("rain",123)		   
        fetch_data_from_onenet()
        if feeding>50:
                send_data_to_onenet("ph",5.6)			
        time.sleep(2)

if __name__ == "__main__":
    main()
'''
