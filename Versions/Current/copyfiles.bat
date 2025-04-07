@echo off
echo Copying All Updated Files

xcopy .\*.* c:\a7\*.* /D /E /Y /R
del c:\a7\CopyFiles.bat
del c:\a7\CopyExecutables.bat
del c:\a7\CopyFilesqa.bat
del c:\a7\CopyFilesqa2.bat
if exist c:\a7\terrain.dll del c:\a7\terrain.dll

pause
