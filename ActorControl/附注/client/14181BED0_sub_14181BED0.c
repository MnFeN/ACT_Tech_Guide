unsigned __int8 __fastcall sub_14181BED0(
        void *self,
        const float *position,
        float rotation,
        const unsigned __int8 *options)
{
  unsigned __int8 result; // al
  unsigned __int8 v8; // dl
  unsigned __int8 v9; // bp
  unsigned __int8 v10; // r12
  unsigned __int8 v11; // r14
  unsigned __int8 v12; // r15
  float *v13; // rax
  char v14; // bl
  __int64 v15; // rbp
  char v16; // al
  _BYTE *v17; // rcx
  void *v18; // rax
  char v19; // bl
  char v20; // al
  __int64 *v21; // rax
  __int64 *v22; // rdi
  _DWORD *v23; // rbx
  _DWORD *v24; // rax
  int v25; // ecx
  __int64 v26; // rax

  if ( sub_140897D40(*((_QWORD *)self + 124)) )
    return 0;
  v8 = 7;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 1;
  if ( options )
  {
    v8 = options[8];
    v12 = options[9];
    v9 = options[11];
    v10 = options[12];
    v11 = options[13];
  }
  result = sub_1418149F0((__int64)self, v8);
  if ( result )
  {
    sub_14181A640((__int64)self, 0);
    if ( **((_DWORD **)self + 113) == 1 )
      sub_14181D7D0((__int64)self);
    if ( !v9 )
      sub_141842A40((__int64)self);
    v13 = (float *)Client__Game__Object__GameObject__GetPosition(*((void **)self + 124));
    if ( *v13 == *position && v13[1] == position[1] && v13[2] == position[2] )
    {
      v14 = 0;
    }
    else
    {
      v14 = 1;
      sub_140471100();
      *((_QWORD *)self + 117) = 0;
      *((_QWORD *)self + 118) = 0;
      *((_DWORD *)self + 238) = 0;
      *((_BYTE *)self + 956) = 0;
      sub_142069A30((__int64)self + 960);
    }
    sub_141816300((__int64)self, (float *)position);
    Client__Game__Object__GameObject__SetRotation(*((void **)self + 124), rotation);
    v15 = *((_QWORD *)self + 124);
    if ( v15 && ((qword_142AA895B & 4) == 0 || sub_1406056C0()) && sub_140897A40(v15, 0, 0) )
    {
      if ( v14 )
      {
        if ( !v11 )
        {
          sub_1406050A0((__int64)&word_142AA7678);
          sub_140754FB0((__int64)position);
        }
        v16 = word_142AB29E6;
        if ( v12 )
          v16 = 1;
        LOBYTE(word_142AB29E6) = v16;
      }
      byte_142AB29E8 = 1;
      sub_14062B3B0((__int64)&qword_142AB2C70);
      if ( byte_142AB29C1 )
      {
        if ( *(_BYTE *)(qword_142AB28E0 + 710) )
          sub_141808420(qword_142AB28E0 + 592);
        sub_140E13730((__int64)byte_142AF9070, 70, 0);
        byte_142AB29C1 = 0;
        dword_142AB29F4 = 0;
      }
      sub_140846820((__int64)&qword_142AA895B + 5);
    }
    v17 = (_BYTE *)*((_QWORD *)self + 124);
    if ( (v17[7400] & 0x20) != 0
      || (v18 = Client__Game__Object__GameObject__GetPosition(v17), !sub_140E13F20((__int64)v18)) )
    {
      v19 = v10 != 0;
    }
    else
    {
      v19 = 2;
    }
    v20 = *((_BYTE *)self + 1040);
    if ( v20 == v19 )
    {
      if ( (unsigned __int8)(v20 - 1) <= 2u )
      {
        v22 = sub_14181CD70((__int64)self);
        v23 = *(_DWORD **)(v22[6] + 992);
        v24 = Client__Game__Object__GameObject__GetPosition(v23);
        *((_DWORD *)v22 + 4) = *v24;
        *((_DWORD *)v22 + 5) = v24[1];
        v25 = v24[2];
        v26 = *v22;
        *((_DWORD *)v22 + 6) = v25;
        *((_DWORD *)v22 + 16) = v23[48];
        (*(void (__fastcall **)(__int64 *))(v26 + 56))(v22);
      }
    }
    else
    {
      if ( (unsigned __int8)(v20 - 1) <= 2u )
      {
        v21 = sub_14181CD70((__int64)self);
        if ( *((_BYTE *)v21 + 102) )
          sub_14180A850((__int64)v21);
        *((_BYTE *)self + 1040) = 0;
      }
      if ( v19 == 1 )
      {
        sub_14181C380((__int64)self);
      }
      else if ( v19 == 2 )
      {
        sub_14181CEC0((__int64)self);
      }
      sub_1408C92C0(*((_QWORD *)self + 124) + 6800LL, 1);
      sub_1409078C0(*((_QWORD *)self + 124));
    }
    if ( v12 )
    {
      *((_BYTE *)self + 1080) &= ~1u;
      *((_QWORD *)self + 129) = 1069547520;
      sub_141816C00((__int64)self);
    }
    return 1;
  }
  return result;
}
