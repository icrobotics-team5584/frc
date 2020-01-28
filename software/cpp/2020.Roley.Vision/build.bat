@ echo off

rem ############################################################################
rem #                                                                          #
rem # STEP 1: ON WINDOWS PC IN A BASH SHELL:                                   #
rem #                                                                          #
rem #   ssh-keygen                                                             #
rem #   (press "enter")                                                        #
rem #   (press "enter")                                                        #
rem #   (press "enter")                                                        #
rem #   scp ~/.ssh/id_rsa.pub ubuntu@10.55.84.8:/tmp                           #
rem #                                                                          #
rem # STEP 2: ON THE JETSON:                                                   #
rem #                                                                          #
rem #   cat /tmp/id_rsa.pub >> /home/ubuntu/.ssh/authorized_keys2              #
rem #   rf -rf /tmp/id_rsa.pub                                                 #
rem #                                                                          #
rem # STEP 3: ON WINDOWS PC:                                                   #
rem #                                                                          #
rem #    You can now build on the JETSON from the command line on your PC,     #
rem #    just open a command prompt and run build.bat, this will transfer      #
rem #    your local files to the JETSON and launch the build.sh script on the  #
rem #    JETSON. Note that you can also run build.bat from the terminal in     #
rem #    VSCODE.                                                               #
rem #                                                                          #
rem # TROUBLESHOOTING:                                                         #
rem #                                                                          #
rem #    If build.bat fails to connect to the JETSON and reports ...           #
rem #                                                                          #
rem #    "It is required that your private key files are NOT accessible        #
rem #    by others. This private key will be ignored."                         #
rem #                                                                          #
rem #    ... then you can resolve this from a command prompt as follows:       #
rem #                                                                          #
rem #    Icacls %USERPROFILE%\.ssh\id_rsa /c /t /Inheritance:d                 #
rem #                                                                          #
rem #    Icacls %USERPROFILE%\.ssh\id_rsa /c /t /Grant %UserName%:F            #
rem #                                                                          #
rem #    Icacls %USERPROFILE%\.ssh\id_rsa /c /t /Remove Administrator \        #
rem #      "Authenticated Users" BUILTIN\Administrators \                      #
rem #      BUILTIN Everyone System Users                                       #
rem #                                                                          #
rem #    You can verify that only your personal account is listed with ...     #
rem #                                                                          #
rem #    Icacls %USERPROFILE%\.ssh\id_rsa                                      #
rem #                                                                          #
rem ############################################################################

set PROJECTNAME=2020.Roley.Vision
set PROJECTWORKSPACE=~/Projects/%PROJECTNAME%
set PROJECTARCHIVE=%PROJECTNAME%.tar
set PROJECTACCOUNT=ubuntu@10.55.84.8

echo ---------------------------------------------------------------------------
echo INFO: constructing archive
tar -cvf ..\%PROJECTARCHIVE% *.txt *.sh *.h *.cpp

echo ---------------------------------------------------------------------------
echo INFO: transporting archive
scp ..\%PROJECTARCHIVE% %PROJECTACCOUNT%:/tmp

echo ---------------------------------------------------------------------------
echo INFO: removing local archive
del ..\%PROJECTARCHIVE%

echo ---------------------------------------------------------------------------
echo INFO: reseting remote workspace
ssh %PROJECTACCOUNT% rm -rf %PROJECTWORKSPACE%
ssh %PROJECTACCOUNT% mkdir -p %PROJECTWORKSPACE%

echo ---------------------------------------------------------------------------
echo INFO: extracting archive
ssh %PROJECTACCOUNT% cd %PROJECTWORKSPACE%; tar -xvf /tmp/%PROJECTARCHIVE%

echo ---------------------------------------------------------------------------
echo INFO: removing remote archive
ssh %PROJECTACCOUNT% rm -rf /tmp/%PROJECTARCHIVE%

echo ---------------------------------------------------------------------------
echo INFO: setting permissions in workspace
ssh %PROJECTACCOUNT% cd %PROJECTWORKSPACE%; chmod a+x *.sh

echo ---------------------------------------------------------------------------
echo INFO: building in remote workspace
ssh %PROJECTACCOUNT% cd %PROJECTWORKSPACE%; ./build.sh
