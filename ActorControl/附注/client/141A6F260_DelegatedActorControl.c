char __fastcall sub_141A6F260(__int64 a1, int a2, __int16 a3, unsigned __int16 a4, int a5, unsigned __int8 a6)
{
  __int64 v9; // rax
  __int64 v10; // rdx
  __int64 v11; // rcx
  __int64 v12; // rax
  __int64 v13; // rdx
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  int v18; // edx
  _BYTE *i; // rax
  __int64 v20; // rax
  _QWORD *v21; // r8
  __int64 v22; // rax
  __int64 v23; // rdx
  __int64 v24; // rdx
  __int64 v25; // rdx
  __int64 v26; // rax
  unsigned int v27; // r8d
  __int64 v28; // r9
  unsigned int v29; // eax
  __int64 v30; // rcx
  __int64 v31; // rdi
  __int64 v32; // rax
  unsigned int v33; // r8d
  __int64 v34; // r9
  unsigned int v35; // eax
  __int64 v36; // rcx
  __int64 v37; // rdx
  __int64 v38; // rax

  switch ( a2 )
  {
    case 3541:
      v9 = sub_140ECDB40();
      if ( !v9 )
        return 1;
      v10 = v9 + 104;
      if ( v9 == -104 )
        return 1;
      v11 = 328LL * (unsigned __int8)a3;
      v12 = *(_QWORD *)(v11 + v10 + 216);
      v13 = *(_QWORD *)(v11 + v10 + 224);
      if ( v12 == v13 )
        return 1;
      while ( *(_WORD *)v12 != a4 )
      {
        v12 += 12;
        if ( v12 == v13 )
          return 1;
      }
      *(_BYTE *)(v12 + 10) = a5 != 0;
      return 1;
    case 3630:
      v15 = sub_140ECDB40();
      if ( !v15 )
        return 1;
      *(_WORD *)(v15 + 3778) = a3;
      return 1;
    case 3631:
      v16 = sub_140ECDB40();
      if ( !v16 || a4 >= 0xD5u )
        return 1;
      if ( a5 )
        *(_BYTE *)(a4 + v16 + 4006) = a3;
      else
        *(_BYTE *)(a4 + v16 + 3793) = a3;
      if ( *(_BYTE *)(a1 + 8) )
        return 1;
      v17 = sub_140ECDB40();
      if ( !v17 )
        return 1;
      v18 = 0;
      for ( i = (_BYTE *)(v17 + 3793); !*i; ++i )
      {
        if ( (unsigned int)++v18 >= 0xD5 )
          return 1;
      }
      *(_BYTE *)(a1 + 8) = 1;
      return 1;
    case 3638:
      v20 = sub_140ECDB40();
      if ( !v20 || v20 == -104 )
        return 1;
      v21 = (_QWORD *)(v20 + 104 + 328LL * (unsigned __int8)a3);
      v22 = v21[27];
      v23 = v21[28];
      if ( v22 != v23 )
      {
        while ( *(_WORD *)v22 != a4 )
        {
          v22 += 12;
          if ( v22 == v23 )
            goto LABEL_28;
        }
        goto LABEL_42;
      }
LABEL_28:
      v22 = v21[24];
      v24 = v21[25];
      if ( v22 != v24 )
      {
        while ( *(_WORD *)v22 != a4 )
        {
          v22 += 12;
          if ( v22 == v24 )
            goto LABEL_31;
        }
        goto LABEL_42;
      }
LABEL_31:
      v22 = v21[30];
      v25 = v21[31];
      if ( v22 != v25 )
      {
        while ( *(_WORD *)v22 != a4 )
        {
          v22 += 12;
          if ( v22 == v25 )
            goto LABEL_34;
        }
LABEL_42:
        *(_DWORD *)(v22 + 4) = a5;
        return 1;
      }
LABEL_34:
      v26 = sub_140ECDB40();
      if ( !v26 || v26 == -104 )
        return 1;
      v27 = 0;
      v28 = v26 + 376;
      while ( 2 )
      {
        v29 = 0;
        v30 = v28;
        do
        {
          if ( *(_WORD *)v30 == a4 )
          {
            *(_DWORD *)(v30 + 4) = a5;
            return 1;
          }
          ++v29;
          v30 += 16;
        }
        while ( v29 < 3 );
        ++v27;
        v28 += 328;
        if ( v27 < 0xB )
          continue;
        break;
      }
      return 1;
    case 3660:
      v31 = sub_140ECDB40();
      if ( !v31 )
        return 1;
      v32 = sub_140ECDB40();
      if ( v32 && v32 != -104 )
      {
        v33 = 0;
        v34 = v32 + 376;
        while ( 2 )
        {
          v35 = 0;
          v36 = v34;
          do
          {
            if ( *(_WORD *)v36 == a4 )
            {
              *(_DWORD *)(v36 + 12) = a5;
              return 1;
            }
            ++v35;
            v36 += 16;
          }
          while ( v35 < 3 );
          ++v33;
          v34 += 328;
          if ( v33 < 0xB )
            continue;
          break;
        }
      }
      if ( v31 == -104 )
        return 1;
      v37 = v31 + 104 + 16 * (a6 + 17LL) + 328LL * (unsigned __int8)a3;
      *(_DWORD *)(v37 + 12) = a5;
      *(_WORD *)v37 = a4;
      return 1;
    case 3661:
      v38 = sub_140ECDB40();
      if ( v38 && v38 != -104 )
        *(_WORD *)(328LL * (unsigned __int8)a3 + v38 + 104 + 320) = a4;
      return 1;
    default:
      return 0;
  }
}
