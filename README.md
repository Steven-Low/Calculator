# Calculator
A simple syntax-directed calculator

NEW PATCH 3.0

Bugs Fix:
1) 2^3 give 2x^3 instead of 8.00
2) Simplify nodes in nodes does not valid
	- The 2nd version simplify function does not verify the difference in inner nodes.
	- Verifying its inner term's identical or not is inefficient and error prone.
	- Implement recursive function based on 2nd version's simplify method.
3) Remove remnants nodes like sfactor and trigfactor


New Features:
1) Enable basic trigonometric functions calculations. Ex: sin(cos(x))*cos(2*x)
2) Polynomial division now available. Ex: x/2 (simple division only, not x/(2*x + 1)
3) Double equations realization. Ex: x^2 = 0 ; 2*x = -1 addition ==> x^2 - 2*x + 1 (output)
4) Avoid syntax error and program can only terminate via Ctrl+C interrupt
5) New function "Compute": Ex: x^2 + sin(pi) compute 3 ==> 9 (output)
6) Special numeric characters. Ex: pi == 3.14159
