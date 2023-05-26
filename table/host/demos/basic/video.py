"""
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

path = os.path.abspath('../../')
if not path in sys.path:
    sys.path.append(path)
import mmwsdr


def main():
    """

    :return:
    :rtype:
    """
    # Parameters
    isdebug = True

    # Create an argument parser
    parser = argparse.ArgumentParser()
    # parser.add_argument("-n", "--node", type=str, default='srv1-in1', help="COSMOS-SB1 node name (i.e., srv1-in1)")
    parser.add_argument("-i", "--index", type=str, default='2', help="the index of the XY table you want to monitor")
    parser.add_argument("-X", "--x", type=int, default=0, help="x coordinate on XY table")
    parser.add_argument("-Y", "--y", type=int, default=0, help="y coordinate on XY table")
    parser.add_argument("-R", "--r", type=int, default=0, help="rotation angle of the array on XY table")
    parser.add_argument("-T", "--Time", dest='videotime', type=int, default=10800, help="video duration")
    args = parser.parse_args()

    # # Create a configuration parser
    # config = configparser.ConfigParser()
    # config.read('../../config/sivers.ini')

    # xytable_obj = mmwsdr.utils.XYTable(config[args.node]['table_name'], isdebug=isdebug)
    xytable_obj = mmwsdr.utils.XYTable('xytable'+args.index, isdebug=isdebug)

    if args.x and args.y and args.a:
        xytable_obj.move(x=args.x, y=args.y, angle=args.a)


    t = threading.Thread(target=xytable_obj.video(t=args.videotime))
    t.daemon = True
    t.start()

    # Create a move
    # xytable_obj.move(x=500, y=500, angle=-45)

    t.join()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
