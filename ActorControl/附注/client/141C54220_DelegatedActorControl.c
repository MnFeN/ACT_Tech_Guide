bool __fastcall sub_141C54220(
        void *a1,
        unsigned int a2,
        unsigned int a3,
        unsigned int a4,
        unsigned int a5,
        unsigned int a6,
        unsigned int a7)
{
  unsigned int *v10; // rax
  unsigned int *v11; // rbx
  unsigned int *v12; // rsi
  __int64 v13; // rax
  __int64 v14; // r10
  __int64 v15; // rsi
  __int16 v16; // si
  char v17; // r14
  unsigned int v19; // ebp
  unsigned int v20; // r15d
  __int64 v21; // rdi
  int v22; // eax
  int v23; // edx
  __int64 v24; // rax
  unsigned int v25; // edi
  __int64 v26; // rax
  __int64 v27; // rdx
  __int64 v28; // r8
  unsigned int **v29; // rsi
  unsigned int v30; // ebp
  unsigned int v31; // ebp
  unsigned int v32; // ebp
  unsigned int v33; // ebp
  float v34; // xmm7_4
  __int64 v35; // rcx
  __int64 v36; // rdi
  __int64 v37; // rax
  float v38; // xmm6_4
  void *v39; // rax
  int Object; // eax
  __int64 v41; // rax
  _BYTE *v42; // rcx
  _BYTE *v43; // rcx
  char v44; // al
  __int64 *v45; // r8
  __int64 *v46; // rcx
  __int64 *v47; // rax
  __int64 v48; // rax
  unsigned int *v49; // rdi
  __int64 v50; // rsi
  unsigned int v51; // edx
  __int64 *v52; // rcx
  __int64 *v53; // r8
  __int64 *v54; // rax
  _BYTE *v55; // rax
  char *v56; // rsi
  bool v57; // al
  _QWORD *v58; // rcx
  _QWORD *j; // rbx
  __int64 v60; // rdi
  __int64 v61; // rax
  __int64 v62; // rdx
  __int64 **v63; // rax
  __int64 i; // rax
  __int64 *v65; // rcx
  _BYTE v66[16]; // [rsp+40h] [rbp-48h] BYREF
  float v67; // [rsp+98h] [rbp+10h] BYREF

  switch ( a2 )
  {
    case 0xDF7u:
      v25 = a5;
      v26 = sub_141C57090(a1, a5);
      v29 = (unsigned int **)v26;
      if ( !v26 )
        return 0;
      v30 = a4 - 1;
      if ( v30 )
      {
        v31 = v30 - 1;
        if ( v31 )
        {
          v32 = v31 - 3;
          if ( v32 )
          {
            v33 = v32 - 1;
            if ( v33 )
            {
              if ( v33 != 1 )
                return 0;
              v34 = (float)(int)a7 / 1000.0;
              if ( !*(_QWORD *)(v26 + 8) )
                return 1;
              v35 = *(_QWORD *)v26;
              if ( !*(_QWORD *)v26 || !*(_QWORD *)(v35 + 264) || *((_BYTE *)a1 + 6744) >= 0xAu )
                return 1;
              LOBYTE(v36) = 0;
              while ( *((_DWORD *)a1 + (unsigned __int8)v36 + 1666) != -1 )
              {
                LOBYTE(v36) = v36 + 1;
                if ( (unsigned __int8)v36 >= 0xAu )
                  return 1;
              }
              v67 = 0.0;
              v37 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(v35 + 264) + 528LL))(*(_QWORD *)(v35 + 264));
              sub_140796B00(&v67, v37);
              v38 = v67;
              v39 = (void *)(*(__int64 (__fastcall **)(_QWORD))(**((_QWORD **)*v29 + 33) + 512LL))(*((_QWORD *)*v29 + 33));
              Object = Client__Game__Object__ReactionEventObjectManager__CreateObject(
                         &qword_142B0E1C0,
                         a6,
                         *v29[1],
                         v39,
                         v38);
              if ( Object == -1 )
                return 1;
              v36 = (char)v36;
              *((_DWORD *)a1 + (char)v36 + 1666) = Object;
              ++*((_BYTE *)a1 + 6744);
              v41 = sub_14198A250(&qword_142B0E1C0);
              if ( !v41 )
                return 1;
              sub_141C42E90(v41, 1, 0, 0);
              *((float *)a1 + v36 + 1676) = v34;
              return 1;
            }
            else
            {
              v42 = (char *)a1 + 6464;
              if ( a6 == 1 )
              {
                sub_141C5B170(v42, v26, 1);
                *((_BYTE *)a1 + 6649) = 1;
              }
              else
              {
                sub_141C5B270((__int64)v42, v26, 1);
                *((_BYTE *)a1 + 6649) = 0;
                *((_QWORD *)a1 + 832) = 0;
              }
              return 1;
            }
          }
          else
          {
            v43 = (char *)a1 + 6272;
            if ( a6 == 1 )
            {
              sub_141C5B170(v43, v26, 1);
              *((_BYTE *)a1 + 6457) = 1;
            }
            else
            {
              sub_141C5B270((__int64)v43, v26, 1);
              *((_BYTE *)a1 + 6457) = 0;
            }
            return 1;
          }
        }
        else
        {
          LOBYTE(v27) = a6 == 1;
          sub_141C52060(v26, v27, v28);
          return 1;
        }
      }
      else
      {
        v44 = *(_BYTE *)(v26 + 34);
        if ( a6 != 0xFFFF )
        {
          if ( v44 && *v29 )
            (*v29)[109] = a6;
          return 1;
        }
        if ( v44 && *v29 )
          sub_140898020((__int64)*v29, 0);
        if ( *((_DWORD *)v29 + 7) == 4 )
        {
          v45 = (__int64 *)*((_QWORD *)a1 + 8);
          v46 = v45;
          v47 = (__int64 *)v45[1];
          while ( !*((_BYTE *)v47 + 25) )
          {
            if ( *((_DWORD *)v47 + 8) >= v25 )
            {
              v45 = v47;
              v47 = (__int64 *)*v47;
            }
            else
            {
              v47 = (__int64 *)v47[2];
            }
          }
          if ( *((_BYTE *)v45 + 25) || v25 < *((_DWORD *)v45 + 8) || v45 == v46 )
            return 1;
          v48 = v45[5];
          *(_QWORD *)v48 = 0;
          *(_QWORD *)(v48 + 8) = 0;
          *(_QWORD *)(v48 + 24) = 0;
          *(_WORD *)(v48 + 33) = 0;
          *(_QWORD *)(v48 + 16) = 0;
          *(_BYTE *)(v48 + 32) = 0;
          sub_141C5C250((char *)a1 + 64, v66);
          return 1;
        }
        else
        {
          *((_DWORD *)v29 + 7) = 5;
          return 1;
        }
      }
    case 0xDF8u:
      if ( a3 != *(_DWORD *)(*((_QWORD *)a1 + 3) + 33368LL) )
        return 0;
      v14 = *((_QWORD *)a1 + 862);
      v15 = (*((_QWORD *)a1 + 863) - v14) >> 3;
      if ( v15 )
      {
        v16 = v15 - 1;
        v17 = a4;
        if ( (unsigned __int8)a4 == 3 )
        {
          v19 = a6;
          if ( !a6 )
            return 1;
          sub_141C5BD30(v14, *((_QWORD *)a1 + 863), (*((_QWORD *)a1 + 863) - v14) >> 3, sub_141C5B750);
        }
        else
        {
          if ( (unsigned __int8)a4 != 4 )
            return 0;
          v19 = *((_DWORD *)a1 + 6286);
        }
        if ( v16 >= 0 )
        {
          v20 = a5;
          while ( 1 )
          {
            v21 = *(_QWORD *)(*((_QWORD *)a1 + 862) + 8LL * v16);
            v22 = *(_DWORD *)(v21 + 4);
            if ( v22 )
            {
              if ( *(_DWORD *)v21 )
              {
                if ( v22 != v20 && v17 != 4 )
                  goto LABEL_24;
                v23 = *(_DWORD *)(v21 + 72);
                *(_BYTE *)(v21 + 204) = 1;
                if ( v23 < 0 )
                  goto LABEL_23;
                v24 = sub_14198A250(&qword_142B0E1C0);
                if ( v24 )
                  break;
              }
            }
LABEL_25:
            if ( --v16 < 0 )
              return 1;
          }
          sub_141C42A30(v24, 30);
          *(_BYTE *)(v21 + 206) = 1;
LABEL_23:
          --v19;
LABEL_24:
          if ( !v19 )
            return 1;
          goto LABEL_25;
        }
        return 1;
      }
      return 1;
    case 0xE00u:
      if ( a3 == *(_DWORD *)(*((_QWORD *)a1 + 3) + 33368LL) )
      {
        v10 = (unsigned int *)EXD__ReactionEventObject__RowAndSubRowId_1408417D0(a4, 0);
        v11 = v10;
        if ( v10 )
        {
          v12 = (unsigned int *)EXD__ReactionEventObjectInfo__RowAndSubRowId_140841820(*v10, 0);
          if ( v12 )
          {
            v13 = sub_140B777C0();
            sub_140B7E440(v13, v11[1], *v12, a3, a5, 0, 0);
          }
        }
      }
      return 0;
    case 0xE02u:
      v49 = (unsigned int *)((char *)a1 + 6288);
      v50 = 3;
      do
      {
        v51 = *v49;
        if ( *v49 )
        {
          v52 = *(__int64 **)(*((_QWORD *)a1 + 785) + 64LL);
          v53 = v52;
          v54 = (__int64 *)v52[1];
          while ( !*((_BYTE *)v54 + 25) )
          {
            if ( *((_DWORD *)v54 + 8) >= v51 )
            {
              v52 = v54;
              v54 = (__int64 *)*v54;
            }
            else
            {
              v54 = (__int64 *)v54[2];
            }
          }
          if ( !*((_BYTE *)v52 + 25) && v51 >= *((_DWORD *)v52 + 8) && v52 != v53 )
          {
            v55 = (_BYTE *)v52[5];
            if ( v55[34] )
            {
              if ( v55 && *(_QWORD *)v55 )
                (*(void (__fastcall **)(_QWORD, _QWORD, _QWORD))(**(_QWORD **)v55 + 160LL))(*(_QWORD *)v55, a4, 0);
            }
          }
        }
        v49 += 14;
        --v50;
      }
      while ( v50 );
      return 0;
    case 0xE03u:
      sub_141C590D0((__int64)a1, a4, a5 == 1);
      return 1;
    case 0xE04u:
      v56 = (char *)a1 + 6272;
      v57 = sub_141C54D70();
      *((_BYTE *)a1 + 6458) = a4 != 0;
      if ( v57 )
      {
        v58 = *(_QWORD **)(*((_QWORD *)a1 + 785) + 64LL);
        j = (_QWORD *)*v58;
        if ( (_QWORD *)*v58 != v58 )
        {
          do
          {
            v60 = j[5];
            if ( v60 )
            {
              v61 = *(_QWORD *)(v60 + 8);
              if ( v61 )
              {
                if ( *(_BYTE *)(v61 + 16) == 7 )
                {
                  v62 = j[5];
                  if ( a4 )
                  {
                    sub_141C5B170(v56, v62, 0);
                    if ( v56[185] )
                      sub_141C5B170(v56, v60, 1);
                  }
                  else
                  {
                    sub_141C5B270((__int64)v56, v62, 0);
                    sub_141C5B270((__int64)v56, v60, 1);
                  }
                }
              }
            }
            v63 = (__int64 **)j[2];
            if ( *((_BYTE *)v63 + 25) )
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
              v65 = *v63;
              for ( j = (_QWORD *)j[2]; !*((_BYTE *)v65 + 25); v65 = (__int64 *)*v65 )
                j = v65;
            }
          }
          while ( j != *(_QWORD **)(*((_QWORD *)v56 + 1) + 64LL) );
        }
      }
      return 0;
    case 0xE05u:
      if ( a3 == *(_DWORD *)(*((_QWORD *)a1 + 3) + 33368LL) )
        *((_BYTE *)a1 + 25149) = 1;
      return 0;
    default:
      return 0;
  }
}
