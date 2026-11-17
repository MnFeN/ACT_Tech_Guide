char __fastcall sub_141A2D7F0(
        __int64 a1,
        __int64 a2,
        unsigned int a3,
        int a4,
        unsigned int a5,
        unsigned int a6,
        int a7,
        int a8)
{
  char result; // al
  char v12; // r13
  __int64 v13; // rcx
  __int64 *v14; // rcx
  __int64 *v15; // rdx
  __int64 *v16; // rax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  unsigned int v20; // eax
  __int64 v21; // rcx
  __int64 v22; // rcx
  unsigned int v23; // ecx
  _QWORD *v24; // rax
  _QWORD *j; // rbx
  __int64 **v26; // rax
  __int64 i; // rax
  int v28; // ecx
  int v29; // ecx
  __int64 v30; // rax
  unsigned int v31; // eax
  __int64 v32; // rsi
  int v33; // ecx
  int v34; // ecx
  __int64 v35; // rcx
  __int64 v36; // rcx
  __int64 v37; // rcx
  __int64 v38; // rax
  void *v39; // rax
  __int64 v40; // rax
  __int64 v41; // rax
  int v42; // ecx
  unsigned int v43; // eax
  int v44; // ecx
  __int64 *v45; // rdx
  int v46; // [rsp+78h] [rbp+10h]

  v46 = a2;
  if ( !*(_BYTE *)(a1 + 67018) )
    return 0;
  v12 = 0;
  switch ( (int)a2 )
  {
    case 3570:
      switch ( (char)a4 )
      {
        case 1:
          if ( a3 == *(_DWORD *)(*(_QWORD *)(a1 + 66992) + 33368LL) )
          {
            sub_141A6BBB0();
            goto LABEL_23;
          }
          break;
        case 2:
          v33 = *(_DWORD *)(a1 + 67012);
          if ( (*(_DWORD *)(a1 + 67012) & 2) == 0 )
          {
            *(_DWORD *)(a1 + 67012) = v33 | 2;
            *(_DWORD *)(a1 + 67008) = a5;
          }
          break;
        case 5:
          v34 = *(_DWORD *)(a1 + 67012);
          if ( (*(_DWORD *)(a1 + 67012) & 2) != 0 )
            *(_DWORD *)(a1 + 67012) = v34 & 0xFFFFFFFD;
          break;
        case 11:
          v37 = *(_QWORD *)(a1 + 66992);
          if ( v37 && a3 == *(_DWORD *)(v37 + 33368) )
          {
            sub_141A6C2E0();
            goto LABEL_23;
          }
          break;
        case 12:
          v36 = *(_QWORD *)(a1 + 66992);
          if ( v36 && a3 == *(_DWORD *)(v36 + 33368) )
          {
            sub_141A6BB50();
            goto LABEL_23;
          }
          break;
        case 13:
          v35 = *(_QWORD *)(a1 + 66992);
          if ( v35 && a3 == *(_DWORD *)(v35 + 33368) )
          {
            sub_141A6C360();
            goto LABEL_23;
          }
          break;
        default:
          goto LABEL_24;
      }
      goto LABEL_24;
    case 3571:
      v13 = *(_QWORD *)(a1 + 66992);
      if ( !v13 )
        return 0;
      LOBYTE(a2) = a4 == 1;
      sub_141A6B680(v13, a2, a5, a6);
      return 1;
    case 3573:
      v17 = *(_DWORD *)(a1 + 67012);
      if ( (v17 & 4) == 0 )
        goto LABEL_24;
      v18 = v17;
      v19 = v17 | 8;
      v20 = v18 & 0xFFFFFFF7;
      if ( a4 != 1 )
        v19 = v20;
      *(_DWORD *)(a1 + 67012) = v19;
      if ( a4 )
        goto LABEL_24;
      v21 = *(_QWORD *)(a1 + 66992);
      *(_BYTE *)(a1 + 16) = 1;
      if ( !v21 )
        goto LABEL_24;
      v22 = *(_QWORD *)(v21 + 33352);
      if ( !v22 )
        goto LABEL_24;
      (*(void (__fastcall **)(__int64))(*(_QWORD *)v22 + 64LL))(v22);
      goto LABEL_23;
    case 3574:
      v28 = *(_DWORD *)(a1 + 67012);
      if ( (v28 & 0x14) != 4 )
        goto LABEL_24;
      v29 = v28 | 0x10;
      *(_DWORD *)(a1 + 67012) = v29;
      if ( (v29 & 0x40) != 0 )
        goto LABEL_24;
      v30 = *(_QWORD *)(a1 + 66992);
      if ( !v30 )
        goto LABEL_24;
      sub_141A30B60(a1, 10841, *(unsigned int *)(v30 + 33368));
      v31 = sub_140ED12C0(1022);
      v32 = *(_QWORD *)(a1 + 66992);
      if ( *(_DWORD *)(v32 + 33376) - (unsigned int)Client__System__Framework__Framework__GetServerTime() > v31 )
        sub_141A30B60(a1, 10842, *(unsigned int *)(v32 + 33368));
      *(_DWORD *)(a1 + 67012) |= 0x40u;
LABEL_23:
      LODWORD(a2) = v46;
      goto LABEL_24;
    case 3577:
      switch ( a4 )
      {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
          switch ( (char)a4 )
          {
            case 1:
            case 5:
              v38 = *(_QWORD *)(a1 + 66992);
              v23 = a6;
              if ( v38 )
              {
                *(_DWORD *)(v38 + 33372) |= 0x80u;
                *(_DWORD *)(*(_QWORD *)(a1 + 66992) + 33384LL) = a5;
                *(_DWORD *)(*(_QWORD *)(a1 + 66992) + 33388LL) = a6;
              }
              break;
            case 2:
            case 6:
            case 7:
              if ( (_BYTE)a4 != 6 )
              {
                v39 = (void *)sub_140ECDB40();
                if ( Client__Game__WKS__WKSManager__IsFunctionUnlocked(v39, 8u) )
                {
                  if ( (*(_BYTE *)(sub_140ECDB40() + 3784) & 0x40) != 0 )
                    sub_141A30B60(a1, 10830, 0);
                }
              }
              v40 = *(_QWORD *)(a1 + 66992);
              LODWORD(a2) = v46;
              v23 = a6;
              if ( v40 )
                *(_DWORD *)(v40 + 33372) |= 0x100u;
              break;
            case 3:
            case 8:
              v41 = *(_QWORD *)(a1 + 66992);
              v23 = a6;
              if ( v41 )
              {
                *(_DWORD *)(v41 + 33372) |= 0x200u;
                *(_DWORD *)(*(_QWORD *)(a1 + 66992) + 33392LL) = a5;
              }
              break;
            default:
              goto LABEL_23;
          }
          break;
        default:
          goto LABEL_24;
      }
      goto LABEL_25;
    case 3578:
      if ( a4 == 1 )
      {
        *(_BYTE *)(a1 + 67017) = a5 == 1;
      }
      else if ( a4 == 2 )
      {
        *(_BYTE *)(a1 + 67016) = a5;
      }
      goto LABEL_24;
    case 3579:
      v14 = *(__int64 **)(a1 + 24);
      v15 = v14;
      v16 = (__int64 *)v14[1];
      while ( !*((_BYTE *)v16 + 25) )
      {
        if ( *((_DWORD *)v16 + 8) >= a3 )
        {
          v14 = v16;
          v16 = (__int64 *)*v16;
        }
        else
        {
          v16 = (__int64 *)v16[2];
        }
      }
      if ( *((_BYTE *)v14 + 25) || a3 < *((_DWORD *)v14 + 8) || v14 == v15 )
        return 0;
      sub_141A6B7D0(v14[5], a4 == 1);
      return 1;
    case 3582:
      v42 = *(_DWORD *)(a1 + 67012);
      v43 = v42 & 0xFFFDFFFF;
      v44 = v42 | 0x20000;
      if ( !a3 )
        v44 = v43;
      *(_DWORD *)(a1 + 67012) = v44;
      goto LABEL_24;
    default:
LABEL_24:
      v23 = a6;
LABEL_25:
      v24 = *(_QWORD **)(a1 + 24);
      j = (_QWORD *)*v24;
      if ( (_QWORD *)*v24 != v24 )
      {
        do
        {
          v12 |= sub_141A6ACC0(j[5], a2, a3, a4, a5, v23, a7, a8);
          v26 = (__int64 **)j[2];
          if ( *((_BYTE *)v26 + 25) )
          {
            for ( i = j[1]; !*(_BYTE *)(i + 25); i = *(_QWORD *)(i + 8) )
            {
              if ( j != *(_QWORD **)(i + 16) )
                break;
              j = (_QWORD *)i;
            }
            j = (_QWORD *)i;
          }
          else
          {
            v45 = *v26;
            for ( j = (_QWORD *)j[2]; !*((_BYTE *)v45 + 25); v45 = (__int64 *)*v45 )
              j = v45;
          }
          LODWORD(a2) = v46;
          v23 = a6;
        }
        while ( j != *(_QWORD **)(a1 + 24) );
      }
      result = v12;
      break;
  }
  return result;
}
