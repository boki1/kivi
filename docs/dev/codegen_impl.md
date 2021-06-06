### Code generation implementation notes

I. Create mapping
> Associate x86-64 asm instruction(or sequence of instructions) to each of the three_address_codes kivi

|Kivi IR 		    | 	x86-64|
----------------------------|------------------
|	Nop		    |	nop	|
|	Init		    |	mov (depends on the value) |
|	Add		    | 	add 	|
|	Negate		    |   neg (<a href="#first_note">note 1</a>) |
|	Multiply	    |   imul (<a href="#second_note">note 2</a>)|
|	Divide		    |   idiv (<a href="#second_note">note 2</a>) |
|	ModularDiv	    |	idiv  (<a href="#third_note">note 3</a>)|
|	Copy		    | 	mov 	|
|	Equals		    |   mov? 	|
|	IfNotZero	    | 	cmp 	|
|	FunctionCall	    | 	params, prologue, call, epilogue |
|	Return		    |	ret 	|

<div id="first_note">
> ✣ usually negate is used when substracting, so a straight-forward optimization would be to check whether addition follows and to directly perform subtraction (`sub`) if that is the case
</div>

<div id="second_note">
> `imul` and `idiv` are signed operations, so a straight-forward optimization would be to check whether the expected_actual_operands are unsigned and if that is the case, to perform their unsigned alternatives (`mul` and `div` respectively)
</div>

<div id="third_note">
> there is not modular division instruction, but `div` (and `idiv`) store the remainder as well so we can get it from there
</div>

# Example
-------------

KIVI IR:
```
fib:
init RO 0; f1
init R1 1; f2
init R2 0; fsum
init R3 0; counter

while_begin:
neg R3, R4; R4 = -R3
add R4, R4, 10; R4 = R4 + 10
ifnz R4, end

copy R1, R0
copy R2, R1
add R2, R1, R0
add R3, R3, 1
print R2
goto while_begin

end:
ret
```

Expected assembly:
```x86
fib: 			; (int, int)

push %rbp		; prologue
mov %rsp, %rbp		;

mov %r8, 0		; f1
mov %r9, 1		; f2
mov %r10, 0		; fsum
mov %r11, 0		; counter

while_begin:

mov %r12, %r11		; (-counter) + 10 == 0 ?
neg %r12		; continue :
add %r12, 10		; goto end
jnz end

mov %r8, %r9		; f1 = f2
mov %r9, %r10		; f2 = fsum
add %r10, %r9		; fsum = f1 + f2
add %r11, 1		; counter ++
print %r10		; do something

goto while_begin

end:			; epiloguep
mov %rbp, %rsp
pop %rbp
leave
ret

```
