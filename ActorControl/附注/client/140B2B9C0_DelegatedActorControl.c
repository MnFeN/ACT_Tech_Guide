char __fastcall sub_140B2B9C0(__int64 a1, __int64 a2, __int64 a3, unsigned __int16 a4, int a5)
{
  __int64 v7; // rax
  unsigned int v8; // edx
  __int64 v9; // rcx
  __int64 v10; // rax
  void *UIModule; // rax
  void *v12; // rbx
  void *v13; // rax
  void *v14; // rax
  void *AgentByInternalId; // rax

  switch ( a4 )
  {
    case 0x5E0u:
      if ( a2 )
        *(_BYTE *)(a2 + 466) = a5;
      return 1;
    case 0x5E1u:
      goto LABEL_11;
    case 0x5E2u:
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      v12 = UIModule;
      if ( UIModule )
      {
        v13 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
        Client__UI__Misc__RaptureLogModule__ShowLogMessage(v13, 0x1CF0u);
        v14 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v12 + 296LL))(v12);
        AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v14, 0xFFu);
        if ( AgentByInternalId )
          sub_14107A9A0((__int64)AgentByInternalId);
      }
      sub_14085BF30(403);
      return 1;
    case 0x5E3u:
      *(_DWORD *)(a1 + 16) = a5;
      return 1;
    case 0x5E4u:
      if ( !a5 )
      {
        v10 = sub_140B777C0();
        v8 = 432;
        v9 = v10 + 432;
        goto LABEL_10;
      }
      if ( a5 == 1 )
      {
        v7 = sub_140B777C0();
        v8 = 433;
        v9 = v7 + 432;
LABEL_10:
        sub_1417CEEF0(v9, v8);
      }
LABEL_11:
      sub_140B2BD20(a1);
      *(_DWORD *)(a1 + 16) = -536870912;
      sub_14085BFC0();
      return 1;
    default:
      return 0;
  }
}
