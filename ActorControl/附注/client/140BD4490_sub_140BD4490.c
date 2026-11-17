__int64 __fastcall sub_140BD4490(__int64 a1)
{
  unsigned int v2; // ebx
  unsigned int ServerTime; // eax
  unsigned int v4; // edx

  v2 = 0;
  ServerTime = Client__System__Framework__Framework__GetServerTime();
  if ( ServerTime >= *(_DWORD *)a1 )
    return 0;
  v4 = *(_DWORD *)a1 - ServerTime;
  if ( *(_BYTE *)(a1 + 24) == 1 )
  {
    v2 = *(_DWORD *)(a1 + 12);
LABEL_13:
    if ( v4 > v2 )
      return v2;
    return v4;
  }
  if ( *(_BYTE *)(a1 + 24) != 2 )
  {
    if ( *(_BYTE *)(a1 + 24) == 3 )
    {
      v2 = *(_DWORD *)(a1 + 4);
      if ( !v2 )
      {
        if ( v4 > *(_DWORD *)(a1 + 8) )
          return *(unsigned int *)(a1 + 8);
        return v4;
      }
    }
    goto LABEL_13;
  }
  if ( v4 > *(_DWORD *)(a1 + 16) )
    return *(unsigned int *)(a1 + 16);
  return v4;
}
