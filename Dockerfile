FROM ptigas/vfxplatform:CY2018
#Building on docker container for CY2018 VFX Reference Platform.
#See https://hub.docker.com/r/ptigas/vfxplatform

MAINTAINER Linda Terlouw (linda.terlouw@icris.nl)

RUN yum -y update
RUN yum install -y git-all vim make valgrind libgflags-dev libboost-dev gcc-c++ cmake gflags-devel
RUN ls
RUN mkdir /workdir/openvdbfractals
RUN mkdir /workdir/openvdbfractals/src
ADD CMakeLists.txt /workdir/openvdbfractals
ADD src/main.cc /workdir/openvdbfractals/src
WORKDIR /workdir/openvdbfractals/build
RUN cmake ..
RUN make 
WORKDIR /workdir/openvdbfractals/bin
