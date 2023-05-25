#!/bin/sh
#this script is meant to "generalize" the disk image, to run correctly after cloning

#-------------------- apt/package tasks --------------------#
apt update

#ensure headers are present for current kernel
apt install -fy linux-headers-$(uname -r)

#clean up apt files
rm -f /etc/apt/apt.conf.d/01proxy && \
    rm -rf /var/lib/apt/lists/* && \
    apt clean && \
    apt autoclean

#-------------------- dhcp/dns tasks --------------------#

#Make sure hostname is set by dhcp
rm -f /etc/hostname
hostnamectl set-hostname localhost

#-------------------- file cleaning tasks --------------------#

# Remove the Trash
rm -rf /home/*/.local/share/Trash/*/**
rm -rf /root/.local/share/Trash/*/**

#Delete all .gz and rotated file
logrotate -f /etc/logrotate.conf
find /var/log -type f -regex ".*\.gz$" -delete
find /var/log -type f -regex ".*\.[0-9].*$" -delete

#remove temporary files, but not base directories
rm -rf /tmp/*
rm -rf /var/tmp/*

#remove bash history
rm -f /home/*/.bash_history
rm -f /root/.bash_history

#Cleaning is completed
echo "Cleaning is completed"