void __fastcall sub_1403A2020(__int64 a1, int a2, int a3, _BYTE *a4, unsigned int a5)
{
  unsigned int i; // r12d
  unsigned int *v10; // rsi
  _BYTE *v11; // rdi
  unsigned int v12; // eax
  int v13; // ecx
  unsigned int v14; // eax
  unsigned int v15; // eax
  int v16; // ecx
  char v17; // cl
  char v18; // al
  unsigned int v19; // eax
  unsigned int v20; // eax
  unsigned int v21; // eax
  unsigned int v22; // eax
  unsigned int v23; // eax
  __int64 v24; // rax

  for ( i = 0; i < a5; a4 = &v11[v24] )
  {
    v10 = (unsigned int *)a4;
    v11 = a4 + 8;
    v12 = *v10;
    if ( *v10 > 0x436F6C45 )
    {
      if ( v12 <= 0x57644252 )
      {
        if ( v12 == 1466188370 )
        {
          v13 = a1 + 64;
        }
        else if ( v12 > 0x506E4473 )
        {
          if ( v12 == 1349403972 )
          {
            *(_BYTE *)(a1 + 4) = *v11;
            goto LABEL_82;
          }
          if ( v12 != 1399223378 )
          {
            if ( v12 == 1415669582 )
              *(_DWORD *)(a1 + 856) = *(_DWORD *)v11;
            goto LABEL_82;
          }
          v13 = a1 + 160;
        }
        else if ( v12 == 1349403763 )
        {
          v13 = a1 + 176;
        }
        else
        {
          if ( v12 != 1281715794 )
          {
            switch ( v12 )
            {
              case 0x4C6E4354u:
                *(_BYTE *)a1 ^= (*(_BYTE *)a1 ^ *v11) & 0xF;
                break;
              case 0x4E424241u:
                *(_BYTE *)a1 = *(_BYTE *)a1 & 0xF | (16 * *v11);
                break;
              case 0x506E4343u:
                *(_BYTE *)(a1 + 3) = *v11;
                break;
            }
            goto LABEL_82;
          }
          v13 = a1 + 136;
        }
        goto LABEL_16;
      }
      if ( v12 > 0x62456467 )
      {
        switch ( v12 )
        {
          case 0x624C636Cu:
            v17 = *v11 != 0 ? 0x10 : 0;
            v18 = *(_BYTE *)(a1 + 5) & 0xEF;
            goto LABEL_81;
          case 0x624E7442u:
            v17 = *v11 != 0 ? 2 : 0;
            v18 = *(_BYTE *)(a1 + 5) & 0xFD;
            goto LABEL_81;
          case 0x6253706Cu:
            v17 = *v11 != 0 ? 8 : 0;
            v18 = *(_BYTE *)(a1 + 5) & 0xF7;
            goto LABEL_81;
        }
      }
      else
      {
        if ( v12 == 1648714855 )
        {
          v17 = *v11 != 0;
          v18 = *(_BYTE *)(a1 + 5) & 0xFE;
          goto LABEL_81;
        }
        v21 = v12 - 1466188626;
        if ( !v21 )
        {
          v13 = a1 + 88;
          goto LABEL_16;
        }
        v22 = v21 - 512;
        if ( !v22 )
        {
          v13 = a1 + 112;
          goto LABEL_16;
        }
        v23 = v22 - 182398741;
        if ( !v23 )
        {
          v17 = *v11 != 0 ? 0x20 : 0;
          v18 = *(_BYTE *)(a1 + 5) & 0xDF;
          goto LABEL_81;
        }
        if ( v23 == 11 )
        {
          v17 = *v11 != 0 ? 0x40 : 0;
          v18 = *(_BYTE *)(a1 + 5) & 0xBF;
          goto LABEL_81;
        }
      }
    }
    else
    {
      if ( v12 == 1131375685 )
      {
        v16 = a1 + 408;
        goto LABEL_41;
      }
      if ( v12 > 0x576445 )
      {
        if ( v12 > 0x436F4543 )
        {
          v19 = v12 - 1131365701;
          if ( !v19 )
          {
            v16 = a1 + 744;
            goto LABEL_41;
          }
          v20 = v19 - 9981;
          if ( !v20 )
          {
            v16 = a1 + 184;
            goto LABEL_41;
          }
          if ( v20 == 1 )
          {
            v16 = a1 + 296;
            goto LABEL_41;
          }
        }
        else
        {
          switch ( v12 )
          {
            case 0x436F4543u:
              v16 = a1 + 632;
              goto LABEL_41;
            case 0x576452u:
              v13 = a1 + 40;
              goto LABEL_16;
            case 0x42577054u:
              *(_BYTE *)(a1 + 1) = *v11;
              break;
            case 0x42645770u:
              v17 = *v11 != 0 ? 4 : 0;
              v18 = *(_BYTE *)(a1 + 5) & 0xFB;
LABEL_81:
              *(_BYTE *)(a1 + 5) = v18 | v17;
              break;
            case 0x436F4542u:
              v16 = a1 + 520;
LABEL_41:
              sub_14039CAE0(v16, a2, a3, (_DWORD)v11, v10[1]);
              break;
          }
        }
      }
      else
      {
        if ( v12 == 5727301 )
        {
          v13 = a1 + 104;
          goto LABEL_16;
        }
        if ( v12 > 0x506E43 )
        {
          v14 = v12 - 5465716;
          if ( v14 )
          {
            v15 = v14 - 261582;
            if ( v15 )
            {
              if ( v15 != 1 )
                goto LABEL_82;
              v13 = a1 + 80;
            }
            else
            {
              v13 = a1 + 56;
            }
          }
          else
          {
            v13 = a1 + 152;
          }
          goto LABEL_16;
        }
        switch ( v12 )
        {
          case 0x506E43u:
            *(_BYTE *)(a1 + 2) = *v11;
            break;
          case 0x4346u:
            v13 = a1 + 8;
            goto LABEL_16;
          case 0x5764u:
            v13 = a1 + 32;
            goto LABEL_16;
          case 0x434652u:
            v13 = a1 + 16;
            goto LABEL_16;
          case 0x4C656Eu:
            v13 = a1 + 128;
LABEL_16:
            sub_1403971D0(v13, a2, a3, (_DWORD)v11, v10[1]);
            break;
        }
      }
    }
LABEL_82:
    v24 = (v10[1] + 3) & 0xFFFFFFFC;
    i += v24 + 8;
  }
}
