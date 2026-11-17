char __fastcall sub_140B70D10(float *a1)
{
  __int64 v1; // rbp
  float v3; // xmm5_4
  float v4; // xmm2_4
  float v5; // xmm1_4
  float v6; // xmm3_4
  float v7; // xmm5_4
  void *v8; // rbx
  _BYTE *v9; // rax
  __int64 v10; // r8
  _BYTE *v11; // rbx
  __int64 v12; // rax
  char v13; // r8
  __int64 v15; // rcx
  int v16; // edx
  __int64 v17; // rax
  __int64 v18; // rbx
  char v19; // r14
  unsigned __int16 v20; // r8
  _QWORD v22[14]; // [rsp+40h] [rbp-A8h] BYREF

  v1 = 0;
  if ( ((_BYTE)a1[843] & 0xC) == 0xC )
  {
    v3 = a1[828];
    v4 = *(float *)(qword_142909910 + 6072) * *(float *)(qword_142909910 + 5824);
    if ( v3 > 0.0 )
    {
      v5 = a1[829];
      if ( v5 != 0.0 )
      {
        v6 = v4 * 0.1;
        if ( v5 <= 0.0 )
        {
          if ( (float)-v5 <= v6 )
          {
            v4 = v4 - v6;
            a1[829] = 0.0;
          }
          else
          {
            v4 = v4 + v6;
            a1[829] = v5 + v6;
          }
        }
        else if ( v5 <= v6 )
        {
          v4 = v4 - v5;
          a1[829] = 0.0;
        }
        else
        {
          v4 = v4 - v6;
          a1[829] = v5 - v6;
        }
      }
      v7 = v3 - v4;
      a1[828] = v7;
      if ( v7 < 0.0 )
      {
        a1[828] = 0.0;
        v7 = 0.0;
      }
      (*(void (__fastcall **)(float *, _QWORD))(*(_QWORD *)a1 + 2672LL))(
        a1,
        (unsigned int)(int)fmaxf(0.0, v7 - 0.99000001));
      sub_140B72CF0(a1, 0);
    }
  }
  sub_140B734F0(a1);
  (*(void (__fastcall **)(float *))(*(_QWORD *)a1 + 2584LL))(a1);
  sub_140902D90(a1 + 330);
  if ( *((_BYTE *)a1 + 1281) )
  {
    v8 = (void *)EXD__SE__Row_14083AE80(*((unsigned __int16 *)a1 + *((char *)a1 + 1280) + 632));
    if ( v8 )
    {
      Client__System__String__Utf8String__Ctor_FromSequence(v22, "sound/", 0xFFFFFFFF);
      v9 = Component__Excel__ExcelRow__ResolveStringColumnIndirection(v8);
      sub_1400894D0(v22, v9, v10);
      v11 = *(_BYTE **)(qword_142909910 + 11144);
      v12 = sub_14008A350((__int64)v22);
      sub_140417460(v11, v12, 1.0, 0, 0, 1u, 6u);
      v13 = -1;
      *((_WORD *)a1 + *((char *)a1 + 1280) + 632) = 0;
      if ( (*((_BYTE *)a1 + 1281))-- != 1 )
      {
        LOBYTE(v15) = *((_BYTE *)a1 + 1280);
        v16 = 0;
        while ( 1 )
        {
          v15 = ((_BYTE)v15 + 1) & 7;
          if ( *((_WORD *)a1 + v15 + 632) )
            break;
          if ( (unsigned int)++v16 >= 7 )
            goto LABEL_22;
        }
        v13 = v15;
      }
LABEL_22:
      *((_BYTE *)a1 + 1280) = v13;
      Client__System__String__Utf8String__Dtor(v22);
    }
  }
  sub_140B51EE0((__int64)(a1 + 322), *(float *)(qword_142909910 + 6072) * *(float *)(qword_142909910 + 5824));
  LOBYTE(v17) = *((_BYTE *)a1 + 1628);
  if ( (v17 & 2) != 0 )
  {
    if ( qword_142AEAF10[0] && byte_142AEB051 )
    {
      sub_140B6DFD0(a1);
      LOBYTE(v17) = *((_BYTE *)a1 + 1628);
    }
    LOBYTE(v17) = v17 & 0xFD;
    *((_BYTE *)a1 + 1628) = v17;
  }
  if ( *((_QWORD *)a1 + 403) )
    LOBYTE(v17) = sub_141787020();
  if ( (*((_BYTE *)a1 + 1675) & 2) != 0 )
  {
    LOBYTE(word_142AD81AB) = 1;
    *((_BYTE *)a1 + 1675) &= ~2u;
  }
  v18 = *((_QWORD *)a1 + 402);
  if ( v18 )
  {
    if ( *(_BYTE *)(v18 + 1542) )
    {
      if ( (dword_142AAB79C & 0xFFFFFFFD) == 0 )
      {
        v19 = 0;
        if ( !*(_WORD *)(v18 + 1538) )
          goto LABEL_47;
        do
        {
          if ( *(_DWORD *)(v18 + 12 * v1) )
          {
            if ( (*(_BYTE *)(v18 + 12 * v1 + 10) & 1) != 0 )
            {
              v20 = *(_WORD *)(v18 + 12 * v1 + 8);
              if ( v20 )
              {
                if ( Client__Game__InstanceContent__ContentDirector__PlayMapEffectTimeline(a1, v1, v20) == 1 )
                {
                  *(_BYTE *)(v18 + 12 * v1 + 10) &= ~1u;
                  *(_BYTE *)(v18 + 12 * v1 + 10) |= 2u;
                }
                else
                {
                  v19 = 1;
                }
              }
            }
          }
          v18 = *((_QWORD *)a1 + 402);
          v1 = (unsigned int)(v1 + 1);
          LODWORD(v17) = *(unsigned __int16 *)(v18 + 1538);
        }
        while ( (unsigned int)v1 < (unsigned int)v17 );
        if ( !v19 )
        {
LABEL_47:
          *(_BYTE *)(v18 + 1541) = 1;
          v17 = *((_QWORD *)a1 + 402);
          *(_BYTE *)(v17 + 1542) = 0;
        }
      }
    }
    else
    {
      LOBYTE(v17) = *(_BYTE *)(v18 + 1540);
      if ( (_BYTE)v17 )
      {
        LOBYTE(v17) = v17 - 1;
        *(_BYTE *)(v18 + 1540) = v17;
        if ( !(_BYTE)v17 )
          LOBYTE(v17) = sub_140AFCAB0(&off_1428BC9F0);
      }
    }
  }
  return v17;
}
