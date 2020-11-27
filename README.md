<h1>courseCPP_TeamE</h1>

<h3>Overview</h3>  

![](https://github.com/anormen/courseCPP_TeamE/blob/main/documentation/system_overview.png "System overview")

<h3> Built executables </h3>
build/InputHandler for sending user action and simulation mode change  
build/ECM for calculating engine speed, fuel consumption and messages  
build/TCM for calculating vehicle speed and actual gear  
build/DisplayHandler for debug information  
build/ext/app/avic/avic GUI for displaying values  
  
All binaries communicate via virtual can  

<h3>Setup</h3>   

git clone https://github.com/anormen/courseCPP_TeamE  
mkdir build  
cd build  
cmake..  
make  
cd ..  
./script_name (run wanted script)  

<h3>Folder structure</h3>  

documentation/      - contains documentation
ext/app/            - contains GUI  
ext/lib/            - contain libcanio (for GUI)  
share/              - contains functionality for can message handling   
src/ECM/            - contains functionality for ECM  
src/TCM/            - contains functionality for TCM  
src/displayHandler/ - contains functionality for displayHandler  
src/inputHandler/   - contains functionality for inputHandler   
test/               - contains unit tests   


<h3>Scripts</h3>  

run.sh run simulation without GUI  
runsim.sh run simulation with GUI  
runcppcheck.sh to run cppcheck for all projetc files  
setupvcan.sh setup and start vcan0  

<h3>Simulation instructions</h3>  

In the inputHandler window:  

Press 'm' to change mode sleep (do nothing, wait for can), inactive (activate network), active (normal), off (close applications)  
Press 's' to start/stop engine (message triggered if conditions not met)  
Press '+/-* to change gear lever up/down (PRND)  
Press arrow left/right for brake presssure 0-100%   
Press arrow up/down for acceleration pedal 0-100%  
