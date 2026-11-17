char __fastcall sub_1406315A0(__int64 rcx0, __int64 a2, __int64 a3)
{
  int v5; // ecx
  char v7; // si
  float *v8; // rax
  int v10; // xmm6_4
  float *Position; // rax
  float v12; // xmm1_4
  float v13; // xmm0_4
  float *v14; // rax
  float v15; // xmm2_4
  float v16; // xmm1_4
  float v17; // xmm0_4
  __int64 v18; // r14
  float a1[4]; // [rsp+30h] [rbp-9h] BYREF
  __int64 (__fastcall **v20)(); // [rsp+40h] [rbp+7h] BYREF
  int v21; // [rsp+48h] [rbp+Fh]
  int v22; // [rsp+4Ch] [rbp+13h]
  __int128 v23; // [rsp+50h] [rbp+17h]
  __int64 v24; // [rsp+60h] [rbp+27h]
  __int64 v25; // [rsp+68h] [rbp+2Fh]
  _BYTE v26[9]; // [rsp+70h] [rbp+37h]

  v5 = *(_DWORD *)(rcx0 + 8);
  if ( !v5 )
  {
    v10 = *(_DWORD *)(rcx0 + 16);
    if ( *(_BYTE *)(a2 + 32) )
    {
      Position = (float *)Client__Game__Object__GameObject__GetPosition((void *)a3);
      v12 = (float)((float)(Position[2] - *(float *)(a2 + 24)) * (float)(Position[2] - *(float *)(a2 + 24)))
          + (float)((float)(*Position - *(float *)(a2 + 16)) * (float)(*Position - *(float *)(a2 + 16)));
      if ( v12 < 0.0 )
        v13 = sqrtf(v12);
      else
        v13 = fsqrt(v12);
      if ( v13 > 0.001 )
      {
        v20 = off_142178A60;
        v24 = 0;
        v25 = 0;
        v26[8] = 0;
        v22 = -1082130432;
        v21 = v10;
        v23 = xmmword_14214B820;
        *(_QWORD *)v26 = 0x10000;
        v14 = (float *)Client__Game__Object__GameObject__GetPosition((void *)a3);
        v15 = *(float *)(a2 + 16) - *v14;
        v16 = *(float *)(a2 + 20) - v14[1];
        a1[2] = *(float *)(a2 + 24) - v14[2];
        a1[3] = 0.0;
        a1[0] = v15;
        a1[1] = v16;
        LODWORD(v17) = sub_1408544E0(a1).m128_u32[0];
        sub_14090AA60((void *)a3, *(float *)(a2 + 16), *(float *)(a2 + 20), *(float *)(a2 + 24), v17, &v20);
        return 0;
      }
      v18 = a3 + 496;
      sub_14181A640(a3 + 496, 1);
    }
    else
    {
      v18 = a3 + 496;
    }
    *(_QWORD *)(a2 + 16) = 0;
    *(_QWORD *)(a2 + 24) = 0;
    *(_BYTE *)(a2 + 32) = 0;
    if ( !*(_BYTE *)(a3 + 1010) )
      sub_14181A640(v18, 1);
    *(_DWORD *)(rcx0 + 8) = 1;
    return 0;
  }
  if ( v5 == 1 )
  {
    v7 = *(_BYTE *)(rcx0 + 12);
    if ( fabs(sub_140854320(*(float *)(a2 + 48) - *(float *)(a3 + 192))) <= 0.098174773 )
    {
      sub_14181A640(a3 + 496, 1);
      return 1;
    }
    v20 = off_142178A60;
    v21 = -1082130432;
    v22 = -1082130432;
    v23 = xmmword_14214B820;
    v24 = 0;
    v25 = 0;
    *(_WORD *)v26 = 0;
    *(_DWORD *)&v26[3] = 0;
    *(_WORD *)&v26[7] = 0;
    v26[2] = v7;
    if ( !v7 )
      LODWORD(v23) = 1086918619;
    v8 = (float *)Client__Game__Object__GameObject__GetPosition((void *)a3);
    sub_14090AA60((void *)a3, *v8, v8[1], v8[2], *(float *)(a2 + 48), &v20);
  }
  return 0;
}
