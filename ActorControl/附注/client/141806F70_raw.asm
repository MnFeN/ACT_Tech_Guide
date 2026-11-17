0000000141806F70 mov     rax, rsp
0000000141806F73 mov     [rax+8], rbx
0000000141806F77 mov     [rax+10h], rsi
0000000141806F7B mov     [rax+18h], rdi
0000000141806F7F mov     [rax+20h], r12
0000000141806F83 push    rbp
0000000141806F84 push    r14
0000000141806F86 push    r15
0000000141806F88 lea     rbp, [rax-28h]
0000000141806F8C sub     rsp, 110h
0000000141806F93 movzx   r14d, byte ptr [rcx+0F2h]
0000000141806F9B mov     rbx, rcx
0000000141806F9E movzx   r15d, byte ptr [rcx+0F8h]
0000000141806FA6 mov     dl, 5; a2
0000000141806FA8 mov     r12d, [rcx+0F4h]
0000000141806FAF movaps  xmmword ptr [rax-28h], xmm6
0000000141806FB3 movss   xmm6, dword ptr [rcx+0B0h]
0000000141806FBB movaps  xmmword ptr [rax-58h], xmm9
0000000141806FC0 movss   xmm9, dword ptr [rcx+0A8h]
0000000141806FC9 movaps  xmmword ptr [rax-78h], xmm11
0000000141806FCE movss   xmm11, dword ptr [rcx+0A4h]
0000000141806FD7 movaps  xmmword ptr [rax-88h], xmm12
0000000141806FDF movss   xmm12, dword ptr [rcx+0A0h]
0000000141806FE8 mov     rcx, [rcx+0B8h]; a1
0000000141806FEF call    sub_1418168A0
0000000141806FF4 mov     rdi, [rbx+0B8h]
0000000141806FFB movzx   eax, byte ptr [rdi+410h]
0000000141807002 dec     al
0000000141807004 cmp     al, 2
0000000141807006 ja      short loc_141807025
0000000141807008 mov     rcx, rdi; a1
000000014180700B call    sub_14181CD70
0000000141807010 cmp     byte ptr [rax+66h], 0
0000000141807014 jz      short loc_14180701E
0000000141807016 mov     rcx, rax; a1
0000000141807019 call    sub_14180A850
000000014180701E mov     byte ptr [rdi+410h], 0
0000000141807025 mov     ecx, r14d; a1
0000000141807028 call    EXD__GimmickJump__Row_14083D100
000000014180702D mov     rsi, rax
0000000141807030 test    rax, rax
0000000141807033 jz      loc_14180744D
0000000141807039 and     byte ptr [rbx+0F8h], 0F7h
0000000141807040 and     r15b, 8
0000000141807044 or      [rbx+0F8h], r15b
000000014180704B movss   dword ptr [rbx+0A0h], xmm12
0000000141807054 movss   dword ptr [rbx+0A4h], xmm11
000000014180705D movss   dword ptr [rbx+0A8h], xmm9
0000000141807066 mov     rcx, [rbx+0B8h]
000000014180706D movaps  [rsp+120h+var_48+8], xmm8
0000000141807076 movaps  [rsp+120h+var_68+8], xmm10
000000014180707F movss   dword ptr [rbx+0B0h], xmm6
0000000141807087 movaps  [rsp+120h+var_98+8], xmm13
0000000141807090 mov     [rbx+0F2h], r14b
0000000141807097 mov     [rbx+0F4h], r12d
000000014180709E mov     rcx, [rcx+3E0h]; self
00000001418070A5 movaps  [rsp+120h+var_A8+8], xmm14
00000001418070AE movaps  [rsp+120h+var_B8+8], xmm15
00000001418070B4 call    Client__Game__Object__GameObject__GetPosition
00000001418070B9 mov     ecx, r14d; a1
00000001418070BC movss   xmm10, dword ptr [rax+4]
00000001418070C2 call    EXD__GimmickJump__Row_14083D100
00000001418070C7 movss   xmm15, cs:flt_14211BF44
00000001418070D0 mov     rcx, rax
00000001418070D3 movss   xmm13, cs:easingFactor
00000001418070DC xorps   xmm8, xmm8
00000001418070E0 test    rax, rax
00000001418070E3 jnz     short loc_1418070EA
00000001418070E5 xorps   xmm6, xmm6
00000001418070E8 jmp     short loc_141807113
00000001418070EA cmp     word ptr [rcx+0Ch], 0
00000001418070EF movzx   eax, word ptr [rax+0Ah]
00000001418070F3 movd    xmm6, eax
00000001418070F7 cvtdq2ps xmm6, xmm6
00000001418070FA divss   xmm6, xmm15
00000001418070FF jz      short loc_141807113
0000000141807101 cmp     word ptr [rcx+0Eh], 0
0000000141807106 jz      short loc_141807113
0000000141807108 movaps  xmm0, xmm13
000000014180710C maxss   xmm0, xmm6
0000000141807110 movaps  xmm6, xmm0
0000000141807113 comiss  xmm11, xmm10
0000000141807117 movaps  [rsp+120h+var_38+8], xmm7
000000014180711F movaps  xmm7, xmm11
0000000141807123 subss   xmm7, xmm10
0000000141807128 jbe     short loc_14180712E
000000014180712A addss   xmm6, xmm7
000000014180712E movss   xmm1, dword ptr [rbx+0B0h]
0000000141807136 ucomiss xmm1, xmm8
000000014180713A jp      short loc_141807147
000000014180713C jnz     short loc_141807147
000000014180713E call    sub_140863D80
0000000141807143 movss   xmm1, dword ptr [rax]
0000000141807147 mulss   xmm1, cs:flt_14211C01C
000000014180714F xorps   xmm0, xmm0
0000000141807152 mulss   xmm1, xmm6
0000000141807156 ucomiss xmm0, xmm1
0000000141807159 ja      short loc_141807166
000000014180715B xorps   xmm14, xmm14
000000014180715F sqrtss  xmm14, xmm1
0000000141807164 jmp     short loc_141807172
0000000141807166 movaps  xmm0, xmm1; X
0000000141807169 call    sqrtf
000000014180716E movaps  xmm14, xmm0
0000000141807172 mov     ecx, r14d; a1
0000000141807175 call    EXD__GimmickJump__Row_14083D100
000000014180717A test    rax, rax
000000014180717D jnz     short loc_141807187
000000014180717F xorps   xmm6, xmm6
0000000141807182 jmp     loc_141807239
0000000141807187 mov     ecx, r14d; a1
000000014180718A call    EXD__GimmickJump__Row_14083D100
000000014180718F mov     rcx, rax
0000000141807192 test    rax, rax
0000000141807195 jnz     short loc_14180719C
0000000141807197 xorps   xmm1, xmm1
000000014180719A jmp     short loc_1418071C3
000000014180719C cmp     word ptr [rcx+0Ch], 0
00000001418071A1 movzx   eax, word ptr [rax+0Ah]
00000001418071A5 movd    xmm1, eax
00000001418071A9 cvtdq2ps xmm1, xmm1
00000001418071AC divss   xmm1, xmm15
00000001418071B1 jz      short loc_1418071C3
00000001418071B3 cmp     word ptr [rcx+0Eh], 0
00000001418071B8 jz      short loc_1418071C3
00000001418071BA maxss   xmm13, xmm1
00000001418071BF movaps  xmm1, xmm13
00000001418071C3 comiss  xmm11, xmm10
00000001418071C7 jbe     short loc_1418071CD
00000001418071C9 addss   xmm1, xmm7
00000001418071CD movaps  xmm0, xmm1
00000001418071D0 movaps  xmm7, xmm11
00000001418071D4 mulss   xmm1, cs:radius
00000001418071DC addss   xmm0, xmm10
00000001418071E1 subss   xmm7, xmm0
00000001418071E5 xorps   xmm0, xmm0
00000001418071E8 ucomiss xmm0, xmm1
00000001418071EB ja      short loc_1418071F6
00000001418071ED xorps   xmm6, xmm6
00000001418071F0 sqrtss  xmm6, xmm1
00000001418071F4 jmp     short loc_141807201
00000001418071F6 movaps  xmm0, xmm1; X
00000001418071F9 call    sqrtf
00000001418071FE movaps  xmm6, xmm0
0000000141807201 xorps   xmm6, cs:xmmword_14211C100
0000000141807208 addss   xmm7, xmm7
000000014180720C divss   xmm6, cs:flt_1421DCF10
0000000141807214 divss   xmm7, cs:flt_1421DCF10
000000014180721C xorps   xmm1, xmm1
000000014180721F ucomiss xmm1, xmm7
0000000141807222 ja      short loc_14180722D
0000000141807224 xorps   xmm0, xmm0
0000000141807227 sqrtss  xmm0, xmm7
000000014180722B jmp     short loc_141807235
000000014180722D movaps  xmm0, xmm7; X
0000000141807230 call    sqrtf
0000000141807235 addss   xmm6, xmm0
0000000141807239 cmp     word ptr [rsi+0Ch], 0
000000014180723E maxss   xmm8, xmm6
0000000141807243 movaps  xmm13, [rsp+120h+var_98+8]
000000014180724C movaps  xmm10, [rsp+120h+var_68+8]
0000000141807255 movaps  xmm7, [rsp+120h+var_38+8]
000000014180725D jz      short loc_1418072BB
000000014180725F cmp     word ptr [rsi+0Eh], 0
0000000141807264 jz      short loc_1418072BB
0000000141807266 mov     rcx, [rbx+0B8h]
000000014180726D mov     rcx, [rcx+3E0h]; self
0000000141807274 call    Client__Game__Object__GameObject__GetPosition
0000000141807279 movaps  xmm0, xmm12
000000014180727D movaps  xmm1, xmm9
0000000141807281 subss   xmm0, dword ptr [rax]
0000000141807285 subss   xmm1, dword ptr [rax+8]
000000014180728A mulss   xmm0, xmm0
000000014180728E mulss   xmm1, xmm1
0000000141807292 addss   xmm1, xmm0
0000000141807296 xorps   xmm0, xmm0
0000000141807299 ucomiss xmm0, xmm1
000000014180729C ja      short loc_1418072A7
000000014180729E xorps   xmm0, xmm0
00000001418072A1 sqrtss  xmm0, xmm1
00000001418072A5 jmp     short loc_1418072AF
00000001418072A7 movaps  xmm0, xmm1; X
00000001418072AA call    sqrtf
00000001418072AF mov     edx, r14d
00000001418072B2 call    sub_1417FE8E0
00000001418072B7 movaps  xmm8, xmm0
00000001418072BB movaps  xmm2, xmm14
00000001418072BF mov     edx, 3
00000001418072C4 mov     rcx, rbx
00000001418072C7 call    sub_141805630
00000001418072CC mov     rdi, [rbx+0B8h]
00000001418072D3 movaps  xmm14, [rsp+120h+var_A8+8]
00000001418072DC movss   [rsp+120h+position], xmm12
00000001418072E3 movss   [rsp+120h+var_FC], xmm11
00000001418072EA movss   dword ptr [rsp+120h+var_F8], xmm9
00000001418072F1 mov     dword ptr [rsp+120h+var_F8+4], 0
00000001418072F9 test    rdi, rdi
00000001418072FC jz      short loc_141807334
00000001418072FE mov     rdi, [rdi+3E0h]
0000000141807305 test    rdi, rdi
0000000141807308 jz      short loc_141807334
000000014180730A test    byte ptr cs:qword_142AA895B, 4
0000000141807311 jz      short loc_141807323
0000000141807313 lea     rcx, word_142AA7678
000000014180731A call    sub_1406056C0
000000014180731F test    al, al
0000000141807321 jz      short loc_141807334
0000000141807323 xor     r8d, r8d; a3
0000000141807326 xor     edx, edx; a2
0000000141807328 mov     rcx, rdi; a1
000000014180732B call    sub_140897A40
0000000141807330 test    al, al
0000000141807332 jnz     short loc_14180737A
0000000141807334 mov     rcx, [rbx+0B8h]
000000014180733B mov     rcx, [rcx+3E0h]; self
0000000141807342 call    Client__Game__Object__GameObject__GetPosition
0000000141807347 movss   xmm0, cs:dword_142178D10
000000014180734F subss   xmm9, dword ptr [rax+8]
0000000141807355 subss   xmm12, dword ptr [rax]
000000014180735A mulss   xmm9, xmm9
000000014180735F mulss   xmm12, xmm12
0000000141807364 addss   xmm9, xmm12
0000000141807369 comiss  xmm0, xmm9
000000014180736D jb      short loc_14180737A
000000014180736F movss   xmm0, dword ptr [rax+4]
0000000141807374 movss   [rsp+120h+var_FC], xmm0
000000014180737A movaps  xmm1, cs:xmmword_14214B820
0000000141807381 lea     rax, off_142178A60
0000000141807388 mov     qword ptr [rsp+120h+options], rax
000000014180738D xor     eax, eax
000000014180738F mov     [rsp+120h+var_D0], rax
0000000141807394 mov     [rsp+120h+var_C8], rax
0000000141807399 mov     qword ptr [rsp+120h+var_C0], rax
000000014180739E mov     byte ptr [rsp+120h+var_B8], al
00000001418073A2 movzx   eax, word ptr [rsi+0Ch]
00000001418073A6 mov     dword ptr [rsp+120h+var_E8], 0BF800000h
00000001418073AE mov     dword ptr [rsp+120h+var_E8+4], 0BF800000h
00000001418073B6 movaps  [rsp+120h+var_E8+8], xmm1
00000001418073BB test    ax, ax
00000001418073BE jz      short loc_1418073EF
00000001418073C0 movzx   ecx, word ptr [rsi+0Eh]
00000001418073C4 test    cx, cx
00000001418073C7 jz      short loc_1418073EF
00000001418073C9 movd    xmm0, eax
00000001418073CD movd    xmm1, ecx
00000001418073D1 cvtdq2ps xmm0, xmm0
00000001418073D4 cvtdq2ps xmm1, xmm1
00000001418073D7 divss   xmm0, xmm15
00000001418073DC divss   xmm1, xmm15
00000001418073E1 movss   dword ptr [rsp+120h+var_E8], xmm0
00000001418073E7 movss   dword ptr [rsp+120h+var_E8+4], xmm1
00000001418073ED jmp     short loc_1418073FE
00000001418073EF movss   dword ptr [rsp+120h+var_E8+0Ch], xmm8
00000001418073F6 mov     dword ptr [rsp+120h+var_C8], 3
00000001418073FE mov     rcx, [rbx+0B8h]; self
0000000141807405 lea     r9, [rsp+120h+options]; options
000000014180740A lea     rdx, [rsp+120h+position]; position
000000014180740F mov     rax, [rcx+3E0h]
0000000141807416 movss   xmm2, dword ptr [rax+0C0h]; rotation
000000014180741E call    sub_141819E90
0000000141807423 call    sub_140B777C0
0000000141807428 mov     rdx, [rbx+0B8h]
000000014180742F mov     rcx, rax
0000000141807432 mov     rdx, [rdx+3E0h]
0000000141807439 call    sub_140B81F90
000000014180743E movaps  xmm15, [rsp+120h+var_B8+8]
0000000141807444 movaps  xmm8, [rsp+120h+var_48+8]
000000014180744D lea     r11, [rsp+120h+var_10]
0000000141807455 mov     rbx, [r11+20h]
0000000141807459 mov     rsi, [r11+28h]
000000014180745D mov     rdi, [r11+30h]
0000000141807461 mov     r12, [r11+38h]
0000000141807465 movaps  xmm6, xmmword ptr [r11-10h]
000000014180746A movaps  xmm9, xmmword ptr [r11-40h]
000000014180746F movaps  xmm11, xmmword ptr [r11-60h]
0000000141807474 movaps  xmm12, xmmword ptr [r11-70h]
0000000141807479 mov     rsp, r11
000000014180747C pop     r15
000000014180747E pop     r14
0000000141807480 pop     rbp
0000000141807481 retn