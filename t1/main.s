.syntax unified
.cpu cortex-m3
.thumb

.equ STACKINIT, 0x20002000

.text
.global _start
    .word STACKINIT         @ stack pointer
    .word _start+1          @ reset
    .word _nmi_handler+1    @ vectors
    .word _hard_fault+1     
    .word _memory_fault+1
    .word _bus_fault+1
    .word _usage_fault+1

_start:
    mov  r0,#5
    adr  r1,value
    ldr  r2,[r1]
    add  r1,r2,r0
    push {r1}
    mov  r1,#0
    pop  {r1}
    blx  _start     @ usage fault

.ascii "example"    @ data in code section

.align 0x0
_dummy:
_nmi_handler:
_hard_fault:
_memory_fault:
_bus_fault:
_usage_fault:
    add r0,1
    add r1,1
    b _dummy 

.align 0x0
value: .word 0x11223344 

.end

