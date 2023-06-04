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
    parser.add_argument("-c", "--ics", default='all', help="can be either 'all' or any number between 1~4")
    parser.add_argument("-N", "--num_elements", type=int, default=16, help="the number of elements to be activated on each IC")
    parser.add_argument("-m", "--mode", type=str, default='tx', help="assign the working mode, tx or rx")
    parser.add_argument("-P", "--pol", type=str, default='v', help="assign the polarization, vertical or horizontal")
    parser.add_argument("-t", "--theta", type=int, default=0, help="the direction of azimuth steering")
    parser.add_argument("-p", "--phi", type=int, default=0, help="the direction of elevation steering")
    args = parser.parse_args()

    # Create a PAAM object
    PAAM0 = paam_packages.object.PAAM(args.node)

    # Set up the RF configuration for the PAAM
    ics = args.ics
    try:
        ics = int(ics)
    except ValueError:
        pass  # ics remains as "all"
    num_elements = args.num_elements
    mode = args.mode
    Pol = args.pol
    theta = args.theta
    phi = args.phi
                 
    # Execute
    print(" ")
    print("*********************************")
    print("Configuring the PAAM board...")
    print("*********************************")
    PAAM0.config(ics, num_elements, mode, Pol, theta, phi)



if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
