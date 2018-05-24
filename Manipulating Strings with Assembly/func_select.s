    # 2493276919 Caleb Shere

	.section	.rodata
    .align 4
	
.Switch:                               # setting up the switch case
    .long .Fifty
    .long .FiftyOne
    .long .FiftyTwo
    .long .FiftyThree
    .long .FiftyFour
    .long .Default
lengthStr:	.string	     "first pstring length: %d, second pstring length: %d\n"
replaceScan:	.string      " %c %c"
replaceStr:	.string      "old char: %c, new char: %c, first string: %s, second string: %s\n"
scanNumberStr:      .string         "%d"
lengthAndStr:            .string         "length: %d, string: %s\n"
errorStr:    .string     "invalid option!\n"
compareResult:              .string             "compare result: %d\n"

	.text
.globl run_func 
	.type run_func, @function
run_func:
	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %eax
	cmpl $50, %eax
	jl error
	cmpl $54, %eax
	jg error
	subl $50, %eax
	jmp *.Switch (,%eax,4)

.Fifty:
    pushl 12(%ebp)                    # first pstring
    call pstrlen
    pushl %eax                        # first length located at -8(%ebp)
    pushl 16(%ebp)                    # second pstring
    call pstrlen
    pushl %eax                        # second length
    pushl -8(%ebp)                    # first length
    pushl $lengthStr
    call printf
    jmp done

.FiftyOne:
    subl $2, %esp
    leal -1(%ebp), %eax
    pushl %eax
    leal -2(%ebp), %eax
    pushl %eax
    pushl $replaceScan
    call scanf

    movl -1(%ebp), %eax		          # newChar
    pushl %eax
    movl -2(%ebp), %eax		          # oldChar
    pushl %eax			
    pushl 12(%ebp)                    # first pstring
    call replaceChar

    incl %eax                         # eax now points to beginning of string
    pushl %eax                        # first (changed) string located at -30(%ebp)
    movl -1(%ebp), %eax               # newChar
    pushl %eax
    movl -2(%ebp), %eax               # oldChar
    pushl %eax
    pushl 16(%ebp)                    # second pstring
    call replaceChar

    incl %eax                         # eax now points to beginning of string
    movl %eax, %edx
    pushl %edx                        # second string
    pushl -30(%ebp)                   # first string
    xorl %eax, %eax
    movl -1(%ebp), %eax               #newChar
    pushl %eax
    xorl %eax, %eax
    movl -2(%ebp), %eax               #oldChar
    pushl %eax
    pushl $replaceStr
    call printf  

    jmp done

.FiftyTwo:
    subl $8, %esp
    leal -4(%ebp), %eax
    pushl %eax
    pushl $scanNumberStr
    call scanf
    pushl %ebx                        # contents of ebx located at -20(%ebp)
    movl -4(%ebp), %ebx               # first num - begin index - stored in ebx
    leal -8(%ebp), %eax
    pushl %eax
    pushl $scanNumberStr
    call scanf

    movl -8(%ebp), %eax              # second num - end index
    pushl %eax
    pushl %ebx                       # first num - begin index
    pushl 16(%ebp)                   # second pstring (src)
    pushl 12(%ebp)                   # first pstring (dst)
    call pstrijcpy
    movl -20(%ebp), %ebx             # restore the contents of ebx

    pushl %eax                       # changed dst string located at -48(%ebp)
    call pstrlen
    movl %eax, %edx                  # store length of dst in edx
    movl -48(%ebp), %eax             # restore the dst string to eax

    # eax stores the address of the pstring, so increment it to get to the actual string

    incl %eax
    pushl %eax                       # the string parameter for dst 
    pushl %edx                       # the length (%d) parameter for dst
    pushl $lengthAndStr
    call printf

    pushl 16(%ebp)                   # src pstring
    call pstrlen
    movl %eax, %edx                  # store length of pstring in edx
    movl 16(%ebp), %eax
    incl %eax                        # now, eax points to beginning of string
    pushl %eax                       # string of src
    pushl %edx                       # length of src
    pushl $lengthAndStr
    call printf                  

    jmp done

.FiftyThree:
    pushl 12(%ebp)                   # first pstring
    call pstrlen
    pushl %eax                       # first length is located at -8(%ebp)

    pushl 12(%ebp)
    call swapCase                    # swapCase on first pstring
    incl %eax                        # eax now points to beginning of string
    pushl %eax                       # %s
    pushl -8(%ebp)                   # first length - %d
    pushl $lengthAndStr
    call printf

    pushl 16(%ebp)                   # second pstring
    call pstrlen
    pushl %eax                       # second length located at -32(%ebp)
    pushl 16(%ebp)
    call swapCase                    # swapCase on second pstring
    incl %eax                        # eax now points to beginning of string
    pushl %eax                       # %s
    pushl -32(%ebp)                  # second length - %d
    pushl $lengthAndStr
    call printf

    jmp done

.FiftyFour:
    subl $8, %esp
    leal -4(%ebp), %eax
    pushl %eax
    pushl $scanNumberStr
    call scanf
    pushl -4(%ebp)                  # first num located at -20(%ebp)

    leal -8(%ebp), %eax
    pushl %eax
    pushl $scanNumberStr
    call scanf

    pushl -8(%ebp)                  # second num
    pushl -20(%ebp)                 # first num
    pushl 16(%ebp)                  # second pstring
    pushl 12(%ebp)                  # first pstring
    call pstrijcmp

    pushl %eax                      # compare result in %eax
    pushl $compareResult
    call printf

    jmp done

.Default:
    jmp done

error:
    pushl $errorStr                 # "invalid option!\n"
    call printf

done:	
    movl %ebp, %esp
    popl %ebp
    ret
	