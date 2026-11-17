char __fastcall sub_141A79C40(__int64 a1, int a2, unsigned int a3, unsigned int a4, unsigned int a5)
{
  int v7; // edx
  int v8; // edx
  int v9; // edx
  __int16 *v11; // rax
  void *UIModule; // rax
  _QWORD *v13; // rax
  unsigned __int64 v14; // r8
  unsigned __int8 v15; // dl
  __int64 v16; // rax
  __int64 v17; // rax
  unsigned __int16 *v18; // rsi
  unsigned int *v19; // rdi
  __int64 v20; // rbp
  void *v21; // rax
  void *v22; // rbx
  __int64 v23; // rax
  __int64 v24; // rax
  __int64 v25; // r8

  v7 = a2 - 3510;
  if ( !v7 )
  {
    if ( sub_140ECDB40() )
    {
      v16 = sub_140ECDB40();
      if ( (unsigned __int8)sub_140ECDF90(v16) )
      {
        v17 = sub_140ECDB40();
        if ( *(_BYTE *)(v17 + 102) != *(_BYTE *)(v17 + 101) )
        {
          *(_DWORD *)(a1 + 696) = 0;
          *(_WORD *)(a1 + 700) = 0;
          *(_BYTE *)(a1 + 702) = 0;
          *(_BYTE *)(a1 + 692) = 99;
        }
      }
    }
    v18 = (unsigned __int16 *)(a1 + 706);
    v19 = (unsigned int *)(a1 + 32);
    *(_BYTE *)(a1 + 694) = 0;
    v20 = 7;
    do
    {
      if ( *v19 != -536870912 )
      {
        v21 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, *v19);
        v22 = v21;
        if ( v21 )
        {
          if ( (*((_BYTE *)v21 + 280) & 1) == 0 )
          {
            v23 = sub_140ECDB40();
            sub_141ACB7D0(*(_QWORD *)(v23 + 4352), v18[2], 0);
            v24 = sub_140ECDB40();
            sub_141ACB7D0(*(_QWORD *)(v24 + 4352), *v18, 1u);
            sub_140909F80((__int64)v22, 1.0, v25);
            sub_140857450(0x9CAu, v22, v22, -1.0, 0, 0);
          }
        }
      }
      v19 += 24;
      v18 += 4;
      --v20;
    }
    while ( v20 );
    return 1;
  }
  v8 = v7 - 1;
  if ( !v8 )
  {
    v14 = a4 | ((unsigned __int64)a3 << 32);
    v15 = 0;
    while ( v14 != *(_QWORD *)(96LL * v15 + a1 + 24) )
    {
      if ( ++v15 >= 7u )
        return 1;
    }
    if ( a5 < 7 )
    {
      *(_BYTE *)(96LL * v15 + a1 + 40) = a5;
      sub_141A7A7D0(a1, v15, a5);
      return 1;
    }
    return 1;
  }
  v9 = v8 - 1;
  if ( v9 )
  {
    if ( v9 == 1 )
    {
      *(_DWORD *)(a1 + 800) = a3;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v11 = sub_140B51D40();
    if ( sub_140DF8810((__int64)v11, 0x1485u) )
    {
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( UIModule )
      {
        v13 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v13, 10792, a3);
      }
    }
    *(_BYTE *)(a1 + 12) = 1;
    return 1;
  }
}
