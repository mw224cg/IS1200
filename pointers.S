 # pointers.S
 # By David Broman, 2015-09-14
 # Ported 2024/??/?? by W Szczerek (from MIPS to RISC-V)
 # This file is in the public domain


# Choose the syntax for RARS or DTEK-V board.
# The syntax for RARS is probably due to its MIPS heritage.
###################
# Macros for RARS #
###################
.macro	PUSH (%reg)
	addi	sp,sp,-4
	sw	%reg,0(sp) 
.end_macro

.macro	POP (%reg)
	lw	%reg,0(sp)
	addi	sp,sp,4
.end_macro
###################
# Macros for DTEK #
###################
#.macro	PUSH reg
#	addi sp,sp,-4
#	sw \reg,0(sp) 
#.endm

#.macro	POP reg
#	lw	\reg,0(sp)
#	addi	sp,sp,4
#.endm
###################

	.data
text1: 	  .asciz "This is a string."
text2:	  .asciz "Yet another thing."

	.align 2
list1: 	.space 80	#80 bytes
list2: 	.space 80
counter:.word  0

	.text
	.globl main
	.type main, @function
main:
	jal	work
stop:	j	stop

# function work()
# Loads text1, list1 and counter = 0 to registers a0, a1 a2
# Calls the function copycodes()
# Repeates for text2, list2
work:
	PUSH	ra		#PUSH ra to stack
	la 	a0,text1	#Set a0 to adress to the start of the string "text1" 
	la	a1,list1	#Set a1 to adress of "list1", size 80 bytes
	la	a2,counter	#Set a2 to adress of variable counter
	jal	copycodes	#Jump to function copycodes()
	
	la 	a0,text2	#Set a0 to adress to the start of the string "text2" 
	la	a1,list2	#Set a1 to adress of "list2", size 80 bytes
	la	a2,counter	#Set a2 to adress of variable counter
	jal	copycodes	#Jump to function copycodes()
	POP	ra		
	jr	ra
	
	
# function copycodes()
# Reads byte from a0 and writes 4 bytes (ASCII) to a1
# Repeats until NULL
# Stores  and updates a counter for each iteration
copycodes:
loop:
	lb	t0,0(a0)	#load byte from start of the adress pointed by a0 (text)
	beqz	t0,done		#if the byte is 0 --> end function
	sw	t0,0(a1)	#store word (4byte) to adress (list)

	addi	a0,a0,1		#move stackpointers to next spot
	addi	a1,a1,4
	
	lw	t1,0(a2)	#read counter to t1	
	addi	t1,t1,1		#counter +1
	sw	t1,0(a2)	#store counter to adress of counter
	j	loop
done:
	jr	ra
		







