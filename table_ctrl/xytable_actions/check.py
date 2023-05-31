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

    # Create an XY-table object
    xytable2 = xytable_packages.object.XYTable('xytable2')

    print(" ")
    print("Checking XY table 2 position...")
    xytable2.check()

    print(" ")



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
