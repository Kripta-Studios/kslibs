#! /usr/bin/python
import os, sys

os.system("rm .config.kslibs")
os.system("rm kslibs")
os.system("make")
os.system("./kslibs")
