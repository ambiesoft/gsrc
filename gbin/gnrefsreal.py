import sys
import os
import subprocess
import platform

import real2gn

''' call gnref with realpath input'''

def isOption(arg):
    return arg[0]=='-'

def main():
    args = ['cmd', '/c', os.path.join(os.path.dirname(__file__), 'gnrefs')]
    
    for arg in sys.argv[1:]:
        if isOption(arg):
            args.append(arg)
        else:
            args.append(real2gn.real2gn(arg))

#	print(args)
    subprocess.call(args)

if __name__ == "__main__":
    main()
