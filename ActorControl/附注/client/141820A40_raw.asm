0000000141820A40  40 55                        push    rbp
0000000141820A42  56                           push    rsi
0000000141820A43  57                           push    rdi
0000000141820A44  48 81 ec c0 00 00 00         sub     rsp, 0C0h
0000000141820A4B  80 b9 f0 03 00 00 00         cmp     byte ptr [rcx+3F0h], 0
0000000141820A52  49 8b f0                     mov     rsi, r8
0000000141820A55  0f 29 bc 24 a0 00 00 00      movaps  [rsp+0D8h+var_38], xmm7
0000000141820A5D  48 8b ea                     mov     rbp, rdx
0000000141820A60  0f 28 fb                     movaps  xmm7, xmm3
0000000141820A63  48 8b f9                     mov     rdi, rcx
0000000141820A66  76 0d                        jbe     short loc_141820A75
0000000141820A68  80 b9 f2 03 00 00 07         cmp     byte ptr [rcx+3F2h], 7
0000000141820A6F  0f 87 34 03 00 00            ja      loc_141820DA9
0000000141820A75  83 b9 d0 00 00 00 00         cmp     dword ptr [rcx+0D0h], 0
0000000141820A7C  48 89 9c 24 e0 00 00 00      mov     [rsp+0D8h+arg_0], rbx
0000000141820A84  4c 89 b4 24 e8 00 00 00      mov     [rsp+0D8h+arg_8], r14
0000000141820A8C  4c 89 bc 24 f0 00 00 00      mov     [rsp+0D8h+arg_10], r15
0000000141820A94  0f 29 b4 24 b0 00 00 00      movaps  [rsp+0D8h+var_28], xmm6
0000000141820A9C  44 0f 29 84 24 90 00 00 00   movaps  [rsp+0D8h+var_48], xmm8
0000000141820AA5  44 0f 29 8c 24 80 00 00 00   movaps  [rsp+0D8h+var_58], xmm9
0000000141820AAE  44 0f 29 54 24 70            movaps  [rsp+0D8h+var_68], xmm10
0000000141820AB4  44 0f 29 5c 24 60            movaps  [rsp+0D8h+var_78], xmm11
0000000141820ABA  44 0f 29 64 24 50            movaps  [rsp+0D8h+var_88], xmm12
0000000141820AC0  44 0f 29 6c 24 40            movaps  [rsp+0D8h+var_98], xmm13
0000000141820AC6  74 1b                        jz      short loc_141820AE3
0000000141820AC8  80 b9 01 01 00 00 03         cmp     byte ptr [rcx+101h], 3
0000000141820ACF  74 12                        jz      short loc_141820AE3
0000000141820AD1  b2 01                        mov     dl, 1
0000000141820AD3  e8 68 9b ff ff               call    sub_14181A640
0000000141820AD8  48 8d 4f 10                  lea     rcx, [rdi+10h]
0000000141820ADC  33 d2                        xor     edx, edx
0000000141820ADE  e8 4d 5d fe ff               call    sub_141806830
0000000141820AE3  b2 07                        mov     dl, 7
0000000141820AE5  48 8b cf                     mov     rcx, rdi
0000000141820AE8  e8 b3 5d ff ff               call    sub_1418168A0
0000000141820AED  0f b6 87 10 04 00 00         movzx   eax, byte ptr [rdi+410h]
0000000141820AF4  fe c8                        dec     al
0000000141820AF6  3c 02                        cmp     al, 2
0000000141820AF8  77 1d                        ja      short loc_141820B17
0000000141820AFA  48 8b cf                     mov     rcx, rdi
0000000141820AFD  e8 6e c2 ff ff               call    sub_14181CD70
0000000141820B02  80 78 66 00                  cmp     byte ptr [rax+66h], 0
0000000141820B06  74 08                        jz      short loc_141820B10
0000000141820B08  48 8b c8                     mov     rcx, rax
0000000141820B0B  e8 40 9d fe ff               call    sub_14180A850
0000000141820B10  c6 87 10 04 00 00 00         mov     byte ptr [rdi+410h], 0
0000000141820B17  48 8b 97 e0 03 00 00         mov     rdx, [rdi+3E0h]
0000000141820B1E  48 8d 0d 50 ac 28 01         lea     rcx, unk_142AAB775
0000000141820B25  80 8f 39 04 00 00 20         or      byte ptr [rdi+439h], 20h
0000000141820B2C  45 33 ff                     xor     r15d, r15d
0000000141820B2F  44 89 bf ec 03 00 00         mov     [rdi+3ECh], r15d
0000000141820B36  c7 87 f0 03 00 00 0a 09 07 00 mov     dword ptr [rdi+3F0h], 7090Ah
0000000141820B40  e8 eb 04 03 ff               call    nullsub_107
0000000141820B45  48 8b cd                     mov     rcx, rbp
0000000141820B48  e8 63 7e 07 ff               call    Client__Game__Object__GameObject__GetPosition
0000000141820B4D  f3 0f 10 0e                  movss   xmm1, dword ptr [rsi]
0000000141820B51  48 8d 4c 24 30               lea     rcx, [rsp+0D8h+var_A8]
0000000141820B56  f3 0f 10 b5 c0 00 00 00      movss   xmm6, dword ptr [rbp+0C0h]
0000000141820B5E  48 8b d8                     mov     rbx, rax
0000000141820B61  f3 0f 10 56 04               movss   xmm2, dword ptr [rsi+4]
0000000141820B66  f3 0f 11 4c 24 30            movss   [rsp+0D8h+var_A8], xmm1
0000000141820B6C  f3 0f 10 4e 08               movss   xmm1, dword ptr [rsi+8]
0000000141820B71  f3 0f 11 4c 24 38            movss   [rsp+0D8h+var_A0], xmm1
0000000141820B77  0f 28 ce                     movaps  xmm1, xmm6
0000000141820B7A  f3 0f 11 54 24 34            movss   [rsp+0D8h+var_A4], xmm2
0000000141820B80  44 89 7c 24 3c               mov     [rsp+0D8h+var_9C], r15d
0000000141820B85  e8 a6 3c 03 ff               call    sub_140854830
0000000141820B8A  f3 0f 58 f7                  addss   xmm6, xmm7
0000000141820B8E  0f 28 c6                     movaps  xmm0, xmm6
0000000141820B91  e8 8a 37 03 ff               call    sub_140854320
0000000141820B96  f3 44 0f 10 44 24 30         movss   xmm8, [rsp+0D8h+var_A8]
0000000141820B9D  44 0f 28 d8                  movaps  xmm11, xmm0
0000000141820BA1  f3 44 0f 10 54 24 34         movss   xmm10, [rsp+0D8h+var_A4]
0000000141820BA8  f3 44 0f 10 4c 24 38         movss   xmm9, [rsp+0D8h+var_A0]
0000000141820BAF  48 8b 8f e0 03 00 00         mov     rcx, [rdi+3E0h]
0000000141820BB6  f3 44 0f 58 03               addss   xmm8, dword ptr [rbx]
0000000141820BBB  f3 44 0f 58 53 04            addss   xmm10, dword ptr [rbx+4]
0000000141820BC1  f3 44 0f 58 4b 08            addss   xmm9, dword ptr [rbx+8]
0000000141820BC7  44 8b 75 78                  mov     r14d, [rbp+78h]
0000000141820BCB  e8 e0 7d 07 ff               call    Client__Game__Object__GameObject__GetPosition
0000000141820BD0  48 8b 8f e0 03 00 00         mov     rcx, [rdi+3E0h]
0000000141820BD7  41 0f 28 c3                  movaps  xmm0, xmm11
0000000141820BDB  48 8b f0                     mov     rsi, rax
0000000141820BDE  f3 44 0f 10 a1 c0 00 00 00   movss   xmm12, dword ptr [rcx+0C0h]
0000000141820BE7  f3 41 0f 5c c4               subss   xmm0, xmm12
0000000141820BEC  e8 2f 37 03 ff               call    sub_140854320
0000000141820BF1  0f b6 ac 24 08 01 00 00      movzx   ebp, [rsp+0D8h+a6]
0000000141820BF9  41 0f 28 d0                  movaps  xmm2, xmm8
0000000141820BFD  41 0f 28 c9                  movaps  xmm1, xmm9
0000000141820C01  44 0f 28 e8                  movaps  xmm13, xmm0
0000000141820C05  f3 0f 5c 16                  subss   xmm2, dword ptr [rsi]
0000000141820C09  f3 0f 5c 4e 08               subss   xmm1, dword ptr [rsi+8]
0000000141820C0E  40 84 ed                     test    bpl, bpl
0000000141820C11  74 0a                        jz      short loc_141820C1D
0000000141820C13  f3 0f 10 3d f5 b2 8f 00      movss   xmm7, cs:flt_14211BF10
0000000141820C1B  eb 08                        jmp     short loc_141820C25
0000000141820C1D  f3 0f 10 3d 07 b3 8f 00      movss   xmm7, cs:flt_14211BF2C
0000000141820C25  f3 0f 59 c9                  mulss   xmm1, xmm1
0000000141820C29  0f 57 c0                     xorps   xmm0, xmm0
0000000141820C2C  f3 0f 59 d2                  mulss   xmm2, xmm2
0000000141820C30  f3 0f 58 ca                  addss   xmm1, xmm2
0000000141820C34  0f 2e c1                     ucomiss xmm0, xmm1
0000000141820C37  77 09                        ja      short loc_141820C42
0000000141820C39  0f 57 f6                     xorps   xmm6, xmm6
0000000141820C3C  f3 0f 51 f1                  sqrtss  xmm6, xmm1
0000000141820C40  eb 0b                        jmp     short loc_141820C4D
0000000141820C42  0f 28 c1                     movaps  xmm0, xmm1; X
0000000141820C45  e8 7e 38 5c 00               call    sqrtf
0000000141820C4A  0f 28 f0                     movaps  xmm6, xmm0
0000000141820C4D  f3 0f 10 0d 63 c3 ab 00      movss   xmm1, cs:dword_1422DCFB8
0000000141820C55  f3 0f 5e f7                  divss   xmm6, xmm7
0000000141820C59  0f 2f ce                     comiss  xmm1, xmm6
0000000141820C5C  76 03                        jbe     short loc_141820C61
0000000141820C5E  0f 57 f6                     xorps   xmm6, xmm6
0000000141820C61  c7 87 00 03 00 00 0b 00 00 00 mov     dword ptr [rdi+300h], 0Bh
0000000141820C6B  48 8b 8f 70 03 00 00         mov     rcx, [rdi+370h]
0000000141820C72  48 85 c9                     test    rcx, rcx
0000000141820C75  74 2c                        jz      short loc_141820CA3
0000000141820C77  b8 ff ff ff ff               mov     eax, 0FFFFFFFFh
0000000141820C7C  f0 0f c1 41 08               lock xadd [rcx+8], eax
0000000141820C81  83 f8 01                     cmp     eax, 1
0000000141820C84  75 16                        jnz     short loc_141820C9C
0000000141820C86  4c 89 39                     mov     [rcx], r15
0000000141820C89  48 8d 8f 70 03 00 00         lea     rcx, [rdi+370h]
0000000141820C90  48 8b 97 70 03 00 00         mov     rdx, [rdi+370h]
0000000141820C97  e8 e4 5f 0a 00               call    sub_1418C6C80
0000000141820C9C  4c 89 bf 70 03 00 00         mov     [rdi+370h], r15
0000000141820CA3  48 8b 9c 24 e0 00 00 00      mov     rbx, [rsp+0D8h+arg_0]
0000000141820CAB  4c 89 bf 48 03 00 00         mov     [rdi+348h], r15
0000000141820CB2  4c 89 bf 10 03 00 00         mov     [rdi+310h], r15
0000000141820CB9  4c 89 bf 20 03 00 00         mov     [rdi+320h], r15
0000000141820CC0  4c 89 bf 30 03 00 00         mov     [rdi+330h], r15
0000000141820CC7  4c 89 bf 18 03 00 00         mov     [rdi+318h], r15
0000000141820CCE  4c 89 bf 28 03 00 00         mov     [rdi+328h], r15
0000000141820CD5  44 89 bf 38 03 00 00         mov     [rdi+338h], r15d
0000000141820CDC  4c 89 bf 40 03 00 00         mov     [rdi+340h], r15
0000000141820CE3  66 44 89 bf 50 03 00 00      mov     [rdi+350h], r15w
0000000141820CEB  8b 06                        mov     eax, [rsi]
0000000141820CED  4c 8b bc 24 f0 00 00 00      mov     r15, [rsp+0D8h+arg_10]
0000000141820CF5  89 87 10 03 00 00            mov     [rdi+310h], eax
0000000141820CFB  8b 46 04                     mov     eax, [rsi+4]
0000000141820CFE  89 87 14 03 00 00            mov     [rdi+314h], eax
0000000141820D04  8b 46 08                     mov     eax, [rsi+8]
0000000141820D07  89 87 18 03 00 00            mov     [rdi+318h], eax
0000000141820D0D  0f b7 84 24 00 01 00 00      movzx   eax, [rsp+0D8h+a5]
0000000141820D15  f3 44 0f 11 87 20 03 00 00   movss   dword ptr [rdi+320h], xmm8
0000000141820D1E  44 0f 28 84 24 90 00 00 00   movaps  xmm8, [rsp+0D8h+var_48]
0000000141820D27  f3 44 0f 11 97 24 03 00 00   movss   dword ptr [rdi+324h], xmm10
0000000141820D30  44 0f 28 54 24 70            movaps  xmm10, [rsp+0D8h+var_68]
0000000141820D36  f3 44 0f 11 8f 28 03 00 00   movss   dword ptr [rdi+328h], xmm9
0000000141820D3F  44 0f 28 8c 24 80 00 00 00   movaps  xmm9, [rsp+0D8h+var_58]
0000000141820D48  f3 44 0f 11 a7 30 03 00 00   movss   dword ptr [rdi+330h], xmm12
0000000141820D51  44 0f 28 64 24 50            movaps  xmm12, [rsp+0D8h+var_88]
0000000141820D57  f3 44 0f 11 9f 34 03 00 00   movss   dword ptr [rdi+334h], xmm11
0000000141820D60  44 0f 28 5c 24 60            movaps  xmm11, [rsp+0D8h+var_78]
0000000141820D66  f3 44 0f 11 af 38 03 00 00   movss   dword ptr [rdi+338h], xmm13
0000000141820D6F  44 0f 28 6c 24 40            movaps  xmm13, [rsp+0D8h+var_98]
0000000141820D75  f3 0f 11 b7 40 03 00 00      movss   dword ptr [rdi+340h], xmm6
0000000141820D7D  0f 28 b4 24 b0 00 00 00      movaps  xmm6, [rsp+0D8h+var_28]
0000000141820D85  44 89 b7 48 03 00 00         mov     [rdi+348h], r14d
0000000141820D8C  4c 8b b4 24 e8 00 00 00      mov     r14, [rsp+0D8h+arg_8]
0000000141820D94  66 89 87 4c 03 00 00         mov     [rdi+34Ch], ax
0000000141820D9B  66 89 87 4e 03 00 00         mov     [rdi+34Eh], ax
0000000141820DA2  40 88 af 51 03 00 00         mov     [rdi+351h], bpl
0000000141820DA9  0f 28 bc 24 a0 00 00 00      movaps  xmm7, [rsp+0D8h+var_38]
0000000141820DB1  48 81 c4 c0 00 00 00         add     rsp, 0C0h
0000000141820DB8  5f                           pop     rdi
0000000141820DB9  5e                           pop     rsi
0000000141820DBA  5d                           pop     rbp
0000000141820DBB  c3                           retn