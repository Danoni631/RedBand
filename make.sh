gcc -ffreestanding -m32 -g -c src/main.c -o binaries/redband.o

ld -m i386pep -T linker.ld -Ttext 0xC90000 "Add/Your/FilesTo/Link/here.txt" -o "binaires/redband.elf"
