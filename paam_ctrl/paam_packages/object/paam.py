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


class PAAMarray(object):
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
            self.adc_conv = json_data['response']['action']['adc_conv']['conv']

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

            return self.step
        


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
            # Success: print status of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))       

            self.step = json_data['response']['action']['step']

            return self.step
        


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
            self.adc_conv = array_action['adc_conv']['conv']



            return self.step
