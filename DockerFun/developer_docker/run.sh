
docker run -it --rm  \
           -e LOCAL_USER_ID=`id -u $USER` -e DISPLAY=$DISPLAY \
           --security-opt seccomp=unconfined \
           -v /tmp/.X11-unix:/tmp/.X11-unix -v ~/sdl:/home/developer/sdl \
           developer_docker /bin/bash
