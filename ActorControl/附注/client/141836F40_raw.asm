0000000141836F40 mov     rax, rsp
0000000141836F43 mov     [rax+8], rbx
0000000141836F47 mov     [rax+18h], rsi
0000000141836F4B push    rbp
0000000141836F4C push    rdi
0000000141836F4D push    r14
0000000141836F4F lea     rbp, [rax-248h]
0000000141836F56 sub     rsp, 330h
0000000141836F5D movaps  xmmword ptr [rax-28h], xmm6
0000000141836F61 movaps  xmmword ptr [rax-38h], xmm7
0000000141836F65 movaps  xmmword ptr [rax-48h], xmm8
0000000141836F6A mov     rax, cs:__security_cookie
0000000141836F71 xor     rax, rsp
0000000141836F74 mov     [rbp+240h+var_50], rax
0000000141836F7B mov     rbx, cs:source
0000000141836F82 mov     rsi, rdx
0000000141836F85 test    rbx, rbx
0000000141836F88 jz      loc_14183739A
0000000141836F8E lea     rcx, word_142AA7678
0000000141836F95 call    sub_140604D10
0000000141836F9A test    al, al
0000000141836F9C jnz     short loc_141836FB7
0000000141836F9E mov     edx, 154h; unlockLink
0000000141836FA3 lea     rcx, qword_142ADE980; self
0000000141836FAA call    Client__Game__UI__UIState__IsUnlockLinkUnlocked
0000000141836FAF test    al, al
0000000141836FB1 jz      loc_14183739A
0000000141836FB7 mov     rax, cs:qword_142AAB7B8
0000000141836FBE movss   xmm6, cs:flt_14211BF70
0000000141836FC6 test    rax, rax
0000000141836FC9 jz      short loc_141836FD9
0000000141836FCB cmp     byte ptr [rax+3Bh], 0
0000000141836FCF jge     short loc_141836FD9
0000000141836FD1 movss   xmm6, cs:flt_14214B59C
0000000141836FD9 mov     rcx, rbx; self
0000000141836FDC call    Client__Game__Object__GameObject__GetPosition
0000000141836FE1 lea     rcx, [rbx+1F0h]; self
0000000141836FE8 mov     rdi, rax
0000000141836FEB call    Client__Game__Control__MoveControl__MoveController__IsFlying
0000000141836FF0 test    al, al
0000000141836FF2 jnz     short loc_141837001
0000000141836FF4 test    byte ptr [rbx+628h], 20h
0000000141836FFB jz      loc_14183739A
0000000141837001 mov     rax, cs:qword_142909910
0000000141837008 lea     r9, [rsp+340h+direction+4]; direction
000000014183700D xorps   xmm0, xmm0
0000000141837010 mov     [rbp+240h+var_2A0], 0
0000000141837018 movaps  [rsp+340h+hitInfo+8], xmm0
000000014183701D lea     r8, [rsp+340h+origin]; origin
0000000141837022 movaps  [rbp+240h+var_2B0], xmm0
0000000141837026 lea     rdx, [rsp+340h+hitInfo+8]; hitInfo
000000014183702B movss   xmm0, cs:control
0000000141837033 xor     r14d, r14d
0000000141837036 mov     [rbp+240h+var_298], 0
000000014183703D xorps   xmm1, xmm1
0000000141837040 movaps  [rbp+240h+var_2C0], xmm1
0000000141837044 mov     [rbp+240h+var_290], r14
0000000141837048 mov     [rbp+240h+var_288], r14d
000000014183704C mov     [rbp+240h+var_280], r14
0000000141837050 mov     [rbp+240h+var_278], r14d
0000000141837054 mov     rcx, [rax+2B58h]; self
000000014183705B lea     rax, [rsp+340h+var_2E0]
0000000141837060 movss   xmm1, dword ptr [rdi]
0000000141837064 movss   dword ptr [rsp+340h+var_2EC], xmm0
000000014183706A movss   xmm0, dword ptr [rdi+4]
000000014183706F addss   xmm0, cs:target
0000000141837077 mov     [rsp+340h+flags], rax; flags
000000014183707C mov     [rsp+340h+layerMask], 1; layerMask
0000000141837084 movss   [rsp+340h+origin], xmm1
000000014183708A mov     qword ptr [rsp+340h+var_2E0], 800000h
0000000141837093 movss   [rsp+340h+var_2FC], xmm0
0000000141837099 movss   xmm0, dword ptr [rdi+8]
000000014183709E movss   [rsp+340h+var_2F8], xmm0
00000001418370A4 movss   xmm0, cs:flt_14211BF10
00000001418370AC movss   [rsp+340h+maxDistance], xmm0; maxDistance
00000001418370B2 mov     qword ptr [rsp+340h+hitInfo], 800000h
00000001418370BB mov     dword ptr [rsp+340h+direction+4], r14d
00000001418370C0 mov     dword ptr [rsp+340h+var_2EC+4], r14d
00000001418370C5 mov     dword ptr [rsp+340h+direction], 38D1B717h
00000001418370CD call    Common__Component__BGCollision__BGCollisionModule__SweepSphereMaterialFilter
00000001418370D2 test    al, al
00000001418370D4 jnz     short loc_1418370DF
00000001418370D6 lea     eax, [r14+2]
00000001418370DA jmp     loc_14183739F
00000001418370DF mov     rax, cs:qword_142909910
00000001418370E6 lea     r9, [rsp+340h+direction+4]; direction
00000001418370EB movss   xmm0, dword ptr [rdi]
00000001418370EF lea     r8, [rsp+340h+origin]; origin
00000001418370F4 movss   xmm1, dword ptr [rdi+4]
00000001418370F9 lea     rdx, [rsp+340h+hitInfo+8]; hitInfo
00000001418370FE subss   xmm1, xmm6
0000000141837102 mov     rcx, [rax+2B58h]; self
0000000141837109 lea     rax, [rsp+340h+var_2E0]
000000014183710E subss   xmm6, cs:dword_14211BF50
0000000141837116 mov     [rsp+340h+flags], rax; flags
000000014183711B movss   [rsp+340h+origin], xmm0
0000000141837121 movss   xmm0, dword ptr [rdi+8]
0000000141837126 mov     [rsp+340h+layerMask], 1; layerMask
000000014183712E movss   [rsp+340h+maxDistance], xmm6; maxDistance
0000000141837134 movss   [rsp+340h+var_2FC], xmm1
000000014183713A movss   [rsp+340h+var_2F8], xmm0
0000000141837140 mov     qword ptr [rsp+340h+var_2E0], 1000000h
0000000141837149 mov     qword ptr [rsp+340h+hitInfo], 1000000h
0000000141837152 mov     dword ptr [rsp+340h+direction+4], r14d
0000000141837157 mov     [rsp+340h+var_2EC], 3F800000h
0000000141837160 mov     dword ptr [rsp+340h+direction], 38D1B717h
0000000141837168 call    Common__Component__BGCollision__BGCollisionModule__SweepSphereMaterialFilter
000000014183716D test    al, al
000000014183716F jnz     short loc_14183717B
0000000141837171 mov     eax, 3
0000000141837176 jmp     loc_14183739F
000000014183717B movss   xmm7, dword ptr [rdi]
000000014183717F lea     rax, [rbp+240h+var_228]
0000000141837183 movss   xmm8, dword ptr [rdi+8]
0000000141837189 xorps   xmm0, xmm0
000000014183718C movss   xmm6, dword ptr [rsp+340h+hitInfo+0Ch]
0000000141837192 xorps   xmm1, xmm1
0000000141837195 movss   [rsp+340h+origin], xmm7
000000014183719B mov     ecx, 0Ah
00000001418371A0 movss   [rsp+340h+var_2FC], xmm6
00000001418371A6 movss   [rsp+340h+var_2F8], xmm8
00000001418371AD movaps  xmmword ptr [rbp+240h+a1], xmm0
00000001418371B1 movaps  [rbp+240h+var_260], xmm1
00000001418371B5 mov     dword ptr [rsp+340h+direction], r14d
00000001418371BA mov     [rbp+240h+var_250], r14d
00000001418371BE mov     [rbp+240h+var_24C], r14b
00000001418371C2 nop     dword ptr [rax+00h]
00000001418371C6 nop     word ptr [rax+rax+00000000h]
00000001418371D0 mov     [rax-18h], r14
00000001418371D4 mov     [rax-10h], r14
00000001418371D8 mov     [rax-8], r14
00000001418371DC mov     [rax], r14
00000001418371DF mov     [rax+8], r14
00000001418371E3 lea     rax, [rax+30h]
00000001418371E7 sub     rcx, 1
00000001418371EB jnz     short loc_1418371D0
00000001418371ED movaps  xmm0, cs:xmmword_14214B670
00000001418371F4 lea     r8, [rsp+340h+var_2E0]
00000001418371F9 movss   xmm3, cs:flt_14211BF2C
0000000141837201 lea     rdx, [rsp+340h+origin]
0000000141837206 mov     [rsp+340h+layerMask], r14d
000000014183720B lea     rcx, [rbp+240h+a1]
000000014183720F movaps  xmmword ptr [rsp+340h+var_2E0], xmm0
0000000141837214 mov     [rbp+240h+var_60], r14d
000000014183721B mov     [rsp+340h+maxDistance], 2
0000000141837223 call    sub_14182EA80
0000000141837228 lea     rcx, [rbp+240h+a1]; a1
000000014183722C call    sub_141842C10
0000000141837231 test    al, al
0000000141837233 jnz     loc_141837393
0000000141837239 movss   xmm3, [rbp+240h+a1]
000000014183723E movss   xmm5, [rbp+240h+a1+4]
0000000141837243 movaps  xmm1, xmm3
0000000141837246 movss   xmm4, [rbp+240h+a1+8]
000000014183724B subss   xmm1, xmm7
000000014183724F movaps  xmm2, xmm5
0000000141837252 movaps  xmm0, xmm4
0000000141837255 subss   xmm2, xmm6
0000000141837259 subss   xmm0, xmm8
000000014183725E mulss   xmm1, xmm1
0000000141837262 mulss   xmm2, xmm2
0000000141837266 mulss   xmm0, xmm0
000000014183726A addss   xmm2, xmm1
000000014183726E addss   xmm2, xmm0
0000000141837272 comiss  xmm2, cs:dword_1422DD050
0000000141837279 ja      loc_141837393
000000014183727F movss   xmm1, cs:dword_14216C028
0000000141837287 comiss  xmm1, xmm3
000000014183728A ja      loc_141837393
0000000141837290 movss   xmm0, cs:flt_14211BFCC
0000000141837298 comiss  xmm3, xmm0
000000014183729B ja      loc_141837393
00000001418372A1 comiss  xmm1, xmm5
00000001418372A4 ja      loc_141837393
00000001418372AA comiss  xmm5, xmm0
00000001418372AD ja      loc_141837393
00000001418372B3 comiss  xmm1, xmm4
00000001418372B6 ja      loc_141837393
00000001418372BC comiss  xmm4, xmm0
00000001418372BF ja      loc_141837393
00000001418372C5 cmp     [rbp+240h+var_250], 2
00000001418372C9 jz      loc_141837393
00000001418372CF call    sub_140863D80
00000001418372D4 movss   xmm0, [rbp+240h+a1+4]
00000001418372D9 addss   xmm0, dword ptr [rax+0Ch]
00000001418372DE addss   xmm0, cs:target
00000001418372E6 comiss  xmm0, xmm6
00000001418372E9 jnb     loc_141837393
00000001418372EF lea     rcx, [rbp+240h+a1]; a1
00000001418372F3 call    sub_140E13F20
00000001418372F8 test    al, al
00000001418372FA jnz     short loc_141837306
00000001418372FC mov     eax, 5
0000000141837301 jmp     loc_14183739F
0000000141837306 movzx   eax, word ptr [rbx+1C4h]
000000014183730D test    ax, ax
0000000141837310 jz      short loc_14183732B
0000000141837312 mov     ecx, eax; a1
0000000141837314 call    EXD__Transformation__Row_14083D180
0000000141837319 test    rax, rax
000000014183731C jz      short loc_14183732B
000000014183731E test    byte ptr [rax+3Bh], 2
0000000141837322 jnz     short loc_14183732B
0000000141837324 mov     eax, 7
0000000141837329 jmp     short loc_14183739F
000000014183732B xor     r9d, r9d; excludedCondition2
000000014183732E lea     rcx, byte_142AF9070; self
0000000141837335 xor     r8d, r8d; excludedCondition1
0000000141837338 mov     edx, 97h; permissionId
000000014183733D call    Client__Game__Conditions__HasPermission
0000000141837342 test    al, al
0000000141837344 jnz     short loc_141837369
0000000141837346 xor     r9d, r9d; excludedCondition2
0000000141837349 lea     rcx, byte_142AF9070; self
0000000141837350 mov     edx, 97h; permissionId
0000000141837355 lea     r8d, [r9+9]; excludedCondition1
0000000141837359 call    Client__Game__Conditions__HasPermission
000000014183735E test    al, al
0000000141837360 jz      short loc_14183739A
0000000141837362 mov     eax, 6
0000000141837367 jmp     short loc_14183739F
0000000141837369 test    byte ptr [rbx+690h], 2
0000000141837370 jnz     short loc_14183739A
0000000141837372 movss   xmm0, [rbp+240h+a1]
0000000141837377 xor     eax, eax
0000000141837379 movss   xmm1, [rbp+240h+a1+4]
000000014183737E movss   dword ptr [rsi], xmm0
0000000141837382 movss   xmm0, [rbp+240h+a1+8]
0000000141837387 movss   dword ptr [rsi+8], xmm0
000000014183738C movss   dword ptr [rsi+4], xmm1
0000000141837391 jmp     short loc_14183739F
0000000141837393 mov     eax, 4
0000000141837398 jmp     short loc_14183739F
000000014183739A mov     eax, 1
000000014183739F mov     rcx, [rbp+240h+var_50]
00000001418373A6 xor     rcx, rsp; StackCookie
00000001418373A9 call    __security_check_cookie
00000001418373AE lea     r11, [rsp+340h+var_10]
00000001418373B6 mov     rbx, [r11+20h]
00000001418373BA mov     rsi, [r11+30h]
00000001418373BE movaps  xmm6, xmmword ptr [r11-10h]
00000001418373C3 movaps  xmm7, xmmword ptr [r11-20h]
00000001418373C8 movaps  xmm8, xmmword ptr [r11-30h]
00000001418373CD mov     rsp, r11
00000001418373D0 pop     r14
00000001418373D2 pop     rdi
00000001418373D3 pop     rbp
00000001418373D4 retn