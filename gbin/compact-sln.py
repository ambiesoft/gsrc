import argparse
import xml.dom.minidom
import os
import sys

parser = argparse.ArgumentParser(description='Compact sln build by gn')
parser.add_argument('sln')
args = parser.parse_args()

sln = args.sln
if !os.path.exists(sln):
    sys.exit('{} not found'.format(sln))

dom = xml.dom.minidom.parse(sln)


