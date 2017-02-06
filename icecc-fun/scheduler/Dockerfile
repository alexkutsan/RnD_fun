FROM ubuntu:trusty

ENV CORE_BRANCH=develop \
    CORE_CWD=/tmp/sdl

RUN sudo apt-get update
RUN apt-get install -y software-properties-common python-software-properties
RUN sudo add-apt-repository ppa:ubuntu-toolchain-r/test
RUN sudo apt-get -qq update

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential \ 
  cmake \
  libudev-dev \
  libsqlite3-dev \
  clang-format-3.6 \
  libssl-dev \
  pkg-config \
  python \
  sudo \
  sqlite3 \
  automake1.11 \
  libexpat1-dev \
  libbluetooth3 \
  libbluetooth-dev \
  ccache \
  git \
  gcc \
  g++ \
  curl \
  icecc


RUN curl -O http://archive.ubuntu.com/ubuntu/pool/main/l/lcov/lcov_1.11-3_all.deb
RUN sudo dpkg -i lcov_1.11-3_all.deb
RUN apt-get -y install g++-4.9 gcc-4.9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 20
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 20
RUN update-alternatives --config gcc
RUN update-alternatives --config g++
RUN sudo ln -sf /usr/bin/gcov-4.9 /usr/bin/gcov
ENTRYPOINT icecc-scheduler
