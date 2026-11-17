void __fastcall sub_14181B6D0(__int64 a1)
{
  float v2; // xmm6_4
  float v3; // xmm0_4
  float v4; // xmm8_4
  float v5; // xmm1_4
  __int64 v6; // rdi
  bool v7; // zf
  char v8; // al
  float v9; // xmm0_4
  float v10; // xmm8_4

  v2 = 1.0;
  if ( sub_141819530(a1) )
  {
    v3 = *(float *)(a1 + 484);
    if ( v3 != -1.0 && (unsigned int)(*(_DWORD *)(a1 + 492) - 3) <= 2 )
    {
      if ( v3 < 0.0 )
      {
        *(_DWORD *)(a1 + 484) = 0;
        v3 = 0.0;
      }
      v4 = *(float *)(a1 + 536);
      v5 = 1.0;
      if ( v3 > 0.0 )
        v5 = fminf(1.0, (float)(sub_14089CCB0(*(_QWORD *)(a1 + 992)) / *(float *)(a1 + 484)) + v4);
      *(float *)(a1 + 536) = v5;
      *(float *)(a1 + 540) = v4;
    }
  }
  v6 = *(_QWORD *)(a1 + 992);
  if ( !v6 || (qword_142AA895B & 4) != 0 && !sub_1406056C0() || (v7 = !sub_140897A40(v6, 0, 0), v8 = byte_142AB28FD, v7) )
    v8 = *(_BYTE *)(a1 + 757);
  if ( v8 )
  {
    v9 = *(float *)(a1 + 488);
    if ( v9 != -1.0 && (unsigned int)(*(_DWORD *)(a1 + 496) - 3) <= 2 )
    {
      v10 = *(float *)(a1 + 568);
      if ( v9 > 0.0 )
        v2 = fminf(1.0, (float)(sub_14089CCB0(*(_QWORD *)(a1 + 992)) / *(float *)(a1 + 488)) + v10);
      *(float *)(a1 + 568) = v2;
      *(float *)(a1 + 572) = v10;
    }
  }
}
