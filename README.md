# Program Assembler Project - C 

## So what is an Assembler?
Assembler is a program for converting instructions written in low-level assembly code into relocatable machine code (binary) and generating crucial information for the loader. It is necessary to perform such a translation for the computer to run any kind of program since computers only work with 1's and 0's.

## Types of Assembler
**• Single-Pass Assembler**: If an assembler does all this work in one scan then it is called a single-pass assembler.

**• Multiple-Pass Assembler:** If it does it in multiple scans then called a multiple-pass assembler. 

The type of assembler I'm using in this project is of the second kind, **A two-pass assembler**.

## Usage

To compile the project using the Makefile use

`> make`

To run the assembler program and translate an assembly (.asm) file into machine code use

`> assembler filename`

You could also pass multiple files separated by commas (,) using

`> assembler filename1, filename2, ...`

*Notice than only file name is required, do not pass the extension as an argument.
file1.as should be passed as file1 (without .as)*

After successfully running the assembler, the program should generate 3 files

•`.ob` - Object file

•`.ent`- Entires file

•`.ext` - Extern file

## Hardware

• CPU

• RAM with size of **1024 words**

•A word's size in memory is **12 bits**

Uses signed 2's complement arithmetic for integers (no support for real numbers)

#### Registers

• The CPU has 8 total registers **(r0, r1, ... , r7)** and a **PSW** (program status word) register

•  Each register size is **12-bits** 

## Instruction Structure

Every code instruction is encoded into distinguished words in memory by the following structure

| 9 8 7 6 |5	4|3	2|1	0|
| :-----------: | :------------: | :------------: | :------------: |
|Source Operand Addressing Method|Opcode|Destination Operand Addressing Method|A,R,E|

**Bits 1-0** (A,R,E) - Defines the type of encoding

• 00 - Absolute

• 01 - External

• 10 - Relocatable


**Bits 2-4** Encodes the number of the the Destination Operand Addressing Method

**Bits 9-11** Encodes the number of the the Source Operand Addressing Method

There are 3 kinds of Addressing Methods in this Imaginary language denoted by 5, 3, 1.

### Encoding each instruction word is done using Base64

|Value|Char|Value|Char|Value|Char|Value|Char|
| :------------: | :------------: | :------------: | :------------: |:------------: | :------------: |:------------: | :------------: |
|0|A|16|Q|32|g|48|w|
|1|B|17 |R|33|h|49|x|
|2|C|18|S|34|i|50|y|
|3|D|19|T|35|j|51|z|
|4|E|20|U|36|k|52|0|
|5|F|21|V|37|l|53|1|
|6|G|22|W|38|m|54|2|
|7|H|23|X|39|n|55|3|
|8|I|24|Y|40|o|56|4|
|9|J|25|Z|41|p|57|5|
|10|K|26|a|42|q|58|6|
|11|L|27|b|43|r|59|7|
|12|M|28|c|44|s|60|8|
|13|N|29|d|45|t|61|9|
|14|O|30|e|46|u|62|+|
|15|P|31|f|47|v|63|/|

Each word in memory is encoded to 2-digits in Base64 for example Aa, Az, /s, etc...

## Operands

There are 16 operands in our imaginary assembly language as follows

|Opcode   |Command   |
| :------------: | :------------: |
|0   |mov   |
|1   |cmp   |
|2   |add   |
|3   |sub   |
|4   |not   |
|5   |clr   |
|6   |lea   |
|7   |inc   |
|8   |dec   |
|9   |jmp   |
|10   |bne   |
|11   |red   |
|12   |prn   |
|13   |jsr   |
|14   |rts   |
|15   |stop   |

## Directives

A directive line of the following structure:
1. An optional label. e.g. `XYZ: `

2. A directive: `.data`, `.string`, `.entry`, `.extern`

3. Operands according to the type of the directive.

### **`.data`**
This instruction reserves memory in the data segment to store received integers for future use (it also increments the data counter and updates the symbol table). The `.data` directive accepts valid integers as arguments, separated by commas.
e.g. `XYZ: .data 7, -57, 17, 9`

### **`.string`**

This directive takes a string as an operand and saves it in the data segment. Each character is stored sequentially in the order they appear in the string, encoded using their ASCII values.

`e.g. STR: .string "abcdef"` is a valid directive.

### **`.entry`**

This directive records a given label name in the symbol table, allowing it to be recognized by other assembly files later and enabling them to reference it. 

e.g.
    ;file1.as
    .entry HELLO
    HELLO: add 1, @r1

### **`.extern`**

This directive takes a label name as a parameter, marking it as external (defined in a different file) and indicating that it will be referenced in the current file.

This way, the directive `.extern HELLO` in `file2.as` will match the `.entry` directive in the previous example.


## Run Examples

running the `make` command 

![make-command](https://github.com/Aviv13467/Maman14/blob/main/make-command.png?raw=true "make-command")

running the assembler program on file prog2.asm with `./assembler prog2` and display the content of the object, extern and entry files that were generated with the successful execution with the`cat prog2.ob`, `cat prog2.ext`, `cat prog2.ent` shell commands.

![successful-run](https://github.com/Aviv13467/Maman14/blob/main/successful-run.png?raw=true "successful-run")

running the assembler program on file prog1.asm with `./assembler prog1` and getting all the correpsonding errors for a failed execution. `.ob`,`.ext`,`.ent` files aren't generated in case of a failed execution.
![failed-run](https://github.com/Aviv13467/Maman14/blob/main/failed-run.png?raw=true "failed-run")

You can use the two files I've attached to the repository named `prog1.as` and `prog2.as` to try to program for yourself. 
