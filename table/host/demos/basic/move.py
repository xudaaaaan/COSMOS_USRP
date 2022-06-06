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
    parser.add_argument("-n", "--node", type=str, default='srv1-in1', help="COSMOS-SB1 node name (i.e., srv1-in1)")
    parser.add_argument("--comb", type=int, default=1, help="combination of the XY table positions")
    parser.add_argument("--x", type=int, default=0, help="x coordinate on XY table")
    parser.add_argument("--y", type=int, default=0, help="y coordinate on XY table")
    parser.add_argument("--angle", type=int, default=0, help="angle of the array on XY table")
    args = parser.parse_args()

    # Create a configuration parser
    config = configparser.ConfigParser()
    config.read('../../config/sivers.ini')

    xytable0 = mmwsdr.utils.XYTable(config[args.node]['table_name'], isdebug=isdebug)

    if not args.comb:
        x = args.x
        y = args.y
        angle = args.angle
    else:
        if args.comb == 1 and args.node == "srv1-in1":  # For table 1:
            x = 0
            y = 0
            angle = 0
        elif args.comb == 2 and args.node == "srv1-in1":
            x = 0
            y = 1300
            angle = 0
        elif args.comb == 3 and args.node == "srv1-in1":
            x = 0
            y = 0
            angle = 0
        elif args.comb == 4 and args.node == "srv1-in1":
            x = 0
            y = 1300
            angle = 0
        elif args.comb == 1 and args.node == "srv1-in2":    # For table 2:
            x = 1300
            y = 0
            angle = 0
        elif args.comb == 2 and args.node == "srv1-in2":
            x = 1300
            y = 0
            angle = 0
        elif args.comb == 3 and args.node == "srv1-in2":
            x = 1300
            y = 1300
            angle = 0
        elif args.comb == 4 and args.node == "srv1-in2":
            x = 1300
            y = 1300
            angle = 0            


    xytable0.move(x, y, angle)


    # t = threading.Thread(target=xytable0.video(t=args.videotime))
    # t.start()

    # Create a move
    # xytable0.move(x=500, y=500, angle=-45)

    # t.join()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
