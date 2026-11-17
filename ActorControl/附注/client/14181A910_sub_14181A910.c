__int64 __fastcall sub_14181A910(__int64 a1, __int64 a5, _DWORD *r8_0)
{
  float *Position; // rdi
  float v7; // xmm7_4
  __int64 result; // rax
  float v9; // xmm6_4
  int v10; // xmm8_4
  float *v11; // rax
  float v12; // xmm4_4
  float v13; // xmm0_4
  __int64 a3[42]; // [rsp+30h] [rbp-188h] BYREF

  Position = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992));
  v7 = 0.30000001;
  if ( Client__Game__Character__Character__IsInPvP(source) )
    v7 = 0.45000002;
  if ( (unsigned __int8)(*(_BYTE *)(a1 + 1040) - 1) > 2u
    && (*(float *)(a1 + 484) == -1.0 || (unsigned int)(*(_DWORD *)(a1 + 492) - 3) > 2) )
  {
    if ( sub_141819530(a1) )
    {
      *(_DWORD *)a5 = dword_142AB2930;
      *(_DWORD *)(a5 + 4) = dword_142AB2934;
      *(_DWORD *)(a5 + 8) = dword_142AB2938;
      v9 = *(float *)&dword_142AB2904;
      v10 = *((_DWORD *)Position + 1);
      *(_DWORD *)(a5 + 4) = 0;
      v11 = sub_1402F8E30((float *)a5);
      v12 = (float)((float)(v11[2] * v9) * v7) + Position[2];
      v13 = (float)((float)(v9 * *v11) * v7) + *Position;
      *(float *)(a5 + 4) = (float)((float)(v11[1] * v9) * v7) + Position[1];
      *(float *)(a5 + 8) = v12;
      *(float *)a5 = v13;
      sub_141841990(a3);
      result = sub_14182D950((__int64)&qword_142AB28C0, (float *)a5, (__int64)a3, Position, a5, byte_142AB28A1);
      if ( *(_DWORD *)(a1 + 208) )
        *(_DWORD *)(a5 + 4) = v10;
    }
    else
    {
      *(float *)a5 = *Position;
      *(float *)(a5 + 4) = Position[1];
      result = *((unsigned int *)Position + 2);
      *(_DWORD *)(a5 + 8) = result;
    }
    if ( *(_BYTE *)(a1 + 512) )
    {
      result = *(unsigned int *)(a1 + 464);
      *r8_0 = result;
    }
  }
  else
  {
    *(float *)a5 = *Position;
    *(float *)(a5 + 4) = Position[1];
    result = *((unsigned int *)Position + 2);
    *(_DWORD *)(a5 + 8) = result;
  }
  return result;
}
