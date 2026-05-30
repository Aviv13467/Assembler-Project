; file ps.as
    .entry LENGTH
    .extern W
    .entry W
MAIN: mov @r3   ,LENGTH
@r1: jmp L1
    .entry a, b
test: .entry hello
    TEST2: .data ,23
TEST3: .data 34,,
    TEST4: .data hello,3
cmprs @r1, @r5
    .extern W, K
    .extern .data
cmp @r1
    cmp @r1, @r2 @r3
mov @r1, 34
cmp @r8, @r2
    sub @r1, 23
lea 23, 23
not
jsr @r3,5
inc Q
Q: jmp W
Q: jmp K
bne Q
prn -5
bne W
sub @r1, @r4
    .extern LENGTH
    bne L3
L1: inc K
    .entry LOOP
jmp W
END: stop
STR: .string “abcdef”
LENGTH: .data 6,-9,15
K: .data 22
    .extern L3
    .entry L3
