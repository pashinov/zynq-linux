# zynq-linux

#### ОПИСАНИЕ ПРОЕКТА

Система сборки для zynq собранная на базе buildroot и утилит от xilinx

#### ИЕРАРХИЯ СИСТЕМЫ СБОРКИ

```
	zynq-linux
	  |
	  --buildroot            buildroot для сборки ядра и файловой системы
	  |
	  --device-tree-xlnx     набор утилит для генерации dts
	  |
	  --projects             директория в которой собирается проект
	  |
	  --qspi-flash           утилита для создания файла прошивки .mcs
	  |
	  --scripts              набор скриптов для автоматизации процесса сборки  
	  |
	  --u-boot-xilinx        набор утилит для создания u-boot
	  |
	  --vivado               директория для vivado-проектов
```

#### ПОДГОТОВКА ПЕРЕД НАСТРОЙКОЙ СИСТЕМЫ СБОРКИ

**Изменить права доступа к /opt:**
```
	* chown -R user:user /opt
```

**После установки vivado в директорию /opt выполнить команды:**
```
	* source /opt/Xilinx/Vivado/2016.4/settings64.sh
	* source /opt/Xilinx/SDK/2016.4/settings64.sh
```

**Записать в .bashrc:**
```
	* export PATH=$PATH:/opt/Xilinx/Vivado/2016.2/bin:/opt/Xilinx/Vivado_HLS/2016.2/bin:/opt/Xilinx/SDK/2016.2/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/arm/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_be/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_le/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-linux/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-none/bin:/opt/Xilinx/SDK/2016.2/gnu/armr5/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/tps/lnx64/cmake-3.3.2/bin:/opt/Xilinx/Vivado/2016.2/bin:/opt/Xilinx/Vivado_HLS/2016.2/bin:/opt/Xilinx/SDK/2016.2/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/arm/lin/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_be/bin:/opt/Xilinx/SDK/2016.2/gnu/microblaze/linux_toolchain/lin64_le/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch32/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-linux/bin:/opt/Xilinx/SDK/2016.2/gnu/aarch64/lin/aarch64-none/bin:/opt/Xilinx/SDK/2016.2/gnu/armr5/lin/gcc-arm-none-eabi/bin:/opt/Xilinx/SDK/2016.2/tps/lnx64/cmake-3.3.2/bin
	* export SWT_GTK3=0
```

**Библиотеки для buildroot (компиляция ядра и файловой системы):**
```
	* sudo apt-get install libncurses5-dev libncursesw5-dev
```

**Библиотеки для u-boot (компиляция вторичного загрузчика):**
```
	* sudo apt-get install lib32z1
	* sudo apt-get install libssl-dev
	* sudo apt-get install device-tree-compiler
```

#### НАСТРОЙКА СИСТЕМЫ СБОРКИ

**Скачать buildroot в корень zynq-linux:**
```
	* git clone https://github.com/buildroot/buildroot.git
	* git checkout 2017.08-rc1
	* git checkout -b v2017.08
```

**Выполнить конфигурацию для zynq:**
```
	* make zynq_zed_defconfig
```

**Основные настройки buildroot:**
```
	* make menuconfig
		- Toolchain -> Enable C++ support -> yes
		- Kernel -> Build a Device Tree Blob (DTB) -> no
		- Bootloaders -> U-boot -> no
		- Host utilities -> host dtc -> no
```

**Настройка ядра xlnx-linux:**
```
	* make linux-menuconfig
```

**Настройкa unix-утилит:**
```
	* make busybox-menuconfig
```

**Собрать ядро и файловую систему:**
```
	* make ARCH=arm
```

**Скачать u-boot-xlnx в корень zynq-linux:**
```
	* git clone https://github.com/buildroot/buildroot.git
	* git checkout xilinx-v2016.2
	* git checkout -b v2016.2
```

**Выполнить конфигурацию для zynq:**
```
	* make zynq_zed_defconfig
```

**Основные настройки:**
```
	* make menuconfig
		- Command line interface -> Device access commands -> sf -> yes
```

**Сборка u-boot:**
```
	* make CROSS_COMPILE=arm-xilinx-linux-gnueabi- ARCH=arm
```

**Скачать device-tree-xlnx в корень zynq-linux:**
```
	* git clone https://github.com/Xilinx/device-tree-xlnx.git
	* git checkout xilinx-v2016.2
	* git checkout -b v2016.2
```

#### СБОРКА ПРОЕКТА

**В vivado выполнить команду для сборки vivado проекта:**
	* source ./vivado/build.tcl

**После создания vivado проекта zynq_gpio, необходимо собрать его:**
	* generate bitstream

**В директории ./projects/zynq_gpio выполнить следующие команды:**
```
	* make import - копирование .sysdef и .bit файлов из проекта собранного vivado
	* make dts - создание dts файла (.sysdef -> dts)
	* make dtb - создание dtb файла (dts -> dtb)
	* make boot - сборка загрузчика (fsbl + bitstream.bit + u-boot)
	* make build - компиляция ядра xlnx-linux и файловой системы
	* make image - создание файла прошивки .mcs (загрузчик + ядро linux + dtb + rootfs)
```
