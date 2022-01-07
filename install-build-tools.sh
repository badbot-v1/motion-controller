RELEASE=$(lsb_release -rs)

if [ "$RELEASE"="20.04" ]; then
    sudo apt install -y curl
fi

sudo apt install -y gnupg default-jdk

$PLATFORM=$(uname -i)

if [ "$PLATFORM" = "aarch64" ]; then
    wget https://github.com/bazelbuild/bazel/releases/download/3.7.0/bazel-3.7.0-linux-arm64
    chmod +x bazel-3.7.0-linux-arm64
else
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
    sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
    echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
    sudo apt update && sudo apt install -y bazel
fi


wget https://github.com/Kitware/CMake/releases/download/v3.18.3/cmake-3.18.3-Linux-x86_64.sh
sudo sh cmake-3.18.3-Linux-x86_64.sh --skip-license --prefix=cmake-3.18.3-Linux-x86_64
