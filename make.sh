gcc -ffreestanding -m32 -g -c NovaOS-Core/RedBand/src/main.c -o NovaOS-Core/RedBand/binaries/redband.o

ld -m i386pep -T NovaOS-Core/Kernel/linker.ld -Ttext 0xC90000 NovaOS-Core/RedBand/binaries/redband.o NovaOS-Core/Network/binaries/iptcp.o NovaOS-Core/Binaries/graphics.o NovaOS-Core/Binaries/text.o -o NovaOS-Core/RedBand/Binaries/redband.elf
