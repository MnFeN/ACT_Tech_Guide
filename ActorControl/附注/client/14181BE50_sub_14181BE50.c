__int64 __fastcall sub_14181BE50(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 result; // rax
  float v4; // xmm0_4
  int v5; // r9d
  float v6; // xmm1_4
  int v7; // xmm0_4

  result = *(unsigned int *)(a3 + 16);
  *(_DWORD *)(a2 + 32) = result;
  v4 = *(float *)(a3 + 24);
  *(float *)(a2 + 40) = v4;
  v5 = *(_DWORD *)(a3 + 44);
  *(_DWORD *)(a2 + 48) = v5;
  if ( v4 != -1.0 && v5 > 2 && v5 < 6 )
  {
    v6 = *(float *)(a3 + 28) * -1.0;
    v7 = *(_DWORD *)(*(_QWORD *)(a1 + 992) + 192LL);
    result = *(unsigned int *)(a2 + 16);
    *(_DWORD *)(a2 + 20) = v7;
    *(_DWORD *)(a2 + 112) = v7;
    *(float *)(a2 + 120) = v6;
    *(float *)(a2 + 124) = v6;
    *(_DWORD *)(a2 + 116) = result;
    *(_DWORD *)(a2 + 32) = -1082130432;
    *(_BYTE *)(a2 + 128) = v5;
  }
  return result;
}
