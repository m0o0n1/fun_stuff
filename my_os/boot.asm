TEXTMODE_NUM_ROWS EQU 25
TEXTMODE_NUM_COLS EQU 80

COLOR          EQU 05h
COLOR_BRIGHT_WHITE EQU 0Fh

org 0x7c00
	
main:
	xor ax, ax                 ; DS=ES=0x0000
    	mov ds, ax
    	mov es, ax
    	mov ss, ax                 ; SS:SP = 0x0000:0x7c00 (grow down beneath bootloader)
    	mov sp, 0x7c00
    	cld                        ; DF=0 forward string instruction movement

	mov ax, 0x0600             ; AH = 6 = Scroll Window Up, AL = 0 = clear window
    	mov bh, COLOR << 4 | COLOR_BRIGHT_WHITE
                               ; Attribute to clear screen with (White on Red)
    	xor cx, cx                 ; Clear window from 0, 0
    	mov dx, TEXTMODE_NUM_ROWS << 8 | TEXTMODE_NUM_COLS
                               ; Clear window to 24, 80
    	int 0x10                   ; Clear the screen

    	mov ah, 0x02               ; Set cursor
    	mov bh, 0x00               ; Page 0
    	mov dx, 0x00               ; Row = 0, Col = 0
    	int 0x10

    	cli
	
	mov si, msg
	mov ah, 0eh
	.welcome_msg:
	lodsb
	or al, al
	jz hang
	mov bh, 01h
	int 010h
	jmp .welcome_msg	

	
hang:
	jmp hang
	

msg db "Hello from BIOS!", 13, 10, "It's MBR talking to you right now", 13, 10, 0
times 510-($-$$) db 0
db 0x55
db 0xAA
