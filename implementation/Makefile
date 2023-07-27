OPT=-O0

.PHONY: all clean delta_compress delta_decompress delta_asm vlq_encode vlq_decode vlq_asm golomb_encode golomb_decode golomb_asm golomb_static_encode golomb_static_decode golomb_static_asm deltadelta_compress deltadelta_decompress deltadelta_asm predictive_compress predictive_decompress predictive_asm

all: 
	@echo "make <version>"
	@echo "exit emulator by ctrl+a then x"
	@echo "available versions:"
	@echo "		delta_compress"
	@echo "		delta_decompress"
	@echo "		delta_asm"
	@echo "		vlq_encode"
	@echo "		vlq_decode"
	@echo "		vlq_asm"
	@echo "		golomb_encode"
	@echo "		golomb_decode"
	@echo "		golomb_asm"
	@echo "		golomb_static_encode"
	@echo "		golomb_static_decode"
	@echo "		golomb_static_asm"
	@echo "		deltadelta_compress"
	@echo "		deltadelta_decompress"
	@echo "		deltadelta_asm"
	@echo "		predictive_compress"
	@echo "		predictive_decompress"
	@echo "		predictive_asm"
	@echo "		clean"

delta_compress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g delta/compress.c -o delta_compress.o $(OPT)
	arm-none-eabi-ld -T linker.ld delta_compress.o startup.o -o delta_compress.elf
	arm-none-eabi-objcopy -O binary delta_compress.elf delta_compress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel delta_compress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

delta_decompress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g delta/decompress.c -o delta_decompress.o $(OPT)
	arm-none-eabi-ld -T linker.ld delta_decompress.o startup.o -o delta_decompress.elf
	arm-none-eabi-objcopy -O binary delta_decompress.elf delta_decompress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel delta_decompress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

delta_asm:
	@echo "compress:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g delta/compress_isolated.c -o compress_isolated.as -S -ffunction-sections $(OPT)
	wc -l compress_isolated.as
	@echo "decompress:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g delta/decompress_isolated.c -o decompress_isolated.as -S -ffunction-sections $(OPT)
	wc -l decompress_isolated.as

vlq_encode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g vlq/encode.c -o vlq_encode.o $(OPT)
	arm-none-eabi-ld -T linker.ld vlq_encode.o startup.o -o vlq_encode.elf
	arm-none-eabi-objcopy -O binary vlq_encode.elf vlq_encode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel vlq_encode.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

vlq_decode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g vlq/decode.c -o vlq_decode.o $(OPT)
	arm-none-eabi-ld -T linker.ld vlq_decode.o startup.o -o vlq_decode.elf
	arm-none-eabi-objcopy -O binary vlq_decode.elf vlq_decode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel vlq_decode.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

vlq_asm:
	@echo "encode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g vlq/encode_isolated.c -o vlq_encode_isolated.as -S -ffunction-sections $(OPT)
	wc -l vlq_encode_isolated.as
	@echo "decode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g vlq/decode_isolated.c -o vlq_decode_isolated.as -S -ffunction-sections $(OPT)
	wc -l vlq_decode_isolated.as

golomb_encode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb/encode.c -o golomb_encode.o $(OPT)
	arm-none-eabi-ld -T linker.ld golomb_encode.o startup.o -o golomb_encode.elf
	arm-none-eabi-objcopy -O binary golomb_encode.elf golomb_encode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel golomb_encode.bin -D log.txt -d exec > output.txt
	@echo "instruction count $(OPT):"
	wc -l log.txt

golomb_decode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb/decode.c -o golomb_decode.o $(OPT)
	arm-none-eabi-ld -T linker.ld golomb_decode.o startup.o -o golomb_decode.elf
	arm-none-eabi-objcopy -O binary golomb_decode.elf golomb_decode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel golomb_decode.bin -D log.txt -d exec > output.txt
	@echo "instruction count $(OPT):"
	wc -l log.txt

