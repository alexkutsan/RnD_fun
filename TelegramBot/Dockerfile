FROM ubuntu:16.04

RUN apt-get update && apt install -y python-pip
RUN pip install python-telegram-bot --upgrade 

COPY entrypoint.sh /var/
ENTRYPOINT ["/bin/bash", "-e", "/var/entrypoint.sh"]
