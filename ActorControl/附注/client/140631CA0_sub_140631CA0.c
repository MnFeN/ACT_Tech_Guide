__int64 __fastcall sub_140631CA0(__int64 a1, _DWORD *a2, float a3, float a4)
{
  *(_DWORD *)(a1 + 16) = *a2;
  *(_DWORD *)(a1 + 20) = a2[1];
  *(_DWORD *)(a1 + 24) = a2[2];
  *(_QWORD *)(a1 + 56) = a1 + 80;
  *(float *)(a1 + 48) = a3;
  *(float *)(a1 + 96) = a4;
  *(_BYTE *)(a1 + 32) = 1;
  *(_DWORD *)(a1 + 88) = 0;
  *(_BYTE *)(a1 + 92) = 1;
  return a1 + 80;
}
