@echo off
:reInput
echo please input blog name:
set /p suffix=
set filename=%date%-%suffix%.md
set filepath=_posts\%filename%
if exist %cd%\%filepath% echo Already exist file: %cd%\%filepath% && goto reInput
echo ---> %filepath%
echo layout: post>> %filepath%
echo title: new post>> %filepath%
echo --->> %filepath%
echo create file successfully!
pause
exit