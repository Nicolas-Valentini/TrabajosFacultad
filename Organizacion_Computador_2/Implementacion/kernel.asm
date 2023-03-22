; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TALLER System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"


global start


; COMPLETAR - Agreguen declaraciones extern según vayan necesitando
extern GDT_DESC
extern gdt  
extern screen_draw_layout
extern IDT_DESC 
extern pic_enable
extern pic_finish1
extern pic_reset
extern idt_init
extern mmu_init
extern mmu_init_kernel_dir
extern mmu_unmap_page
extern mmu_map_page 
extern copy_page
extern mmu_init_task_dir
extern tss_init
extern sched_init
extern task_init

; COMPLETAR - Definan correctamente estas constantes cuando las necesiten
%define CS_RING_0_SEL  0b1000
%define DS_RING_0_SEL  0x18
%define TASK_IDLE_SEL (12 << 3)
%define TASK_INITIAL_SEL (11 << 3)

BITS 16
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; COMPLETAR - Deshabilitar interrupciones

    CLI


    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font




    ; COMPLETAR - Imprimir mensaje de bienvenida - MODO REAL
    ; (revisar las funciones definidas en print.mac y los mensajes se encuentran en la
    ; sección de datos)
    print_text_rm start_rm_msg, start_rm_len, 0xF, 0, 0


    

    ; COMPLETAR - Habilitar A20
    ; (revisar las funciones definidas en a20.asm)
    call A20_enable

       
    ; COMPLETAR - Cargar la GDT
     
    LGDT [GDT_DESC]


 
    MOV eax, CR0
    OR EAX, 0x1
    MOV CR0, EAX

    

    

    ; COMPLETAR - Setear el bit PE del registro CR0

    ; COMPLETAR - Saltar a modo protegido (far jump)
    ; (recuerden que un far jmp se especifica como jmp CS_selector:address)
    ; Pueden usar la constante CS_RING_0_SEL definida en este archivo

    

    jmp CS_RING_0_SEL:modo_protegido

BITS 32
modo_protegido:
    ; COMPLETAR - A partir de aca, todo el codigo se va a ejectutar en modo protegido
    ; Establecer selectores de segmentos DS, ES, GS, FS y SS en el segmento de datos de nivel 0
    
    ; Pueden usar la constante DS_RING_0_SEL definida en este archivo
    MOV AX, DS_RING_0_SEL
    mov DS, AX
    mov ES, AX
    MOV SS, AX
    MOV FS, AX 
    MOV GS, AX
    
    ; COMPLETAR - Establecer el tope y la base de la pila
    MOV EBP, 0x25000
    MOV ESP, EBP

   ; COMPLETAR - Imprimir mensaje de bienvenida - MODO PROTEGIDO
    print_text_pm start_pm_msg, start_pm_len, 0xF, 5, 0

    ; COMPLETAR - Inicializar pantalla

    call screen_draw_layout

    LIDT [IDT_DESC]

    call pic_reset
    call pic_enable

   

    call idt_init

    call mmu_init 
  
    call mmu_init_kernel_dir
    

    
    mov cr3, eax


    mov eax, cr0

    
    or eax, 0x80000000
    
    mov cr0, eax

    ; push 0x1
    ;push 0x500000
    ;push 0x1000000
    ;mov eax, cr3
    ;push eax
    ;call mmu_map_page 
    ;xchg bx,bx ; Magic Breakpoint
    ;push 0x1000000
    ;mov eax, cr3
    ;push eax
    ;call mmu_unmap_page
    ;xchg bx,bx ; Magic Breakpoint
    ;mov DWORD [0x100000], 30h
    ;push 0x100000
    ;push 0x101000
    ;call copy_page
    
    ;xchg bx, bx
    ;mov eax, [0x101000]
    ;mov eax, cr3
    ;push eax
    ;push 0x18000
    ;add esp, 4
    ;call mmu_init_task_dir
    ;mov cr3, eax
    ;xchg bx,bx ; Magic Breakpoint


    call tss_init

    call sched_init

    call task_init


    mov ax, TASK_INITIAL_SEL
    ltr ax
    xchg bx,bx 
    jmp TASK_IDLE_SEL:0


   



 



    sti 



    
    
   
    ; Ciclar infinitamente 
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
