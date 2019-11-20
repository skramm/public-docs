@echo off
set INPUT_FILE=RT1_nom_login.csv
goto d1

Sebastien Kramm, 20191120
IUT Rouen, dept R&T

:d1
:: page de code française
chcp 863
if not "%3"=="" goto st1

:: default values
set MODULE=M1106
set GROUPE=B
set NOM=tp2_3.html

:err1
echo Ce script permet de vérifier si un fichier est présent pour un groupe RT1
echo donné sur le disque T:
echo Concretement, il permet de vérifier la présence d'un fichier:
echo T:\M1234\a.txt
echo pour un groupe RT1 donné.
echo Il faut donner
echo - le groupe (RT1)
echo - le module (sous la forme "M1106")
echo - le nom du fichier
echo usage: check [groupe] [module] [nom_fichier]
echo .
echo Il nécessite comme fichier d'entrée un fichier csv donnant la correspondance
echo groupe-nom-prenom-login
echo Le nom de ce fichier est à donner "en dur" dans le script.
goto :eof

:st1
set PATH1=R:\RT\RT1
set compt=0

set GROUPE=%1
set MODULE=%2
set NOM=%3

echo Recherche du fichier "%3" du module "%2" pour le groupe %1:
for /F "delims=; tokens=1,2,3,5" %%a in (%INPUT_FILE%) do call :sp1 %%a %%b %%c %%d
echo Nb fichirs manquants: %compt%
echo fini
goto :eof

:sp1
::echo arg1=%1 arg2=%2 arg3=%3 arg4=%4

::echo test de %PATH1%\%4\%MODULE% 
::if exist %PATH1%\%4\%MODULE% goto ok
if exist %PATH1%\%4 goto groupe_ok %2 %1
echo login %4: inexistant dans %PATH1%
:echo Nb pas bon=%compt%
goto :eof

:groupe_ok
::echo NOM=%2 groupe=%1: bon
if NOT %1==%GROUPE% goto :eof
if exist %PATH1%\%4\%MODULE%\%NOM% goto :eof
echo NOM:%2 : fichier manquant
set /A compt=%compt%+1
goto :eof
