__int64 __fastcall sub_140E6B110(__int64 a1, __int64 a2, int a3, unsigned int a4, unsigned int a5)
{
  __int64 result; // rax
  _DWORD *v7; // rdi
  int v8; // r8d
  void *v9; // rax
  __int64 v10; // rdi
  __int64 v11; // r8
  __int64 v12; // r9
  void *v13; // rax
  __int64 *v14; // rbp
  unsigned int v15; // esi
  bool v16; // zf
  void *UIModule; // rax
  void *v18; // rax
  _BYTE *AgentByInternalId; // rax
  __int64 v20; // r8
  __int64 v21; // r9
  int v22; // ebx

  result = (unsigned int)(a3 - 912);
  if ( a3 == 912 )
  {
    *(_DWORD *)(a1 + 80) = a4;
    return result;
  }
  result = (unsigned int)(a3 - 914);
  if ( a3 == 914 )
  {
    *(_BYTE *)(a1 + 88) = a4;
    return result;
  }
  result = (unsigned int)(a3 - 1207);
  if ( a3 == 1207 )
  {
    *(_WORD *)(a1 + 86) = a4;
    return result;
  }
  if ( a3 == 1208 )
  {
    *(_DWORD *)(a1 + 92) = a4;
    return result;
  }
  v7 = (_DWORD *)(a1 + 48);
  v8 = a3 - 1109;
  if ( v8 )
  {
    if ( v8 == 1 )
    {
      result = (__int64)Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( result )
      {
        v9 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)result + 296LL))(result);
        result = (__int64)Client__UI__Agent__AgentModule__GetAgentByInternalId(v9, 0xAAu);
        v10 = result;
        if ( result )
        {
          sub_1410A4B10(result, a4);
          sub_1410A4B60(v10, a5, v11, v12);
        }
      }
    }
    return result;
  }
  result = (__int64)Client__System__Framework__Framework__GetUIModule(qword_142909910);
  if ( !result )
    return result;
  v13 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)result + 296LL))(result);
  result = (__int64)Client__UI__Agent__AgentModule__GetAgentByInternalId(v13, 0xAAu);
  v14 = (__int64 *)result;
  if ( !result )
    return result;
  v15 = 1;
  if ( a4 == 2 )
  {
    v7[5] = a5;
LABEL_19:
    v16 = a4 == 7;
    goto LABEL_20;
  }
  v16 = a4 == 7;
  if ( a4 == 7 )
  {
    UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
    if ( UIModule )
    {
      v18 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
      AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v18, 0xAAu);
      if ( AgentByInternalId )
        AgentByInternalId[72] = 2;
    }
    v7[7] = 2;
    sub_1410A4B10((__int64)v14, 1);
    sub_1410A4B60((__int64)v14, 2, v20, v21);
    sub_1410A4A20((__int64)v14, a5 != 0);
    v7[4] = 0;
    goto LABEL_19;
  }
LABEL_20:
  if ( !v16 )
    v15 = a4;
  v22 = sub_1410A47A0((__int64)v14);
  sub_1410A47C0(v14, v15);
  result = sub_140E6A7C0((__int64)v7);
  if ( v22 != v15 && qword_142AEAF10[0] && byte_142AEB051 )
    sub_140C11740((__int64)qword_142AEAF10);
  return result;
}
