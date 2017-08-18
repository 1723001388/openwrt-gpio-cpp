export STAGING_DIR=/home/wooya/Downloads/openwrt/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2
export PATH=$PATH:$STAGING_DIR/bin
mipsel-openwrt-linux-g++ gpio-cpp/gpio.cpp gpio-cpp/main.cpp -o gpio-cpp/gpio-cpp
