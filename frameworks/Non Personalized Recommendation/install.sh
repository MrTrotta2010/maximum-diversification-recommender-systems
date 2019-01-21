#!/bin/bash

# install python
sudo apt-get update
sudo apt-get install python

# install python setuptools
wget https://bootstrap.pypa.io/ez_setup.py
sudo python ez_setup.py
sudo rm -f ez_setup.py
sudo rm -f setuptools-15.2.zip

# install numpy library
sudo apt-get install python-numpy  

# install scipy library
sudo apt-get install python-scipy

# install nimfa library
wget https://github.com/marinkaz/nimfa/archive/master.zip
unzip master.zip
cd nimfa-master/
sudo python setup.py install
cd ../
sudo rm -rf nimfa-master master.zip