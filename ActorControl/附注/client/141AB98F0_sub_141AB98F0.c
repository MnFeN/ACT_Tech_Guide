char __fastcall sub_141AB98F0(_BYTE *a1, __int64 a2)
{
  _BYTE *v4; // rcx

  if ( !a1[124] )
    return 0;
  v4 = a1 + 96;
  if ( a1[120] < 2u || a1[121] < 4u )
    return 0;
  *(_DWORD *)a2 = sub_140BD4490(v4);
  *(_BYTE *)(a2 + 4) = a1[123];
  *(_BYTE *)(a2 + 5) = a1[122];
  return 1;
}
