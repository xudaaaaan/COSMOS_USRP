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
        self.xy_status = None
        self.rotator_status = None
        self.current_position = None
        self.target_position = None

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
            array_data = json_data['response']['action']['state']


            """
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))
            table_data = json_data['response']['action']['xy_table']
            self.xy_status = table_data['@xy_status']
            self.rotator_status = table_data['@rotator_status']
            current_pos = table_data['current_position']
            target_pos = table_data['target_position']
            self.current_position = [current_pos['@x'], current_pos['@y'], current_pos['@angle']]
            self.target_position = [target_pos['@x'], target_pos['@y'], target_pos['@angle']]

            print("The current position: {}".format(self.current_position))
            print("The target position: {}".format(self.target_position))

            return self.xy_status, self.rotator_status, self.current_position, self.target_position
            """
            

'''
    def move(self, x, y, angle):
        """

        :param x:
        :type x:
        :param y:
        :type y:
        :param angle:
        :type angle:
        :return:
        :rtype:
        """

        params = {'name': self.array + '.sb1.cosmos-lab.org',
                  'x': int(x),
                  'y': int(y),
                  'angle': angle}
        try:
            r = requests.get(url=self.main_url + 'move_to', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print new position of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))
            table_data = json_data['response']['action']['xy_table']
            self.xy_status = table_data['@xy_status']
            self.rotator_status = table_data['@rotator_status']
            current_pos = table_data['current_position']
            target_pos = table_data['target_position']
            self.current_position = [current_pos['@x'], current_pos['@y'], current_pos['@angle']]
            self.target_position = [target_pos['@x'], target_pos['@y'], target_pos['@angle']]

            print("The current position: {}".format(self.current_position))
            print("The target position: {}".format(self.target_position))

            return self.xy_status, self.rotator_status, self.current_position, self.target_position


    def check(self):
        """

        :param x:
        :type x:
        :param y:
        :type y:
        :param angle:
        :type angle:
        :return:
        :rtype:
        """

        params = {'name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'status', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print new position of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))
            table_data = json_data['response']['action']['xy_table']
            self.xy_status = table_data['@xy_status']
            self.rotator_status = table_data['@rotator_status']
            current_pos = table_data['current_position']
            target_pos = table_data['target_position']
            self.current_position = [current_pos['@x'], current_pos['@y'], current_pos['@angle']]
            self.target_position = [target_pos['@x'], target_pos['@y'], target_pos['@angle']]

            print("The current position: {}".format(self.current_position))
            print("The target position: {}".format(self.target_position))
            print("The array status is: {}".format(self.xy_status))   # Idle, or moving, or other status, it's not the RF status of the array but its movement status
            print("The rotor status is: {}".format(self.rotator_status))

            return self.xy_status, self.rotator_status, self.current_position


    def stop(self):
        """

        :return:
        :rtype:
        """

        params = {'name': self.array + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'stop', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print the current stop position of the xytable
            json_data = json.loads(json.dumps(xmltodict.parse(r.content)))
            table_data = json_data['response']['action']['xy_table']
            self.xy_status = table_data['@xy_status']
            self.rotator_status = table_data['@rotator_status']
            current_pos = table_data['current_position']
            self.current_position = [current_pos['@x'], current_pos['@y'], current_pos['@angle']]

            print("The current position: {}".format(self.current_position))

            return self.xy_status, self.rotator_status, self.current_position
'''