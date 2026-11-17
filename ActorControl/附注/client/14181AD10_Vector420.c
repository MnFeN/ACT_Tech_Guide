void __fastcall sub_14181AD10(__int64 a1)
{
  __int64 v2; // rdi
  float *Position; // rax
  __int64 v4; // rdi
  float v5; // xmm14_4
  float v6; // xmm12_4
  float v7; // xmm13_4
  float v8; // xmm7_4
  float v9; // xmm6_4
  float v10; // xmm15_4
  __int64 v11; // rdi
  char v12; // si
  __int64 v13; // rdx
  char v14; // cl
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rdi
  float v18; // xmm10_4
  float v19; // xmm11_4
  float v20; // xmm9_4
  float v21; // xmm6_4
  float v22; // xmm7_4
  float v23; // xmm8_4
  double v24; // xmm0_8
  float v25; // xmm9_4
  float v26; // xmm1_4
  float v27; // xmm6_4
  double v28; // xmm0_8
  float v29; // xmm2_4
  float v30; // xmm8_4
  bool v31; // di
  char v32; // r8
  float v33; // xmm9_4
  float v34; // xmm11_4
  float v35; // xmm10_4
  float v36; // xmm0_4
  int v37; // edx
  __int64 v38; // rsi
  float v39; // xmm6_4
  float v40; // xmm7_4
  double v41; // xmm0_8
  char v42; // al
  __int64 v43; // rdi
  float *v44; // rax
  _DWORD *v45; // rax
  int v46; // xmm1_4
  unsigned int v47; // xmm0_4
  __int64 v48; // rax
  void *v49; // rdi
  void *v50; // rcx
  float *v51; // rax
  float v52; // xmm2_4
  __int64 v53; // rdi
  char v54; // al
  __int64 v55; // rdi
  void *v56; // rax
  float v57; // xmm8_4
  char v58; // al
  void *v59; // rdi
  void *v60; // rcx
  float *v61; // rax
  float v62; // xmm2_4
  __int64 v63; // rdi
  float *v64; // rax
  int v65; // xmm0_4
  int v66; // xmm1_4
  int v67; // xmm2_4
  __int128 v68; // [rsp+20h] [rbp-C8h] BYREF
  float v69; // [rsp+F0h] [rbp+8h]
  float v70; // [rsp+F8h] [rbp+10h]
  float v71; // [rsp+100h] [rbp+18h]

  if ( !*(_BYTE *)(a1 + 511) && (*(_BYTE *)(a1 + 1072) & 3) != 3 )
    return;
  v2 = *(_QWORD *)(a1 + 992);
  if ( v2
    && ((qword_142AA895B & 4) == 0 || sub_1406056C0())
    && sub_140897A40(v2, 0, 0)
    && ((unsigned int)(*(_DWORD *)(a1 + 208) - 2) <= 2 && *(_BYTE *)(a1 + 257) != 3 || byte_142AB29E0) )
  {
    return;
  }
  Position = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992));
  v4 = *(_QWORD *)(a1 + 992);
  v5 = *(float *)(a1 + 448);
  v6 = *(float *)(a1 + 452);
  v7 = *Position;
  v8 = Position[1];
  v9 = Position[2];
  v10 = *(float *)(a1 + 456);
  v71 = *Position;
  v69 = v8;
  v70 = v9;
  if ( v4
    && ((qword_142AA895B & 4) == 0 || sub_1406056C0())
    && sub_140897A40(v4, 0, 0)
    && (*(_BYTE *)(a1 + 1072) & 3) == 3 )
  {
    v5 = v7;
    v6 = v8;
    v10 = v9;
  }
  v11 = *(_QWORD *)(a1 + 992);
  v12 = 0;
  if ( !v11 || (qword_142AA895B & 4) != 0 && !sub_1406056C0() || !sub_140897A40(v11, 0, 0) )
  {
    v14 = *(_BYTE *)(a1 + 84);
    v15 = 81;
    v13 = 145;
    if ( v14 )
      v15 = 145;
    if ( *(_BYTE *)(v15 + a1) )
    {
      v16 = 84;
      v13 = 148;
      if ( v14 )
        v16 = 148;
      if ( !*(_BYTE *)(v16 + a1) )
        goto LABEL_27;
    }
    if ( *(_DWORD *)(a1 + 208) == 1 )
LABEL_27:
      v12 = 1;
  }
  v17 = *(_QWORD *)(a1 + 992);
  if ( v17 && ((qword_142AA895B & 4) == 0 || sub_1406056C0()) && sub_140897A40(v17, 0, 0)
    || (unsigned int)(*(_DWORD *)(a1 + 208) - 2) <= 2
    || v12 )
  {
    v6 = v8;
  }
  v18 = v5 - v7;
  v19 = v6 - v8;
  v20 = v10 - v9;
  if ( *(_BYTE *)(a1 + 509) )
  {
    v21 = *(float *)&dword_142AB28D0;
    v22 = *(float *)&dword_142AB28D4;
    v23 = *(float *)&dword_142AB28D8;
    v24 = sub_141815FE0(a1);
    v25 = (float)((float)(*(float *)&v24 * *(float *)&dword_142AB2904) * 1.1) + 0.0020000001;
    v19 = v25 * v22;
    v8 = v69;
    v18 = v25 * v21;
    v20 = v25 * v23;
  }
  v26 = (float)(v18 * v18) + (float)(v20 * v20);
  if ( v26 < 0.0 )
    v27 = sqrtf(v26);
  else
    v27 = fsqrt(v26);
  v28 = sub_14181B840(a1, v13, a1 + 448);
  v29 = *(float *)(a1 + 484);
  v30 = -1.0;
  v31 = 0;
  v32 = 0;
  v68 = 0;
  if ( (float)(*(float *)&v28 + 0.001) < v27 )
  {
    v36 = *(float *)&v28 / v27;
    v35 = (float)(v18 * v36) + v7;
    v34 = (float)(v19 * v36) + v8;
    v33 = (float)(v20 * v36) + v70;
    *(_QWORD *)&v68 = __PAIR64__(LODWORD(v34), LODWORD(v35));
    *((float *)&v68 + 2) = v33;
  }
  else
  {
    v31 = v29 == -1.0;
    v33 = *((float *)&v68 + 2);
    v32 = 1;
    v34 = *((float *)&v68 + 1);
    LODWORD(v35) = v68;
  }
  if ( v29 != -1.0 )
  {
    if ( v29 == 0.0 )
    {
      v31 = 1;
LABEL_52:
      *(_QWORD *)&v68 = __PAIR64__(LODWORD(v6), LODWORD(v5));
      v35 = v5;
      v34 = v6;
      *((float *)&v68 + 2) = v10;
      v33 = v10;
      goto LABEL_53;
    }
    v37 = *(_DWORD *)(a1 + 492);
    if ( v37 == 1 )
    {
      if ( *(float *)(a1 + 1012) >= v29 )
      {
        v31 = 1;
        goto LABEL_52;
      }
    }
    else if ( v29 != -1.0 && (unsigned int)(v37 - 3) <= 2 && *(float *)(a1 + 536) >= 1.0 )
    {
      v31 = 1;
    }
  }
  if ( v32 )
    goto LABEL_52;
