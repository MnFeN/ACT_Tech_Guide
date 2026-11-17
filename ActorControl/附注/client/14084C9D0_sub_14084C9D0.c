char __fastcall sub_14084C9D0(__int64 a1, unsigned __int16 *a2, unsigned int *a3)
{
  __int64 v6; // r8
  unsigned int v7; // eax
  char result; // al
  unsigned __int64 targetId; // rax
  unsigned int v10; // ecx
  unsigned int v11; // ecx
  unsigned int v12; // ecx
  unsigned int v13; // ecx
  unsigned int v14; // ecx
  char v15; // al
  unsigned int v16; // ecx
  unsigned int v17; // edi
  __int64 v18; // rax
  __int64 v19; // rax
  __int64 v20; // rcx
  __int64 v21; // rcx
  struct HINSTANCE__ *v22; // rdx
  unsigned __int64 v23; // r9
  void *UIModule; // rax
  __int64 v25; // rcx
  __int64 v26; // rax
  __int64 v27; // rcx

  sub_140B4BEF0(*((unsigned int *)a2 + 2), *a2);
  v7 = *a2;
  if ( v7 > 0x16C )
  {
    if ( v7 > 0x26C )
    {
      if ( v7 > 0x378 )
      {
        switch ( *a2 )
        {
          case 0x37Bu:
LABEL_156:
            sub_140B37040(*((_DWORD *)a2 + 2), a3, 1);
            result = 1;
            break;
          case 0x38Au:
            sub_140B4B6E0(a3);
            result = 1;
            break;
          case 0x38Bu:
LABEL_151:
            sub_140B31F70(*a3, a3[1], a3 + 3, *((unsigned __int8 *)a3 + 8));
            result = 1;
            break;
          case 0x39Cu:
            sub_140B385F0(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x39Fu:
            sub_140B31C20(a3[2], *(_QWORD *)a3, *((unsigned __int8 *)a3 + 12), a3[4], *((_BYTE *)a3 + 13));
            v25 = *(unsigned __int8 *)(a1 + 1824);
            if ( (unsigned __int64)(v25 + 1) >= 8 )
              goto LABEL_164;
            v26 = (unsigned __int8)(v25 + 1);
            *(_BYTE *)(a1 + 1824) = v26;
            v27 = 3 * (v26 + 68);
            *(_OWORD *)(a1 + 8 * v27) = *(_OWORD *)a3;
            *(_QWORD *)(a1 + 8 * v27 + 16) = *((_QWORD *)a3 + 2);
            result = 1;
            break;
          case 0x3A5u:
            sub_140B32330(a3);
            result = 1;
            break;
          case 0x3A6u:
            sub_140B37A70(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x3ABu:
            sub_140B4D9D0(a3);
            result = 1;
            break;
          case 0x3ACu:
            LOBYTE(v6) = 1;
            sub_140B361D0(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x3B2u:
            LOBYTE(v6) = 1;
            sub_140B49B50(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x3C0u:
            sub_140B49AA0(a3);
            result = 1;
            break;
          case 0x3CEu:
            sub_140B4B720(a3);
            goto LABEL_164;
          case 0x3D2u:
            sub_140B49090(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x3DBu:
            sub_140B4BD30(a3);
            result = 1;
            break;
          case 0x3E3u:
            LOBYTE(v6) = 1;
            sub_140B48640(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          default:
LABEL_164:
            result = 1;
            break;
        }
      }
      else if ( v7 == 888 )
      {
        sub_140B4B9E0(a3);
        return 1;
      }
      else
      {
        v22 = &_ImageBase;
        switch ( *a2 )
        {
          case 0x26Eu:
            sub_140B4D990(a3);
            result = 1;
            break;
          case 0x271u:
            goto LABEL_151;
          case 0x287u:
            sub_140B4B7A0(a3);
            result = 1;
            break;
          case 0x293u:
          case 0x2C9u:
          case 0x355u:
            goto LABEL_156;
          case 0x2B0u:
            LOBYTE(v22) = 1;
            sub_140B4C8F0(a3, v22);
            result = 1;
            break;
          case 0x2B5u:
            sub_140B323B0(a3);
            result = 1;
            break;
          case 0x2BEu:
            LOBYTE(v6) = 1;
            sub_140B49B80(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x2BFu:
          case 0x344u:
LABEL_115:
            v23 = *((_QWORD *)a3 + 2) & 0xFFFFFFFFFFFFD7FFuLL;
            if ( (*((_QWORD *)a3 + 2) & 0x400LL) != 0 )
              v23 = *((_QWORD *)a3 + 2);
            Client__Network__PacketDispatcher__HandleEventPlayPacket(
              *(_QWORD *)a3,
              a3[2],
              *((_WORD *)a3 + 6),
              v23,
              a3 + 7,
              *((_BYTE *)a3 + 24));
            result = 1;
            break;
          case 0x2CFu:
            sub_140B32370(a3);
            result = 1;
            break;
          case 0x2D2u:
            sub_1408FD370((__int64)qword_142AA81A0, *((_DWORD *)a2 + 2), (char *)a3);
            result = 1;
            break;
          case 0x2DAu:
            sub_140B49030(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x2DDu:
            sub_140B37B50(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x2DFu:
            targetId = 3758096384LL;
LABEL_113:
            HandleActorControl(
              *((_DWORD *)a2 + 2),
              *(unsigned __int16 *)a3,
              a3[1],
              a3[2],
              a3[3],
              a3[4],
              0,
              0,
              0,
              0,
              targetId,
              1u);
            result = 1;
            break;
          case 0x2E3u:
            sub_140B37820(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x2E6u:
            sub_140B4B9A0(a3);
            result = 1;
            break;
          case 0x2F4u:
            sub_140B321D0(a3);
            result = 1;
            break;
          case 0x2F8u:
            sub_140B36170(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x2FCu:
            Client__Network__PacketDispatcher__HandleSpawnPlayerPacket(*((_DWORD *)a2 + 2), a3);
            result = 1;
            break;
          case 0x2FDu:
            sub_140B35EB0(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x308u:
            LOBYTE(v6) = 1;
            sub_140B48E20(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x30Bu:
            LOBYTE(v6) = 1;
            sub_140B49BB0(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x318u:
            sub_140B4DE80(a3);
            result = 1;
            break;
          case 0x319u:
            goto LABEL_118;
          case 0x31Eu:
            sub_140B33400((__int64)a3);
            result = 1;
            break;
          case 0x320u:
            LOBYTE(v6) = 1;
            sub_140B36DC0(*((unsigned int *)a2 + 2), a3, v6);
            result = 1;
            break;
          case 0x323u:
            sub_1408FD340(qword_142AA81A0, a3);
            if ( *(char *)(a1 + 1859) < 0 || *(_BYTE *)(a1 + 1844) < 0x40u )
              goto LABEL_164;
            if ( (unsigned __int8)sub_140BE03D0((__int64)&byte_142ADF3B8, 0) != byte_142AA81F8 )
            {
              UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              if ( UIModule )
                (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)UIModule + 1000LL))(
                  UIModule,
                  2,
                  (unsigned __int8)byte_142AA81F8);
            }
            *(_BYTE *)(a1 + 1859) |= 0x80u;
            result = 1;
            break;
          case 0x33Bu:
LABEL_126:
            sub_140B37430(*((_DWORD *)a2 + 2), a3, 1);
            result = 1;
            break;
          case 0x345u:
            sub_140B49F80(a3);
            result = 1;
            break;
          case 0x35Du:
            sub_140B36110(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x363u:
            sub_140B4C910(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          case 0x36Cu:
            sub_140B4C140(*((unsigned int *)a2 + 2), a3);
            result = 1;
            break;
          default:
            goto LABEL_164;
        }
      }
    }
    else if ( v7 == 620 )
    {
LABEL_118:
      sub_140B31E60(
        *a3,
        *((_QWORD *)a3 + 1),
        a3[4],
        a3[5],
        *((_BYTE *)a3 + 24) != 0,
        a3[7],
        *((_BYTE *)a3 + 32) != 0,
        (__int64)(a3 + 9),
        *((_BYTE *)a3 + 33));
      return 1;
    }
    else
    {
      switch ( *a2 )
      {
        case 0x16Eu:
          sub_140B4DF00(a3);
          result = 1;
          break;
        case 0x172u:
          sub_140B379E0(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x176u:
          Client__Network__PacketDispatcher__HandleSpawnNpcPacket(*((_DWORD *)a2 + 2), a3);
          result = 1;
          break;
        case 0x177u:
          sub_140B37D30(a3);
          result = 1;
          break;
        case 0x178u:
          LOBYTE(v6) = 1;
          sub_140B36C30(*((unsigned int *)a2 + 2), a3, v6);
          result = 1;
          break;
        case 0x18Au:
          sub_140B4CEA0(a3);
          result = 1;
          break;
        case 0x18Fu:
          sub_140B32250(a3);
          result = 1;
          break;
        case 0x190u:
          sub_140B38490(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x19Eu:
          sub_140B37D10(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x1A5u:
          sub_140B4DDE0(a3);
          result = 1;
          break;
        case 0x1A6u:
        case 0x1AFu:
        case 0x24Au:
        case 0x25Fu:
          goto LABEL_126;
        case 0x1B1u:
          sub_140B4CDC0(a3);
          result = 1;
          break;
        case 0x1B3u:
          sub_140B322A0(a3);
          result = 1;
          break;
        case 0x1BAu:
          sub_140B35FA0(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x1C4u:
          LOBYTE(v6) = 1;
          sub_140B369A0(*((unsigned int *)a2 + 2), a3, v6);
          result = 1;
          break;
        case 0x1C8u:
          sub_140B4B760(a3);
          result = 1;
          break;
        case 0x1D0u:
          sub_140B49760(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x1D2u:
        case 0x1DEu:
          goto LABEL_151;
        case 0x1DFu:
          sub_140B33440(a3);
          result = 1;
          break;
        case 0x1E5u:
        case 0x20Bu:
        case 0x231u:
          goto LABEL_115;
        case 0x1EDu:
          sub_140B4BA60(a3);
          result = 1;
          break;
        case 0x1EEu:
          sub_140B4C950(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x1F9u:
          sub_140B32430(a3);
          result = 1;
          break;
        case 0x1FCu:
          sub_140B4B670(a3);
          result = 1;
          break;
        case 0x21Du:
          sub_140B31F00(*a3, 0xCu);
          result = 1;
          break;
        case 0x21Fu:
          sub_140B4D1A0(a3);
          result = 1;
          break;
        case 0x226u:
          sub_140B37B90(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x230u:
          goto LABEL_86;
        case 0x233u:
          sub_140B384F0(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        case 0x238u:
          sub_140B32290(a3);
          result = 1;
          break;
        case 0x23Cu:
          sub_140B33480(a3);
          result = 1;
          break;
        case 0x246u:
          sub_140B4D220(a3);
          result = 1;
          break;
        case 0x247u:
          sub_140B4CE20(a3);
          result = 1;
          break;
        case 0x250u:
          sub_140B4DE20(a3);
          result = 1;
          break;
        case 0x254u:
          sub_140B322B0(a3);
          result = 1;
          break;
        case 0x25Cu:
          sub_1419DB7B0(*((unsigned int *)a2 + 2), a3);
          result = 1;
          break;
        default:
          goto LABEL_164;
      }
    }
  }
  else if ( v7 == 364 )
  {
LABEL_86:
    sub_140B31DB0(
      a3[2],
      *(_QWORD *)a3,
      *((unsigned __int8 *)a3 + 28),
      a3[3],
      a3[4],
      a3[5],
      *((unsigned __int8 *)a3 + 29),
      a3[6],
      (__int64)(a3 + 8),
      *((_BYTE *)a3 + 30));
    return 1;
  }
  else
  {
    switch ( *a2 )
    {
      case 0x6Bu:
        goto LABEL_118;
      case 0x6Du:
      case 0x72u:
      case 0x108u:
        goto LABEL_115;
      case 0x77u:
        goto LABEL_126;
      case 0x83u:
        sub_140B4DD30(a3);
        return 1;
      case 0x89u:
        sub_1419DB820(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0x97u:
        Client__Network__PacketDispatcher__HandleMapEffectPacket(a3);
        return 1;
      case 0x9Cu:
        sub_140B4C0D0(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0xA4u:
        LOBYTE(v6) = 1;
        sub_140B36B00(*((unsigned int *)a2 + 2), a3, v6);
        return 1;
      case 0xA9u:
        HandleActorControl(
          *((_DWORD *)a2 + 2),
          *(unsigned __int16 *)a3,
          a3[1],
          a3[2],
          a3[3],
          a3[4],
          a3[5],
          a3[6],
          a3[7],
          a3[8],
          0xE0000000,
          1u);
        switch ( *(_WORD *)a3 )
        {
          case 0x64:
            if ( HIWORD(a3[1]) == 32771 || HIWORD(a3[1]) == 32772 || HIWORD(a3[1]) == 32780 )
            {
              *(_DWORD *)(a1 + 1624) = a3[1];
              return 1;
            }
            break;
          case 0x65:
            if ( *(_DWORD *)(a1 + 1624) != a3[1] )
              goto LABEL_164;
            *(_BYTE *)(a1 + 1859) &= ~0x40u;
            *(_DWORD *)(a1 + 1624) = 0;
            return 1;
          case 0x6D:
            v10 = *(_DWORD *)(a1 + 1624);
            if ( v10 && v10 == a3[1] )
            {
              v11 = HIWORD(v10);
              if ( v11 == 32771 || v11 == 32772 || v11 == 32780 )
              {
                if ( a3[2] == 1073741825 )
                {
                  v14 = a3[3];
                  *(_DWORD *)(a1 + 1848) = *((_DWORD *)a2 + 1);
                  v15 = *(_BYTE *)(a1 + 1858);
                  *(_DWORD *)(a1 + 1852) = v14;
                  if ( v15 >= 0 )
                    *(_BYTE *)(a1 + 1858) = v15 | 0x80;
                }
              }
              else
              {
                v12 = v11 - 32771;
                if ( v12 )
                {
                  v13 = v12 - 1;
                  if ( v13 )
                  {
                    if ( v13 != 8 )
                      return 1;
                  }
                }
              }
              if ( a3[2] == -2147483645 )
              {
                v16 = a3[3];
                *(_DWORD *)(a1 + 1848) = *((_DWORD *)a2 + 1);
                *(_DWORD *)(a1 + 1852) = v16;
                return 1;
              }
            }
            break;
          case 0x3A6:
            *(_WORD *)(a1 + 1856) = *((_WORD *)a3 + 2);
            return 1;
          default:
            goto LABEL_164;
        }
        goto LABEL_164;
      case 0xABu:
        Client__Network__PacketDispatcher__HandleZoneInitPacket(
          *((_DWORD *)a2 + 2),
          a3,
          (*(_BYTE *)(a1 + 1844) < 0x40u) + 1);
        return 1;
      case 0xAEu:
        sub_140B37A90(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0xB0u:
        sub_140B4D1E0(a3);
        return 1;
      case 0xB1u:
        sub_140B4BA20(a3);
        return 1;
      case 0xB6u:
        v17 = *((unsigned __int8 *)a3 + 5);
        if ( v17 == 1 )
        {
          v18 = sub_140B777C0();
          v19 = sub_140B84920(v18);
          if ( v19 )
          {
            if ( *(_DWORD *)(v19 + 32) == *a3 && *(_WORD *)(v19 + 120) != 0xFFFF )
              return 0;
          }
        }
        sub_140B31C80(*a3, *((unsigned __int8 *)a3 + 4), a3[2], v17);
        v20 = *(unsigned __int8 *)(a1 + 1824);
        if ( (unsigned __int8)(v20 - 1) > 6u )
          goto LABEL_164;
        v21 = 3 * (v20 + 68);
        *(_OWORD *)(a1 + 8 * v21) = 0;
        *(_QWORD *)(a1 + 8 * v21 + 16) = 0;
        --*(_BYTE *)(a1 + 1824);
        if ( *(_BYTE *)(a1 + 1844) < 0x40u
          || (unsigned __int8)sub_140848090(a1)
          || (unsigned int)(int)(float)(*(float *)(a1 + 1828) * 1000.0) >= *(_DWORD *)(a1 + 188)
          || (*(_BYTE *)(a1 + 1859) & 4) == 0
          || !*(_BYTE *)(a1 + 180)
          || (unsigned __int8)sub_140848090(a1) >= 0x40u )
        {
          goto LABEL_164;
        }
        sub_140850440(a1, 0);
        result = 1;
        break;
      case 0xBCu:
        sub_140B4A050(*((_DWORD *)a2 + 2), a3);
        return 1;
      case 0xC5u:
        sub_140B4CD90(a3);
        return 1;
      case 0xD2u:
        Client__Network__PacketDispatcher__HandleSpawnTreasurePacket(*((_DWORD *)a2 + 2), a3);
        return 1;
      case 0xDBu:
        Client__Network__PacketDispatcher__HandleSpawnObjectPacket(*((_DWORD *)a2 + 2), a3);
        return 1;
      case 0xDDu:
        sub_140B38670(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0xDEu:
        sub_140B4B980((__int64)a3);
        return 1;
      case 0xE7u:
        sub_140B4DEC0(a3);
        return 1;
      case 0xE9u:
        sub_140B37D50(a3);
        return 1;
      case 0xECu:
        goto LABEL_86;
      case 0xFDu:
        LOBYTE(v6) = 1;
        sub_140B48E60(*((unsigned int *)a2 + 2), a3, v6);
        return 1;
      case 0x100u:
        targetId = *((_QWORD *)a3 + 3);
        goto LABEL_113;
      case 0x10Bu:
        sub_140B49720(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0x112u:
        sub_140B32210(a3);
        return 1;
      case 0x119u:
        sub_140B38570(*((unsigned int *)a2 + 2), a3);
        return 1;
      case 0x128u:
        sub_140B322F0(a3);
        return 1;
      case 0x12Bu:
        sub_140B49A10(*((unsigned int *)a2 + 2));
        return 1;
      case 0x12Fu:
        goto LABEL_151;
      case 0x15Du:
        LOBYTE(v6) = 1;
        sub_140B36990(*((unsigned int *)a2 + 2), a3, v6);
        return 1;
      case 0x160u:
        Client__Network__PacketDispatcher__HandleActorCastPacket(*((_DWORD *)a2 + 2), a3);
        return 1;
      case 0x165u:
        sub_140B4CE60(a3);
        return 1;
      case 0x168u:
        sub_140B323F0(a3);
        return 1;
      default:
        goto LABEL_164;
    }
  }
  return result;
}
