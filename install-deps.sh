#!/bin/bash

#https://help.ubuntu.com/community/UbuntuTime
echo "Asia/Qatar" | sudo tee /etc/timezone
dpkg-reconfigure --frontend noninteractive tzdata

sudo apt install -y build-essential
sudo apt install -y libglib2.0-0 libglib2.0-bin libglib2.0-dev libglibmm-2.4-dev libglibmm-2.4-1v5

CORE_COUNT=$1

if [ -z $1 ]; then
	CORE_COUNT=4
fi

echo ""
echo ""
echo "Using core count of $CORE_COUNT"
echo ""
echo ""

mkdir -p ../deps

pushd ../deps
wget https://github.com/jarro2783/cxxopts/archive/v2.2.0.zip
unzip v2.2.0.zip
cd cxxopts-2.2.0/
mkdir build
cd build
cmake -DCXXOPTS_BUILD_TESTS=OFF -DCXXOPTS_BUILD_EXAMPLES=OFF ..
make -j $CORE_COUNT
sudo make install
popd

pushd ../deps
git clone https://github.com/AlexeyAB/darknet
cd darknet
mkdir build-release
cd build-release
cmake ..
make -j $CORE_COUNT
sudo make install
popd

pushd ../deps
wget https://github.com/gabime/spdlog/archive/v1.5.0.zip
unzip v1.5.0.zip
mv spdlog-1.5.0/ spdlog
cd spdlog
mkdir build
cd build
cmake ..
make -j $CORE_COUNT
sudo make install
popd

pushd ../deps
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp/
mkdir build
cd build
cmake -DYAML_CPP_BUILD_TESTS=OFF ..
make -j $CORE_COUNT
sudo make install
popd

pushd ../deps
git clone https://github.com/YDLIDAR/sdk
mv sdk ydlidar
cd ydlidar
git checkout TOF
mkdir build
cd build
cmake ..
make -j $CORE_COUNT
sudo make install
popd

pushd ../deps
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.9.0/protobuf-all-3.9.0.tar.gz
tar -xvf protobuf-all-3.9.0.tar.gz
cd protobuf-3.9.0
./configure
make -j $CORE_COUNT
sudo make install
sudo ldconfig
popd

pushd ../deps
wget https://github.com/zeromq/libzmq/releases/download/v4.3.3/zeromq-4.3.3.tar.gz
tar -xvf zeromq-4.3.3.tar.gz
cd zeromq-4.3.3
mkdir build && cd build
cmake ..
make -j $CORE_COUNT
sudo make install
sudo ldconfig
popd

pushd ../deps
wget https://github.com/zeromq/cppzmq/archive/v4.7.1.tar.gz
tar -xvf v4.7.1.tar.gz
cd cppzmq-4.7.1
mkdir build && cd build
cmake ..
make -j $CORE_COUNT
sudo make install
sudo ldconfig
popd

sudo apt install -y gpsd gpsd-clients libgps-dev

RELEASE=$(lsb_release -rs)

if [ "$RELEASE"="18.04" ]; then
    
    sudo apt install -y \
        libgstreamermm-1.0-1 \
        libgstreamermm-1.0-dev \
        libgstreamer-plugins-bad1.0-0 \
        libgstreamer-plugins-bad1.0-dev \
        gstreamer1.0-plugins-ugly \
        gstreamer1.0-plugins-bad \
        gstreamer1.0-omx-generic \
        gstreamer1.0-omx-generic-config \
        gstreamer1.0-libav \
        libgstreamer-plugins-good1.0-0 \
        libgstreamer-plugins-good1.0-dev \
        libgstreamer1.0-0 \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-0 \
        libgstreamer-plugins-base1.0-dev \
        gstreamer1.0-alsa \
        gstreamer1.0-plugins-base \
        gstreamer1.0-plugins-base-apps \
        gstreamer1.0-plugins-good \
        gstreamer1.0-pulseaudio \
        gstreamer1.0-tools
else
    sudo apt install -y \
        libgstreamermm-1.0-1 \
        libgstreamermm-1.0-dev \
        libgstreamer-plugins-bad1.0-0 \
        libgstreamer-plugins-bad1.0-dev \
        gstreamer1.0-plugins-ugly \
        gstreamer1.0-plugins-rtp \
        gstreamer1.0-plugins-bad \
        gstreamer1.0-omx-generic \
        gstreamer1.0-omx-generic-config \
        gstreamer1.0-libav \
        libgstreamer-plugins-good1.0-0 \
        libgstreamer-plugins-good1.0-dev \
        libgstreamer1.0-0 \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-0 \
        libgstreamer-plugins-base1.0-dev \
        gstreamer1.0-alsa \
        gstreamer1.0-plugins-base \
        gstreamer1.0-plugins-base-apps \
        gstreamer1.0-plugins-good \
        gstreamer1.0-pulseaudio \
        gstreamer1.0-tools
fi
