    .global _start

_start:
    str, R0, [16]

loop:
    ldr, R0, [16]
    add, R0, R0, 2
    str, R0, [16]
    bne loop