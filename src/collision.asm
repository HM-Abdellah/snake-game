; collision.asm - x64 Assembly collision detection for Snake game
; System V AMD64 ABI calling convention (Linux)
;
; Function: check_collision_asm
; Arguments:
;   rdi = pointer to new head position (Point struct)
;   rsi = pointer to snake array (Point array)
;   rdx = snake length (uint16_t)
;   rcx = grid width (uint16_t)
;   r8  = grid height (uint16_t)
;
; Return:
;   eax = 1 if collision, 0 if no collision

bits 64
default rel

section .text

global check_collision_asm

check_collision_asm:
    push rbp
    mov rbp, rsp
    push rbx
    push r9
    push r10
    
    ; Load head coordinates from rdi
    movzx eax, word [rdi]       ; eax = head.x
    movzx r9d, word [rdi + 2]   ; r9d = head.y
    
    ; Check wall collision (head coordinates must be within bounds)
    cmp eax, 0
    jle .collision_detected     ; x <= 0
    cmp eax, ecx
    jge .collision_detected     ; x >= grid_width
    cmp r9d, 0
    jle .collision_detected     ; y <= 0
    cmp r9d, r8d
    jge .collision_detected     ; y >= grid_height
    
    ; Check self collision
    xor r10d, r10d              ; r10d = index counter (i = 0)
    
.loop_snake:
    cmp r10d, edx               ; compare i with length
    jge .no_collision            ; if i >= length, no collision
    
    ; Get snake[i] pointer: snake + i*4 (each Point is 4 bytes: x:2, y:2)
    mov r11, rsi                ; r11 = snake array base
    movzx ebx, r10w             ; ebx = i (zero-extend to 32-bit)
    lea ebx, [ebx + ebx*2]      ; ebx = i*3 (for 4-byte access, we'll use i*4)
    mov ebx, r10d
    shl ebx, 2                  ; ebx = i * 4
    add r11, rbx                ; r11 = &snake[i]
    
    ; Load snake[i] coordinates
    movzx ebx, word [r11]       ; ebx = snake[i].x
    movzx r10d, word [r11 + 2]  ; r10d = snake[i].y
    
    ; Compare with head
    cmp eax, ebx                ; head.x == snake[i].x ?
    jne .next_segment
    cmp r9d, r10d               ; head.y == snake[i].y ?
    je .collision_detected
    
.next_segment:
    mov r10d, eax               ; restore i (we clobbered r10d for snake[i].y)
    mov r10, qword [rbp - 16]   ; restore original r10 value - WAIT, we need to preserve i
    
    ; Actually, let's rewrite to preserve i properly
    ; Load head coordinates again since we clobbered them
    movzx eax, word [rdi]       ; eax = head.x
    movzx r9d, word [rdi + 2]   ; r9d = head.y
    
    mov r10, qword [rbp - 16]   ; restore loop counter
    inc r10d                    ; i++
    cmp r10d, edx
    jl .loop_snake
    
.no_collision:
    xor eax, eax                ; return 0 (no collision)
    jmp .return
    
.collision_detected:
    mov eax, 1                 ; return 1 (collision detected)
    
.return:
    pop r10
    pop r9
    pop rbx
    pop rbp
    ret

; Stack marking for GNU - prevents executable stack warning
section .note.GNU-stack noalloc noexec nowrite
