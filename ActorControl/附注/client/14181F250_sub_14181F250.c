char __fastcall sub_14181F250(__int64 a1, unsigned __int8 a2, char a3, float *a4, int a5)
{
  unsigned int v5; // r14d
  __int64 v9; // rax
  __int64 v10; // rdx
  __int64 v11; // r8
  __int64 v12; // rsi
  __int64 v13; // rbx
  float v14; // xmm6_4
  float *Position; // rax
  __int64 v16; // rcx
  float v17; // xmm1_4
  double v18; // xmm0_8
  float v19; // xmm9_4
  float v20; // xmm7_4
  float v21; // xmm8_4
  double v22; // xmm0_8
  float v23; // xmm6_4
  float v24; // xmm7_4
  float v25; // xmm7_4
  float v26; // xmm6_4
  float v27; // xmm0_4

  v5 = a2;
  v9 = EXD__GimmickJump__Row_14083D100(a2);
  v12 = v9;
  if ( (_BYTE)v5 && v9 )
  {
    if ( *(_BYTE *)(a1 + 1008) && *(_BYTE *)(a1 + 1010) > 5u )
    {
      v13 = *(_QWORD *)(a1 + 992);
      if ( v13 )
      {
        if ( (qword_142AA895B & 4) == 0 || (LOBYTE(v9) = sub_1406056C0(), (_BYTE)v9) )
        {
          LOBYTE(v9) = sub_140897A40(v13, 0, 0);
          if ( (_BYTE)v9 )
            LOBYTE(v9) = Client__Game__GameMain__ExecuteCommand(602, a5, 0, 0, 0);
        }
      }
    }
    else
    {
      v14 = 0.0;
      if ( *(_WORD *)(v9 + 12) && *(_WORD *)(v9 + 14) )
      {
        Position = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992));
        v17 = (float)((float)(a4[2] - Position[2]) * (float)(a4[2] - Position[2]))
            + (float)((float)(*a4 - *Position) * (float)(*a4 - *Position));
        if ( v17 < 0.0 )
          sqrtf(v17);
        v18 = sub_1417FE8E0(v16, v5);
        v19 = *(float *)&v18;
        v20 = a4[1];
        v21 = *((float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992)) + 1);
        if ( *(float *)&v18 > 0.0 )
        {
          if ( EXD__GimmickJump__Row_14083D100(v5) )
          {
            v22 = sub_1417FE600(v5);
            v23 = *(float *)&v22;
            if ( v20 > v21 )
              v23 = *(float *)&v22 + (float)(v20 - v21);
            v24 = (float)(v20 - (float)(v21 + v23)) * -2.0;
            if ( v24 < 0.0 )
              v25 = sqrtf(v24);
            else
              v25 = fsqrt(v24);
            v26 = v23 + v23;
            if ( v26 < 0.0 )
              v27 = sqrtf(v26);
            else
              v27 = fsqrt(v26);
            v14 = (float)-(float)((float)(v25 + v27) / v19) * (float)((float)(v25 + v27) / v19);
          }
          else
          {
            v14 = -30.0;
          }
        }
        else
        {
          v14 = -30.0;
        }
      }
      if ( *(_BYTE *)(a1 + 257) == 3 )
      {
        if ( (*(_BYTE *)(v12 + 16) & 2) != 0 )
        {
          *(float *)(a1 + 176) = *a4;
          *(float *)(a1 + 180) = a4[1];
          *(float *)(a1 + 184) = a4[2];
          *(_DWORD *)(a1 + 260) = a5;
          *(_DWORD *)(a1 + 192) = 0;
          LOBYTE(v9) = a5;
          return v9;
        }
        sub_14181ECB0(a1, v10, v11);
      }
      *(_BYTE *)(a1 + 1081) |= 0x20u;
      nullsub_107();
      *(_BYTE *)(a1 + 258) = v5;
      *(float *)(a1 + 176) = *a4;
      *(float *)(a1 + 180) = a4[1];
      *(float *)&v9 = a4[2];
      *(_BYTE *)(a1 + 264) &= ~8u;
      *(_BYTE *)(a1 + 264) |= 8 * (a3 & 1);
      *(_DWORD *)(a1 + 184) = v9;
      LOBYTE(v9) = a5;
      *(_DWORD *)(a1 + 260) = a5;
      *(float *)(a1 + 192) = v14;
      if ( (*(_BYTE *)(v12 + 16) & 1) == 0 )
        LOBYTE(v9) = sub_141806F70(a1 + 16);
    }
  }
  return v9;
}
