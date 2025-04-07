@echo off
echo Copying All Updated Files

xcopy .\*.* c:\version\a7\*.* /D /E /Y /F /R
del c:\version\a7\CopyFiles.bat
del c:\version\a7\CopyExecutables.bat
del c:\version\a7\CopyFilesQa.bat
pause
