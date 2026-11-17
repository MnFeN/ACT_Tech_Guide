__int64 __fastcall sub_141800580(__int64 a1, unsigned __int16 *a2)
{
  unsigned __int16 v3; // cx
  float v5; // xmm9_4
  unsigned int v6; // esi
  int v7; // r12d
  float v8; // xmm6_4
  float v9; // xmm13_4
  float v10; // xmm10_4
  float v11; // xmm0_4
  __int64 *v12; // rdi
  float v13; // xmm7_4
  __int64 v14; // rax
  int v15; // r9d
  float v16; // xmm8_4
  __int64 v17; // rax
  char v18; // cl
  __int64 v19; // rcx
  __int64 result; // rax
  __int64 v21; // rcx
  __int64 v22; // rcx
  __int64 v23; // rcx
  __int64 v24; // rcx
  __int64 v25; // rax
  __int64 v26; // rax
  void *v27; // rdi
  void *v28; // rcx
  float *v29; // rax
  float v30; // xmm2_4
  __int64 v31; // rcx
  __int64 v32; // rax
  __int64 v33; // rdi
  __int64 v34; // rax
  void *v35; // rdi
  void *v36; // rcx
  float *Position; // rax
  float v38; // xmm2_4
  char v39; // cl
  __int64 v40; // rcx
  char v41; // r13
  bool v42; // di
  bool v43; // r15
  int v44; // esi
  float *v45; // rax
  int v46; // r8d
  int v47; // ecx
  float v48; // xmm11_4
  float v49; // xmm2_4
  float v50; // xmm10_4
  int v51; // eax
  unsigned __int16 v52; // ax
  bool v53; // r9
  int v54; // edx
  int v55; // eax
  __int16 v56; // cx
  __int16 v57; // ax
  __int16 v58; // ax
  __int64 v59; // rax
  void *v60; // r14
  void *v61; // rcx
  float *v62; // rax
  float *v63; // rcx
  float v64; // xmm11_4
  float *v65; // rax
  float v66; // xmm6_4
  float v67; // xmm7_4
  float v68; // xmm8_4
  float v69; // xmm0_4
  float v70; // xmm0_4
  float v71; // xmm8_4
  int v72; // edx
  float v73; // xmm0_4
  int v74; // ecx
  float v75; // xmm11_4
  float v76; // xmm6_4
  float v77; // xmm0_4
  char v78; // al
  bool v79; // al
  char v80; // di
  double v81; // xmm0_8
  int v82; // ecx
  __int128 v83; // [rsp+70h] [rbp-90h] BYREF
  _DWORD v84[2]; // [rsp+80h] [rbp-80h] BYREF
  float v85; // [rsp+88h] [rbp-78h]
  int v86; // [rsp+8Ch] [rbp-74h]
  __int64 (__fastcall **v87)(); // [rsp+90h] [rbp-70h] BYREF
  int v88; // [rsp+98h] [rbp-68h]
  int v89; // [rsp+9Ch] [rbp-64h]
  int v90; // [rsp+A0h] [rbp-60h]
  float v91; // [rsp+A4h] [rbp-5Ch]
  float v92; // [rsp+A8h] [rbp-58h]
  int v93; // [rsp+ACh] [rbp-54h]
  __int64 v94; // [rsp+B0h] [rbp-50h]
  int v95; // [rsp+B8h] [rbp-48h]
  int v96; // [rsp+BCh] [rbp-44h]
  char v97; // [rsp+C0h] [rbp-40h]
  char v98; // [rsp+C1h] [rbp-3Fh]
  char v99; // [rsp+C2h] [rbp-3Eh]
  bool v100; // [rsp+C3h] [rbp-3Dh]
  bool v101; // [rsp+C4h] [rbp-3Ch]
  __int16 v102; // [rsp+C5h] [rbp-3Bh]
  char v103; // [rsp+C7h] [rbp-39h]
  char v104; // [rsp+C8h] [rbp-38h]
  bool v105; // [rsp+1C0h] [rbp+C0h]
  bool v106; // [rsp+1C8h] [rbp+C8h]
  float v107; // [rsp+1D0h] [rbp+D0h] BYREF
  float v108; // [rsp+1D8h] [rbp+D8h]

  v3 = a2[1];
  v5 = 0.30000001;
  if ( (v3 & 0x40) != 0 )
  {
    v5 = 0.60000002;
  }
  else if ( (v3 & 0x80u) != 0 )
  {
    v5 = 0.89999998;
  }
  if ( *(float *)&dword_142AB2888 > 0.0 )
    v5 = v5 + *(float *)&dword_142AB2888;
  v6 = a2[1];
  v7 = v3 & 0x320;
  v106 = 1;
  v105 = v5 <= 0.0;
  v8 = (float)((float)((float)a2[3] * 3.0518043) * 0.0099999998) - 1000.0;
  v9 = (float)((float)((float)*a2 * 0.0095875263) * 0.0099999998) - 3.1415927;
  v10 = (float)((float)((float)a2[4] * 3.0518043) * 0.0099999998) - 1000.0;
  v11 = (float)*((unsigned __int8 *)a2 + 4);
  v12 = *(__int64 **)(*(_QWORD *)(a1 + 8) + 992LL);
  v13 = (float)((float)((float)a2[5] * 3.0518043) * 0.0099999998) - 1000.0;
  *(float *)&v83 = v8;
  v14 = *v12;
  *((_QWORD *)&v83 + 1) = LODWORD(v13);
  v108 = v11 / 10.0;
  if ( (*(unsigned int (__fastcall **)(__int64 *))(v14 + 16))(v12) != 2
    && (*(unsigned int (__fastcall **)(__int64 *))(*v12 + 16))(v12) != 3 )
  {
    goto LABEL_15;
  }
  *((float *)&v83 + 1) = v10;
  v16 = v10;
  if ( (v6 & 0x20) != 0 )
    goto LABEL_16;
  v17 = *(_QWORD *)(a1 + 8);
  *((float *)&v83 + 1) = v10;
  v106 = 0;
  v18 = *(_BYTE *)(v17 + 1080);
  if ( (v18 & 1) == 0 )
    goto LABEL_16;
  if ( byte_142AAB774 != 2 )
  {
    *(_QWORD *)(v17 + 1032) = 1069547520;
    *(_BYTE *)(v17 + 1080) = v18 & 0xFE;
LABEL_15:
    *((float *)&v83 + 1) = v10;
    v16 = v10;
    goto LABEL_16;
  }
  *((float *)&v83 + 1) = v10;
  v107 = 0.0;
  if ( (unsigned __int8)sub_141817CA0(
                          v17,
                          (unsigned int)&v83,
                          (unsigned int)&v107,
                          v15,
                          1128792064,
                          0,
                          0,
                          -1082130432,
                          0,
                          0,
                          0,
                          0,
                          0) )
  {
    v16 = v107;
    *((float *)&v83 + 1) = v107;
  }
LABEL_16:
  if ( *(_BYTE *)(a1 + 39) )
  {
    v19 = *(_QWORD *)(a1 + 8);
    *(_BYTE *)(a1 + 39) = 0;
    v105 = 1;
    sub_140909D60(*(_QWORD *)(v19 + 992));
  }
  result = *(_QWORD *)(a1 + 8);
  v21 = *(_QWORD *)(result + 992);
  if ( *(_BYTE *)(v21 + 152) )
  {
    *(float *)(v21 + 16) = v8;
    *(float *)(v21 + 20) = v10;
    *(float *)(v21 + 24) = v13;
    *(_DWORD *)(v21 + 28) = 0;
    return result;
  }
  if ( (*(_BYTE *)(result + 1081) & 0x20) == 0 )
  {
    result = sub_140615000(v21 + 1584);
    if ( !(_BYTE)result )
    {
      v22 = *(_QWORD *)(a1 + 8);
      if ( !*(_BYTE *)(v22 + 715) )
        goto LABEL_40;
      if ( v7 != 32 )
      {
        if ( *(_BYTE *)(v22 + 712) )
        {
          v23 = v22 + 592;
          *(float *)(v23 + 80) = v8;
          *(float *)(v23 + 84) = v16;
          *(float *)(v23 + 88) = v13;
          *(float *)(v23 + 92) = v9;
          *(_BYTE *)(v23 + 121) = 1;
          if ( (qword_142AA895B & 4) != 0 && (unsigned __int8)qword_142AA894C < 0x40u )
            result = sub_141808420(v23);
        }
      }
      v24 = *(_QWORD *)(a1 + 8);
      if ( !*(_BYTE *)(v24 + 710) )
      {
LABEL_40:
        if ( (v6 & 0x8000) != 0 )
          return result;
        if ( sub_141819970(*(_QWORD *)(a1 + 8)) )
        {
          if ( *(_BYTE *)(a1 + 36) )
            sub_141801ED0(a1);
          if ( *(_BYTE *)(a1 + 37) )
            sub_141801FF0(a1);
          v32 = *(_QWORD *)(a1 + 8);
          if ( v7 == 32 )
          {
            sub_141806110(v32 + 16, v6, &v83);
          }
          else
          {
            if ( *(_DWORD *)(v32 + 208) )
            {
              sub_141803220(v32 + 16);
              v32 = *(_QWORD *)(a1 + 8);
            }
            v33 = v32 + 16;
            if ( (unsigned __int8)sub_1418067F0(v32 + 16) )
              sub_141802880(v33);
          }
          v34 = *(_QWORD *)(a1 + 8);
          v35 = *(void **)(v34 + 992);
          v36 = v35;
          if ( (*(_BYTE *)(v34 + 1080) & 2) != 0 )
          {
            Position = (float *)Client__Game__Object__GameObject__GetPosition(v35);
            v36 = v35;
            v38 = Position[1];
          }
          else
          {
            v38 = v16;
          }
          Client__Game__Object__GameObject__SetPosition(v36, v8, v38, v13);
          Client__Game__Object__GameObject__SetRotation(*(void **)(*(_QWORD *)(a1 + 8) + 992LL), v9);
          if ( v7 == 32 )
          {
            result = *(_QWORD *)(a1 + 8);
            if ( *(_BYTE *)(result + 1041) < 2u )
              *(_WORD *)(result + 1041) = 2;
          }
          else
          {
            result = sub_140605030(&word_142AA7678);
            if ( (_BYTE)result )
            {
              result = *(_QWORD *)(a1 + 8);
              v39 = *(_BYTE *)(result + 1080);
              if ( v39 >= 0 )
              {
                *(_BYTE *)(result + 1042) = 0;
                *(_BYTE *)(result + 1080) = v39 | 0x80;
              }
              *(_BYTE *)(result + 1081) |= 1u;
              *(_DWORD *)(result + 1028) = 1036831949;
            }
          }
          return result;
        }
        sub_141806110(*(_QWORD *)(a1 + 8) + 16LL, v6, &v83);
        v40 = *(_QWORD *)(a1 + 8);
        v87 = off_142178A60;
        v93 = 0;
        v94 = 0;
        v41 = *(_BYTE *)(v40 + 514);
        v97 = 0;
        v103 = 0;
        v104 = 0;
        v42 = (v6 & 4) != 0;
        v43 = (v6 & 8) != 0;
        v100 = (v6 & 2) != 0;
        v98 = v105;
        v99 = v105;
        v88 = -1082130432;
        v89 = -1082130432;
        v90 = -1082130432;
        v101 = v42;
        v102 = v43;
        v44 = v6 & 0x800;
        if ( v44 )
        {
          v42 = 0;
          v99 = 1;
          v101 = 0;
        }
        v45 = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(v40 + 992));
        v46 = 0xFFFF;
        v47 = 0xFFFF;
        v48 = *v45;
        v49 = v45[1];
        v50 = v45[2];
        v51 = (int)(float)((float)((float)(*v45 + 1000.0) * 100.0) / 3.0518043);
        if ( v51 < 0xFFFF )
          v47 = v51;
        v52 = 0;
        if ( v47 > 0 )
          v52 = v47;
        if ( a2[3] == v52 )
          v48 = v8;
        v53 = a2[3] == v52;
        if ( v7 != 32 )
        {
          v54 = 0xFFFF;
          if ( (int)(float)((float)((float)(v49 + 1000.0) * 100.0) / 3.0518043) < 0xFFFF )
            v54 = (int)(float)((float)((float)(v49 + 1000.0) * 100.0) / 3.0518043);
          v55 = 0xFFFF;
          if ( (int)(float)((float)((float)(v16 + 1000.0) * 100.0) / 3.0518043) < 0xFFFF )
            v55 = (int)(float)((float)((float)(v16 + 1000.0) * 100.0) / 3.0518043);
          v56 = 0;
          if ( v55 > 0 )
            v56 = v55;
          v57 = 0;
          if ( v54 > 0 )
            v57 = v54;
          if ( v56 == v57 )
          {
            v49 = v16;
            v53 = 1;
          }
        }
        if ( (int)(float)((float)((float)(v50 + 1000.0) * 100.0) / 3.0518043) < 0xFFFF )
          v46 = (int)(float)((float)((float)(v50 + 1000.0) * 100.0) / 3.0518043);
        v58 = 0;
        if ( v46 > 0 )
          v58 = v46;
        if ( a2[5] == v58 )
        {
          v50 = v13;
        }
        else if ( !v53 )
        {
LABEL_91:
          v63 = *(float **)(*(_QWORD *)(a1 + 8) + 992LL);
          v64 = v63[48];
          v65 = (float *)Client__Game__Object__GameObject__GetPosition(v63);
          v66 = v8 - *v65;
          v67 = v13 - v65[2];
          v68 = v16 - v65[1];
          v86 = 0;
          *(float *)v84 = v66;
          *(float *)&v84[1] = v68;
          v85 = v67;
          if ( (float)((float)(v66 * v66) + (float)(v67 * v67)) > 0.00000011920929 )
          {
            v69 = atan2f(v66, v67);
            v70 = sub_140854320(v69 - v64);
            v71 = v70;
            if ( !v42 )
            {
              if ( *(_BYTE *)(a1 + 36) )
              {
                v72 = *(_DWORD *)(*(_QWORD *)(a1 + 8) + 500LL);
                if ( v72 == 4
                  || *(_DWORD *)(*(_QWORD *)(a1 + 8) + 500LL) == 5
                  || (unsigned int)(*(_DWORD *)(*(_QWORD *)(a1 + 8) + 500LL) - 6) <= 1 )
                {
                  v73 = fabs(v70);
                  if ( v73 > 0.81681406 )
                  {
                    if ( v73 <= 2.3247786 )
                      v74 = (v71 <= 0.0) + 5;
                    else
                      v74 = 7;
                    v42 = v74 == v72;
                    v101 = v74 == v72;
                  }
                }
              }
            }
            v66 = *(float *)v84;
            v67 = v85;
          }
          v75 = v108;
          v95 = 1;
          v96 = 1;
          v91 = v5 + 0.2;
          v92 = v5 + 0.2;
          if ( v108 > 0.00000011920929 && v5 > 0.00000011920929 && !v43 )
          {
            v76 = (float)(v66 * v66) + (float)(v67 * v67);
            v77 = v76 < 0.0 ? sqrtf(v76) : fsqrt(v76);
            if ( v77 >= 12.0 )
            {
              v78 = v105;
              if ( (float)(v77 / v5) > (float)(v75 * 4.0) )
                v78 = 1;
              v98 = v78;
            }
          }
          *(float *)(a1 + 32) = v75;
          v79 = v7 == 32 || *(_DWORD *)(*(_QWORD *)(a1 + 8) + 208LL);
          sub_1418015D0((void *)a1, (float *)&v83, v9, &v87, v79, v106);
          sub_141802540(a1, v42);
          v80 = 0;
          if ( v44 && (*(_BYTE *)(a1 + 36) || *(_BYTE *)(a1 + 37)) )
          {
            v83 = 0;
            v80 = 1;
            sub_140854740(&v83);
            v81 = sub_140854380(&v83, v84);
            v82 = 0;
            if ( *(float *)&v81 < -0.00000011920929 )
              v82 = 8;
            if ( *(float *)&v81 > 0.00000011920929 )
              v82 = 9;
            *(_DWORD *)(*(_QWORD *)(a1 + 8) + 500LL) = v82;
          }
          result = *(_QWORD *)(a1 + 8);
          *(_BYTE *)(result + 518) = v80;
          if ( *(_BYTE *)(*(_QWORD *)(a1 + 8) + 514LL) )
          {
            if ( !v41 )
            {
              if ( *(_BYTE *)(a1 + 36) )
              {
                result = sub_1418198E0();
                if ( (_BYTE)result )
                {
                  result = sub_141821270(*(_QWORD *)(a1 + 8), 10);
                  if ( !(_BYTE)result )
                    result = sub_14181AAF0(*(_QWORD *)(a1 + 8));
                }
              }
            }
          }
          if ( *(_BYTE *)(a1 + 36) || *(_BYTE *)(a1 + 37) )
          {
            result = *(_QWORD *)(a1 + 8);
            *(_DWORD *)(result + 1012) = 0;
          }
          return result;
        }
        v59 = *(_QWORD *)(a1 + 8);
        v60 = *(void **)(v59 + 992);
        v61 = v60;
        if ( (*(_BYTE *)(v59 + 1080) & 2) != 0 )
        {
          v62 = (float *)Client__Game__Object__GameObject__GetPosition(v60);
          v61 = v60;
          v49 = v62[1];
        }
        Client__Game__Object__GameObject__SetPosition(v61, v48, v49, v50);
        goto LABEL_91;
      }
      if ( (v6 & 0x8000) != 0
        || (v25 = *(_QWORD *)(v24 + 992), *(_BYTE *)(v25 + 7076))
        || (result = (unsigned __int64)*(unsigned int *)(v25 + 280) >> 26, (result & 1) != 0) )
      {
        sub_14181A880(v24);
        v26 = *(_QWORD *)(a1 + 8);
        v27 = *(void **)(v26 + 992);
        v28 = v27;
        if ( (*(_BYTE *)(v26 + 1080) & 2) != 0 )
        {
          v29 = (float *)Client__Game__Object__GameObject__GetPosition(v27);
          v28 = v27;
          v30 = v29[1];
        }
        else
        {
          v30 = v16;
        }
        Client__Game__Object__GameObject__SetPosition(v28, v8, v30, v13);
        Client__Game__Object__GameObject__SetRotation(*(void **)(*(_QWORD *)(a1 + 8) + 992LL), v9);
        result = *(_QWORD *)(a1 + 8);
        if ( *(_BYTE *)(result + 1041) < 2u )
          *(_WORD *)(result + 1041) = 2;
      }
      if ( (v6 & 8) != 0 )
      {
        v31 = *(_QWORD *)(a1 + 8);
        if ( *(_BYTE *)(v31 + 710) )
          result = sub_141808420(v31 + 592);
        goto LABEL_40;
      }
    }
  }
  return result;
}
