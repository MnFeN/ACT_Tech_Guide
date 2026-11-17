char __fastcall sub_140ECF140(
        __int64 a1,
        unsigned int a2,
        unsigned int a3,
        unsigned int a4,
        int a5,
        int a6,
        int a7,
        int a8)
{
  void *UIModule; // rax
  void *v13; // rbx
  _QWORD *v14; // rax
  int v15; // edx
  void *v16; // rax
  _QWORD *AgentByInternalId; // rax
  void *v19; // rax
  void *v20; // rbx
  void *v21; // rax
  void *v22; // rax
  void *v23; // rax
  char v24; // al
  _QWORD *v25; // rbx

  switch ( a2 )
  {
    case 0xDACu:
      if ( *(_QWORD *)(a1 + 4416) )
        sub_141A6D940();
      *(_DWORD *)(a1 + 3784) = a3;
      return 1;
    case 0xDADu:
      *(_DWORD *)(a1 + 3780) = a3;
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      v13 = UIModule;
      if ( UIModule )
      {
        v14 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
        v15 = 10784;
        if ( (a4 & 1) == 0 )
          v15 = 3522;
        Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v14, v15, a3);
        v16 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v13 + 296LL))(v13);
        AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v16, 0x77u);
        if ( AgentByInternalId )
          sub_140F286C0(AgentByInternalId);
      }
      return 1;
    case 0xDAEu:
      v24 = *(_BYTE *)(a1 + 62);
      *(_DWORD *)(a1 + 3788) = a3;
      if ( (v24 & 2) != 0 )
        return 1;
      *(_BYTE *)(a1 + 62) = v24 | 2;
      return 1;
    case 0xDC0u:
      *(_BYTE *)(a1 + 55) &= ~2u;
      v19 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      v20 = v19;
      if ( !v19 )
        return 1;
      v21 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v19 + 88LL))(v19);
      Client__UI__Misc__RaptureLogModule__ShowLogMessage(v21, 0x2A72u);
      v22 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v20 + 296LL))(v20);
      v23 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v22, 0x1DBu);
      if ( !v23 )
        return 1;
      sub_140A86C90((__int64)v23);
      return 1;
    case 0xDCAu:
      *(_DWORD *)(a1 + 68) = 0;
      return 1;
    case 0xE37u:
      if ( (unsigned __int8)a3 >= 0xBu )
        return 1;
      *(_DWORD *)(a1 + 4LL * (unsigned __int8)a3 + 4220) = a4;
      return 1;
    default:
      v25 = *(_QWORD **)(a1 + 4440);
      if ( v25 == *(_QWORD **)(a1 + 4448) )
        return 0;
      break;
  }
  do
  {
    if ( (*(unsigned __int8 (__fastcall **)(_QWORD, _QWORD, _QWORD, _QWORD, int, int, int, int))(*(_QWORD *)*v25 + 8LL))(
           *v25,
           a2,
           a3,
           a4,
           a5,
           a6,
           a7,
           a8) )
    {
      return 1;
    }
    ++v25;
  }
  while ( v25 != *(_QWORD **)(a1 + 4448) );
  return 0;
}
