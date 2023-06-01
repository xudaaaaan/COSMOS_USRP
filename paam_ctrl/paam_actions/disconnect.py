"""
: Author: Yuning Zhang
: Created time: 2023/05
: Organization: University of Southern California
: Modification Log
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
import paam_packages


def main():
    """

    :return:
    :rtype:
    """
    # Create an argument parser
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--node", type=str, default='rfdev4-in2', help="the domain of the PAAM that you want to control")
    args = parser.parse_args()

    # Create a PAAM object
    PAAM0 = paam_packages.object.PAAM(args.node)

    # Execute
    print(" ")
    print("Disconnecting the PAAM board...")
    PAAM0.disconnect()

    print(" ")



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
