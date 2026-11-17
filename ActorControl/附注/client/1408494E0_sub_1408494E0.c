__int64 __fastcall sub_1408494E0(__int64 a1, __int64 a2, unsigned __int16 *a3)
{
  unsigned int v3; // edi
  unsigned int v6; // r15d
  unsigned int v7; // esi
  char v8; // al
  int v9; // ecx
  char v10; // al
  char v11; // cl
  __int64 v12; // rax
  void *UIModule; // rax
  __int64 result; // rax
  __int64 v15; // rdx
  bool v16; // zf
  unsigned int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  __int64 v20; // r14

  v3 = 0;
  v6 = a2;
  v7 = 1;
  if ( *a3 == 931 )
  {
    v8 = *(_BYTE *)(a1 + 1859);
    v9 = *((_DWORD *)a3 + 1);
    if ( (v8 & 1) != 0 )
    {
      v10 = v8 & 0xFE;
      *(_BYTE *)(a1 + 1859) = v10;
      if ( !v9 || (v11 = *(_BYTE *)(a1 + 1858), (v11 & 4) != 0) )
      {
        sub_140E13730((__int64)byte_142AF9070, 86, 0);
      }
      else
      {
        *(_QWORD *)(a1 + 48) = 0;
        *(_QWORD *)(a1 + 56) = 0;
        *(_BYTE *)(a1 + 1859) = v10 & 0x73 | 4;
        *(_BYTE *)(a1 + 1858) = v11 & 0x7F;
        *(_QWORD *)(a1 + 16) = *(_QWORD *)(a1 + 8);
        *(_QWORD *)(a1 + 1056) = 0;
        *(_QWORD *)(a1 + 1064) = 0;
        *(_DWORD *)(a1 + 1072) = 0;
        *(_QWORD *)(a1 + 64) = 0;
        *(_QWORD *)(a1 + 1104) = contentId;
        *(_DWORD *)(a1 + 1828) = 0;
        *(_DWORD *)(a1 + 1832) = 1065353216;
        *(_DWORD *)(a1 + 1836) = 1065353216;
        *(_BYTE *)(a1 + 1844) = 64;
        *(_QWORD *)(a1 + 1848) = 0;
        *(_WORD *)(a1 + 1856) = 0;
        Client__System__Memory__IMemorySpace__Memset((void *)(a1 + 72), 0, 0x36Cu);
        v12 = sub_140B777C0();
        sub_140B873C0(v12, 55, 1);
        UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( UIModule )
          (*(void (__fastcall **)(void *, _QWORD, _QWORD, __int64, _BYTE, _DWORD))(*(_QWORD *)UIModule + 1192LL))(
            UIModule,
            0,
            0,
            1,
            0,
            0);
        if ( !*(_DWORD *)(a1 + 1076) )
        {
          *(_DWORD *)(a1 + 1076) = 7;
          *(_QWORD *)(a1 + 1080) = 0;
          *(_QWORD *)(a1 + 1088) = 876;
          *(_QWORD *)(a1 + 1096) = 0;
          if ( *(_QWORD *)(a1 + 16) - *(_QWORD *)(a1 + 8) < 0x36Cu )
            sub_1408672B0(a1 + 8, 876);
        }
      }
    }
  }
  else if ( *a3 == 932 )
  {
    sub_14084C600(a1, *((_DWORD *)a3 + 1) != 0);
  }
  result = sub_14084BEA0(a1, *a3);
  if ( (_BYTE)result )
  {
    result = sub_14084B4E0(a1, v6, 169, a3, 40);
    if ( (_BYTE)result )
    {
      switch ( *a3 )
      {
        case 0x64u:
          if ( HIWORD(*((_DWORD *)a3 + 1)) == 32771
            || HIWORD(*((_DWORD *)a3 + 1)) == 32772
            || HIWORD(*((_DWORD *)a3 + 1)) == 32780 )
          {
            *(_DWORD *)(a1 + 1624) = *((_DWORD *)a3 + 1);
          }
          break;
        case 0x6Du:
          v17 = *(_DWORD *)(a1 + 1624);
          if ( v17 && v17 == *((_DWORD *)a3 + 1) )
          {
            v18 = HIWORD(v17) - 32771;
            if ( v18 )
            {
              v19 = v18 - 1;
              if ( (!v19 || v19 == 8) && *((_DWORD *)a3 + 2) == 1073741825 )
                goto LABEL_30;
            }
            else
            {
              if ( *((_DWORD *)a3 + 2) != 1073741825 )
              {
                if ( *((_DWORD *)a3 + 2) == 1073741826 || *((_DWORD *)a3 + 2) == 1073741827 )
                {
                  *(_QWORD *)(a1 + 112) |= 4uLL;
                  return result;
                }
                v16 = *((_DWORD *)a3 + 2) == 1073741830;
                goto LABEL_21;
              }
              *(_BYTE *)(a1 + 1858) |= 0x40u;
              sub_14084FA80(a1);
              result = sub_140C226B0(&qword_142AE2C40);
              if ( (_DWORD)result )
              {
                do
                {
                  if ( v7 >= 8 )
                    break;
                  result = (__int64)sub_140C227A0(&qword_142AE2C40, v3);
                  v20 = result;
                  if ( result )
                  {
                    if ( !*(_BYTE *)(a1 + v7 + 128) )
                    {
                      *(_BYTE *)(a1 + v7 + 128) = sub_140C227E0((__int64)&qword_142AE2C40, v3);
                      *(_BYTE *)(a1 + v7 + 164) = sub_140C22830((__int64)&qword_142AE2C40, v3);
                      result = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v20 + 384LL))(v20);
                      *(_WORD *)(a1 + 2LL * v7 + 148) = result;
                    }
                    ++v7;
                  }
                  ++v3;
                }
                while ( v3 < 7 );
              }
            }
          }
          break;
        case 0x640u:
          *(_QWORD *)(a1 + 112) |= 8uLL;
          return result;
        case 0x642u:
          if ( *((_DWORD *)a3 + 1) != 1073741825 )
          {
            v16 = *((_DWORD *)a3 + 1) == 1073741830;
LABEL_21:
            if ( v16 )
            {
              LOBYTE(v15) = 2;
              return sub_14084F4F0(a1, v15);
            }
            return result;
          }
LABEL_30:
          *(_BYTE *)(a1 + 1858) |= 0x40u;
          return sub_14084FA80(a1);
        default:
          return result;
      }
    }
  }
  return result;
}
