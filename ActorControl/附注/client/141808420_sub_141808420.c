__int64 __fastcall sub_141808420(__int64 a1)
{
  __int64 v2; // rcx
  __int64 v3; // rdi
  __int64 v4; // r8
  __int64 v6; // rax

  *(_BYTE *)(a1 + 118) = 0;
  v2 = *(_QWORD *)(a1 + 16);
  if ( v2 )
  {
    v3 = *(_QWORD *)(v2 + 992);
    if ( v3 )
    {
      sub_141820090(v2);
      if ( sub_140897A40(v3, 1, 0) )
      {
        sub_14062B130((__int64)&unk_142AB2C70, 0x1000u);
        LOBYTE(word_142AB29E6) = 1;
        return sub_141807F10(a1);
      }
      v6 = *(_QWORD *)(a1 + 16);
      if ( *(_BYTE *)(v6 + 1041) < 2u )
        *(_WORD *)(v6 + 1041) = 2;
      if ( *(_BYTE *)(a1 + 121) )
        sub_141808F40(a1, (float *)(a1 + 80), v4, 0);
    }
  }
  return sub_141807F10(a1);
}
