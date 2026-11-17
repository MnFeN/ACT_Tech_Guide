char __fastcall sub_140BC0180(__int64 a1, void *a2, unsigned int a3, int a4)
{
  __int64 v8; // rax

  if ( sub_140897A40((__int64)a2, 0, 0) )
    sub_1417CEEF0(*(_QWORD *)(a1 + 24), 0x5AAu);
  if ( (*(unsigned __int8 (__fastcall **)(void *))(*(_QWORD *)a2 + 344LL))(a2) )
    sub_140857450(0x74u, a2, a2, -1.0, 0, 0);
  Client__Game__BattleLog__AddLogMessage3Params(0x2ACDu, a2, a3, a4, 0, 25.0);
  LOBYTE(v8) = sub_140897A40((__int64)a2, 0, 0);
  if ( (_BYTE)v8 == 1 )
  {
    v8 = EXD__MKDSupportJob__Row_140842FE0(a3);
    if ( v8 )
    {
      LODWORD(v8) = *(unsigned __int8 *)(v8 + 40);
      if ( (_DWORD)v8 == a4 )
      {
        sub_140B6E350(a1, 11012, a3);
        LOBYTE(v8) = sub_140B6E350(a1, 11013, a3);
      }
    }
  }
  return v8;
}
