"""
: Modifier: Yuning Zhang
: Modified time: 2023/05
: Modifier Organization: University of Southern California
: Modification Log
:    - Hardcode the XYtable index as xytable 2
:    - Update the system abspath layers
"""

# Import Libraries
import os
import sys
import argparse
import numpy as np
import matplotlib
import configparser
import threading

matplotlib.use('TkAgg')
from matplotlib import pyplot as plt

# path = os.path.abspath('../../')
path = os.path.abspath('../')
if not path in sys.path:
    sys.path.append(path)
import xytable_packages


def main():
    """

    :return:
    :rtype:
    """
    # Parameters
    isdebug = True

    # Create an argument parser
    parser = argparse.ArgumentParser()
    parser.add_argument("-T", "--Time", dest='videotime', type=int, default=10800, help="video duration")
    args = parser.parse_args()


    # Create an XY-table object
    xytable2 = xytable_packages.object.XYTable('xytable2')

    # Start video streaming
    t = threading.Thread(target=xytable2.video(t=args.videotime))
    t.daemon = True
    t.start()
    t.join()



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
