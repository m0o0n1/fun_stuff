ASMC=nasm
EMU=qemu-system-i386

boot: boot.asm
	$(ASMC) boot.asm -f bin -o boot.bin

run: boot
	$(EMU) -hda boot.bin

clean:
	rm -vf *.bin
