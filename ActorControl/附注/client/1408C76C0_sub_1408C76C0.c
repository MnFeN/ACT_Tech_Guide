void __fastcall sub_1408C76C0(
        void *self,
        unsigned int command,
        unsigned int value1,
        unsigned int value2,
        unsigned int value3)
{
  __int64 v6; // r14
  __int64 v8; // rax
  __int64 EventHandlerById; // rax
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  unsigned int v20; // r9d
  unsigned int v21; // r14d
  void *v22; // rax
  __int64 v23; // rcx
  unsigned __int16 v24; // dx
  __int64 v25; // rcx
  __int64 v26; // r8
  char v27; // cl
  char v28; // al
  __int64 v29; // rcx
  char v30; // al
  __int64 v31; // rsi
  unsigned __int16 v32; // dx
  unsigned int v33; // r14d
  _QWORD *v34; // rax
  _DWORD *v35; // rbx
  void *UIModule; // rax
  void *v37; // rax
  __int64 v38; // r8
  _QWORD *v39; // r9
  __int64 v40; // rdx
  __int64 v41; // rsi
  _DWORD **v42; // rbx
  _DWORD *v43; // rbx
  __int64 i; // rbx
  void *v45; // rcx
  void *v46; // rcx
  unsigned int v47; // eax
  __int64 v48; // rsi
  unsigned int v49; // r14d
  unsigned __int16 v50; // dx
  unsigned __int16 v51; // r8
  unsigned __int16 v52; // dx
  __int64 v53; // rcx
  unsigned __int64 v54; // r8
  __int64 v55; // r15
  __int64 v56; // rcx
  char v57; // al
  __int64 v58; // rcx
  __int64 v59; // rsi
  __int64 v60; // rcx
  char v61; // al
  __int64 v62; // rcx
  void *v63; // rax
  char v64; // al
  void *v65; // rax
  bool v66; // zf
  unsigned __int16 v67; // dx
  unsigned __int8 v68; // al
  void *v69; // rdx
  unsigned __int16 v70; // r8
  unsigned __int16 v71; // dx
  void *v72; // rdx
  unsigned __int64 v73; // r14
  unsigned int v74; // edx
  __int64 v75; // rcx
  signed int v76; // edi
  unsigned __int64 v77; // r14
  __int64 v78; // r14
  __int64 v79; // rsi
  bool v80; // al
  __int64 v81; // rcx
  unsigned __int64 v82; // r14
  _QWORD *a1; // [rsp+40h] [rbp-21h] BYREF
  void *pointer; // [rsp+48h] [rbp-19h]
  __int64 v85; // [rsp+50h] [rbp-11h]
  __int64 v86; // [rsp+58h] [rbp-9h]
  __int64 v87; // [rsp+60h] [rbp-1h]
  __int64 a2; // [rsp+68h] [rbp+7h] BYREF
  __int64 *p_a2; // [rsp+70h] [rbp+Fh]
  char v90; // [rsp+78h] [rbp+17h]

  v6 = value2;
  switch ( command )
  {
    case 0u:
      Client__Game__Character__DrawDataContainer__LoadWeapon(*((_QWORD *)self + 1) + 1784LL, 1u, 0, 0, 1, 0, 0, 0);
      v23 = *((_QWORD *)self + 1);
      v24 = 255;
      *((_BYTE *)self + 32) &= ~1u;
      v25 = v23 + 2608;
      *((_BYTE *)self + 30) = 0;
      goto LABEL_121;
    case 1u:
      *((_BYTE *)self + 32) |= 1u;
      v24 = 263;
      *((_BYTE *)self + 30) = 0;
      goto LABEL_119;
    case 2u:
      v26 = *((_QWORD *)self + 1);
      v27 = *(_BYTE *)(v26 + 458);
      if ( value1 )
      {
        v28 = (v27 != 16) + 10;
      }
      else
      {
        v28 = 5;
        if ( v27 == 16 )
          v28 = 2;
      }
      *((_BYTE *)self + 30) = v28;
      v25 = v26 + 2608;
      v24 = 8 * (*((_BYTE *)self + 32) & 1) + 258;
      goto LABEL_121;
    case 3u:
      v29 = *((_QWORD *)self + 1);
      v30 = 4;
      if ( *(_BYTE *)(v29 + 458) != 16 )
        v30 = 7;
      *((_BYTE *)self + 30) = v30;
      v24 = 8 * (*((_BYTE *)self + 32) & 1) + 258;
      goto LABEL_120;
    case 4u:
      v31 = *((_QWORD *)self + 1) + 2608LL;
      if ( (*((_BYTE *)self + 32) & 1) != 0 )
      {
        *((_BYTE *)self + 30) = 1;
        v32 = 265;
      }
      else
      {
        *((_BYTE *)self + 30) = 0;
        v32 = 257;
      }
      v33 = (unsigned __int16)sub_1408BFF70(v31, v32);
      if ( Client__Game__Control__MoveControl__MoveController__IsDiving((void *)(*(_QWORD *)(v31 + 8) + 496LL))
        || (*(_BYTE *)(*(_QWORD *)(v31 + 8) + 1576LL) & 0x20) != 0 )
      {
        std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(v31, v33, 0, 0, 0);
        *((_BYTE *)self + 32) &= ~1u;
      }
      else
      {
        sub_140609420(v31 + 512, v33, 0, 0, 0);
        *((_BYTE *)self + 32) &= ~1u;
      }
      return;
    case 5u:
      pointer = 0;
      v85 = 0;
      v86 = 0;
      v87 = 0;
      v34 = Client__System__Memory__MemoryPool__Alloc(0x10u);
      v90 = 0;
      v34[1] = 0;
      a1 = v34;
      *v34 = &a1;
      a2 = value1;
      p_a2 = &a2;
      sub_1401EABA0(&a1, (__int64)&a2);
      if ( p_a2 )
      {
        if ( v90 == 1 )
        {
          v35 = (_DWORD *)*p_a2;
          if ( (int)--v35[26] <= 0 )
          {
            Client__System__String__Utf8String__Dtor(v35);
            j_Client__System__Memory__IMemorySpace__Free_4((__int64)v35, 112);
          }
        }
      }
      UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
      if ( UIModule )
      {
        v37 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
          v37,
          0x42Fu,
          source,
          0,
          &a1);
      }
      v38 = v87;
      v39 = pointer;
      if ( v87 )
      {
        v40 = v86;
        do
        {
          v41 = v39[(v85 - 1) & (v40 + v38 - 1)];
          v42 = *(_DWORD ***)(v41 + 8);
          if ( v42 )
          {
            if ( *(_BYTE *)(v41 + 16) == 1 )
            {
              v43 = *v42;
              if ( (int)--v43[26] <= 0 )
              {
                Client__System__String__Utf8String__Dtor(v43);
                j_Client__System__Memory__IMemorySpace__Free_4((__int64)v43, 112);
              }
            }
            *(_QWORD *)(v41 + 8) = 0;
            *(_BYTE *)(v41 + 16) = -1;
            v38 = v87;
            v40 = v86;
            v39 = pointer;
          }
          v87 = --v38;
          if ( !v38 )
            v40 = 0;
          v86 = v40;
        }
        while ( v38 );
      }
      for ( i = v85; i; --i )
      {
        v45 = (void *)v39[i - 1];
        if ( v45 )
        {
          Client__System__Memory__MemoryPool__Free(v45);
          v39 = pointer;
        }
      }
      if ( v39 )
        Client__System__Memory__MemoryPool__Free(v39);
      v46 = a1;
      a1 = 0;
      v85 = 0;
      pointer = 0;
      Client__System__Memory__MemoryPool__Free(v46);
      return;
    case 6u:
      switch ( value1 )
      {
        case 0x56A6u:
        case 0x56A7u:
        case 0x56A8u:
        case 0x56AAu:
        case 0x56ABu:
        case 0x56ACu:
          *((_BYTE *)self + 30) = (*(_BYTE *)(*((_QWORD *)self + 1) + 458LL) != 16) + 8;
          *((_BYTE *)self + 31) = value2;
          break;
        default:
          break;
      }
      v47 = value1 - 22183;
      if ( (*((_BYTE *)self + 32) & 1) != 0 )
      {
        v24 = 8197;
        if ( (v47 & 0xFFFFFFFB) != 0 )
          v24 = 4658;
        v29 = *((_QWORD *)self + 1);
      }
      else
      {
        v24 = 4657;
        if ( (v47 & 0xFFFFFFFB) == 0 )
          v24 = 8196;
        v29 = *((_QWORD *)self + 1);
      }
      goto LABEL_120;
    case 7u:
      if ( value1 == 42060 )
        *((_BYTE *)self + 30) = 12;
      return;
    case 8u:
      *((_BYTE *)self + 32) &= ~1u;
      *((_BYTE *)self + 30) = 14;
      switch ( value1 )
      {
        case 0u:
        case 1u:
        case 2u:
          v50 = 236;
          v51 = 237;
          goto LABEL_79;
        case 3u:
        case 4u:
        case 5u:
          v52 = 237;
          goto LABEL_81;
        default:
          goto LABEL_82;
      }
      goto LABEL_82;
    case 9u:
      *((_BYTE *)self + 32) |= 1u;
      *((_BYTE *)self + 30) = 14;
      switch ( value1 )
      {
        case 0u:
        case 1u:
        case 2u:
          v50 = 243;
          v51 = 244;
LABEL_79:
          Client__Game__Character__TimelineContainer__PlayActionTimeline(
            (void *)(*((_QWORD *)self + 1) + 2608LL),
            v50,
            v51,
            0);
          break;
        case 3u:
        case 4u:
        case 5u:
          v52 = 244;
LABEL_81:
          std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(
            *((_QWORD *)self + 1) + 2608LL,
            v52,
            0,
            0,
            0);
          break;
        default:
          break;
      }
LABEL_82:
      v53 = *((_QWORD *)self + 1);
      v54 = v6 | ((unsigned __int64)value3 << 32);
      if ( v54 != *(_QWORD *)(v53 + 2024) )
        goto LABEL_161;
      return;
    case 0xAu:
      v55 = *((_QWORD *)self + 1);
      if ( *(_QWORD *)(v55 + 6592) )
      {
        v56 = *(_QWORD *)(v55 + 6592);
        if ( v56 )
        {
          v57 = sub_140390FF0(v56);
          v58 = *(_QWORD *)(v55 + 6592);
          if ( v57 )
            sub_140391030(v58, 1);
          else
            sub_140390F50(v58);
          sub_140391940(*(_QWORD *)(v55 + 6592), 0);
          *(_QWORD *)(v55 + 6592) = 0;
        }
      }
      *((_BYTE *)self + 28) = 0;
      sub_1408C6AC0((__int64)self, value1);
      if ( (_DWORD)v6 )
      {
        v59 = *((_QWORD *)self + 1);
        if ( *(_QWORD *)(v59 + 6600) )
        {
          v60 = *(_QWORD *)(v59 + 6600);
          if ( v60 )
          {
            v61 = sub_140390FF0(v60);
            v62 = *(_QWORD *)(v59 + 6600);
            if ( v61 )
              sub_140391030(v62, 1);
            else
              sub_140390F50(v62);
            sub_140391940(*(_QWORD *)(v59 + 6600), 0);
            *(_QWORD *)(v59 + 6600) = 0;
          }
        }
        *((_BYTE *)self + 29) = 0;
        sub_1408C6AC0((__int64)self, v6);
      }
      return;
    case 0xBu:
      sub_1408C6DC0((__int64)self, 1);
      return;
    case 0xCu:
      v63 = (void *)(*(__int64 (__fastcall **)(_QWORD, struct HINSTANCE__ *))(**((_QWORD **)self + 1) + 632LL))(
                      *((_QWORD *)self + 1),
                      &_ImageBase);
      if ( !Client__Game__StatusManager__HasStatus(v63, 0xEE5u, 0xE0000000)
        || value1 == 11619
        || (v64 = 16, (_DWORD)v6 == 11620) )
      {
        v64 = 15;
      }
      goto LABEL_110;
    case 0xDu:
      v65 = (void *)(*(__int64 (__fastcall **)(_QWORD, struct HINSTANCE__ *))(**((_QWORD **)self + 1) + 632LL))(
                      *((_QWORD *)self + 1),
                      &_ImageBase);
      if ( !Client__Game__StatusManager__HasStatus(v65, 0xEE5u, 0xE0000000)
        || value1 == 11619
        || (v64 = 18, (_DWORD)v6 == 11620) )
      {
        v64 = 17;
      }
LABEL_110:
      *((_BYTE *)self + 30) = v64;
      if ( (*((_BYTE *)self + 32) & 1) == 0 )
        LOWORD(v6) = value1;
      std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(
        *((_QWORD *)self + 1) + 2608LL,
        v6,
        0,
        0,
        0);
      sub_1408C6AC0((__int64)self, value3);
      return;
    case 0xEu:
      v66 = (*((_BYTE *)self + 32) & 1) == 0;
      v67 = 245;
      *((_BYTE *)self + 30) = 14;
      if ( v66 )
        v67 = 238;
      Client__Game__Character__TimelineContainer__PlayActionTimeline(
        (void *)(*((_QWORD *)self + 1) + 2608LL),
        v67,
        3u,
        0);
      sub_1408C6DC0((__int64)self, 0);
      Client__Game__Character__DrawDataContainer__LoadWeapon(*((_QWORD *)self + 1) + 1784LL, 1u, 0, 0, 1, 0, 0, 0);
      Client__Game__Character__DrawDataContainer__LoadWeapon(*((_QWORD *)self + 1) + 1784LL, 2u, 0, 0, 1, 0, 0, 0);
      Client__Game__Character__Character__SetMode(*((void **)self + 1), 1u, 0);
      *((_BYTE *)self + 32) &= ~1u;
      return;
    case 0xFu:
      sub_1408C6DC0((__int64)self, 1);
      sub_1408C6AC0((__int64)self, 0xEu);
      return;
    case 0x10u:
      sub_1408C6DC0((__int64)self, 1);
      sub_1408C6AC0((__int64)self, 0xFu);
      return;
    case 0x11u:
      v68 = *((_BYTE *)self + 32) & 1;
      *((_BYTE *)self + 30) = 20;
      v24 = v68 + 251;
      goto LABEL_119;
    case 0x12u:
    case 0x13u:
      if ( value1 && value2 )
      {
        v69 = (void *)*((_QWORD *)self + 1);
        if ( value2 == 1 )
          Client__Game__BattleLog__AddLogMessage3Params(0x484u, v69, value1, 0, 0, 5.0);
        else
          Client__Game__BattleLog__AddLogMessage3Params(0x485u, v69, value1, value2, 0, 5.0);
      }
      return;
    case 0x14u:
      sub_1408C6DC0((__int64)self, 1);
      sub_1408C6AC0((__int64)self, 0xDu);
      return;
    case 0x15u:
      *((_BYTE *)self + 30) = 19;
      goto LABEL_131;
    case 0x16u:
      *((_BYTE *)self + 30) = 20;
      goto LABEL_131;
    case 0x17u:
      *((_BYTE *)self + 30) = 21;
LABEL_131:
      v70 = 244;
      v71 = 248;
      if ( (*((_BYTE *)self + 32) & 1) == 0 )
      {
        v70 = 237;
        v71 = 241;
      }
      Client__Game__Character__TimelineContainer__PlayActionTimeline(
        (void *)(*((_QWORD *)self + 1) + 2608LL),
        v71,
        v70,
        0);
      return;
    case 0x18u:
      if ( value1 )
        Client__Game__BattleLog__AddLogMessage3Params(0x170Eu, *((void **)self + 1), value1, 0, 0, 5.0);
      return;
    case 0x19u:
      if ( value1 )
      {
        v72 = (void *)*((_QWORD *)self + 1);
        if ( value2 )
          Client__Game__BattleLog__AddLogMessage3Params(0x171Du, v72, value1, 0, 0, 5.0);
        else
          Client__Game__BattleLog__AddLogMessage3Params(0x1710u, v72, value1, 0, 0, 5.0);
      }
      return;
    case 0x1Au:
      v8 = sub_140B777C0();
      EventHandlerById = j_Client__Game__Event__EventFramework__GetEventHandlerById(v8, 1376257);
      if ( EventHandlerById )
        sub_140E90C50(EventHandlerById, *((_DWORD **)self + 1), value1, v6, value3);
      return;
    case 0x1Bu:
      v10 = sub_140B777C0();
      v11 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v10, 1376257);
      if ( v11 )
        sub_140E90CC0(v11, *((_QWORD *)self + 1), value1);
      return;
    case 0x1Cu:
      v12 = sub_140B777C0();
      v13 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v12, 1376257);
      if ( v13 )
        sub_140E90CE0(v13, *((_QWORD *)self + 1), value1, v6);
      return;
    case 0x1Du:
      v14 = sub_140B777C0();
      v15 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v14, 1376257);
      if ( v15 )
        sub_140E90D50(v15, *((_QWORD *)self + 1), value1);
      return;
    case 0x1Eu:
      v16 = sub_140B777C0();
      v17 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v16, 1376257);
      if ( v17 )
        sub_140E90F40(v17);
      return;
    case 0x20u:
      v18 = sub_140B777C0();
      v19 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v18, 1376257);
      if ( v19 )
        sub_140E90F60(v19, *((_QWORD *)self + 1));
      return;
    case 0x21u:
      if ( value1 && value2 )
      {
        v20 = value2 / 0xA;
        v21 = (unsigned int)v6 % 0xA;
        v22 = (void *)*((_QWORD *)self + 1);
        if ( value3 <= 1 )
          Client__Game__BattleLog__AddLogMessage3Params(0xDB8u, v22, value1, v20, v21, 20.0);
        else
          Client__Game__BattleLog__AddLogMessage(0xDE7u, v22, value1, v20, v21, value3, 20.0);
      }
      return;
    case 0x22u:
      *((_BYTE *)self + 32) |= 1u;
      *((_BYTE *)self + 30) = 13;
      return;
    case 0x23u:
      *((_BYTE *)self + 32) |= 1u;
      v24 = 4819;
      *((_BYTE *)self + 30) = 13;
      goto LABEL_119;
    case 0x24u:
      v24 = 4822;
