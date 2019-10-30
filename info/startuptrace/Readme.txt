chrome.lnk --trace-startup --trace-startup-file=%~dp0foo.json --trace-startup-duration=10

run 'startchromewithtrace.bat', this launches chrome and record for 10 sec
Open chrome://tracing/ in chrome
Load foo.json