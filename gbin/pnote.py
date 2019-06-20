import sys
import urllib.parse
import subprocess as sp

'''
Read stdin and open them with chrome
This script can be used in the same way of 'less'
ex)
> dir | python pnote.py
'''

# Get all date from stdin, data is list
data = sys.stdin.readlines()

# data protocol + urlecoded text
url = 'data:text/plain,' + urllib.parse.quote(''.join(data))

# open chromium
sp.Popen(['C:/Program Files (x86)/Google/Chrome/Application/chrome.exe', url])
