FROM ubuntu:focal

# Install dependencies
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update
RUN apt-get -y install \
    git cmake build-essential \
    libusb-1.0-0-dev 

# Install libch340g
RUN git clone https://github.com/seanavery/ch340g-user.git && \
    cd ch340g-user && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install
