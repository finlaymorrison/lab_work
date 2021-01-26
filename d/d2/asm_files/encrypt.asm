    .global _start

_start:
loop:
    LDR R0, [30]
    XOR R0, R0, 10
    STR R0, [31]
    LDR 10
    JNE 0