000000014181B840  48 89 5c 24 08               mov     [rsp+arg_0], rbx
000000014181B845  57                           push    rdi
000000014181B846  48 83 ec 70                  sub     rsp, 70h
000000014181B84A  f3 41 0f 10 50 24            movss   xmm2, dword ptr [r8+24h]
000000014181B850  49 8b f8                     mov     rdi, r8
000000014181B853  0f 29 74 24 60               movaps  [rsp+78h+var_18], xmm6
000000014181B858  0f 28 e1                     movaps  xmm4, xmm1
000000014181B85B  0f 57 f6                     xorps   xmm6, xmm6
000000014181B85E  44 0f 29 54 24 30            movaps  [rsp+78h+var_48], xmm10
000000014181B864  0f 2e d6                     ucomiss xmm2, xmm6
000000014181B867  48 8b d9                     mov     rbx, rcx
000000014181B86A  7a 0a                        jp      short loc_14181B876
000000014181B86C  75 08                        jnz     short loc_14181B876
000000014181B86E  0f 28 f1                     movaps  xmm6, xmm1
000000014181B871  e9 98 01 00 00               jmp     loc_14181BA0E
000000014181B876  f3 41 0f 10 40 18            movss   xmm0, dword ptr [r8+18h]
000000014181B87C  f3 0f 10 0d 8c 07 90 00      movss   xmm1, cs:control
000000014181B884  0f 2e c1                     ucomiss xmm0, xmm1
000000014181B887  0f 8a 51 01 00 00            jp      loc_14181B9DE
000000014181B88D  0f 85 4b 01 00 00            jnz     loc_14181B9DE
000000014181B893  0f 2e d1                     ucomiss xmm2, xmm1
000000014181B896  7a 78                        jp      short loc_14181B910
000000014181B898  75 76                        jnz     short loc_14181B910
000000014181B89A  48 8b b9 e0 03 00 00         mov     rdi, [rcx+3E0h]
000000014181B8A1  48 85 ff                     test    rdi, rdi
000000014181B8A4  74 5c                        jz      short loc_14181B902
000000014181B8A6  f6 05 ae d0 28 01 04         test    byte ptr cs:qword_142AA895B, 4
000000014181B8AD  74 10                        jz      short loc_14181B8BF
000000014181B8AF  48 8d 0d c2 bd 28 01         lea     rcx, word_142AA7678
000000014181B8B6  e8 05 9e de fe               call    sub_1406056C0
000000014181B8BB  84 c0                        test    al, al
000000014181B8BD  74 43                        jz      short loc_14181B902
000000014181B8BF  45 33 c0                     xor     r8d, r8d; a3
000000014181B8C2  33 d2                        xor     edx, edx; a2
000000014181B8C4  48 8b cf                     mov     rcx, rdi; a1
000000014181B8C7  e8 74 c1 07 ff               call    sub_140897A40
000000014181B8CC  84 c0                        test    al, al
000000014181B8CE  74 32                        jz      short loc_14181B902
000000014181B8D0  80 3d 25 70 29 01 00         cmp     cs:byte_142AB28FC, 0
000000014181B8D7  75 11                        jnz     short loc_14181B8EA
000000014181B8D9  0f b6 83 30 04 00 00         movzx   eax, byte ptr [rbx+430h]
000000014181B8E0  24 03                        and     al, 3
000000014181B8E2  3c 03                        cmp     al, 3
000000014181B8E4  0f 85 24 01 00 00            jnz     loc_14181BA0E
000000014181B8EA  48 8b cb                     mov     rcx, rbx
000000014181B8ED  e8 ee a6 ff ff               call    sub_141815FE0
000000014181B8F2  0f 28 f0                     movaps  xmm6, xmm0
000000014181B8F5  f3 0f 59 35 07 70 29 01      mulss   xmm6, cs:dword_142AB2904
000000014181B8FD  e9 0c 01 00 00               jmp     loc_14181BA0E
000000014181B902  0f b6 83 30 04 00 00         movzx   eax, byte ptr [rbx+430h]
000000014181B909  24 03                        and     al, 3
000000014181B90B  e9 fe 00 00 00               jmp     loc_14181BA0E
000000014181B910  41 8b 50 2c                  mov     edx, [r8+2Ch]
000000014181B914  83 fa 01                     cmp     edx, 1
000000014181B917  0f 84 9e 00 00 00            jz      loc_14181B9BB
000000014181B91D  8d 42 fd                     lea     eax, [rdx-3]
000000014181B920  83 f8 02                     cmp     eax, 2
000000014181B923  0f 87 e5 00 00 00            ja      loc_14181BA0E
000000014181B929  f3 45 0f 10 50 58            movss   xmm10, dword ptr [r8+58h]
000000014181B92F  44 0f 2f d6                  comiss  xmm10, xmm6
000000014181B933  0f 82 d5 00 00 00            jb      loc_14181BA0E
000000014181B939  f3 0f 10 35 b7 05 90 00      movss   xmm6, cs:target
000000014181B941  48 8d 0d 68 6f 29 01         lea     rcx, qword_142AB28B0
000000014181B948  f3 41 0f 10 50 5c            movss   xmm2, dword ptr [r8+5Ch]
000000014181B94E  0f 28 de                     movaps  xmm3, xmm6
000000014181B951  41 0f b6 50 60               movzx   edx, byte ptr [r8+60h]
000000014181B956  0f 29 7c 24 50               movaps  [rsp+78h+var_28], xmm7
000000014181B95B  44 0f 29 44 24 40            movaps  [rsp+78h+var_38], xmm8
000000014181B961  f3 45 0f 10 40 54            movss   xmm8, dword ptr [r8+54h]
000000014181B967  f3 45 0f 5c 40 50            subss   xmm8, dword ptr [r8+50h]
000000014181B96D  e8 ce 8b 01 00               call    sub_141834540
000000014181B972  0f b6 57 60                  movzx   edx, byte ptr [rdi+60h]
000000014181B976  48 8d 0d 33 6f 29 01         lea     rcx, qword_142AB28B0
000000014181B97D  0f 28 f8                     movaps  xmm7, xmm0
000000014181B980  0f 28 de                     movaps  xmm3, xmm6
000000014181B983  f3 41 0f 59 f8               mulss   xmm7, xmm8
000000014181B988  41 0f 28 d2                  movaps  xmm2, xmm10
000000014181B98C  f3 0f 58 7f 50               addss   xmm7, dword ptr [rdi+50h]
000000014181B991  e8 aa 8b 01 00               call    sub_141834540
000000014181B996  0f 28 f0                     movaps  xmm6, xmm0
000000014181B999  f3 41 0f 59 f0               mulss   xmm6, xmm8
000000014181B99E  44 0f 28 44 24 40            movaps  xmm8, [rsp+78h+var_38]
000000014181B9A4  f3 0f 58 77 50               addss   xmm6, dword ptr [rdi+50h]
000000014181B9A9  f3 0f 5c f7                  subss   xmm6, xmm7
000000014181B9AD  0f 28 7c 24 50               movaps  xmm7, [rsp+78h+var_28]
000000014181B9B2  0f 54 35 37 07 90 00         andps   xmm6, cs:xmmword_14211C0F0
000000014181B9B9  eb 53                        jmp     short loc_14181BA0E
000000014181B9BB  f3 0f 10 99 f4 03 00 00      movss   xmm3, dword ptr [rcx+3F4h]
000000014181B9C3  0f 28 cc                     movaps  xmm1, xmm4
000000014181B9C6  f3 0f 11 54 24 20            movss   [rsp+78h+var_58], xmm2
000000014181B9CC  f3 0f 10 91 e8 02 00 00      movss   xmm2, dword ptr [rcx+2E8h]
000000014181B9D4  e8 97 02 00 00               call    sub_14181BC70
000000014181B9D9  0f 28 f0                     movaps  xmm6, xmm0
000000014181B9DC  eb 30                        jmp     short loc_14181BA0E
000000014181B9DE  f3 41 0f 10 40 1c            movss   xmm0, dword ptr [r8+1Ch]
000000014181B9E4  0f 2e c1                     ucomiss xmm0, xmm1
000000014181B9E7  7a 11                        jp      short loc_14181B9FA
000000014181B9E9  75 0f                        jnz     short loc_14181B9FA
000000014181B9EB  e8 f0 a5 ff ff               call    sub_141815FE0
000000014181B9F0  0f 28 f0                     movaps  xmm6, xmm0
000000014181B9F3  f3 0f 59 77 18               mulss   xmm6, dword ptr [rdi+18h]
000000014181B9F8  eb 14                        jmp     short loc_14181BA0E
000000014181B9FA  e8 b1 9c ff ff               call    sub_1418156B0
000000014181B9FF  48 8b cb                     mov     rcx, rbx
000000014181BA02  0f 28 f0                     movaps  xmm6, xmm0
000000014181BA05  e8 d6 a5 ff ff               call    sub_141815FE0
000000014181BA0A  f3 0f 59 f0                  mulss   xmm6, xmm0
000000014181BA0E  48 8b 9c 24 80 00 00 00      mov     rbx, [rsp+78h+arg_0]
000000014181BA16  0f 28 c6                     movaps  xmm0, xmm6
000000014181BA19  0f 28 74 24 60               movaps  xmm6, [rsp+78h+var_18]
000000014181BA1E  44 0f 28 54 24 30            movaps  xmm10, [rsp+78h+var_48]
000000014181BA24  48 83 c4 70                  add     rsp, 70h
000000014181BA28  5f                           pop     rdi
000000014181BA29  c3                           retn