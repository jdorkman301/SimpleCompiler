# SimpleCompiler
This was a school project I did at UMSL. It is a simple compiler written in C++ that takes the source `*.fs17` and outputs `out.asm` files that run on a virtual machine for most Linux-based distros

## Input Language Definition

### Keywords and some syntax
#### Keywords
The following keywords are reserved by the fs17 input language and cannot be used as variable names. Keywords are case-sensitive.
1. `Begin`
2. `End`
3. `Check` is used for conditional operations. Use `Begin` and `End` to make a block execute instead of one statement
4. `Loop` is used for looped conditionals. Use `Begin` and `End` to make a block execute instead of one statement
5. `Void`
6. `Var`
7. `Return`
8. `Input`
9. `Output`

#### Syntax
All data is 2-byte signed integer. Variable names can be up to but not exceed 8 characters in length. 
For example, `varname` is valid because it is only 7 characters in length but `nametoolong` is invalid because it is 11 characters in length.
1. Use commas to separate variables and a period end variable declarations                                   
* `Var x, y, z.`
* `Var x.`
2. End all other statements with a semicolon `;`
* `Input x;`
* `Output 3;`
3. Assignment values to variable using colon `:`. You can assign a single value or the result of an expression
* `x : 4;`
* `x : y - 2;`

##### Operators, Delimiters, etc              
* == >=  <=  != : ; +  -  *  / . & % (  ) , { } [ ]
* In our language, `%` (traditionally modulus) is the division operator.

##### Comments
Comments start and end with #               
* `#This is a comment# and this is not`

### Semantics
1. Basic semantics as in C - program executes sequentially from the beginning to the end, one statement at a time
2. Conditional statement is like the else-less if statement in C
3. Loop statement is like the while loop in C
4. Assignment evaluates the expression on the right and assigns to the ID on the left
5. Relational and arithmetical operators have the standard meaning
6. IO reads/prints a 2-byte signed integer
7. All data is 2-byte signed integer



## Example Programs

### Input 3 Variables, Output Reverse Order
```
Var x .                                            
  Begin                                            
    Var y .                                            
    Input x ;                                            
    Input y;                                            
      Begin                                            
        Var z .                                            
        Input z ;                                            
        Output z ;                                            
      End                                            
    Output y ;                                            
    Output x ;                                            
  End                                            
```

### If input is positive or zero, display 2. If negative, display 1. 
```
Begin
  Var x.
  Input x;
  Check [ x >= 0 ]
    Output 2;
  Check [ x < 0 ]
    Output 1;
End
```

### Simple echo input
```
Begin
  Var x.
  Input x;
  Output x;
End
```

