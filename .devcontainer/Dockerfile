FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update
RUN apt-get -y install gcc g++ gfortran gdb ca-certificates gpg wget
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg && \
	echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' > /etc/apt/sources.list.d/kitware.list && \
	apt-get -y update && \
	rm /usr/share/keyrings/kitware-archive-keyring.gpg && \
	apt-get -y install kitware-archive-keyring cmake
RUN apt-get -y install locate
RUN apt-get -y install git
RUN apt-get -y install libgromacs-dev

ENTRYPOINT [ "/bin/bash" ]
