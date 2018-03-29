FROM developer_docker

RUN apt-get update
RUN apt install -y git tmux wget zsh vim fonts-powerline
RUN git clone https://github.com/robbyrussell/oh-my-zsh /opt/oh-my-zsh

RUN cp /opt/oh-my-zsh/templates/zshrc.zsh-template .zshrc 
RUN cp -r /opt/oh-my-zsh .oh-my-zsh 

RUN mkdir /home/developer
RUN cp /opt/oh-my-zsh/templates/zshrc.zsh-template /home/developer/.zshrc
RUN cp -r /opt/oh-my-zsh /home/developer/.oh-my-zsh 
RUN sed  's/robbyrussell/bira/' -i /home/developer/.zshrc

CMD ["/bin/zsh"]
