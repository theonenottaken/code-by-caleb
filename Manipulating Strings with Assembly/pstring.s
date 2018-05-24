	# 2493276919 Caleb Shere

	.section	.rodata
	.align 4
errorStr:		.string 		"invalid input!\n"
	.text
.globl pstrlen
	.type pstrlen, @function
pstrlen:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ecx						# get pstring parameter
	xorl %eax, %eax							# clear eax to avoid confusion
	movb (%ecx), %al 						# the char at the first address of the pstring is the length
	movl %ebp, %esp
	popl %ebp
	ret

.globl replaceChar
	.type replaceChar, @function
replaceChar:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %edx						# get pstring parameter
    xorl %ecx, %ecx
	movb (%edx), %cl						# store length of string in cl (counter)
	incl %edx								# increment address to beginning of string
	movb 12(%ebp), %ch						# get oldChar, store in ch
	xorl %eax, %eax							# clear eax
	movb 16(%ebp), %al						# get newChar and store it in %al
	
	repLoop:
	    movb (%edx), %ah					# move the current char into ah to be compared
	    cmpb %ah, %ch 						# compare current char with oldChar
	    jne notEqual
	    movb %al, (%edx)					# if equal, replace with newChar
	    
	notEqual:
	    incl %edx							# move on to next char in string
	    decb %cl 							# decrement counter
	    cmpb $0, %cl
 	    jg repLoop							# if greater than 0, enter loop again

	movl 8(%ebp), %eax						# retrieve and return address of pstring
	movl %ebp, %esp
	popl %ebp
	ret

.globl pstrijcpy
	.type pstrijcpy, @function
pstrijcpy:
	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %edx						# first pstring, dst
	pushl %edx
	call pstrlen							# get length of first pstring. length now in eax
	movb 16(%ebp), %cl 						# get begin index
	movb 20(%ebp), %ch						# get end index
	decl %eax								# decrement the length to line up with the indices

	# make sure that the begin and end indices lie within the bounds of the first string 
	cmpb %al, %cl
	jg error1
	cmpb %al, %ch
	jg error1

	movl 12(%ebp), %edx						# second pstring, src
	pushl %edx
	call pstrlen							# get length of second pstring, length now in eax
	movb 16(%ebp), %cl 						# get begin index - ecx might have been overwritten
	movb 20(%ebp), %ch 						# end index
	decl %eax

	# make sure that the begin and end indices lie within the bounds of the second string 
	cmpb %al, %cl
	jg error1
	cmpb %al, %ch
	jg error1

	# make sure the begin and end indices are not negative, and that end is greater than begin 
	cmpb $0, %cl
	jl error1
	cmpb $0, %ch
	jl error1
	cmpb %cl, %ch
	jl error1

	movl 8(%ebp), %edx      				# get dst
	incl %edx								# edx now points to dst string
	movl 12(%ebp), %eax   					# get src
	incl %eax								# eax now points to src string
	pushl %edx
	xorl %edx, %edx
	movb %cl, %dl
	addl %edx, %eax							# eax now points to ith character of src string
	popl %edx
	pushl %eax
	xorl %eax, %eax
	movb %cl, %al
	addl %eax, %edx							# edx now points to ith character of dst string
	popl %eax

	subb %cl, %ch 							# Store the difference of begin index and end index
	movb %ch, %cl
	incb %cl 								# add 1 to count because the substring includes both endpoints

	cpyLoop:
		movb (%eax), %ch 					# move the current char from src...
		movb %ch, (%edx) 					# ...to dst
		incl %edx						 	# increment dst pointer to next char
		incl %eax							# increment src pointer to next char  
		decb %cl 							# decrement counter
		cmpb $0, %cl 	
		jg cpyLoop	 						# if greater than 0, enter loop again
	jmp end

	error1:
		pushl $errorStr 					# "invalid input!\n"
		call printf

	end:

		movl 8(%ebp), %eax 					# whether it has been altered or not, retrieve and return the address of dst
		xorl %ecx, %ecx
		movl %ebp, %esp
		popl %ebp
		ret

.globl swapCase
	.type swapCase, @function
