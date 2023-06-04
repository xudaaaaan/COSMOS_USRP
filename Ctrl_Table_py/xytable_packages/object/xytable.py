"""
:description: This class creates an object to control the XY-table in COSMOS PAWR Testbed

:organization: New York University

:authors: Panagiotis Skrimponis
          Tommy Azzino

: Modifier: Yuning Zhang
: Modified time: 2023/05
: Modifier Organization: University of Southern California
: Modification Log
:    - Set printing the current location as always true
:    - Update the package path and name
:    - Limit the availibility only to XY table 2

:copyright: 2021
"""

import requests
import xmltodict
import json
import cv2


class XYTable(object):
    """
    XYTable class
    """

    def __init__(self, table_name):
        """

        :param table_name:
        :type table_name:
        """
        # self.isdebug = isdebug
        self.table = table_name  # has to be xytable2, string format, cannot be xytabl1
        self.main_url = 'http://am1.cosmos-lab.org:5054/xy_table/'
        self.xy_status = None
        self.rotator_status = None
        self.current_position = None
        self.target_position = None

    @property
    def table(self):
        """

        :return:
        :rtype:
        """
        return self.__table

    @table.setter
    def table(self, table_name):
        """

        :param table_name:
        :type table_name:
        :return:
        :rtype:
        """
        # if table_name == 'xytable1' or table_name == 'xytable2':
        if table_name == 'xytable2':
            self.__table = table_name
        else:
            raise NotImplemented

    @property
    def status(self):
        params = {'name': self.table + '.sb1.cosmos-lab.org'}
        try:
            r = requests.get(url=self.main_url + 'status', params=params)
            r.raise_for_status()
        except requests.exceptions.HTTPError as err:
            raise SystemExit(err)
        else:
            # Success: print status of the xytable
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


    # def video(self, t=20, filename='savedImage.jpg', isSaveData='n'):
    def video(self, t=20, filename='savedImage.jpg'):
        """
        This functions opens the video stream for t seconds

        :param t: time to stream the video in seconds
        :type t: int
        :return:
        :rtype:
        """
        # if self.table == 'xytable1':
        #     cap = cv2.VideoCapture('http://camera3.orbit-lab.org/mjpg/video.mjpg')
        # el
        if self.table == 'xytable2':
            cap = cv2.VideoCapture('http://camera2.orbit-lab.org/mjpg/video.mjpg')
        else:
            raise NotImplemented
        a=0
        for _ in range(t):
            
            frame = cap.read()[1]
            a = a + 1
            # if a == t:
            #     if isSaveData == "y":
            #         cv2.imwrite(filename, frame)
            cv2.imshow(self.table, frame)
            cv2.waitKey(1)

        cap.release()


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

        params = {'name': self.table + '.sb1.cosmos-lab.org',
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
        Isn't it almost duplicate function with status?
        """

        params = {'name': self.table + '.sb1.cosmos-lab.org'}
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
            print("The array status is: {}".format(self.xy_status))   # Idle, Run, or other status, it's not the RF status of the array but its movement status
            print("The rotor status is: {}".format(self.rotator_status))

            return self.xy_status, self.rotator_status, self.current_position


    def stop(self):
        """

        :return:
        :rtype:
        """

        params = {'name': self.table + '.sb1.cosmos-lab.org'}
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
