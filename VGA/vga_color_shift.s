# This program draws a repeating test pattern to a 320x240 VGA frame buffer

.equ VGA_ADDR_PORT,  0x11100000
.equ VGA_WRITE_PORT, 0x11140000

.global main
.type main, @function
main:
	# Global constant registers
	li   s2, VGA_ADDR_PORT
	li   s3, VGA_WRITE_PORT

	# Number of pixels to write (320x240)
	# This will be used to address which addresss in the framebuffer we're writing to
	li   t0, 76800 

write_pixel:
	# Decrement address
	addi t0, t0, -1
	# Use the last 8 bits as the pixel value to form a repeating pattern
	andi t1, t0, 0xFF

	# Write screen address to VGA_ADDR_PORT
	sw   t0, 0(s2)
	# Write pixel value to VGA_WRITE_PORT
	sw   t1, 0(s3)

	bne  t0, zero, write_pixel
    j end

end:
    j end

