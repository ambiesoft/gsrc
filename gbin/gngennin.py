import sys
import subprocess
import argparse
from os import path
import os

def myexit(message):
  '''Show message and quit'''
  print(message)
  exit(1)

# http://code.activestate.com/recipes/577058/
def query_yes_no(question, default="no"):
    """Ask a yes/no question via raw_input() and return their answer.
    
    "question" is a string that is presented to the user.
    "default" is the presumed answer if the user just hits <Enter>.
        It must be "yes" (the default), "no" or None (meaning
        an answer is required of the user).

    The "answer" returned is one of "yes" or "no".
    """
    valid = {"yes":"yes",   "y":"yes",  "ye":"yes",
             "no":"no",     "n":"no"}
    if default == None:
        prompt = " [y/n] "
    elif default == "yes":
        prompt = " [Y/n] "
    elif default == "no":
        prompt = " [y/N] "
    else:
        raise ValueError("invalid default answer: '%s'" % default)

    while 1:
        sys.stdout.write(question + prompt)
        choice = raw_input().lower()
        if default is not None and choice == '':
            return default
        elif choice in valid.keys():
            return valid[choice]
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' "\
                             "(or 'y' or 'n').\n")

  
def main():
  '''
  run gn gen for creating visual studio's sln.
  after creating it, start build with ninja.
  '''
  parser = argparse.ArgumentParser(description='gn gen and ninja')
  parser.add_argument('-j', help="ninja's -j, the number of processes", type=int)
  parser.add_argument("target")
  parser.add_argument("outdir", nargs='?')
  
  args = parser.parse_args()
  
  fullTarget = args.target
  outdir = args.outdir
  if not outdir:
    outdir=path.join('out', 'debug')
  
  if not fullTarget:
    myexit('fullTarget is empty.')
  if fullTarget[0:2] != '//':
    myexit('targe must be full target')
    
  # Name is after colon
  targetName = fullTarget.split(':')[-1]
  if not targetName:
    # if no colon, target name is same as folder name
    targetName = fullTarget.split('/')[-1]
  
  slnFilename = targetName+'.sln'
  if path.exists(path.join(outdir, slnFilename)):
     if 'yes' != query_yes_no(slnFilename + ' already exists. Do you want to run "gn gen" again?'):
       myexit(0)
     else:
       os.remove(path.join(outdir, slnFilename))
  
  ninjaarg = ['autoninja', '-C', outdir, fullTarget[2:]]
  if(args.j):
    ninjaarg.append('-j')
    ninjaarg.append(str(args.j))
  print(ninjaarg)
  subprocess.call(['cmd', '/c'] + ninjaarg)  


  tmpSlnFileName = targetName + '_gngennin'
  gngenarg = ['gn', 'gen', '--ide=vs2019', '--filters='+fullTarget, '--sln=' + tmpSlnFileName, outdir]
  print(gngenarg)
  subprocess.call(['cmd', '/c'] + gngenarg)
  os.rename(path.join(outdir, tmpSlnFileName+'.sln'), path.join(outdir, slnFilename))
  
if __name__ == "__main__":
  main() 
