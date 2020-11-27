<h1>courseCPP_TeamE</h1>


Setup  
git clone dir/  
make build dir/ in root. mkdir build  
cd to build dir/  
cmake..  
make  
run ../script  

<h3>Folder structure</h3>  


<h3>Overview</h3>  

InputHandler exe for sending user action and simulation mode change  
ECM for calculating engine speed, fuel consumption and messages  
TCM for calculating vehicle speed and actual gear  
DisplayHandler for debug information  
GUI for displaying values  

<h3>Scripts</h3>  

run.sh run simulation without GUI  
runsim.sh run simulation with GUI  
runcppcheck.sh to run cppcheck for all projetc files  
setupvcan.sh setup and start vcan0  

<h3>Simulation instructions</h3>  

Press 'm' to change mode sleep (do nothing, wait for can), inactive (activate network), active (normal), off (close applications)  
Press 's' to start/stop engine (message triggered if conditions not met)  
Press '+/-* to change gear lever up/down (PRND)  
Press arrow left/right for brake presssure 0-100%   
Press arrow up/down for acceleration pedal 0-100%  
