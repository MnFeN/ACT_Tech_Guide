void __fastcall sub_1403F9A50(__int64 a1, float a2, char a3)
{
  if ( a2 >= 0.0 )
  {
    if ( a3 && *(float *)(a1 + 1112) >= 0.0 )
    {
      *(_DWORD *)(a1 + 1120) = 0;
      *(float *)(a1 + 1116) = a2;
      return;
    }
    *(float *)(a1 + 1112) = a2;
  }
  else
  {
    *(_DWORD *)(a1 + 1112) = -1082130432;
  }
  *(_DWORD *)(a1 + 1120) = 1065353216;
  *(_DWORD *)(a1 + 1116) = -1082130432;
}
