void __fastcall sub_140391030(__int64 a1, int a2)
{
  __int64 v2; // rbx
  char v3; // di
  __int64 v4; // rcx
  unsigned __int8 v5; // cl
  unsigned __int64 v6; // rsi
  __int64 v7; // rax
  __int64 v8; // rcx
  int v9; // eax

  v2 = *(_QWORD *)(a1 + 440);
  v3 = a2;
  if ( v2 )
  {
    *(_DWORD *)(v2 + 140) = a2;
    *(_DWORD *)(v2 + 136) |= 1 << a2;
    v4 = *(_QWORD *)(v2 + 8);
    if ( v4 )
    {
      if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v4 + 12), 0) == 1 )
      {
        if ( (unsigned __int8)sub_1403901D0(v2) )
        {
          v5 = *(_BYTE *)(v2 + 196);
          if ( (v5 & 1) != 0 )
            *(_BYTE *)(v2 + 196) = v5 ^ (v5 ^ (2 * ~(v5 >> 1))) & 2;
          else
            sub_14037AA50(*(_QWORD *)(v2 + 96));
        }
        if ( *(float *)(v2 + 112) == 0.0 )
          sub_140390C10(v2);
        v6 = *(_QWORD *)(v2 + 96);
        v7 = sub_1403B5AF0();
        if ( HIDWORD(v6) < 0x800 )
        {
          if ( (_DWORD)v6 )
          {
            v8 = *(_QWORD *)(v7 + 5272) + 136 * HIDWORD(v6);
            if ( *(_DWORD *)(v8 + 8288) == (_DWORD)v6 )
            {
              if ( *(_QWORD *)(v8 + 8240) )
              {
                v9 = *(unsigned __int16 *)(v8 + 8278) | (1 << v3);
                *(_BYTE *)(v8 + 8274) = v3;
                *(_WORD *)(v8 + 8278) = v9;
                *(_BYTE *)(v8 + 8275) = v3;
              }
            }
          }
        }
      }
    }
  }
}
