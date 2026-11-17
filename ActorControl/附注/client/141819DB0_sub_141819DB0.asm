0000000141819DB0  48 89 5c 24 08               mov     [rsp+arg_0], rbx
0000000141819DB5  57                           push    rdi
0000000141819DB6  48 83 ec 20                  sub     rsp, 20h
0000000141819DBA  0f b6 81 10 04 00 00         movzx   eax, byte ptr [rcx+410h]
0000000141819DC1  8b fa                        mov     edi, edx
0000000141819DC3  fe c8                        dec     al
0000000141819DC5  48 8b d9                     mov     rbx, rcx
0000000141819DC8  3c 02                        cmp     al, 2
0000000141819DCA  0f 86 a5 00 00 00            jbe     loc_141819E75
0000000141819DD0  80 b9 01 01 00 00 03         cmp     byte ptr [rcx+101h], 3
0000000141819DD7  0f 84 98 00 00 00            jz      loc_141819E75
0000000141819DDD  48 8b 81 98 03 00 00         mov     rax, [rcx+398h]
0000000141819DE4  48 85 c0                     test    rax, rax
0000000141819DE7  74 09                        jz      short loc_141819DF2
0000000141819DE9  83 38 02                     cmp     dword ptr [rax], 2
0000000141819DEC  0f 84 83 00 00 00            jz      loc_141819E75
0000000141819DF2  0f b6 91 f0 03 00 00         movzx   edx, byte ptr [rcx+3F0h]
0000000141819DF9  8b ca                        mov     ecx, edx
0000000141819DFB  83 e9 03                     sub     ecx, 3
0000000141819DFE  74 0a                        jz      short loc_141819E0A
0000000141819E00  83 e9 04                     sub     ecx, 4
0000000141819E03  74 05                        jz      short loc_141819E0A
0000000141819E05  83 f9 01                     cmp     ecx, 1
0000000141819E08  75 04                        jnz     short loc_141819E0E
0000000141819E0A  85 d2                        test    edx, edx
0000000141819E0C  75 67                        jnz     short loc_141819E75
0000000141819E0E  84 d2                        test    dl, dl
0000000141819E10  74 09                        jz      short loc_141819E1B
0000000141819E12  80 bb f2 03 00 00 04         cmp     byte ptr [rbx+3F2h], 4
0000000141819E19  77 5a                        ja      short loc_141819E75
0000000141819E1B  83 bb d0 00 00 00 00         cmp     dword ptr [rbx+0D0h], 0
0000000141819E22  74 0b                        jz      short loc_141819E2F
0000000141819E24  48 8d 4b 10                  lea     rcx, [rbx+10h]; a1
0000000141819E28  33 d2                        xor     edx, edx; a2
0000000141819E2A  e8 01 ca fe ff               call    sub_141806830
0000000141819E2F  b2 04                        mov     dl, 4; a2
0000000141819E31  48 8b cb                     mov     rcx, rbx; a1
0000000141819E34  e8 67 ca ff ff               call    sub_1418168A0
0000000141819E39  48 8b 8b e0 03 00 00         mov     rcx, [rbx+3E0h]; self
0000000141819E40  e8 6b eb 07 ff               call    Client__Game__Object__GameObject__GetPosition
0000000141819E45  0f b7 cf                     movzx   ecx, di
0000000141819E48  45 33 c9                     xor     r9d, r9d; options
0000000141819E4B  48 8b d0                     mov     rdx, rax; position
0000000141819E4E  66 0f 6e d1                  movd    xmm2, ecx
0000000141819E52  48 8b cb                     mov     rcx, rbx; self
0000000141819E55  0f 5b d2                     cvtdq2ps xmm2, xmm2
0000000141819E58  f3 0f 59 15 b4 ee 95 00      mulss   xmm2, cs:dword_142178D14
0000000141819E60  f3 0f 59 15 8c 1f 90 00      mulss   xmm2, cs:flt_14211BDF4
0000000141819E68  f3 0f 5c 15 ac 20 90 00      subss   xmm2, cs:angle; rotation
0000000141819E70  e8 1b 00 00 00               call    sub_141819E90
0000000141819E75  48 8b 5c 24 30               mov     rbx, [rsp+28h+arg_0]
0000000141819E7A  48 83 c4 20                  add     rsp, 20h
0000000141819E7E  5f                           pop     rdi
0000000141819E7F  c3                           retn