LABEL_53:
  if ( (*(_BYTE *)(a1 + 1072) & 1) != 0
    && !(*(unsigned __int8 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 992) + 464LL))(*(_QWORD *)(a1 + 992)) )
  {
    v38 = *(_QWORD *)(a1 + 992);
    if ( v38 )
    {
      if ( ((qword_142AA895B & 4) == 0 || sub_1406056C0())
        && sub_140897A40(v38, 0, 0)
        && !(unsigned __int8)sub_141829CD0(&unk_142AB28C0) )
      {
        v39 = *(float *)(a1 + 1056);
        v40 = *(float *)(a1 + 1064);
        v41 = sub_141815FE0(a1);
        v35 = v35 + (float)(*(float *)&v41 * v39);
        v34 = v34 + (float)(*(float *)&v41 * 0.0);
        v33 = v33 + (float)(*(float *)&v41 * v40);
        *(_QWORD *)&v68 = __PAIR64__(LODWORD(v34), LODWORD(v35));
        *((float *)&v68 + 2) = v33;
      }
    }
  }
  *(_BYTE *)(a1 + 511) = !v31;
  v42 = *(_BYTE *)(a1 + 1080) & 2;
  if ( v42 || *(_BYTE *)(a1 + 257) == 3 )
  {
    v59 = *(void **)(a1 + 992);
    v60 = v59;
    if ( v42 )
    {
      v61 = (float *)Client__Game__Object__GameObject__GetPosition(v59);
      v60 = v59;
      v62 = v61[1];
    }
    else
    {
      v62 = v34;
    }
    Client__Game__Object__GameObject__SetPosition(v60, v35, v62, v33);
  }
  else
  {
    v43 = *(_QWORD *)(a1 + 992);
    if ( v43 && ((qword_142AA895B & 4) == 0 || sub_1406056C0()) && sub_140897A40(v43, 0, 0) )
    {
      sub_14182D230(&unk_142AB28C0, &v68);
    }
    else
    {
      v44 = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(*(_QWORD *)(a1 + 728) + 992LL));
      if ( *v44 != v35 || v44[1] != v34 || v44[2] != v33 )
      {
        v45 = Client__Game__Object__GameObject__GetPosition(*(void **)(*(_QWORD *)(a1 + 728) + 992LL));
        v46 = v45[1];
        LODWORD(v68) = *v45;
        v47 = v45[2];
        v48 = *(_QWORD *)(a1 + 728);
        DWORD1(v68) = v46;
        *((_QWORD *)&v68 + 1) = v47;
        v49 = *(void **)(v48 + 992);
        v50 = v49;
        if ( (*(_BYTE *)(v48 + 1080) & 2) != 0 )
        {
          v51 = (float *)Client__Game__Object__GameObject__GetPosition(v49);
          v50 = v49;
          v52 = v51[1];
        }
        else
        {
          v52 = v34;
        }
        Client__Game__Object__GameObject__SetPosition(v50, v35, v52, v33);
        if ( !*(_BYTE *)(a1 + 758) )
        {
          v53 = *(_QWORD *)(a1 + 728);
          if ( (unsigned __int8)sub_1418164B0(v53) )
          {
            if ( byte_142AAB774 == 2 )
            {
              v54 = *(_BYTE *)(v53 + 1080);
              if ( (v54 & 1) != 0 && (v54 & 4) == 0 )
              {
                v55 = *(_QWORD *)(v53 + 992);
                if ( (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v55 + 16LL))(v55) == 1 )
                {
                  v56 = Client__Game__Object__GameObject__GetPosition(*(void **)(*(_QWORD *)(a1 + 728) + 992LL));
                  v57 = fmaxf(0.1, sub_141815A30(&v68, v56));
                  if ( byte_142AB28A1 )
                    v30 = v57 + 0.2;
                  else
                    v30 = v57 + 0.1;
                }
                v58 = *(_BYTE *)(v55 + 1576);
                if ( v58 >= 0 )
                {
                  *(_BYTE *)(v55 + 1538) = 0;
                  *(_BYTE *)(v55 + 1576) = v58 | 0x80;
                }
                *(_BYTE *)(v55 + 1577) &= ~1u;
                *(float *)(v55 + 1524) = v30;
              }
            }
          }
        }
      }
    }
  }
  v63 = *(_QWORD *)(a1 + 992);
  if ( v63 && ((qword_142AA895B & 4) == 0 || sub_1406056C0()) && sub_140897A40(v63, 0, 0) )
  {
    if ( byte_142AB28FC )
    {
      v64 = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992));
      *(float *)&v65 = *v64 - v71;
      *(float *)&v66 = v64[1] - v69;
      *(float *)&v67 = v64[2] - v70;
      *(float *)&dword_142AB2930 = v35 - v71;
      *(float *)&dword_142AB2934 = v34 - v69;
      dword_142AB2920 = v65;
      dword_142AB2924 = v66;
      dword_142AB2928 = v67;
      *(float *)&dword_142AB2938 = v33 - v70;
    }
  }
}