golomb_asm:
	@echo "encode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb/encode_isolated.c -o golomb_encode_isolated.as -S -ffunction-sections $(OPT)
	wc -l golomb_encode_isolated.as
	@echo "decode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb/decode_isolated.c -o golomb_decode_isolated.as -S -ffunction-sections $(OPT)
	wc -l golomb_decode_isolated.as

golomb_static_encode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb_staticDiv/encode.c -o golomb_encode.o $(OPT)
	arm-none-eabi-ld -T linker.ld golomb_encode.o startup.o -o golomb_encode.elf
	arm-none-eabi-objcopy -O binary golomb_encode.elf golomb_encode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel golomb_encode.bin -D log.txt -d exec > output.txt
	@echo "instruction count $(OPT):"
	wc -l log.txt

golomb_static_decode:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb_staticDiv/decode.c -o golomb_decode.o $(OPT)
	arm-none-eabi-ld -T linker.ld golomb_decode.o startup.o -o golomb_decode.elf
	arm-none-eabi-objcopy -O binary golomb_decode.elf golomb_decode.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel golomb_decode.bin -D log.txt -d exec > output.txt
	@echo "instruction count $(OPT):"
	wc -l log.txt

golomb_static_asm:
	@echo "encode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb_staticDiv/encode_isolated.c -o golomb_encode_isolated.as -S -ffunction-sections $(OPT)
	wc -l golomb_encode_isolated.as
	@echo "decode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g rice-golomb_staticDiv/decode_isolated.c -o golomb_decode_isolated.as -S -ffunction-sections $(OPT)
	wc -l golomb_decode_isolated.as

deltadelta_compress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g deltadelta/compress.c -o deltadelta_compress.o $(OPT)
	arm-none-eabi-ld -T linker.ld deltadelta_compress.o startup.o -o deltadelta_compress.elf
	arm-none-eabi-objcopy -O binary deltadelta_compress.elf deltadelta_compress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel deltadelta_compress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

deltadelta_decompress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g deltadelta/decompress.c -o deltadelta_decompress.o $(OPT)
	arm-none-eabi-ld -T linker.ld deltadelta_decompress.o startup.o -o deltadelta_decompress.elf
	arm-none-eabi-objcopy -O binary deltadelta_decompress.elf deltadelta_decompress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel deltadelta_decompress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

deltadelta_asm:
	@echo "encode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g deltadelta/compress_isolated.c -o compress_isolated.as -S -ffunction-sections $(OPT)
	wc -l compress_isolated.as
	@echo "decode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g deltadelta/decompress_isolated.c -o decompress_isolated.as -S -ffunction-sections $(OPT)
	wc -l decompress_isolated.as

predictive_compress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g predictive/compress.c -o predictive_compress.o $(OPT)
	arm-none-eabi-ld -T linker.ld predictive_compress.o startup.o -o predictive_compress.elf
	arm-none-eabi-objcopy -O binary predictive_compress.elf predictive_compress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel predictive_compress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

predictive_decompress:
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g predictive/decompress.c -o predictive_decompress.o $(OPT)
	arm-none-eabi-ld -T linker.ld predictive_decompress.o startup.o -o predictive_decompress.elf
	arm-none-eabi-objcopy -O binary predictive_decompress.elf predictive_decompress.bin
	@echo "ctrl+a then x to cancel"
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel predictive_decompress.bin -D log.txt -d exec > output.txt
	@echo "instruction count:"
	wc -l log.txt

predictive_asm:
	@echo "encode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g predictive/compress_isolated.c -o compress_isolated.as -S -ffunction-sections $(OPT)
	wc -l compress_isolated.as
	@echo "decode:"
	arm-none-eabi-as -mcpu=arm926ej-s -g startup.s -o startup.o
	arm-none-eabi-gcc -c -mcpu=arm926ej-s -g predictive/decompress_isolated.c -o decompress_isolated.as -S -ffunction-sections $(OPT)
	wc -l decompress_isolated.as

clean:
	rm -f *.o *.elf *.bin *.as output.txt log.txt