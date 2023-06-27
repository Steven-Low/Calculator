# Calculator

# SETUP
1) Install flex and bison.
2) Download the calculator files in any directory.
3) Open the command prompt in that directory.
4) Run commands:
   - flex polynomial.l
   - bison -d polynomial.y
   - gcc lex.yy.c polynomial.tab.c 
5) The executable file will be generated as 'a' (you are ready to go!)

Program executing image:
<img width="674" alt="image" src="https://github.com/Steven-Low/Calculator/assets/106484271/1d2ee729-0c7c-4553-a0a5-ff5be61adcce">


# DESCRIPTION
Syntax-directed calculator is a command-line program to perform arithmetic operations and mathematical techniques on polynomials. It is built via lex and yacc files and requires gcc to compile.

``` [equation] [functions] \n```
``` [equation] ; [equation] [functions] (for addition) \n``` 
``` (2*x + 1)^3 solve ```

# FUNCTIONS
1) print
2) simplify
3) addition
4) derivative
5) integrate
6) solve
7) compute
   
   

   
