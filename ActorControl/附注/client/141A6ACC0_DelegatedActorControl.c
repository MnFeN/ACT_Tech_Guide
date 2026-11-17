char __fastcall sub_141A6ACC0(
        __int64 a1,
        unsigned int a2,
        unsigned int a3,
        unsigned int a4,
        unsigned int a5,
        unsigned int a6,
        unsigned int a7,
        int a8)
{
  char v8; // r15
  __int64 v12; // rdi
  void *v13; // rax
  _BYTE *v14; // rax
  int v15; // edi
  __int64 v16; // rcx
  __int64 v17; // rdi
  __int128 v18; // xmm0
  __int128 v19; // xmm1
  int v20; // eax
  __int128 v21; // xmm0
  __int128 v22; // xmm1
  __int128 v23; // xmm0
  _QWORD *v24; // rcx
  _BYTE *v25; // rax
  _BYTE *v26; // rdx
  void *v27; // rax
  __int64 v28; // rax
  void *v29; // rax
  void *v30; // rax
  void *v31; // rax
  void *UIModule; // rax
  __int64 v33; // rax
  void *v34; // rax
  void *v35; // rax
  void *AgentByInternalId; // rax
  void *v37; // rax
  __int64 v38; // rax
  __int64 v39; // rax
  void *v40; // rax
  void *MassivePcContentDirector; // rax
  int v42; // eax
  __int64 v43; // rax
  void *LayoutInstanceStatic; // rax
  char v45; // r15
  _BYTE self[104]; // [rsp+50h] [rbp-128h] BYREF
  unsigned int a1a[4]; // [rsp+B8h] [rbp-C0h] BYREF
  __int128 v51; // [rsp+C8h] [rbp-B0h]
  __int128 v52; // [rsp+D8h] [rbp-A0h]
  __int128 v53; // [rsp+E8h] [rbp-90h]
  __int128 v54; // [rsp+F8h] [rbp-80h]
  __int64 v55; // [rsp+108h] [rbp-70h]
  int v56; // [rsp+110h] [rbp-68h]
  __int16 v57; // [rsp+114h] [rbp-64h]
  char v58; // [rsp+116h] [rbp-62h]

  v8 = 0;
  if ( a3 == *(_DWORD *)(a1 + 33368) && (*(_BYTE *)(a1 + 33372) & 3) == 3 )
  {
    v12 = *(_QWORD *)(sub_140ECDB40() + 4360);
    if ( v12 )
    {
      switch ( a2 )
      {
        case 0xDF4u:
          v13 = (void *)sub_140B777C0();
          if ( !Client__Game__Event__EventFramework__GetMassivePcContentDirector(v13) )
            return 0;
          switch ( a4 )
          {
            case 1u:
              v8 = sub_141A6B5C0(a1, (unsigned __int8)a5);
              break;
            case 2u:
              *(_DWORD *)(a1 + 33408) = a5;
              v8 = 1;
              break;
            case 3u:
              *(_DWORD *)(a1 + 33412) = a5;
              *(_DWORD *)(a1 + 33416) = a6;
              sub_141A2FA90(v12);
              break;
            case 4u:
              sub_141A6C410(a1, a5, a6, a7 == 1);
              break;
            case 5u:
              *(_DWORD *)(a1 + 33420) = a5;
              sub_141A2FB40(v12);
              break;
            case 6u:
              *(_DWORD *)(a1 + 33424) = a5;
              *(_DWORD *)(a1 + 33428) = a6;
              *(_DWORD *)(a1 + 33432) = a7;
              sub_141A301E0(v12);
              break;
            case 7u:
              *(_DWORD *)(a1 + 33436) = a5;
              *(_DWORD *)(a1 + 33440) = a6;
              sub_141A2FB40(v12);
              break;
            case 8u:
              *(_DWORD *)(a1 + 33444) = a5;
              *(_DWORD *)(a1 + 33448) = a6;
              *(_DWORD *)(a1 + 33452) = a7;
              sub_141A301E0(v12);
              break;
            case 9u:
              v14 = (_BYTE *)(a1 + 25500);
              v15 = 0;
              v16 = 0;
              while ( *((_DWORD *)v14 - 2) != a5 || (_BYTE)a6 != *v14 )
              {
                ++v15;
                ++v16;
                v14 += 200;
                if ( v16 >= 40 )
                  goto LABEL_56;
              }
              if ( v15 != -1 )
              {
                Client__System__String__Utf8String__Ctor_FromSequence(self, (void *)&str, 0xFFFFFFFF);
                sub_140C11CF0(a1a, 0, 0);
                v55 = 0;
                v17 = 200LL * v15 + a1 + 25304;
                v56 = 0;
                v57 = 0;
                v58 = 0;
                Client__System__String__Utf8String__Copy((void *)v17, self);
                v18 = *(_OWORD *)a1a;
                v19 = v51;
                *(_DWORD *)(v17 + 184) = v55;
                v20 = HIDWORD(v55);
                *(_OWORD *)(v17 + 104) = v18;
                *(_DWORD *)(v17 + 188) = v20;
                v21 = v52;
                *(_DWORD *)(v17 + 192) = v56;
                LOBYTE(v20) = v57;
                *(_OWORD *)(v17 + 120) = v19;
                *(_BYTE *)(v17 + 196) = v20;
                v22 = v53;
                *(_BYTE *)(v17 + 197) = HIBYTE(v57);
                LOBYTE(v20) = v58;
                *(_OWORD *)(v17 + 136) = v21;
                *(_BYTE *)(v17 + 198) = v20;
                v23 = v54;
                *(_OWORD *)(v17 + 152) = v22;
                *(_OWORD *)(v17 + 168) = v23;
                Client__System__String__Utf8String__Dtor(self);
                v24 = *(_QWORD **)(a1 + 25280);
                v25 = *(_BYTE **)(a1 + 25288);
                if ( v24 != (_QWORD *)v25 )
                {
                  while ( 1 )
                  {
                    v26 = v24 + 1;
                    if ( *v24 == v17 )
                      break;
                    ++v24;
                    if ( v26 == v25 )
                      goto LABEL_56;
                  }
                  memmove(v24, v26, v25 - v26);
                  *(_QWORD *)(a1 + 25288) -= 8LL;
                }
              }
              break;
            default:
              goto LABEL_56;
          }
          goto LABEL_56;
        case 0xDFAu:
          if ( a4 == 3 )
          {
            if ( *(_DWORD *)(a1 + 33344) )
            {
              UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v33 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 64LL))(UIModule);
              (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v33 + 168LL))(v33, *(unsigned int *)(a1 + 33344));
              *(_DWORD *)(a1 + 33344) = 0;
            }
            v34 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v35 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v34 + 296LL))(v34);
            AgentByInternalId = Client__UI__Agent__AgentModule__GetAgentByInternalId(v35, 0x1D5u);
            sub_140A7BBB0(AgentByInternalId);
          }
          else if ( a4 == 4 )
          {
            if ( *(_DWORD *)(a1 + 33344) )
            {
              v27 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v28 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v27 + 64LL))(v27);
              (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v28 + 168LL))(v28, *(unsigned int *)(a1 + 33344));
              *(_DWORD *)(a1 + 33344) = 0;
            }
            v29 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v30 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v29 + 296LL))(v29);
            v31 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v30, 0x1D5u);
            sub_140A7BE70(v31);
          }
          goto LABEL_56;
        case 0xDFCu:
          *(_DWORD *)(a1 + 33376) = a4;
          v8 = 1;
          *(_DWORD *)(a1 + 33380) = a5;
          *(_DWORD *)(a1 + 33388) = a6;
          goto LABEL_56;
        case 0xDFDu:
          if ( a4 != 1 )
          {
            v39 = sub_141A6CB00(a1);
            sub_140A7BDA0(v39);
            goto LABEL_39;
          }
          if ( *(_DWORD *)(a1 + 33344) )
          {
            v37 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v38 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v37 + 64LL))(v37);
            (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v38 + 168LL))(v38, *(unsigned int *)(a1 + 33344));
            *(_DWORD *)(a1 + 33344) = 0;
          }
          *(_DWORD *)(v12 + 67012) &= ~2u;
          v8 = 1;
          *(_DWORD *)(v12 + 67008) = 0;
          goto LABEL_56;
        case 0xDFFu:
          if ( *(_DWORD *)(a1 + 33460) == a4 )
            goto LABEL_39;
          *(_DWORD *)(a1 + 33460) = a4;
          v40 = (void *)sub_140B777C0();
          MassivePcContentDirector = Client__Game__Event__EventFramework__GetMassivePcContentDirector(v40);
          if ( MassivePcContentDirector )
            sub_141A23F40(MassivePcContentDirector, 0);
          v42 = *(_DWORD *)(a1 + 33368);
          if ( v42 != 8 )
            goto LABEL_51;
          if ( !*(_DWORD *)(a1 + 33460) )
            goto LABEL_39;
          v43 = *(_QWORD *)(a1 + 25280);
          if ( v43 == *(_QWORD *)(a1 + 25288) )
            goto LABEL_39;
          do
          {
            if ( *(_BYTE *)(*(_QWORD *)v43 + 196LL) == 3 )
              *(_BYTE *)(*(_QWORD *)v43 + 176LL) |= 1u;
            v43 += 8;
          }
          while ( v43 != *(_QWORD *)(a1 + 25288) );
          v42 = *(_DWORD *)(a1 + 33368);
LABEL_51:
          if ( v42 == 10
            && *(_DWORD *)(a1 + 33460) == 1
            && (LayoutInstanceStatic = Client__LayoutEngine__LayoutWorld__GetLayoutInstanceStatic(6u, 0xC0F5D3u, 0)) != 0 )
          {
            Client__LayoutEngine__Group__SharedGroupLayoutInstance__PlayTimeline(LayoutInstanceStatic, 1u, 0);
            v8 = 1;
          }
          else
          {
LABEL_39:
            v8 = 1;
          }
LABEL_56:
          v45 = sub_141C54220((void *)(a1 + 112), a2, a3, a4, a5, a6, a7) | v8;
          return v45
               | (*(__int64 (__fastcall **)(_QWORD, _QWORD, _QWORD, _QWORD, unsigned int, unsigned int, unsigned int, int))(**(_QWORD **)(a1 + 33352) + 72LL))(
                   *(_QWORD *)(a1 + 33352),
                   a2,
                   a3,
                   a4,
                   a5,
                   a6,
                   a7,
                   a8);
        case 0xE01u:
          *(_BYTE *)(a1 + 33457) = 1;
          goto LABEL_56;
        default:
          goto LABEL_56;
      }
    }
  }
  return 0;
}
