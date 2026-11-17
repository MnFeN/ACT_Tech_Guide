0000000141807B70  48 8b c4                     mov     rax, rsp
0000000141807B73  48 89 58 20                  mov     [rax+20h], rbx
0000000141807B77  55                           push    rbp
0000000141807B78  48 8d 68 a1                  lea     rbp, [rax-5Fh]
0000000141807B7C  48 81 ec 90 00 00 00         sub     rsp, 90h
0000000141807B83  80 79 76 00                  cmp     byte ptr [rcx+76h], 0
0000000141807B87  48 8b d9                     mov     rbx, rcx
0000000141807B8A  0f 84 49 03 00 00            jz      loc_141807ED9
0000000141807B90  48 89 78 18                  mov     [rax+18h], rdi
0000000141807B94  48 8b 79 10                  mov     rdi, [rcx+10h]
0000000141807B98  48 85 ff                     test    rdi, rdi
0000000141807B9B  0f 84 30 03 00 00            jz      loc_141807ED1
0000000141807BA1  48 8b bf e0 03 00 00         mov     rdi, [rdi+3E0h]
0000000141807BA8  48 85 ff                     test    rdi, rdi
0000000141807BAB  0f 84 20 03 00 00            jz      loc_141807ED1
0000000141807BB1  80 bf a4 1b 00 00 00         cmp     byte ptr [rdi+1BA4h], 0
0000000141807BB8  0f 85 13 03 00 00            jnz     loc_141807ED1
0000000141807BBE  0f b6 49 72                  movzx   ecx, byte ptr [rcx+72h]
0000000141807BC2  f3 0f 10 05 ba 9e 29 01      movss   xmm0, dword ptr cs:qword_142AA1A80+4
0000000141807BCA  48 89 70 10                  mov     [rax+10h], rsi
0000000141807BCE  0f 29 70 e8                  movaps  xmmword ptr [rax-18h], xmm6
0000000141807BD2  f3 0f 10 35 a6 9e 29 01      movss   xmm6, dword ptr cs:qword_142AA1A80
0000000141807BDA  0f 29 78 d8                  movaps  xmmword ptr [rax-28h], xmm7
0000000141807BDE  0f 57 ff                     xorps   xmm7, xmm7
0000000141807BE1  44 0f 29 40 c8               movaps  xmmword ptr [rax-38h], xmm8
0000000141807BE6  45 0f 57 c0                  xorps   xmm8, xmm8
0000000141807BEA  44 0f 29 48 b8               movaps  xmmword ptr [rax-48h], xmm9
0000000141807BEF  f3 44 0f 10 0d 90 9e 29 01   movss   xmm9, cs:dword_142AA1A88
0000000141807BF8  44 0f 29 50 a8               movaps  xmmword ptr [rax-58h], xmm10
0000000141807BFD  f3 0f 11 45 eb               movss   [rbp+57h+var_6C], xmm0
0000000141807C02  c7 45 f3 00 00 00 00         mov     [rbp+57h+var_64], 0
0000000141807C09  80 f9 01                     cmp     cl, 1
0000000141807C0C  74 1d                        jz      short loc_141807C2B
0000000141807C0E  8d 41 fa                     lea     eax, [rcx-6]
0000000141807C11  3c 02                        cmp     al, 2
0000000141807C13  76 16                        jbe     short loc_141807C2B
0000000141807C15  f3 44 0f 10 4b 20            movss   xmm9, dword ptr [rbx+20h]
0000000141807C1B  f3 0f 10 73 24               movss   xmm6, dword ptr [rbx+24h]
0000000141807C20  f3 44 0f 10 53 28            movss   xmm10, dword ptr [rbx+28h]
0000000141807C26  e9 a8 00 00 00               jmp     loc_141807CD3
0000000141807C2B  80 7b 77 00                  cmp     byte ptr [rbx+77h], 0
0000000141807C2F  0f 84 2c 01 00 00            jz      loc_141807D61
0000000141807C35  48 8b 53 18                  mov     rdx, [rbx+18h]
0000000141807C39  b8 00 00 00 e0               mov     eax, 0E0000000h
0000000141807C3E  48 3b d0                     cmp     rdx, rax
0000000141807C41  74 62                        jz      short loc_141807CA5
0000000141807C43  48 8d 0d 86 51 0b 01         lea     rcx, qword_1428BCDD0
0000000141807C4A  e8 e1 6c 2f ff               call    Client__Game__Object__ObjectArrays__GetObjectByGameObjectId
0000000141807C4F  48 8b f0                     mov     rsi, rax
0000000141807C52  48 85 c0                     test    rax, rax
0000000141807C55  0f 84 06 01 00 00            jz      loc_141807D61
0000000141807C5B  48 8b 10                     mov     rdx, [rax]
0000000141807C5E  48 8b c8                     mov     rcx, rax
0000000141807C61  ff 92 f0 01 00 00            call    qword ptr [rdx+1F0h]
0000000141807C67  84 c0                        test    al, al
0000000141807C69  74 1c                        jz      short loc_141807C87
0000000141807C6B  48 8b ce                     mov     rcx, rsi
0000000141807C6E  e8 4d 32 09 ff               call    sub_14089AEC0
0000000141807C73  48 8d 88 f0 01 00 00         lea     rcx, [rax+1F0h]
0000000141807C7A  e8 c1 45 01 00               call    Client__Game__Control__MoveControl__MoveController__IsFlying
0000000141807C7F  84 c0                        test    al, al
0000000141807C81  0f 85 da 00 00 00            jnz     loc_141807D61
0000000141807C87  48 8b ce                     mov     rcx, rsi
0000000141807C8A  e8 21 0d 09 ff               call    Client__Game__Object__GameObject__GetPosition
0000000141807C8F  0f b6 4b 72                  movzx   ecx, byte ptr [rbx+72h]
0000000141807C93  f3 44 0f 10 08               movss   xmm9, dword ptr [rax]
0000000141807C98  f3 0f 10 70 04               movss   xmm6, dword ptr [rax+4]
0000000141807C9D  f3 44 0f 10 50 08            movss   xmm10, dword ptr [rax+8]
0000000141807CA3  eb 11                        jmp     short loc_141807CB6
0000000141807CA5  f3 44 0f 10 4b 20            movss   xmm9, dword ptr [rbx+20h]
0000000141807CAB  f3 0f 10 73 24               movss   xmm6, dword ptr [rbx+24h]
0000000141807CB0  f3 44 0f 10 53 28            movss   xmm10, dword ptr [rbx+28h]
0000000141807CB6  0f b6 c9                     movzx   ecx, cl
0000000141807CB9  83 e9 01                     sub     ecx, 1
0000000141807CBC  74 0a                        jz      short loc_141807CC8
0000000141807CBE  83 e9 06                     sub     ecx, 6
0000000141807CC1  74 5b                        jz      short loc_141807D1E
0000000141807CC3  83 f9 01                     cmp     ecx, 1
0000000141807CC6  75 0b                        jnz     short loc_141807CD3
0000000141807CC8  48 8b cb                     mov     rcx, rbx
0000000141807CCB  e8 c0 0b 00 00               call    sub_141808890
0000000141807CD0  0f 28 f8                     movaps  xmm7, xmm0
0000000141807CD3  f3 0f 5c 73 34               subss   xmm6, dword ptr [rbx+34h]
0000000141807CD8  f3 44 0f 5c 4b 30            subss   xmm9, dword ptr [rbx+30h]
0000000141807CDE  f3 44 0f 5c 53 38            subss   xmm10, dword ptr [rbx+38h]
0000000141807CE4  0f 57 c0                     xorps   xmm0, xmm0
0000000141807CE7  f3 0f 11 75 eb               movss   [rbp+57h+var_6C], xmm6
0000000141807CEC  f3 0f 59 f6                  mulss   xmm6, xmm6
0000000141807CF0  f3 44 0f 11 4d e7            movss   [rbp+57h+var_70], xmm9
0000000141807CF6  f3 45 0f 59 c9               mulss   xmm9, xmm9
0000000141807CFB  f3 44 0f 11 55 ef            movss   [rbp+57h+var_68], xmm10
0000000141807D01  f3 45 0f 59 d2               mulss   xmm10, xmm10
0000000141807D06  f3 41 0f 58 f1               addss   xmm6, xmm9
0000000141807D0B  f3 41 0f 58 f2               addss   xmm6, xmm10
0000000141807D10  0f 2e c6                     ucomiss xmm0, xmm6
0000000141807D13  77 17                        ja      short loc_141807D2C
0000000141807D15  0f 57 c0                     xorps   xmm0, xmm0
0000000141807D18  f3 0f 51 c6                  sqrtss  xmm0, xmm6
0000000141807D1C  eb 16                        jmp     short loc_141807D34
0000000141807D1E  48 8b cb                     mov     rcx, rbx
0000000141807D21  e8 6a 0b 00 00               call    sub_141808890
0000000141807D26  f3 0f 5c f8                  subss   xmm7, xmm0
0000000141807D2A  eb a7                        jmp     short loc_141807CD3
0000000141807D2C  0f 28 c6                     movaps  xmm0, xmm6; X
0000000141807D2F  e8 94 c7 5d 00               call    sqrtf
0000000141807D34  f3 0f 5c c7                  subss   xmm0, xmm7
0000000141807D38  44 0f 2f c0                  comiss  xmm8, xmm0
0000000141807D3C  76 07                        jbe     short loc_141807D45
0000000141807D3E  0f 57 c0                     xorps   xmm0, xmm0
0000000141807D41  c6 43 77 00                  mov     byte ptr [rbx+77h], 0
0000000141807D45  f3 0f 59 43 60               mulss   xmm0, dword ptr [rbx+60h]
0000000141807D4A  48 8d 4d e7                  lea     rcx, [rbp+57h+var_70]
0000000141807D4E  0f 28 c8                     movaps  xmm1, xmm0
0000000141807D51  e8 aa 67 c6 fe               call    sub_14046E500
0000000141807D56  f3 44 0f 10 4d ef            movss   xmm9, [rbp+57h+var_68]
0000000141807D5C  f3 0f 10 75 e7               movss   xmm6, [rbp+57h+var_70]
0000000141807D61  f3 0f 58 73 30               addss   xmm6, dword ptr [rbx+30h]
0000000141807D66  f3 44 0f 58 4b 38            addss   xmm9, dword ptr [rbx+38h]
0000000141807D6C  48 8b cf                     mov     rcx, rdi
0000000141807D6F  c7 45 f3 00 00 00 00         mov     [rbp+57h+var_64], 0
0000000141807D76  f3 0f 11 75 e7               movss   [rbp+57h+var_70], xmm6
0000000141807D7B  f3 44 0f 11 4d ef            movss   [rbp+57h+var_68], xmm9
0000000141807D81  e8 2a 0c 09 ff               call    Client__Game__Object__GameObject__GetPosition
0000000141807D86  f3 0f 10 40 04               movss   xmm0, dword ptr [rax+4]
0000000141807D8B  f3 0f 11 45 eb               movss   [rbp+57h+var_6C], xmm0
0000000141807D90  f3 0f 10 43 6c               movss   xmm0, dword ptr [rbx+6Ch]
0000000141807D95  f3 0f 59 43 68               mulss   xmm0, dword ptr [rbx+68h]
0000000141807D9A  f3 0f 58 43 64               addss   xmm0, dword ptr [rbx+64h]
0000000141807D9F  e8 7c c5 04 ff               call    sub_140854320
0000000141807DA4  45 33 c0                     xor     r8d, r8d
0000000141807DA7  b2 01                        mov     dl, 1
0000000141807DA9  48 8b cf                     mov     rcx, rdi
0000000141807DAC  0f 28 f8                     movaps  xmm7, xmm0
0000000141807DAF  e8 8c fc 08 ff               call    sub_140897A40
0000000141807DB4  44 0f 28 54 24 40            movaps  xmm10, [rsp+90h+var_58+8]
0000000141807DBA  44 0f 28 4c 24 50            movaps  xmm9, [rsp+90h+var_48+8]
0000000141807DC0  48 8b b4 24 a8 00 00 00      mov     rsi, [rsp+90h+arg_8]
0000000141807DC8  84 c0                        test    al, al
0000000141807DCA  74 17                        jz      short loc_141807DE3
0000000141807DCC  41 b1 01                     mov     r9b, 1
0000000141807DCF  48 8d 55 e7                  lea     rdx, [rbp+57h+var_70]
0000000141807DD3  0f 28 d7                     movaps  xmm2, xmm7
0000000141807DD6  48 8b cb                     mov     rcx, rbx
0000000141807DD9  e8 62 11 00 00               call    sub_141808F40
0000000141807DDE  e9 db 00 00 00               jmp     loc_141807EBE
0000000141807DE3  80 7b 7a 00                  cmp     byte ptr [rbx+7Ah], 0
0000000141807DE7  0f 85 c2 00 00 00            jnz     loc_141807EAF
0000000141807DED  48 8b 07                     mov     rax, [rdi]
0000000141807DF0  48 8b cf                     mov     rcx, rdi
0000000141807DF3  ff 50 10                     call    qword ptr [rax+10h]
0000000141807DF6  83 f8 02                     cmp     eax, 2
0000000141807DF9  75 0a                        jnz     short loc_141807E05
0000000141807DFB  80 7b 73 04                  cmp     byte ptr [rbx+73h], 4
0000000141807DFF  0f 84 87 00 00 00            jz      loc_141807E8C
0000000141807E05  4c 8d 4d f7                  lea     r9, [rbp+57h+var_60]
0000000141807E09  48 c7 45 f7 00 00 00 00      mov     [rbp+57h+var_60], 0
0000000141807E11  4c 8d 45 67                  lea     r8, [rbp+57h+arg_0]
0000000141807E15  c7 45 ff 00 00 00 00         mov     dword ptr [rbp+57h+var_58], 0
0000000141807E1C  48 8d 55 e7                  lea     rdx, [rbp+57h+var_70]
0000000141807E20  c6 45 67 00                  mov     [rbp+57h+arg_0], 0
0000000141807E24  48 8b cb                     mov     rcx, rbx
0000000141807E27  e8 04 0b 00 00               call    sub_141808930
0000000141807E2C  80 7d 67 00                  cmp     [rbp+57h+arg_0], 0
0000000141807E30  74 5a                        jz      short loc_141807E8C
0000000141807E32  f3 0f 10 75 fb               movss   xmm6, dword ptr [rbp+57h+var_60+4]
0000000141807E37  44 0f 2f c6                  comiss  xmm8, xmm6
0000000141807E3B  73 4b                        jnb     short loc_141807E88
0000000141807E3D  f3 0f 10 45 f7               movss   xmm0, dword ptr [rbp+57h+var_60]
0000000141807E42  f3 0f 10 4d ff               movss   xmm1, dword ptr [rbp+57h+var_58]
0000000141807E47  f3 0f 59 c0                  mulss   xmm0, xmm0
0000000141807E4B  f3 0f 59 c9                  mulss   xmm1, xmm1
0000000141807E4F  f3 0f 58 c8                  addss   xmm1, xmm0
0000000141807E53  0f 57 c0                     xorps   xmm0, xmm0
0000000141807E56  0f 2e c1                     ucomiss xmm0, xmm1
0000000141807E59  77 09                        ja      short loc_141807E64
0000000141807E5B  0f 57 c0                     xorps   xmm0, xmm0
0000000141807E5E  f3 0f 51 c1                  sqrtss  xmm0, xmm1
0000000141807E62  eb 08                        jmp     short loc_141807E6C
0000000141807E64  0f 28 c1                     movaps  xmm0, xmm1; X
0000000141807E67  e8 5c c6 5d 00               call    sqrtf
0000000141807E6C  f3 0f 5e c6                  divss   xmm0, xmm6; X
0000000141807E70  e8 a7 9a 5f 00               call    atanf
0000000141807E75  e8 b6 47 ff ff               call    sub_1417FC630
0000000141807E7A  0f 28 f0                     movaps  xmm6, xmm0
0000000141807E7D  e8 fe be 05 ff               call    sub_140863D80
0000000141807E82  0f 2f 70 08                  comiss  xmm6, dword ptr [rax+8]
0000000141807E86  72 04                        jb      short loc_141807E8C
0000000141807E88  c6 43 7a 01                  mov     byte ptr [rbx+7Ah], 1
0000000141807E8C  48 8d 55 e7                  lea     rdx, [rbp+57h+var_70]
0000000141807E90  48 8b cb                     mov     rcx, rbx
0000000141807E93  e8 48 0e 00 00               call    sub_141808CE0
0000000141807E98  f3 0f 10 5d ef               movss   xmm3, [rbp+57h+var_68]
0000000141807E9D  48 8b cf                     mov     rcx, rdi
0000000141807EA0  f3 0f 10 55 eb               movss   xmm2, [rbp+57h+var_6C]
0000000141807EA5  f3 0f 10 4d e7               movss   xmm1, [rbp+57h+var_70]
0000000141807EAA  e8 51 0b 09 ff               call    Client__Game__Object__GameObject__SetPosition
0000000141807EAF  48 8d 8f f0 01 00 00         lea     rcx, [rdi+1F0h]
0000000141807EB6  0f 28 cf                     movaps  xmm1, xmm7
0000000141807EB9  e8 e2 22 01 00               call    sub_14181A1A0
0000000141807EBE  0f 28 7c 24 70               movaps  xmm7, [rsp+90h+var_28+8]
0000000141807EC3  0f 28 b4 24 80 00 00 00      movaps  xmm6, [rsp+90h+var_18+8]
0000000141807ECB  44 0f 28 44 24 60            movaps  xmm8, [rsp+90h+var_38+8]
0000000141807ED1  48 8b bc 24 b0 00 00 00      mov     rdi, [rsp+90h+arg_10]
0000000141807ED9  48 8b 9c 24 b8 00 00 00      mov     rbx, [rsp+90h+arg_18]
0000000141807EE1  48 81 c4 90 00 00 00         add     rsp, 90h
0000000141807EE8  5d                           pop     rbp
0000000141807EE9  c3                           retn