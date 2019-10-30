import sys
import os
import subprocess
import platform

import real2gn

''' call gnref with realpath input'''

def isOption(arg):
    return arg[0]=='-'

def main():
    # args = ['cmd', '/c', os.path.join(os.path.dirname(__file__), 'gnrefs')]
    args = [os.path.join(os.path.dirname(__file__), 'gnrefs')]
    if platform.system().lower()[0:7] == 'windows':
        args.insert(0, '/c')
        args.insert(0, 'cmd')
    for arg in sys.argv[1:]:
        if isOption(arg):
            args.append(arg)
        else:
            args.append(real2gn.real2gn(arg))

#	print(args)
    subprocess.call(args)

if __name__ == "__main__":
    main()