LABEL_119:
      v29 = *((_QWORD *)self + 1);
LABEL_120:
      v25 = v29 + 2608;
LABEL_121:
      std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(v25, v24, 0, 0, 0);
      return;
    case 0x25u:
      v48 = *((_QWORD *)self + 1);
      *((_BYTE *)self + 30) = 1;
      v49 = (unsigned __int16)sub_1408BFF70(v48 + 2608, 0x12D5u);
      if ( Client__Game__Control__MoveControl__MoveController__IsDiving((void *)(*(_QWORD *)(v48 + 2616) + 496LL))
        || (*(_BYTE *)(*(_QWORD *)(v48 + 2616) + 1576LL) & 0x20) != 0 )
      {
        std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(v48 + 2608, v49, 0, 0, 0);
        *((_BYTE *)self + 32) &= ~1u;
      }
      else
      {
        sub_140609420(v48 + 3120, v49, 0, 0, 0);
        *((_BYTE *)self + 32) &= ~1u;
      }
      return;
    case 0x26u:
      v53 = *((_QWORD *)self + 1);
      v73 = value1 | ((unsigned __int64)value2 << 32);
      if ( v73 == *(_QWORD *)(v53 + 1800) )
        return;
      if ( !v73 )
      {
        sub_1408C6DC0((__int64)self, 0);
        v53 = *((_QWORD *)self + 1);
      }
      v54 = v73;
      v74 = 0;
      break;
    case 0x27u:
      v75 = *((_QWORD *)self + 1);
      v76 = 0;
      v77 = value1 | ((unsigned __int64)value2 << 32);
      if ( v77 != *(_QWORD *)(v75 + 1912) )
      {
        if ( !v77 )
        {
          sub_1408C6DC0((__int64)self, 0);
          v75 = *((_QWORD *)self + 1);
        }
        Client__Game__Character__DrawDataContainer__LoadWeapon(v75 + 1784, 1u, v77, 0, 1, 0, 0, 0);
      }
      v78 = 0;
      do
      {
        v79 = *((_QWORD *)self + 1) + 1784LL;
        if ( (*(_BYTE *)(*(_QWORD *)(*((_QWORD *)self + 1) + 1792LL) + 3454LL) & 0x40) != 0 || v76 == 2 )
          *(_BYTE *)(v79 + v78 + 122) |= 8u;
        else
          *(_BYTE *)(v79 + v78 + 122) &= ~8u;
        if ( (*(_BYTE *)(v79 + v78 + 122) & 4) != 0 )
        {
          v80 = sub_1408B1AB0(v79, v76);
          v81 = *(_QWORD *)(v79 + v78 + 24);
          *(_BYTE *)(v81 + 136) &= ~1u;
          *(_BYTE *)(v81 + 136) |= v80;
        }
        ++v76;
        v78 += 112;
      }
      while ( v76 < 3 );
      return;
    case 0x28u:
      v53 = *((_QWORD *)self + 1);
      v82 = value1 | ((unsigned __int64)value2 << 32);
      if ( v82 == *(_QWORD *)(v53 + 2024) )
        return;
      if ( !v82 )
      {
        sub_1408C6DC0((__int64)self, 0);
        v53 = *((_QWORD *)self + 1);
      }
      v54 = v82;
LABEL_161:
      v74 = 2;
      break;
    default:
      return;
  }
  Client__Game__Character__DrawDataContainer__LoadWeapon(v53 + 1784, v74, v54, 0, 1, 0, 0, 0);
}
