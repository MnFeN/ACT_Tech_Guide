char __fastcall sub_141836A30(__int64 a1)
{
  float *v1; // rbx
  int v2; // eax
  _DWORD *Position; // rax
  int v4; // eax
  void *NetworkModuleProxy; // rdi
  _BYTE a2[12]; // [rsp+30h] [rbp-F88h] BYREF
  int v8; // [rsp+3Ch] [rbp-F7Ch]
  __int128 v9; // [rsp+40h] [rbp-F78h] BYREF
  int packet; // [rsp+50h] [rbp-F68h] BYREF
  __int64 v11; // [rsp+58h] [rbp-F60h]
  int v12; // [rsp+70h] [rbp-F48h]
  __int64 v13; // [rsp+74h] [rbp-F44h]
  int v14; // [rsp+7Ch] [rbp-F3Ch]
  int v15; // [rsp+80h] [rbp-F38h]
  __int64 v16; // [rsp+84h] [rbp-F34h]

  v1 = source;
  v9 = 0;
  v2 = sub_141836F40(a1, &v9);
  if ( !v2 )
  {
    Position = Client__Game__Object__GameObject__GetPosition(v1);
    *(_QWORD *)a2 = *(_QWORD *)Position;
    *(_DWORD *)&a2[8] = Position[2];
    v8 = 0;
    if ( !Client__Game__Control__MoveControl__MoveController__IsFlying(v1 + 124)
      || (v4 = (unsigned int)Client__Game__Object__GameObject__GetPosition(v1),
          sub_140C4D360((__int64)&qword_142ADE980, (__int64)a2, v4)) )
    {
      if ( !(_DWORD)dword_1428BBBD0 && sub_140862C10((__int64)&dword_1428BBBD0) >= 4.0 )
      {
        if ( sub_140862D00((__int64)&dword_1428BBBD0) )
        {
          NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
          if ( NetworkModuleProxy )
          {
            sub_1408BDCB0((__int64)(v1 + 652), 0x1376u, 0, 0);
            v12 = *((_DWORD *)v1 + 48);
            v13 = v9;
            v15 = *(_DWORD *)a2;
            v14 = DWORD2(v9);
            v16 = *(_QWORD *)&a2[4];
            packet = 934;
            v11 = 48;
            sub_140481E80(NetworkModuleProxy, &packet, 0, 0);
          }
        }
      }
      return 1;
    }
    return 0;
  }
  if ( v2 == 7 )
  {
    if ( !(_DWORD)dword_1428BBBD0 && sub_140862C10((__int64)&dword_1428BBBD0) >= 4.0 )
      Client__Game__GameMain__ExecuteCommand(614, 0, 0, 0, 0);
    return 1;
  }
  if ( v2 != 6 )
    return 0;
  sub_140E13AB0((__int64)byte_142AF9070, 0x97u, 0);
  return 1;
}
