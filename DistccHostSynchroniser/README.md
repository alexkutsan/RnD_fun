# DistccHostSynchroniser
Pet project for synchronisaiton hosts file of distcc distributed compiler adapter. 

## Why?
Distcc - wonderfull system. But you should monitor list of hosts on each developer worstation. I would like to sync this file between developers worstations and automaticaly update it in case if new worstation added to distributed compiled network. 

It is not the simpliets solution. But I do it for fun and education, so I try to use interesting technologies, newest C++ standard. 

## Do you need it? 
I suppose no, buisness valuie of this project is easier to reach probably with some small python script, or even with dropbox.
Note, that I am trying to do no server arhitecture, with automatic adding new worstations to list, when this new worstation will run this DistccHostSynchroniser deamon. 

## What I can to other way? 
I will be gracefull for all you tips and fixed. But please do not adwice me to solve my problem easily, I am doing this project for education. The best help for me wold finding wrong way of using techologies, patterns I used.  

## Dependencies:
- boost version boost-bin-boost-1.62 
- flatbuffers [v1.6.0](https://github.com/google/flatbuffers/releases/tag/v1.6.0)
