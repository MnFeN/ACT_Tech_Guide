void __fastcall sub_140B6F7D0(__int64 *a1, void *a2, int a3, int a4)
{
  unsigned int v8; // eax
  __int64 v9; // rax
  int value2; // [rsp+60h] [rbp+8h] BYREF
  int value1; // [rsp+68h] [rbp+10h] BYREF
  unsigned int logMessageId; // [rsp+70h] [rbp+18h] BYREF
  int value3; // [rsp+78h] [rbp+20h] BYREF

  if ( sub_140897A40((__int64)a2, 0, 0) )
  {
    v8 = (*(__int64 (__fastcall **)(__int64 *))(*a1 + 2720))(a1);
    if ( v8 )
      sub_1417CEEF0(a1[3], v8);
  }
  if ( (*(unsigned __int8 (__fastcall **)(void *))(*(_QWORD *)a2 + 344LL))(a2) )
    sub_140857450(0x74u, a2, a2, -1.0, 0, 0);
  v9 = *a1;
  logMessageId = 0;
  value1 = a3;
  value2 = a4;
  value3 = 0;
  (*(void (__fastcall **)(__int64 *, void *, unsigned int *, int *, int *, int *))(v9 + 2728))(
    a1,
    a2,
    &logMessageId,
    &value1,
    &value2,
    &value3);
  if ( logMessageId )
    Client__Game__BattleLog__AddLogMessage3Params(logMessageId, a2, value1, value2, value3, 25.0);
}
