@echo off
for /f "delims=: tokens=2" %%i in ('chcp') do ( 
	call :DefaultCodePage %%i
)

goto :End

:DefaultCodePage
set default_codepage=%1
goto :eof

:End

chcp 65001
echo %1> input.args
chcp %default_codepage%

C:\urlcoder\bin\urlcoder.exe decode input.args
