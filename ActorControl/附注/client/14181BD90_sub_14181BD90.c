void __fastcall sub_14181BD90(__int64 a1, __int64 a2, __int64 a3)
{
  float v4; // xmm1_4
  int v5; // edi
  float *Position; // rax
  float v7; // xmm1_4
  float v8; // xmm0_4
  float v9; // xmm1_4
  float v10; // xmm0_4

  *(_QWORD *)(a2 + 24) = *(_QWORD *)(a3 + 8);
  v4 = *(float *)(a3 + 20);
  *(float *)(a2 + 36) = v4;
  v5 = *(_DWORD *)(a3 + 40);
  *(_DWORD *)(a2 + 44) = v5;
  if ( v4 != -1.0 && v5 > 2 && v5 < 6 )
  {
    Position = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 992));
    v7 = *(float *)a2 - *Position;
    v8 = *(float *)(a2 + 8) - Position[2];
    *(_BYTE *)(a2 + 96) = v5;
    *(_DWORD *)(a2 + 24) = -1082130432;
    *(_DWORD *)(a2 + 28) = -1082130432;
    *(_DWORD *)(a2 + 80) = 0;
    v9 = (float)(v7 * v7) + (float)(v8 * v8);
    if ( v9 < 0.0 )
      v10 = sqrtf(v9);
    else
      v10 = fsqrt(v9);
    *(float *)(a2 + 84) = v10;
    *(_QWORD *)(a2 + 88) = 0;
  }
}
