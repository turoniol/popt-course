nasm -f elf64 -g -F dwarf -o $1.o $1.asm

mkdir -p bin
mv $1.o ./bin

ld -o ./bin/${1}.out ./bin/$1.o