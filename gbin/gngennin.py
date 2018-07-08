from sys import argv
import subprocess






def myexit(message):
  '''Show message and quit'''
  exit(1)

def main():
  '''
  run gn gen for creating visual studio's sln.
  after creating it, start build with ninja.
  '''
  
  fullTarget = argv[1]
  if not fullTarget:
    myexit('fullTarget is empty.')

  # Name is after colon
  targetName = fullTarget.split(':')[-1]
  if not targetName:
    # if no colon, target name is same as folder name
    targetName = fullTarget.split('/')[-1]
    
  gngenarg = ['gn.bat', 'gen', '--ide=vs2017', '--filters='+fullTarget, '--sln='+targetName, 'out/debug']
  print(gngenarg)
  subprocess.call(gngenarg)
  
  
  ninjaarg = ['ninja', '-j', '1', '-C', 'out/debug', targetName]
  print(ninjaarg)
  subprocess.call(ninjaarg)  
  
if __name__ == "__main__":
  main() 
