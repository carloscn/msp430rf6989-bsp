# Test MSP430

* DOC: https://www.ti.com/product/MSP430FR6989
* DOC: https://www.ti.com/tool/MSP-EXP430FR6989
* BSP: https://www.ti.com/tool/MSPDRIVERLIB#downloads
* GCC: https://www.ti.com/tool/download/MSP430-GCC-OPENSOURCE/9.3.1.2
* Examples: https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP-EXP430FR6989/latest/index_FDS.html

## Toolchains:
* https://www.ti.com/tool/MSP430-GCC-OPENSOURCE#downloads
* Note1 : recommand the msp430-gcc-9.3.1.11
* Note2 : linux system, can use `curl -sk https://raw.githubusercontent.com/carloscn/script/master/down_tool_chains/down_toolchain_msp430-gcc-9.3.1.11_linux64.sh | bash`

## Programmer
* https://www.ti.com/tool/MSP430-FLASHER#downloads  (MSPFlasher_1.3.20)
* Download it and install it at `/opt/ti`

## Debugger
* `bash install_mspdebug.sh`

## Compile code
1. Config your cross compile tool path in `prj.cfg`
2. `source prj.cfg`
3. `make`

## Burn code
`bash flash.sh`

Note,
* stm32cubeprog can be supported by MAC-OS/WIN/Linux
* st-flash can be supported by WIN and Linux.

The program auto runs.