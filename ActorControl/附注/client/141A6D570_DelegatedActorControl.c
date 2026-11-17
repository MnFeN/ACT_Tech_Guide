char __fastcall sub_141A6D570(__int64 a1, int a2, unsigned __int8 a3, __int16 a4, __int16 a5)
{
  int v6; // edx
  int v7; // edx
  unsigned __int8 v9; // r8
  unsigned __int8 v10; // r9

  v6 = a2 - 3620;
  if ( !v6 )
  {
    v10 = a4 - 1;
    if ( (unsigned __int8)(a3 - 1) < 0xBu && v10 < 7u )
      *(_WORD *)(a1 + 2 * (v10 + 7LL * (unsigned __int8)(a3 - 1)) + 8) = a5;
    goto LABEL_12;
  }
  v7 = v6 - 1;
  if ( !v7 )
  {
    if ( (unsigned __int8)(a3 - 1) < 0xBu )
      *(_BYTE *)((unsigned __int8)(a3 - 1) + a1 + 162) = a4;
LABEL_12:
    sub_141A6E470(a1, a3);
    sub_141A6E540(a1);
    return 1;
  }
  if ( v7 != 1 )
    return 0;
  v9 = a3 - 1;
  if ( v9 < 4u )
  {
    *(_WORD *)(a1 + 2LL * v9 + 184) = a4;
    return 1;
  }
  return 1;
}
