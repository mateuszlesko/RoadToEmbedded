# C basics concepts

## Scope of variables:
Every variable has a identificator, that has its scope in program.
If there are variables which has the same identifcator but other scopes, the variable in use is going to be that which was created in particular place.

There are 3 declared scopes:
- *file scope*: the variable can be used in entire file and every file which include this file.
- *block scope*: the variable can be used only in block where was created
- *function prototype* scope: variable was created as function header param, 

## Storage durration:
Every variable when it's creating, has not only memory address, value but also time to erase.
There are few storage durration for:
- *file scope* = the variable life is as long as entire program, and its value is intialized before execution - __static__
- *block scope* = the variable life is as long as block is executed.
### ! REMEMBER !
The scope and storage duration are separately concepts. Scope is assigned to identificators, storage duration is for objects