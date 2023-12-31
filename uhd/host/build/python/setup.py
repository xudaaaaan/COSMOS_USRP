#!/usr/bin/env python
#
#  Copyright 2017-2018 Ettus Research, a National Instruments Company
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#
"""Setup file for uhd module"""

from setuptools import setup

setup(name='uhd',
      version='3.15.0',
      description='Universal Software Radio Peripheral (USRP) Hardware Driver Python API',
      classifiers=[
          'Development Status :: 4 - Beta',
          'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
          'Programming Language :: C++',
          'Programming Language :: Python',
          'Topic :: System :: Hardware :: Hardware Drivers',
      ],
      keywords='SDR UHD USRP',
      author='Ettus Research',
      author_email='packages@ettus.com',
      url='https://www.ettus.com/',
      license='GPLv3',
      package_dir={'': r'/root/uhd/host/build/python'},
      package_data={'uhd': ['*.so']},
      zip_safe=False,
      packages=['uhd'],
      install_requires=['numpy'])
