    ; initializing RAM locations 16 and 17 to the first 2 fibonacci numbers
    ldr 1
    str [16]
    str [17]

    str [31] ; putting first value on displays

loop:
    ; calculate next fibonacci number and store in RAM location 18
    ldr [16]
    add [17]
    str [18]

    ; putting value on the displays
    str [31]

    ; move the old largest fibonnaci number to RAM location 16
    ldr [17]
    str [16]

    ; move new fibonacci number to RAM location 17
    ldr [18]
    str [17]

    bne loop ; jump to beginning of loop
