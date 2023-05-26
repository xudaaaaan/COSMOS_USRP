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
    # parser.add_argument("-g", "--group", type=str, help="if use para group, then control 2 XY tables together")
    # parser.add_argument("-c", "--comb", type=int, default=1, help="combination of the XY table positions")
    parser.add_argument("-X", "--x", type=int, default=0, help="x coordinate on XY table")
    parser.add_argument("-Y", "--y", type=int, default=0, help="y coordinate on XY table")
    parser.add_argument("-R", "--r", type=int, default=0, help="rotation angle of the array on XY table")
    args = parser.parse_args()

    # # Create a configuration parser
    # config = configparser.ConfigParser()
    # config.read('../../config/sivers.ini')

    

    # if args.group == "yes":
    #     # xytable1 = mmwsdr.utils.XYTable(config["srv1-in1"]['table_name'], isdebug=isdebug)
    #     # xytable2 = mmwsdr.utils.XYTable(config["srv1-in2"]['table_name'], isdebug=isdebug)
    #     xytable_obj_1 = mmwsdr.utils.XYTable('xytable1', isdebug=isdebug)
    #     xytable_obj_2 = mmwsdr.utils.XYTable('xytable2', isdebug=isdebug)
    #     if args.comb == 1:
    #         x1 = 0
    #         y1 = 0
    #         a1 = 0
    #         x2 = 1300
    #         y2 = 0
    #         a2 = 0
    #     elif args.comb == 2:
    #         x1 = 0
    #         y1 = 1300
    #         a1 = 0
    #         x2 = 1300
    #         y2 = 0
    #         a2 = 0
    #     elif args.comb == 3:
    #         x1 = 0
    #         y1 = 0
    #         a1 = 0
    #         x2 = 1300
    #         y2 = 1300
    #         a2 = 0
    #     elif args.comb == 4:
    #         x1 = 0
    #         y1 = 1300
    #         a1 = 0
    #         x2 = 1300
    #         y2 = 1300
    #         a2 = 0
    #     xytable1.move(x1, y1, a1)
    #     xytable2.move(x2, y2, a2)
    # elif args.group == "no":
    xytable0 = mmwsdr.utils.XYTable('xytable'+args.index, isdebug=isdebug)
        # if not args.comb:
    x = args.x
    y = args.y
    r = args.r
        # else:
        #     if args.node == "srv1-in1":
        #         if args.comb == 1:
        #             x = 0
        #             y = 0
        #             a = 0
        #         elif args.comb == 2:
        #             x = 0
        #             y = 1300
        #             a = 0
        #         elif args.comb == 3:
        #             x = 0
        #             y = 0
        #             a = 0
        #         elif args.comb == 4:
        #             x = 0
        #             y = 1300
        #             a = 0
        #     elif args.node == "srv1-in2":
        #         if args.comb == 1:
        #             x = 1300
        #             y = 0
        #             a = 0
        #         elif args.comb == 2:
        #             x = 1300
        #             y = 0
        #             a = 0
        #         elif args.comb == 3:
        #             x = 1300
        #             y = 1300
        #             a = 0
        #         elif args.comb == 4:
        #             x = 1300
        #             y = 1300
        #             a = 0         
    xytable0.move(x, y, r)
    # else:
    #     raise Exception("Please specify the parameter group by yes or no")

    


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
