# zynq-linux
The build system for zynq based on the buildroot and xilinx toolchain

__________________________________________________________________________________

                        ОПИСАНИЕ ПРОЕКТА:
__________________________________________________________________________________

Система сборки для zynq собранная на базе buildroot и утилит от xilinx

__________________________________________________________________________________

                     ИЕРАРХИЯ СИСТЕМЫ СБОРКИ
__________________________________________________________________________________

    zynq-linux
      |
      --buildroot		buildroot для сборки ядра и файловой системы
      |
      --device-tree-xlnx	набор утилит для генерации dts
      |
      --projects		директория в которой собирается проект
      |
      --qspi-flash		утилита для создания файла прошивки .mcs
      |
      --scripts			набор скриптов для автоматизации процесса сборки
      |
      --u-boot-xilinx		набор утилит для создания u-boot
      |
      --vivado			директория для vivado-проектов

__________________________________________________________________________________

              ПОДГОТОВКА ПЕРЕД НАСТРОЙКОЙ СИСТЕМЫ СБОРКИ
__________________________________________________________________________________

Изменить права доступа к /opt
    chown -R user:user /opt

После установки vivado в директорию /opt выполнить команды:
    source /opt/Xilinx/Vivado/2016.4/settings64.sh
    source /opt/Xilinx/SDK/2016.4/settings64.sh

Записать в .bashrc 
    export PATH=$PATH:/opt/Xilinx/Vivado/2016.2/bin:/opt/Xilinx/Vivado_HLS/2016.2/bin:/opt/Xilinx/SDK/2016.2/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/arm/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_be/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_le/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-linux/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-none/bin:/opt/Xilinx/SDK/2016.2/gnu/armr5/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/tps/lnx64/cmake-3.3.2/bin:/opt/Xilinx/Vivado/2016.2/bin:/opt/Xilinx/Vivado_HLS/2016.2/bin:/opt/Xilinx/SDK/2016.2/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/arm/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_be/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_le/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-linux/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-none/bin:/opt/Xilinx/SDK/2016.2/gnu/armr5/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/tps/lnx64/cmake-3.3.2/bin
    export SWT_GTK3=0 

Библиотеки для buildroot
    sudo apt-get install libncurses5-dev libncursesw5-dev

Библиотеки для u-boot
    sudo apt-get install lib32z1
    sudo apt-get install libssl-dev
    sudo apt-get install device-tree-compiler

__________________________________________________________________________________

                      НАСТРОЙКА СИСТЕМЫ СБОРКИ
__________________________________________________________________________________

Скачивание buildroot в корень zynq-linux
    git clone https://github.com/buildroot/buildroot.git
    git checkout 2017.08-rc1
    git checkout -b v2017.08

Конфигурация под zynq
    make zynq_zed_defconfig

Основные настройки
    make menuconfig
        Toolchain -> Enable C++ support -> yes
        Kernel -> Build a Device Tree Blob (DTB) -> no
        Bootloaders -> U-boot -> no
        Host utilities -> host dtc -> no

Настройкa ядра 
    make linux-menuconfig

Настройкa unix-утилит 
    make busybox-menuconfig

Сборка ядра и файловой системы
    make ARCH=arm

Скачивание u-boot-xlnx в корень build
    git clone https://github.com/buildroot/buildroot.git
    git checkout xilinx-v2016.2
    git checkout -b v2016.2

Конфигурация под zynq
    make zynq_zed_defconfig

Основные настройки
    make menuconfig
    Command line interface -> Device access commands -> sf -> yes

Сборка u-boot
    make CROSS_COMPILE=arm-xilinx-linux-gnueabi- ARCH=arm

Скачивание device-tree-xlnx в корень build
    git clone https://github.com/Xilinx/device-tree-xlnx.git
    git checkout xilinx-v2016.2
    git checkout -b v2016.2
