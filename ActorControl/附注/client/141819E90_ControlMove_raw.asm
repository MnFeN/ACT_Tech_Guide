0000000141819E90 mov     rax, rsp
0000000141819E93 mov     [rax+10h], rbx
0000000141819E97 mov     [rax+18h], rsi
0000000141819E9B mov     [rax+20h], r14
0000000141819E9F push    rbp
0000000141819EA0 lea     rbp, [rax-5Fh]
0000000141819EA4 sub     rsp, 0D0h
0000000141819EAB movaps  xmm0, cs:xmmword_14214B820
0000000141819EB2 xor     r14d, r14d
0000000141819EB5 movaps  xmmword ptr [rax-18h], xmm6
0000000141819EB9 mov     rsi, rdx
0000000141819EBC movss   xmm6, cs:control
0000000141819EC4 mov     rbx, rcx
0000000141819EC7 movaps  xmmword ptr [rax-28h], xmm7
0000000141819ECB movaps  xmm7, xmm6
0000000141819ECE movaps  xmmword ptr [rax-38h], xmm8
0000000141819ED3 movaps  xmmword ptr [rax-48h], xmm9
0000000141819ED8 movaps  xmm9, xmm2
0000000141819EDC movaps  xmmword ptr [rax-58h], xmm10
0000000141819EE1 movaps  xmmword ptr [rax-68h], xmm11
0000000141819EE6 lea     rax, off_142178A60
0000000141819EED mov     [rbp+57h+options], rax
0000000141819EF1 movss   [rbp+57h+var_98], xmm6
0000000141819EF6 mov     [rbp+57h+var_94], 0BF800000h
0000000141819EFD movaps  [rbp+57h+var_90], xmm0
0000000141819F01 mov     [rbp+57h+var_80], r14
0000000141819F05 mov     [rbp+57h+var_78], r14
0000000141819F09 mov     [rbp+57h+var_70], r14
0000000141819F0D mov     [rbp+57h+var_68], r14b
0000000141819F11 test    r9, r9
0000000141819F14 jz      loc_141819FBF
0000000141819F1A mov     rax, [r9+20h]
0000000141819F1E movss   xmm0, dword ptr [r9+0Ch]
0000000141819F24 movss   xmm7, dword ptr [r9+8]
0000000141819F2A movss   xmm10, dword ptr [r9+10h]
0000000141819F30 movss   xmm8, dword ptr [r9+14h]
0000000141819F36 movss   xmm11, dword ptr [r9+18h]
0000000141819F3C mov     [rbp+57h+var_80], rax
0000000141819F40 mov     eax, [r9+28h]
0000000141819F44 mov     dword ptr [rbp+57h+var_78], eax
0000000141819F47 mov     eax, [r9+2Ch]
0000000141819F4B mov     dword ptr [rbp+57h+var_78+4], eax
0000000141819F4E movzx   eax, byte ptr [r9+30h]
0000000141819F53 mov     byte ptr [rbp+57h+var_70], al
0000000141819F56 movzx   eax, byte ptr [r9+31h]
0000000141819F5B mov     byte ptr [rbp+57h+var_70+1], al
0000000141819F5E movzx   eax, byte ptr [r9+32h]
0000000141819F63 mov     byte ptr [rbp+57h+var_70+2], al
0000000141819F66 movzx   eax, byte ptr [r9+33h]
0000000141819F6B mov     byte ptr [rbp+57h+var_70+3], al
0000000141819F6E movzx   eax, byte ptr [r9+34h]
0000000141819F73 mov     byte ptr [rbp+57h+var_70+4], al
0000000141819F76 movzx   eax, byte ptr [r9+35h]
0000000141819F7B mov     byte ptr [rbp+57h+var_70+5], al
0000000141819F7E movzx   eax, byte ptr [r9+36h]
0000000141819F83 mov     byte ptr [rbp+57h+var_70+6], al
0000000141819F86 movzx   eax, byte ptr [r9+37h]
0000000141819F8B mov     byte ptr [rbp+57h+var_70+7], al
0000000141819F8E movzx   eax, byte ptr [r9+38h]
0000000141819F93 movss   [rbp+57h+var_94], xmm0
0000000141819F98 movss   xmm0, dword ptr [r9+1Ch]
0000000141819F9E mov     [rbp+57h+var_68], al
0000000141819FA1 movss   [rbp+57h+var_98], xmm7
0000000141819FA6 movss   dword ptr [rbp+57h+var_90], xmm10
0000000141819FAC movss   dword ptr [rbp+57h+var_90+4], xmm8
0000000141819FB2 movss   dword ptr [rbp+57h+var_90+8], xmm11
0000000141819FB8 movss   dword ptr [rbp+57h+var_90+0Ch], xmm0
0000000141819FBD jmp     short loc_141819FD1
0000000141819FBF movss   xmm11, dword ptr [rbp+57h+var_90+8]
0000000141819FC5 movss   xmm8, dword ptr [rbp+57h+var_90+4]
0000000141819FCB movss   xmm10, dword ptr [rbp+57h+var_90]
0000000141819FD1 movzx   eax, byte ptr [rcx+410h]
0000000141819FD8 dec     al
0000000141819FDA cmp     al, 2
0000000141819FDC jbe     loc_14181A0BF
0000000141819FE2 mov     [rsp+0D0h+arg_0], rdi
0000000141819FEA mov     rdi, [rcx+3E0h]
0000000141819FF1 test    rdi, rdi
0000000141819FF4 jz      short loc_14181A039
0000000141819FF6 test    byte ptr cs:qword_142AA895B, 4
0000000141819FFD jz      short loc_14181A00F
0000000141819FFF lea     rcx, word_142AA7678
000000014181A006 call    sub_1406056C0
000000014181A00B test    al, al
000000014181A00D jz      short loc_14181A039
000000014181A00F xor     r8d, r8d; a3
000000014181A012 xor     edx, edx; a2
000000014181A014 mov     rcx, rdi; a1
000000014181A017 call    sub_140897A40
000000014181A01C test    al, al
000000014181A01E jz      short loc_14181A039
000000014181A020 lea     r9, [rbp+57h+options]; options
000000014181A024 movaps  xmm2, xmm9; rotation
000000014181A028 mov     rdx, rsi; position
000000014181A02B lea     rcx, qword_142AB28C0; self
000000014181A032 call    sub_14182CD70
000000014181A037 jmp     short loc_14181A0B7
000000014181A039 ucomiss xmm7, xmm6
000000014181A03C jp      short loc_14181A059
000000014181A03E jnz     short loc_14181A059
000000014181A040 ucomiss xmm8, xmm6
000000014181A044 jp      short loc_14181A059
000000014181A046 jnz     short loc_14181A059
000000014181A048 movss   xmm0, cs:flt_14211BF10
000000014181A050 movss   [rbp+57h+var_98], xmm0
000000014181A055 mov     dword ptr [rbp+57h+var_78], r14d
000000014181A059 ucomiss xmm10, xmm6
000000014181A05D jp      short loc_14181A07D
000000014181A05F jnz     short loc_14181A07D
000000014181A061 ucomiss xmm11, xmm6
000000014181A065 jp      short loc_14181A07D
000000014181A067 jnz     short loc_14181A07D
000000014181A069 movss   xmm0, cs:flt_14211BEC8
000000014181A071 movss   dword ptr [rbp+57h+var_90+8], xmm0
000000014181A076 mov     dword ptr [rbp+57h+var_78+4], 4
000000014181A07D lea     rcx, [rbx+2D0h]; self
000000014181A084 mov     [rsp+0D0h+flag2], r14b; flag2
000000014181A089 lea     r9, [rbp+57h+options]; options
000000014181A08D mov     [rsp+0D0h+flag1], r14b; flag1
000000014181A092 movaps  xmm2, xmm9; rotation
000000014181A096 mov     rdx, rsi; position
000000014181A099 call    sub_1418015D0
000000014181A09E cmp     [rbx+2F4h], r14b
000000014181A0A5 jnz     short loc_14181A0B0
000000014181A0A7 cmp     [rbx+2F5h], r14b
000000014181A0AE jz      short loc_14181A0B7
000000014181A0B0 mov     [rbx+3F4h], r14d
000000014181A0B7 mov     rdi, [rsp+0D0h+arg_0]
000000014181A0BF lea     r11, [rsp+0D0h+var_s0]
000000014181A0C7 mov     rbx, [r11+18h]
000000014181A0CB mov     rsi, [r11+20h]
000000014181A0CF mov     r14, [r11+28h]
000000014181A0D3 movaps  xmm6, xmmword ptr [r11-10h]
000000014181A0D8 movaps  xmm7, xmmword ptr [r11-20h]
000000014181A0DD movaps  xmm8, xmmword ptr [r11-30h]
000000014181A0E2 movaps  xmm9, xmmword ptr [r11-40h]
000000014181A0E7 movaps  xmm10, xmmword ptr [r11-50h]
000000014181A0EC movaps  xmm11, xmmword ptr [r11-60h]
000000014181A0F1 mov     rsp, r11
000000014181A0F4 pop     rbp
000000014181A0F5 retn