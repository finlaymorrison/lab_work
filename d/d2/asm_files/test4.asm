    .global _start

_start:
    str, R0, [16]

loop:
    ldr, R0, [16]
    xor, R0, R0, [30]
    str, R0, [16]
    str, R0, [31]
    bne loop