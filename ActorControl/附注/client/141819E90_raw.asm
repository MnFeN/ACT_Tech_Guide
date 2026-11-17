0000000141819E90  48 8b c4                     mov     rax, rsp
0000000141819E93  48 89 58 10                  mov     [rax+10h], rbx
0000000141819E97  48 89 70 18                  mov     [rax+18h], rsi
0000000141819E9B  4c 89 70 20                  mov     [rax+20h], r14
0000000141819E9F  55                           push    rbp
0000000141819EA0  48 8d 68 a1                  lea     rbp, [rax-5Fh]
0000000141819EA4  48 81 ec d0 00 00 00         sub     rsp, 0D0h
0000000141819EAB  0f 28 05 6e 19 93 00         movaps  xmm0, cs:xmmword_14214B820
0000000141819EB2  45 33 f6                     xor     r14d, r14d
0000000141819EB5  0f 29 70 e8                  movaps  xmmword ptr [rax-18h], xmm6
0000000141819EB9  48 8b f2                     mov     rsi, rdx
0000000141819EBC  f3 0f 10 35 4c 21 90 00      movss   xmm6, cs:X
0000000141819EC4  48 8b d9                     mov     rbx, rcx
0000000141819EC7  0f 29 78 d8                  movaps  xmmword ptr [rax-28h], xmm7
0000000141819ECB  0f 28 fe                     movaps  xmm7, xmm6
0000000141819ECE  44 0f 29 40 c8               movaps  xmmword ptr [rax-38h], xmm8
0000000141819ED3  44 0f 29 48 b8               movaps  xmmword ptr [rax-48h], xmm9
0000000141819ED8  44 0f 28 ca                  movaps  xmm9, xmm2
0000000141819EDC  44 0f 29 50 a8               movaps  xmmword ptr [rax-58h], xmm10
0000000141819EE1  44 0f 29 58 98               movaps  xmmword ptr [rax-68h], xmm11
0000000141819EE6  48 8d 05 73 eb 95 00         lea     rax, off_142178A60
0000000141819EED  48 89 45 b7                  mov     [rbp+57h+var_A0], rax
0000000141819EF1  f3 0f 11 75 bf               movss   [rbp+57h+var_98], xmm6
0000000141819EF6  c7 45 c3 00 00 80 bf         mov     [rbp+57h+var_94], 0BF800000h
0000000141819EFD  0f 29 45 c7                  movaps  [rbp+57h+var_90], xmm0
0000000141819F01  4c 89 75 d7                  mov     [rbp+57h+var_80], r14
0000000141819F05  4c 89 75 df                  mov     [rbp+57h+var_78], r14
0000000141819F09  4c 89 75 e7                  mov     [rbp+57h+var_70], r14
0000000141819F0D  44 88 75 ef                  mov     [rbp+57h+var_68], r14b
0000000141819F11  4d 85 c9                     test    r9, r9
0000000141819F14  0f 84 a5 00 00 00            jz      loc_141819FBF
0000000141819F1A  49 8b 41 20                  mov     rax, [r9+20h]
0000000141819F1E  f3 41 0f 10 41 0c            movss   xmm0, dword ptr [r9+0Ch]
0000000141819F24  f3 41 0f 10 79 08            movss   xmm7, dword ptr [r9+8]
0000000141819F2A  f3 45 0f 10 51 10            movss   xmm10, dword ptr [r9+10h]
0000000141819F30  f3 45 0f 10 41 14            movss   xmm8, dword ptr [r9+14h]
0000000141819F36  f3 45 0f 10 59 18            movss   xmm11, dword ptr [r9+18h]
0000000141819F3C  48 89 45 d7                  mov     [rbp+57h+var_80], rax
0000000141819F40  41 8b 41 28                  mov     eax, [r9+28h]
0000000141819F44  89 45 df                     mov     dword ptr [rbp+57h+var_78], eax
0000000141819F47  41 8b 41 2c                  mov     eax, [r9+2Ch]
0000000141819F4B  89 45 e3                     mov     dword ptr [rbp+57h+var_78+4], eax
0000000141819F4E  41 0f b6 41 30               movzx   eax, byte ptr [r9+30h]
0000000141819F53  88 45 e7                     mov     byte ptr [rbp+57h+var_70], al
0000000141819F56  41 0f b6 41 31               movzx   eax, byte ptr [r9+31h]
0000000141819F5B  88 45 e8                     mov     byte ptr [rbp+57h+var_70+1], al
0000000141819F5E  41 0f b6 41 32               movzx   eax, byte ptr [r9+32h]
0000000141819F63  88 45 e9                     mov     byte ptr [rbp+57h+var_70+2], al
0000000141819F66  41 0f b6 41 33               movzx   eax, byte ptr [r9+33h]
0000000141819F6B  88 45 ea                     mov     byte ptr [rbp+57h+var_70+3], al
0000000141819F6E  41 0f b6 41 34               movzx   eax, byte ptr [r9+34h]
0000000141819F73  88 45 eb                     mov     byte ptr [rbp+57h+var_70+4], al
0000000141819F76  41 0f b6 41 35               movzx   eax, byte ptr [r9+35h]
0000000141819F7B  88 45 ec                     mov     byte ptr [rbp+57h+var_70+5], al
0000000141819F7E  41 0f b6 41 36               movzx   eax, byte ptr [r9+36h]
0000000141819F83  88 45 ed                     mov     byte ptr [rbp+57h+var_70+6], al
0000000141819F86  41 0f b6 41 37               movzx   eax, byte ptr [r9+37h]
0000000141819F8B  88 45 ee                     mov     byte ptr [rbp+57h+var_70+7], al
0000000141819F8E  41 0f b6 41 38               movzx   eax, byte ptr [r9+38h]
0000000141819F93  f3 0f 11 45 c3               movss   [rbp+57h+var_94], xmm0
0000000141819F98  f3 41 0f 10 41 1c            movss   xmm0, dword ptr [r9+1Ch]
0000000141819F9E  88 45 ef                     mov     [rbp+57h+var_68], al
0000000141819FA1  f3 0f 11 7d bf               movss   [rbp+57h+var_98], xmm7
0000000141819FA6  f3 44 0f 11 55 c7            movss   dword ptr [rbp+57h+var_90], xmm10
0000000141819FAC  f3 44 0f 11 45 cb            movss   dword ptr [rbp+57h+var_90+4], xmm8
0000000141819FB2  f3 44 0f 11 5d cf            movss   dword ptr [rbp+57h+var_90+8], xmm11
0000000141819FB8  f3 0f 11 45 d3               movss   dword ptr [rbp+57h+var_90+0Ch], xmm0
0000000141819FBD  eb 12                        jmp     short loc_141819FD1
0000000141819FBF  f3 44 0f 10 5d cf            movss   xmm11, dword ptr [rbp+57h+var_90+8]
0000000141819FC5  f3 44 0f 10 45 cb            movss   xmm8, dword ptr [rbp+57h+var_90+4]
0000000141819FCB  f3 44 0f 10 55 c7            movss   xmm10, dword ptr [rbp+57h+var_90]
0000000141819FD1  0f b6 81 10 04 00 00         movzx   eax, byte ptr [rcx+410h]
0000000141819FD8  fe c8                        dec     al
0000000141819FDA  3c 02                        cmp     al, 2
0000000141819FDC  0f 86 dd 00 00 00            jbe     loc_14181A0BF
0000000141819FE2  48 89 bc 24 e0 00 00 00      mov     [rsp+0D0h+arg_0], rdi
0000000141819FEA  48 8b b9 e0 03 00 00         mov     rdi, [rcx+3E0h]
0000000141819FF1  48 85 ff                     test    rdi, rdi
0000000141819FF4  74 43                        jz      short loc_14181A039
0000000141819FF6  f6 05 5e e9 28 01 04         test    byte ptr cs:qword_142AA895B, 4
0000000141819FFD  74 10                        jz      short loc_14181A00F
0000000141819FFF  48 8d 0d 72 d6 28 01         lea     rcx, word_142AA7678
000000014181A006  e8 b5 b6 de fe               call    sub_1406056C0
000000014181A00B  84 c0                        test    al, al
000000014181A00D  74 2a                        jz      short loc_14181A039
000000014181A00F  45 33 c0                     xor     r8d, r8d
000000014181A012  33 d2                        xor     edx, edx
000000014181A014  48 8b cf                     mov     rcx, rdi
000000014181A017  e8 24 da 07 ff               call    sub_140897A40
000000014181A01C  84 c0                        test    al, al
000000014181A01E  74 19                        jz      short loc_14181A039
000000014181A020  4c 8d 4d b7                  lea     r9, [rbp+57h+var_A0]
000000014181A024  41 0f 28 d1                  movaps  xmm2, xmm9
000000014181A028  48 8b d6                     mov     rdx, rsi
000000014181A02B  48 8d 0d 8e 88 29 01         lea     rcx, unk_142AB28C0
000000014181A032  e8 39 2d 01 00               call    sub_14182CD70
000000014181A037  eb 7e                        jmp     short loc_14181A0B7
000000014181A039  0f 2e fe                     ucomiss xmm7, xmm6
000000014181A03C  7a 1b                        jp      short loc_14181A059
000000014181A03E  75 19                        jnz     short loc_14181A059
000000014181A040  44 0f 2e c6                  ucomiss xmm8, xmm6
000000014181A044  7a 13                        jp      short loc_14181A059
000000014181A046  75 11                        jnz     short loc_14181A059
000000014181A048  f3 0f 10 05 c0 1e 90 00      movss   xmm0, cs:flt_14211BF10
000000014181A050  f3 0f 11 45 bf               movss   [rbp+57h+var_98], xmm0
000000014181A055  44 89 75 df                  mov     dword ptr [rbp+57h+var_78], r14d
000000014181A059  44 0f 2e d6                  ucomiss xmm10, xmm6
000000014181A05D  7a 1e                        jp      short loc_14181A07D
000000014181A05F  75 1c                        jnz     short loc_14181A07D
000000014181A061  44 0f 2e de                  ucomiss xmm11, xmm6
000000014181A065  7a 16                        jp      short loc_14181A07D
000000014181A067  75 14                        jnz     short loc_14181A07D
000000014181A069  f3 0f 10 05 57 1e 90 00      movss   xmm0, cs:dword_14211BEC8
000000014181A071  f3 0f 11 45 cf               movss   dword ptr [rbp+57h+var_90+8], xmm0
000000014181A076  c7 45 e3 04 00 00 00         mov     dword ptr [rbp+57h+var_78+4], 4
000000014181A07D  48 8d 8b d0 02 00 00         lea     rcx, [rbx+2D0h]
000000014181A084  44 88 74 24 28               mov     [rsp+0D0h+var_A8], r14b
000000014181A089  4c 8d 4d b7                  lea     r9, [rbp+57h+var_A0]
000000014181A08D  44 88 74 24 20               mov     [rsp+0D0h+var_B0], r14b
000000014181A092  41 0f 28 d1                  movaps  xmm2, xmm9
000000014181A096  48 8b d6                     mov     rdx, rsi
000000014181A099  e8 32 75 fe ff               call    sub_1418015D0
000000014181A09E  44 38 b3 f4 02 00 00         cmp     [rbx+2F4h], r14b
000000014181A0A5  75 09                        jnz     short loc_14181A0B0
000000014181A0A7  44 38 b3 f5 02 00 00         cmp     [rbx+2F5h], r14b
000000014181A0AE  74 07                        jz      short loc_14181A0B7
000000014181A0B0  44 89 b3 f4 03 00 00         mov     [rbx+3F4h], r14d
000000014181A0B7  48 8b bc 24 e0 00 00 00      mov     rdi, [rsp+0D0h+arg_0]
000000014181A0BF  4c 8d 9c 24 d0 00 00 00      lea     r11, [rsp+0D0h+var_s0]
000000014181A0C7  49 8b 5b 18                  mov     rbx, [r11+18h]
000000014181A0CB  49 8b 73 20                  mov     rsi, [r11+20h]
000000014181A0CF  4d 8b 73 28                  mov     r14, [r11+28h]
000000014181A0D3  41 0f 28 73 f0               movaps  xmm6, xmmword ptr [r11-10h]
000000014181A0D8  41 0f 28 7b e0               movaps  xmm7, xmmword ptr [r11-20h]
000000014181A0DD  45 0f 28 43 d0               movaps  xmm8, xmmword ptr [r11-30h]
000000014181A0E2  45 0f 28 4b c0               movaps  xmm9, xmmword ptr [r11-40h]
000000014181A0E7  45 0f 28 53 b0               movaps  xmm10, xmmword ptr [r11-50h]
000000014181A0EC  45 0f 28 5b a0               movaps  xmm11, xmmword ptr [r11-60h]
000000014181A0F1  49 8b e3                     mov     rsp, r11
000000014181A0F4  5d                           pop     rbp
000000014181A0F5  c3                           retn