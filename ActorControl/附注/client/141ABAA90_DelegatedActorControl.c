char __fastcall sub_141ABAA90(
        __int64 a1,
        unsigned int a2,
        unsigned int a3,
        unsigned int a4,
        int a5,
        int a6,
        int a7,
        int a8)
{
  int v12; // ecx
  __int64 v13; // rax
  __int64 v14; // rax
  float *v16; // rsi
  _QWORD *v17; // rax
  int v18; // ecx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  void *UIModule; // rax
  __int64 v23; // r9
  void *v24; // rax
  void *v25; // rax
  __int64 v26; // rax
  __int64 v27; // rax
  void *v28; // rax
  void *v29; // rax
  void *AgentByInternalId; // rax
  __int64 v31; // r8
  __m128i v32; // [rsp+40h] [rbp-68h] BYREF
  int v33; // [rsp+50h] [rbp-58h]
  __int16 v34; // [rsp+54h] [rbp-54h]
  int v35; // [rsp+58h] [rbp-50h]
  __int16 v36; // [rsp+5Ch] [rbp-4Ch]
  int v37; // [rsp+60h] [rbp-48h]
  __int16 v38; // [rsp+64h] [rbp-44h]
  unsigned int v39; // [rsp+68h] [rbp-40h]
  unsigned int v40; // [rsp+6Ch] [rbp-3Ch]
  int v41; // [rsp+70h] [rbp-38h]
  __int64 v42; // [rsp+78h] [rbp-30h]

  if ( !*(_BYTE *)(a1 + 69) )
    return 0;
  if ( sub_141C46130((_DWORD *)a1, a2, a3, a4) )
    return 1;
  if ( a2 == 3801 )
  {
    if ( *(_DWORD *)(a1 + 92) )
    {
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( UIModule )
      {
        LOBYTE(v23) = 1;
        (*(void (__fastcall **)(void *, __int64, _QWORD, __int64, int, int, int, int))(*(_QWORD *)UIModule + 1272LL))(
          UIModule,
          58,
          0,
          v23,
          a5,
          a6,
          a7,
          a8);
      }
    }
    if ( sub_141C46FB0() )
    {
      v24 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      v25 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v24 + 296LL))(v24);
      if ( Client__UI__Agent__AgentModule__GetAgentByInternalId(v25, 0x18Cu) )
      {
        v33 = 30;
        v38 = 0;
        v41 = 0;
        v34 = *(_WORD *)(a1 + 80);
        v32.m128i_i16[6] = *(_WORD *)(a1 + 84);
        v32.m128i_i16[2] = *(_WORD *)(a1 + 88);
        v36 = *(_WORD *)(a1 + 76);
        v37 = *(_DWORD *)(a1 + 92);
        v32.m128i_i32[2] = 50;
        v32.m128i_i32[0] = 100;
        v35 = 1;
        v39 = a3;
        v40 = a4;
        v26 = sub_141C46FB0();
        v27 = (*(__int64 (__fastcall **)(__int64, __int64))(*(_QWORD *)v26 + 2408LL))(v26, 2001);
        v42 = sub_14008A350(v27);
        v28 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v29 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v28 + 296LL))(v28);
        AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v29, 0x18Cu);
        sub_140A68EA0((__int64)AgentByInternalId, &v32, v31);
      }
    }
    return 1;
  }
  if ( a2 != 3812 )
  {
    if ( a2 != 3814 )
    {
      if ( a2 != 3815 )
      {
        if ( a2 == 3816 )
        {
          v12 = *(_DWORD *)(a1 + 41648);
          if ( (v12 & 0x10000) == 0 )
          {
            v13 = sub_140B777C0();
            sub_1417CEEF0(v13 + 432, 0x644u);
            sub_141ABCBE0(a1, 1);
            v14 = sub_141ABB1E0(a1);
            sub_140A68DD0(v14);
            if ( (*(_DWORD *)(a1 + 41648) & 0x80000) == 0 )
              *(_DWORD *)(a1 + 41648) |= 0x80000u;
            *(float *)(a1 + 41668) = (float)*(int *)EXD__LiveMinigamesDynamicDefine__Row_140843310(8);
            return 1;
          }
          if ( (v12 & 0x20000) != 0 )
          {
            Client__Game__GameMain__ExecuteCommand(3752, 2, 0, 0, 0);
            return 1;
          }
          if ( (v12 & 0x40000) == 0 )
          {
            *(_DWORD *)(a1 + 41648) = v12 | 0x40000;
            return 1;
          }
          return 1;
        }
        return (**(char (__fastcall ***)(__int64, _QWORD, _QWORD, _QWORD, int, int, int, int))(a1 + 128))(
                 a1 + 128,
                 a2,
                 a3,
                 a4,
                 a5,
                 a6,
                 a7,
                 a8);
      }
      v16 = source;
      if ( source )
      {
        if ( (*(__int64 (__fastcall **)(float *))(*(_QWORD *)source + 632LL))(source) )
        {
          v17 = (_QWORD *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v16 + 632LL))(v16);
          sub_1408A89E0(v17, 0);
          Client__Game__GameMain__ExecuteCommand(3755, a3, 0, 0, 0);
          return 1;
        }
        return (**(char (__fastcall ***)(__int64, _QWORD, _QWORD, _QWORD, int, int, int, int))(a1 + 128))(
                 a1 + 128,
                 a2,
                 a3,
                 a4,
                 a5,
                 a6,
                 a7,
                 a8);
      }
      return 0;
    }
    v18 = *(_DWORD *)(a1 + 41648);
    if ( (v18 & 4) == 0 )
      return (**(char (__fastcall ***)(__int64, _QWORD, _QWORD, _QWORD, int, int, int, int))(a1 + 128))(
               a1 + 128,
               a2,
               a3,
               a4,
               a5,
               a6,
               a7,
               a8);
    if ( a3 == 1 )
    {
      if ( (v18 & 0x80) != 0 )
      {
LABEL_27:
        sub_141ABCBE0(a1, 1);
        return 1;
      }
      v19 = v18 | 0x80;
    }
    else
    {
      if ( a3 != 2 || (v18 & 0x100) != 0 )
        goto LABEL_27;
      v19 = v18 | 0x100;
    }
    *(_DWORD *)(a1 + 41648) = v19;
    goto LABEL_27;
  }
  v20 = 8;
  if ( !a3 )
    v20 = 4;
  v21 = *(_DWORD *)(a1 + 41648);
  if ( (v20 & v21) == 0 )
    *(_DWORD *)(a1 + 41648) = v21 | v20;
  sub_141ABC620(a1, 0);
  return 1;
}
