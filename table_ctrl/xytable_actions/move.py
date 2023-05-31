"""
: Modifier: Yuning Zhang
: Modified time: 2023/05
: Modifier Organization: University of Southern California
: Modification Log
:    - Change the rotation angle of the XYtable as constant number, 0 - no need to modify it during the indoor experiment
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
    parser.add_argument("-X", "--x", type=int, default=0, help="x coordinate on XY table")
    parser.add_argument("-Y", "--y", type=int, default=0, help="y coordinate on XY table")
    # parser.add_argument("-R", "--r", type=int, default=0, help="rotation angle of the array on XY table")
    args = parser.parse_args()

    # Create an XY-table object
    xytable2 = xytable_packages.object.XYTable('xytable2')

    # Set up the movement parameters
    x = args.x
    y = args.y
    # r = args.r
             
    # Move
    # xytable2.move(x, y, r)
    xytable2.move(x, y, 0)



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
