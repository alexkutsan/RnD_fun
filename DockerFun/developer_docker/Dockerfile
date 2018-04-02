FROM ubuntu:16.04

RUN apt-get update
RUN apt install -y sudo

COPY entrypoint.sh /usr/bin/
ENTRYPOINT ["/bin/bash", "-e", "/usr/bin/entrypoint.sh"]
