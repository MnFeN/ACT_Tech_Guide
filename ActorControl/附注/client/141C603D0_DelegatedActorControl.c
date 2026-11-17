__int64 __fastcall sub_141C603D0(__int64 a1, int a2, unsigned int a3, unsigned int a4, unsigned int a5, int a6)
{
  unsigned __int8 v6; // bl
  int v10; // edx
  int v11; // edx
  int v12; // edx
  unsigned int *v13; // rax
  unsigned int *v14; // rdi
  unsigned int *v15; // r14
  __int64 v16; // rax
  __int64 v17; // rdx
  __int64 v18; // r10
  __int16 v19; // si
  unsigned int v20; // ebp
  __int64 v21; // rcx
  __int64 v22; // rdx
  __int64 v23; // rbx
  int v24; // eax
  signed int v25; // edx
  int v26; // eax
  __int64 v27; // rax
  __int64 v28; // r14
  __int64 v29; // rdx

  v6 = 0;
  v10 = a2 - 3800;
  if ( !v10 )
  {
    if ( sub_14198E450() == -80 )
      return v6;
    if ( sub_141C62020(a1, a3, 0) )
    {
      sub_141C61CF0(a1, 11321, 0);
      v29 = sub_14198E450();
      if ( (*(_DWORD *)(v29 + 41728) & 0x200000) == 0 )
        *(_DWORD *)(v29 + 41728) |= 0x200000u;
    }
    return 1;
  }
  v11 = v10 - 2;
  if ( !v11 )
  {
    if ( (*(_DWORD *)(sub_14198E450() + 41728) & 0x200000) != 0 || !sub_141C62020(a1, a3, 1u) )
      return v6;
    return 1;
  }
  v12 = v11 - 8;
  if ( !v12 )
  {
    v17 = *(_QWORD *)(a1 + 24);
    v18 = *(_QWORD *)(a1 + 16);
    if ( ((v17 - v18) & 0xFFFFFFFFFFFFFFF8uLL) != 0 )
    {
      v19 = 0;
      if ( a4 == 1 )
      {
        v20 = *(_DWORD *)(a1 + 41492);
        goto LABEL_14;
      }
      v20 = a5;
      if ( a5 )
      {
        sub_141C630F0(v18, v17, (v17 - v18) >> 3, sub_141C62CC0);
        v17 = *(_QWORD *)(a1 + 24);
LABEL_14:
        v21 = *(_QWORD *)(a1 + 16);
        if ( (v17 - v21) >> 3 )
        {
          v22 = 0;
          do
          {
            v23 = *(_QWORD *)(v21 + 8 * v22);
            v24 = *(_DWORD *)(v23 + 4);
            if ( v24 && *(_DWORD *)v23 )
            {
              v25 = *(_DWORD *)(v23 + 160);
              if ( v25 >= 0 )
              {
                if ( a4 == 1 || v24 == a3 && ((v26 = *(_DWORD *)(v23 + 76)) == 0 || v26 == a6) )
                {
                  *(_BYTE *)(v23 + 168) = 1;
                  *(_DWORD *)(v23 + 164) = 1;
                  *(_BYTE *)(v23 + 170) = 1;
                  v27 = sub_14198A250((__int64)&qword_142B0E1C0, v25);
                  v28 = v27;
                  if ( v27 )
                  {
                    (*(void (__fastcall **)(__int64, _QWORD, _QWORD))(*(_QWORD *)v27 + 160LL))(
                      v27,
                      *(unsigned int *)(v23 + 164),
                      0);
                    sub_141C42A30(v28, 30);
                    *(_BYTE *)(v23 + 171) = 1;
                    if ( !--v20 )
                      return 1;
                  }
                }
              }
              else if ( *(_BYTE *)(v23 + 172) )
              {
                *(_BYTE *)(v23 + 172) = 0;
                *(_BYTE *)(v23 + 168) = 1;
              }
            }
            v21 = *(_QWORD *)(a1 + 16);
            v22 = ++v19;
          }
          while ( v19 < (unsigned __int64)((*(_QWORD *)(a1 + 24) - v21) >> 3) );
        }
      }
    }
    return 1;
  }
  if ( v12 == 1 && *(int *)(a1 + 41492) > 0 )
  {
    v13 = (unsigned int *)EXD__ReactionEventObject__RowAndSubRowId_1408417D0(a4, 0);
    v14 = v13;
    if ( v13 )
    {
      v15 = (unsigned int *)EXD__ReactionEventObjectInfo__RowAndSubRowId_140841820(*v13, 0);
      if ( v15 )
      {
        v16 = sub_140B777C0();
        sub_140B7E440(v16, v14[1], *v15, a5, 0, 0, 0);
      }
    }
  }
  return v6;
}
