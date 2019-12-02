@echo off
IF [%1]==[/?] SET /A debug = 0
IF [%1]==[0] SET /A debug = 0
IF [%1]==[1] SET /A debug = 1

gcc scoreController.c menusController.c carracing.c display.c main.c -o game -D DEBUG=%debug%
start .\game.exe