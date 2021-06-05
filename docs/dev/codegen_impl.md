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
> `imul` and `idiv` are signed operations, so a straight-forward optimization would be to check whether the operands are unsigned and if that is the case, to perform their unsigned alternatives (`mul` and `div` respectively)
</div>

<div id="third_note">
> there is not modular division instruction, but `div` (and `idiv`) store the remainder as well so we can get it from there
</div>
