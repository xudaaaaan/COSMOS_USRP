"""
: Description: This class creates an object to control the PAAM Array in COSMOS PAWR Testbed

: Author: Yuning Zhang
: Created time: 2023/05
: Organization: University of Southern California
: Modification Log


:copyright: 2023
"""

import requests
import xmltodict
import json
import cv2


class PAAM(object):
    """
    PAAM Array class
    """

    def __init__(self, array_name):
        """

        :param array_name:
        :type array_name:
        """
        # self.isdebug = isdebug
        self.array = array_name  # string format
        self.main_url = 'http://am1.orbit-lab.org:5054/array_mgmt/'
        """
        self.xy_status = None
        self.rotator_status = None
        self.current_position = None
        self.target_position = None
        """
        self.state = None
        self.adc_conv = None
        self.step = None


    @property
    def array(self):
        """

        :return:
        :rtype:
        """
        return self.__array


    @array.setter
    def array(self, array_name):
        """

        :param array_name:
        :type array_name:
        :return:
        :rtype:
        """
        if array_name == 'rfdev4-in2' or array_name == 'rfdev-mob4-1':
            self.__array = array_name
        else:
            raise NotImplemented


    @property
    def status(self):
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'status', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))
            
            self.state = json_data['response']['action']['state']
            self.adc_conv = json_data['response']['action']['adc']['conv']

            # Print information
            # --- states ---
            print("Array RF state: ")
            print("    PAAM_ID = {}".format(self.state['@PAAM_ID']))
            print("    LO_switch = {}".format(self.state['@LO_switch']))
            print("    if_sw1 = {}".format(self.state['@if_sw1']))
            print("    if_sw2 = {}".format(self.state['@if_sw2']))
            print("    if_sw3 = {}".format(self.state['@if_sw3']))
            print("    if_sw4 = {}".format(self.state['@if_sw4']))
            # --- ADCs ---
            print("ADC status: ")
            for step_idx in self.adc_conv[:-2]:
                print("    index = {}, name = {}, tADC = {}, tVolt = {}, tCurr = {}".format(step_idx['@index'], 
                                                                                            step_idx['@name'],
                                                                                            step_idx['@tADC'],
                                                                                            step_idx['@tVolt'],
                                                                                            step_idx['@tCurr']))
            for step_idx in self.adc_conv[-2:]:
                print("    index = {}, name = {}, tADC = {}, tVolt = {}".format(step_idx['@index'], 
                                                                                step_idx['@name'],
                                                                                step_idx['@tADC'],
                                                                                step_idx['@tVolt']))

            return self.state, self.adc_conv

            

    def connect(self):
        """
        "connect" will execute 3 steps: open, initialization, and enabling
        """
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'connect', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))   

            self.step = json_data['response']['action']['step']

            # Print information
            # --- steps ---
            print("The step(s) been executed:")
            for step_idx in self.step:
                print("    {}".format(step_idx['@name']))

            return self.step
        


    def enable(self, ics, num_elements, txrx, pol):
        """
        Somehow "enable" doesn't get any return info. 
        """
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org',
                  'ics': ics,
                  'num_elements': int(num_elements),
                  'txrx': txrx,
                  'pol': pol}
        try:
            r = requests.get(url=self.main_url + 'enable', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))   

            self.step = json_data['response']['action']['step']

            # Print information
            # --- steps ---
            print("The step(s) been executed:")
            for step_idx in self.step:
                print("    {}".format(step_idx['@name']))

            return self.step
        


    def steer(self, theta, phi):
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org',
                  'theta': theta,
                  'phi': phi}
        try:
            r = requests.get(url=self.main_url + 'steer', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))   

            self.step = json_data['response']['action']['step']

            # Print information
            # --- steps ---
            print("The step(s) been executed:")
            for step_idx in self.step:
                print("    {}".format(step_idx['@name']))

            return self.step
        

    
    def config(self, ics, num_elements, txrx, pol, theta, phi):
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org',
                  'ics': ics,
                  'num_elements': int(num_elements),
                  'txrx': txrx,
                  'pol': pol, 
                  'theta': theta,
                  'phi': phi}
        try:
            r = requests.get(url=self.main_url + 'configure', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))         
            array_action = json_data['response']['action']

            self.step = array_action['step']
            self.state = array_action['state']
            self.adc_conv = array_action['adc']['conv']

            # Print information
            # --- steps ---
            print("The step(s) been executed:")
            for step_idx in self.step:
                print("    {}".format(step_idx['@name']))
            # --- states ---
            print("Array RF state: ")
            print("    PAAM_ID = {}".format(self.state['@PAAM_ID']))
            print("    LO_switch = {}".format(self.state['@LO_switch']))
            print("    if_sw1 = {}".format(self.state['@if_sw1']))
            print("    if_sw2 = {}".format(self.state['@if_sw2']))
            print("    if_sw3 = {}".format(self.state['@if_sw3']))
            print("    if_sw4 = {}".format(self.state['@if_sw4']))
            # --- ADCs ---
            print("ADC status: ")
            for step_idx in self.adc_conv[:-2]:
                print("    index = {}, name = {}, tADC = {}, tVolt = {}, tCurr = {}".format(step_idx['@index'], 
                                                                                            step_idx['@name'],
                                                                                            step_idx['@tADC'],
                                                                                            step_idx['@tVolt'],
                                                                                            step_idx['@tCurr']))
            for step_idx in self.adc_conv[-2:]:
                print("    index = {}, name = {}, tADC = {}, tVolt = {}".format(step_idx['@index'], 
                                                                                step_idx['@name'],
                                                                                step_idx['@tADC'],
                                                                                step_idx['@tVolt']))


            return self.step, self.state, self.adc_conv



    def disconnect(self):
        """
        "disconnect" will execute 1 step: close
        """
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'disconnect', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success to get return info: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))       
            if 'step' in json_data['response']['action']:
                self.step = json_data['response']['action']['step']
                # Print information
                # --- steps ---
                print("The step been executed:")
                print("    {}".format(self.step['@name']))

                return self.step
            elif 'error' in json_data['response']['action']:
                print("The board is already disconnected!")


            
        


    def cleanup(self):
        """
        "disconnect" will execute 1 step: close
            
        ***Question***: the same as disconnect?
        """
        params = {'dev_name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'cleanup', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))      

            self.step = json_data['response']['action']['step']

            # Print information
            # --- steps ---
            print("The step(s) been executed:")
            for step_idx in self.step:
                print("    {}".format(step_idx['@name']))

            return self.step
        


    



    
