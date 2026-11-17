char __fastcall sub_141A709C0(__int64 a1, int a2, signed int a3, int a4, int a5, __int16 a6)
{
  __int64 v9; // rax
  char result; // al
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rbx
  unsigned int v14; // eax
  void *UIModule; // rax
  void *v16; // rax
  __int64 v17; // rax
  unsigned int v18; // ecx
  __int64 v19; // rsi
  __int64 v20; // rax
  __int64 v21; // rbx
  __int64 v22; // rax
  __int64 v23; // rax
  _BYTE *v24; // rax
  unsigned int v25; // eax
  __int64 v26; // rax
  __int64 v27; // rdi
  unsigned __int64 v28; // rbx
  __int64 v29; // rax
  __int64 v30; // rax
  int v31; // ebx
  __int64 v32; // rax
  __int64 v33; // rax
  void *v34; // rax
  void *v35; // rbx
  void *v36; // rax
  void *v37; // rax
  void *v38; // rax
  void *v39; // rax
  void *v40; // rax
  void *v41; // rax
  __int64 v42; // rax
  __int64 v43; // rax
  __int64 v44; // rax
  __int64 v45; // rax
  __int64 v46; // rax
  __int64 v47; // rax
  __int64 v48; // rax
  __int64 v49; // rdi
  __int64 v50; // rax
  __int64 v51; // rcx
  __int64 v52; // rax
  __int64 v53; // rax
  __int64 v54; // rax
  __int64 v55; // rax
  __int64 v56; // rax
  __int64 v57; // rax
  void *v58; // rax
  void *v59; // rax
  void *AgentByInternalId; // rax

  switch ( a2 )
  {
    case 3540:
      v9 = sub_140B777C0();
      sub_1417CEEF0(v9 + 432, a3);
      result = 1;
      break;
    case 3542:
      v11 = sub_140ECDB40();
      if ( !v11 )
        goto LABEL_78;
      *(_DWORD *)(v11 + 3724) = a3;
      sub_140148C10(0);
      sub_141A73BD0();
      v12 = sub_140ECDB40();
      v13 = v12;
      if ( !v12 )
        goto LABEL_78;
      if ( !*(_QWORD *)(v12 + 4368) )
        goto LABEL_78;
      v14 = *(_DWORD *)(v12 + 3764);
      if ( !v14 )
        goto LABEL_78;
      if ( *(_BYTE *)(v13 + 3772) )
        goto LABEL_78;
      if ( *(_DWORD *)(v13 + 3724) <= v14 )
        goto LABEL_78;
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( !UIModule )
        goto LABEL_78;
      v16 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
      Client__UI__Misc__RaptureLogModule__ShowLogMessage(v16, 0x2D19u);
      *(_BYTE *)(v13 + 3772) = 1;
      result = 1;
      break;
    case 3543:
      v17 = sub_140ECDB40();
      if ( !v17 )
        goto LABEL_78;
      v18 = 4;
      if ( !*(_DWORD *)(v17 + 3728) && a3 != 5 )
        v18 = 2;
      *(_DWORD *)(v17 + 3728) = a3;
      *(_DWORD *)(v17 + 3760) = a4;
      sub_140148C10(v18);
      sub_141A73E60();
      v19 = sub_140ECDB40();
      if ( !v19 )
        goto LABEL_78;
      v20 = sub_140ECDB40();
      v21 = v20;
      if ( (!v20
         || (v22 = EXD__WKSMissionUnit__Row_140841000(*(unsigned __int16 *)(v20 + 3712))) == 0
         || (v23 = EXD__WKSMissionToDo__Row_140841040(*(unsigned __int16 *)(v22
                                                                          + 2LL * *(unsigned __int8 *)(v21 + 3714)
                                                                          + 24))) == 0
         || *(_BYTE *)(v23 + 44) != 8)
        && *(_DWORD *)(v19 + 3728) != 3 )
      {
        goto LABEL_78;
      }
      v24 = (_BYTE *)sub_141A74010(a1);
      if ( v24 )
        *v24 = 0;
      if ( *(_DWORD *)(v19 + 3728) != 3 )
        goto LABEL_78;
      v25 = sub_140ED1910();
      v26 = sub_141A23770(v25);
      v27 = v26;
      if ( !v26 )
        goto LABEL_78;
      v28 = 0;
      if ( sub_141A23E50(v26, 1) )
      {
        do
        {
          v29 = sub_141A23F60(v27, 1, (unsigned int)v28);
          if ( *(_DWORD *)(v29 + 4) == 1
            && (!*(_BYTE *)(v29 + 113) || *(_DWORD *)(v29 + 120) < *(_DWORD *)(v29 + 124))
            && !*(_BYTE *)(v29 + 112) )
          {
            *(_BYTE *)(v29 + 112) = 1;
          }
          ++v28;
        }
        while ( v28 < sub_141A23E50(v27, 1) );
      }
      sub_140C4B0A0(&unk_142AEB1A0);
      result = 1;
      break;
    case 3544:
      sub_141A74D70(a1, a3);
      result = 1;
      break;
    case 3545:
      v30 = sub_140ECDB40();
      if ( !v30 )
        goto LABEL_78;
      v31 = *(_DWORD *)(v30 + 3728);
      sub_141A75710(v30 + 3712);
      sub_141A74520(a1);
      if ( v31 != 5 )
      {
        v32 = sub_140ECDB40();
        if ( v32 )
        {
          v33 = *(_QWORD *)(v32 + 4368);
          if ( v33 )
          {
            if ( !*(_BYTE *)(v33 + 8) )
            {
              v34 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v35 = v34;
              if ( v34 )
              {
                v36 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v34 + 88LL))(v34);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v36, 0x2AB4u);
                v37 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v35 + 88LL))(v35);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v37, 0x2AB5u);
                v38 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v35 + 88LL))(v35);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v38, 0x2AB6u);
                v39 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v35 + 88LL))(v35);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v39, 0x2AB7u);
                v40 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v35 + 88LL))(v35);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v40, 0x2AB8u);
                v41 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v35 + 88LL))(v35);
                Client__UI__Misc__RaptureLogModule__ShowLogMessage(v41, 0x2AB9u);
              }
            }
          }
        }
      }
      sub_140148AD0();
      result = 1;
      break;
    case 3546:
      v43 = sub_140ECDB40();
      if ( !v43 )
        goto LABEL_78;
      sub_141A75710(v43 + 3712);
      sub_141A74520(a1);
      sub_140148A10();
      result = 1;
      break;
    case 3547:
      if ( !sub_140ECDB40() )
        goto LABEL_78;
      sub_1401489D0();
      result = 1;
      break;
    case 3548:
      v44 = sub_140ECDB40();
      if ( !v44 )
        goto LABEL_78;
      *(_BYTE *)(v44 + 3768) = 1;
      sub_140148C10(3u);
      result = 1;
      break;
    case 3549:
      v45 = sub_140ECDB40();
      if ( !v45 )
        goto LABEL_78;
      *(_BYTE *)(v45 + 3732) = a3 != 0;
      if ( a3 )
        goto LABEL_78;
      sub_1401490E0();
      result = 1;
      break;
    case 3632:
      v46 = sub_140ECDB40();
      if ( !v46 )
        goto LABEL_78;
      *(_WORD *)(v46 + 3734) = (unsigned __int8)a3;
      sub_140148C10(0);
      sub_141A73BD0();
      result = 1;
      break;
    case 3633:
      v47 = sub_140ECDB40();
      if ( !v47 )
        goto LABEL_78;
      *(_BYTE *)(v47 + 3736) = a3;
      sub_140148C10(0);
      sub_141A73BD0();
      result = 1;
      break;
    case 3634:
      v48 = sub_140ECDB40();
      if ( !v48 )
        goto LABEL_78;
      *(_BYTE *)(v48 + 3737) = 1;
      sub_140148C10(0);
      sub_141A73BD0();
      result = 1;
      break;
    case 3635:
      if ( !(_WORD)a4 )
        goto LABEL_78;
      if ( a3 >= 6 )
        goto LABEL_78;
      v49 = sub_140ECDB40();
      if ( !v49 )
        goto LABEL_78;
      v50 = EXD__WKSItemInfo__Row_140840F80((unsigned __int16)a4);
      if ( !v50 )
        goto LABEL_78;
      v51 = v49 + 3744;
      switch ( a3 )
      {
        case 0:
          *(_DWORD *)sub_141A75530(v51, v50) = a5;
          result = 1;
          break;
        case 1:
          *(_DWORD *)(sub_141A75530(v51, v50) + 4) = a5;
          result = 1;
          break;
        case 2:
          v52 = sub_141A75530(v51, v50);
          *(_WORD *)(v52 + 8) = a6;
          *(_DWORD *)(v52 + 12) = a5;
          result = 1;
          break;
        case 3:
          v53 = sub_141A75530(v51, v50);
          *(_WORD *)(v53 + 16) = a6;
          *(_DWORD *)(v53 + 20) = a5;
          result = 1;
          break;
        case 4:
          v54 = sub_141A75530(v51, v50);
          *(_WORD *)(v54 + 24) = a6;
          *(_DWORD *)(v54 + 28) = a5;
          result = 1;
          break;
        case 5:
          v55 = sub_141A75530(v51, v50);
          *(_WORD *)(v55 + 32) = a6;
          *(_DWORD *)(v55 + 36) = a5;
          result = 1;
          break;
        default:
          goto LABEL_78;
      }
      break;
    case 3636:
      v56 = sub_140ECDB40();
      if ( !v56 )
        goto LABEL_78;
      *(_BYTE *)(v56 + 3738) = a3;
      result = 1;
      break;
    case 3637:
      v57 = sub_140ECDB40();
      if ( !v57 )
        goto LABEL_78;
      *(_BYTE *)(v57 + 3739) = a3;
      sub_141A73BD0();
      result = 1;
      break;
    case 3640:
      v58 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( v58 )
      {
        v59 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v58 + 296LL))(v58);
        AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v59, 0xCCu);
        if ( AgentByInternalId )
          sub_1410773C0(AgentByInternalId);
      }
      goto LABEL_78;
    case 3641:
      if ( (unsigned __int8)a3 <= 5u && (v42 = sub_140ECDB40()) != 0 )
      {
        *(_BYTE *)(v42 + 3776) = a3;
        result = 1;
      }
      else
      {
LABEL_78:
        result = 1;
      }
      break;
    default:
      result = 0;
      break;
  }
  return result;
}
