char __fastcall sub_1408F9FA0(__int64 a1, __int64 a2, __int64 a3, __int16 a4)
{
  void *UIModule; // rax
  void *v6; // rax
  void *AgentByInternalId; // rax

  if ( a4 != 1528 )
    return 0;
  UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
  if ( UIModule )
  {
    v6 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
    AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v6, 4u);
    if ( AgentByInternalId )
      sub_140FF8EC0(AgentByInternalId);
  }
  return 1;
}
