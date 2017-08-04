PROJECT = zynq_gpio
BACK = ..

all: help

.PHONY: import dts fsbl

import:
	mkdir -p import
	cp -rf $(BACK)/$(BACK)/vivado/$(PROJECT)/$(PROJECT).runs/impl_1/zynq_design_wrapper.sysdef import/zynq_design_wrapper.sysdef;\
	cp -rf $(BACK)/$(BACK)/vivado/$(PROJECT)/$(PROJECT).runs/impl_1/zynq_design_wrapper.bit import/zynq_design_wrapper.bit;

dts:
	mkdir -p hw;\
	cd hw;\
	hsi -mode batch -quiet -notrace -source $(BACK)/$(BACK)/$(BACK)/scripts/dts.hsi.tcl -tclargs $(BACK)/import/zynq_design_wrapper.sysdef $(BACK)/$(BACK)/$(BACK)/device-tree-xlnx $(BACK)/dts;\

fsbl:
	cd hw;\
	hsi -mode batch -quiet -notrace -source $(BACK)/$(BACK)/$(BACK)/scripts/fsbl.hsi.tcl -tclargs $(BACK)/import/zynq_design_wrapper.sysdef $(BACK)/fsbl;

uboot:
	cd $(BACK)/$(BACK)/u-boot-xlnx;\
	make CROSS_COMPILE=arm-xilinx-linux-gnueabi- ARCH=arm;\
	cp u-boot $(BACK)/projects/$(PROJECT)/output/temp/u-boot.elf;

bitfile:
	cp import/zynq_design_wrapper.bit output/temp/bitstream.bit;

dtb:
	dtc -I dts -O dtb -o output/images/devicetree.dtb dts/system.dts;

boot: fsbl uboot bitfile
	bootgen -w -image $(BACK)/$(BACK)/scripts/boot.bif -o output/images/BOOT.bin;

build:
	cd $(BACK)/$(BACK)/buildroot;\
	make ARCH=arm;\
	cp output/images/uImage $(BACK)/projects/$(PROJECT)/output/images/uImage;\
	cp output/images/rootfs.cpio.uboot $(BACK)/projects/$(PROJECT)/output/images/uramdisk.image.gz;

image:
	cd $(BACK)/$(BACK)/qspi-flash;\
	./qspi-flash $(BACK)/projects/$(PROJECT)/output/images/BOOT.bin 0x000000 $(BACK)/projects/$(PROJECT)/output/images/uImage 0x700000 $(BACK)/projects/$(PROJECT)/output/images/devicetree.dtb 0xB00000 $(BACK)/projects/$(PROJECT)/output/images/uramdisk.image.gz 0xB20000 -o $(BACK)/projects/$(PROJECT)/output/temp/image.bin 0x2000000;\
	srec_cat $(BACK)/projects/$(PROJECT)/output/temp/image.bin -Binary -o $(BACK)/projects/$(PROJECT)/output/images/image.mcs -Intel;

clean:
	rm -rf dts fsbl hw output/images/* output/temp/* import;

help:
	@echo "Available commands:"
	@echo " make import"
	@echo " make dts"
	@echo " make dtb"
	@echo " make boot"
	@echo " make build"
	@echo " make image"
	@echo " make clean"

#kernel:
#	cd $(BUILDDIR)/linux-xlnx;\
	make ARCH=arm;\
	mkimage -A arm -O linux -C none -T kernel -a 0x8000 -e 0x8000 -d arch/arm/boot/zImage ../output/images/uImage;
