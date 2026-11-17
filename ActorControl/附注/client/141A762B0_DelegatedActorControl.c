__int64 __fastcall sub_141A762B0(
        __int64 a1,
        int a2,
        int a3,
        unsigned int a4,
        unsigned int a5,
        unsigned int a6,
        unsigned int a7,
        int a8)
{
  unsigned __int8 v11; // r15
  int v12; // edx
  int v13; // edx
  __int64 v14; // rdi
  __int128 *v15; // rbx
  __int64 v16; // rax
  __int64 v17; // rbp
  __int64 v18; // rcx
  char v19; // bl
  __int64 v20; // rax
  unsigned __int8 v21; // bl
  _BYTE *v22; // rax
  __int128 v23; // xmm0
  __int128 v25; // [rsp+40h] [rbp-68h] BYREF
  int v26; // [rsp+50h] [rbp-58h]

  v11 = 1;
  v12 = a2 - 3560;
  if ( v12 )
  {
    v13 = v12 - 1;
    if ( v13 )
    {
      if ( v13 == 1 )
      {
        sub_141A76720(a1, a4, (unsigned __int16)a3, a5, a6);
        sub_140149480(a3);
      }
      else
      {
        return 0;
      }
    }
    else
    {
      sub_140149350(a3);
      v14 = 5;
      *((_QWORD *)&v25 + 1) = __PAIR64__(a7, a6);
      *(_QWORD *)&v25 = __PAIR64__(a5, a4);
      v15 = &v25;
      v26 = a8;
      do
      {
        if ( *(_DWORD *)v15 )
          sub_1401493A0(*(_DWORD *)v15);
        v15 = (__int128 *)((char *)v15 + 4);
        --v14;
      }
      while ( v14 );
    }
  }
  else if ( sub_140ECDB40() )
  {
    v16 = sub_140ECDB40();
    v17 = *(_QWORD *)(a1 + 8);
    DWORD2(v25) = 0;
    v18 = v17;
    v19 = *(_BYTE *)(v16 + 101);
    v20 = *(_QWORD *)(v17 + 8);
    v21 = v19 & 3;
    *(_QWORD *)&v25 = v20;
    while ( !*(_BYTE *)(v20 + 25) )
    {
      *(_QWORD *)&v25 = v20;
      if ( *(_BYTE *)(v20 + 28) >= v21 )
      {
        v18 = v20;
        DWORD2(v25) = 1;
        v20 = *(_QWORD *)v20;
      }
      else
      {
        v20 = *(_QWORD *)(v20 + 16);
        DWORD2(v25) = 0;
      }
    }
    if ( *(_BYTE *)(v18 + 25) || v21 < *(_BYTE *)(v18 + 28) )
    {
      if ( *(_QWORD *)(a1 + 16) == 0xFFFFFFFFLL )
        unknown_libname_25();
      v22 = Client__System__Memory__MemoryPool__Alloc(0x28u);
      v23 = v25;
      v22[28] = v21;
      *((_DWORD *)v22 + 8) = 0;
      *(_QWORD *)v22 = v17;
      *((_QWORD *)v22 + 1) = v17;
      *((_QWORD *)v22 + 2) = v17;
      *((_WORD *)v22 + 12) = 0;
      v25 = v23;
      v18 = sub_141A777D0(a1 + 8, &v25, v22);
    }
    *(_DWORD *)(v18 + 32) = 0;
    *(_WORD *)(a1 + 136) = 0;
    *(_DWORD *)(a1 + 140) = a3;
    sub_1401493F0();
  }
  return v11;
}
