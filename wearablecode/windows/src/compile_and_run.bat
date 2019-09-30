echo off
cls
SET /A a = 0 
cl /W3 /GA /DWIN32 /MT /I C:\boost_1_70_0\boost_1_70_0 /I C:\stb /I C:\armadillo-9.600.5\include /I C:\mlpack /c main.cpp && SET /A a =  %a% + 1 
if %a%==0 (goto fail)
link /LIBPATH:C:\boost_1_70_0\boost_1_70_0\stage\lib\* /LIBPATH:..\ main kernel32.lib user32.lib ..\lib\daq\cbw64.lib ..\lib\filter\iir.lib  && SET /A a = %a% + 1 
if %a%==2 (goto success) else (goto fail)

:success
cls
echo.
echo.
echo ************************************************
echo  Compiled Successfully!! Now Running Backend
echo ************************************************
echo.
echo.
main.exe
echo.
echo.
goto end

:fail
echo.
echo.
echo ************************************************
echo               Compilation Failed!
echo ************************************************
echo.
echo.
goto end

:end