swapCase:
	pushl %ebp
	movl %esp, %ebp

	pushl 8(%ebp)							# get length of pstring
	call pstrlen
	xorl %ecx, %ecx
	movb %al, %cl 							# store the length in cl 
	movl 8(%ebp), %edx
	incl %edx 								# edx now points to beginning of the string 

	swapLoop:
		movb (%edx), %al 					# move current char into al for comparing and manipulating
		cmpb $'A', %al
		jl continue 						# not a letter

		cmpb $'Z', %al 						
		jle capital 						# somewhere in between A and Z. It's a capital letter

		cmpb $'a', %al
		jl continue 						# between Z and a - not a letter

		cmp $'z', %al 						
		jle lowercase 						# between a and z - lowercase letter
		jmp continue 						# greater than 'z' - not a letter

		capital:
			addb $32, %al 					# convert from capital to lowercase
			movb %al, (%edx) 				# insert into string 
			jmp continue

		lowercase:
			subb $32, %al 					# convert from lowercase to capital
			movb %al, (%edx) 				# insert into string 

		continue:
			incl %edx 						# increment string pointer to next char in string 
			decb %cl 						# decrement counter
			cmpb $0, %cl 				
			jg swapLoop 					# if greater than 0, enter loop again

	movl 8(%ebp), %eax 						# retrieve and return the address of the pstring
	movl %ebp, %esp
	popl %ebp
	ret

.globl pstrijcmp
	.type pstrijcmp, @function
pstrijcmp:
	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %edx		     			# first pstring, dst
	pushl %edx
	call pstrlen 							# get length of dst string, in eax 
	movb 16(%ebp), %cl 		 				# begin index
	movb 20(%ebp), %ch						# end index
	decl %eax								# decrement the length to line up with the indices

	# make sure that the begin and end indices lie within the bounds of the first string
	cmpb %al, %cl
	jg error2
	cmpb %al, %ch
	jg error2

	movl 12(%ebp), %edx						# second pstring, src
	pushl %edx
	call pstrlen 							# get length of src string, in eax
	movb 16(%ebp), %cl 						# begin index
	movb 20(%ebp), %ch 						# end index
	decl %eax 								# decrement the length to line up with the indices

	# make sure that the begin and end indices lie within the bounds of the second string
	cmpb %al, %cl
	jg error2
	cmpb %al, %ch
	jg error2

	# make sure the begin and end indices are not negative, and that end is greater than begin
	cmpb $0, %cl
	jl error2
	cmpb $0, %ch
	jl error2
	cmpb %cl, %ch
	jl error2

	movl 8(%ebp), %edx
	incl %edx								# edx now points to first string
	movl 12(%ebp), %eax
	incl %eax								# eax now points to second string
	pushl %edx
	xorl %edx, %edx
	movb %cl, %dl
	addl %edx, %eax							# eax now points to ith character of second string
	popl %edx
	pushl %eax
	xorl %eax, %eax
	movb %cl, %al
	addl %eax, %edx							# edx now points to ith character of first string
	popl %eax

	subb %cl, %ch 							# Store the difference of begin index and end index
	movb %ch, %cl
	incb %cl 								# add 1 to count because the substring includes both endpoints

	cmpLoop:
		movb (%edx), %ch 					# compare the current char in dst...
		cmp (%eax), %ch 					# ...with the current char in src
		jg first  							# dst is greater
		jl second 							# src is greater
											# the current chars are equal...
		incl %edx 							# move dst pointer to next char 							
		incl %eax 							# move src pointer to next char  
		decb %cl 							# decrement counter	 
		cmpb $0, %cl 
		jg cmpLoop							# if greater than 0, enter loop again and check the next chars 

		movl $0, %eax 						# otherwise, the substrings are equal. Return 0
		jmp done

		first:
			movl $1, %eax 					# first is greater. Return 1
			jmp done
		second:
			movl $-1, %eax 					# second is greater. Return -1
			jmp done

	error2:
		pushl $errorStr 					# "invalid input!\n"
		call printf
		movl $-2, %eax 						# There was an invalid input. Return -2

	done:
		movl %ebp, %esp
		popl %ebp
		ret













	    	