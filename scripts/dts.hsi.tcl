#
# SecBus ( http://secbus.telecom-paristech.fr/ ) - This file is part of SecBus
# Copyright (C) - Telecom ParisTech
# Contacts: contact-secbus@telecom-paristech.fr
#
# This file must be used under the terms of the CeCILL.
# This source file is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at
# http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
#

puts $argc
if { $argc != 3 } {
	puts "usage: dts.hsi.tcl <hardware-description-file> <path-to-device-tree-xlnx> <local-device-tree-directory>"
} else {
	set hdf [lindex $argv 0]
	set xdts [lindex $argv 1]
	set ldts [lindex $argv 2]
	open_hw_design $hdf
	set_repo_path $xdts
	create_sw_design device-tree -os device_tree -proc ps7_cortexa9_0
	generate_target -dir $ldts
	file delete -force ../import/drivers
	eval file delete [glob nocomplain ../import/*.c ../import/*.h ../import/*.html ../import/*.tcl]
}
