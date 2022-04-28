How To
======

Build FPGA
----------

From the project root dir, execute:

::
  
  ql_symbiflow -compile -d ql-eos-s3 -P pu64 -v fpga/rtl/*.v -t top -p fpga/rtl/quickfeather.pcf -dump jlink binary

This will create both a :code:`top.bin` which can be flashed, as well as :code:`top.jlink` which can be used with J-Link, in the project root dir.


Build M4
--------

From the project root dir, execute:

::
  
  make -C m4/GCC_Project

This will generate a :code:`m4.bin` in m4/GCC_Project/output/bin which can be flashed. Note:- while compiling you will face a make error this is due to fact that the ARM toolchain path is different for everyone. To solve this
1. Open Vaman_LCD/m4/GCC_Project/config.mk
2. Change *export PROJ_ROOT=/home/hy/qorc-sdk* to your qorc-sdk path


Flash FPGA and M4
------------------

Put the development board into Flash Mode.

From the project root dir, execute:

::
  
  qfprog --port /dev/ttyACM0 --m4app m4/GCC_Project/output/bin/m4.bin --appfpga top.bin --mode m4-fpga
  
  
Ensure that you have connected a USB-UART adapter connected to the EOSS3 UART pins (IO_44/IO_45), and you have a terminal connected to that port.


LCD Display and Pygmy connections
----------------------------------

- LCD PIN <----> PYGMY
- LCD_D4  <---->  6
- LCD_D5  <---->  8
- LCD_D6  <---->  10
- LCD_D7  <---->  12
- LCD_RS  <---->  2
- LCD_EN  <---->  4
- LCD_RW  <---->  GND
