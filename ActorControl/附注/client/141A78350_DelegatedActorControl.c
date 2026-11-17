char __fastcall sub_141A78350(__int64 a1, int a2, int a3, int a4)
{
  __int64 v4; // rbx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  void *UIModule; // rax
  void *v10; // rax
  void *AgentByInternalId; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  _DWORD *v15; // rcx

  v4 = a1;
  v5 = a2 - 3590;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      v7 = v6 - 1;
      if ( v7 )
      {
        if ( v7 != 1 )
          return 0;
        goto LABEL_12;
      }
      UIModule = Client__System__Framework__Framework__GetUIModule((void *)qword_142909910);
      if ( UIModule )
      {
        v10 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
        AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v10, 0x1D9u);
        if ( AgentByInternalId )
        {
          sub_1401E6650(AgentByInternalId);
          v12 = sub_140B777C0();
          if ( sub_140B839C0(v12) )
          {
            v13 = sub_140B777C0();
            if ( (unsigned int)sub_140B83A00(v13) == 721814 )
            {
              v14 = sub_140B777C0();
              sub_140B84740(v14, 0x37u, 1);
            }
          }
          a1 = v4;
LABEL_12:
          sub_141A786F0(a1);
          return 1;
        }
      }
      return 0;
    }
    else
    {
      *(_DWORD *)(a1 + 248) = a3;
      *(_DWORD *)(a1 + 252) = a4;
      return 1;
    }
  }
  else
  {
    v15 = *(_DWORD **)(a1 + 384);
    if ( v15[2] == 1 )
    {
      *v15 = 0;
      *(_DWORD *)(*(_QWORD *)(v4 + 384) + 8LL) = 2;
    }
    return 1;
  }
}
