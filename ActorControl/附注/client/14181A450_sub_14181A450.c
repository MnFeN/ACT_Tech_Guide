unsigned __int8 __fastcall sub_14181A450(void *self, void *position, float rotation, float duration)
{
  _UNKNOWN **v4; // rax
  __int64 v5; // rbx
  __int64 v8; // rax
  float v9; // xmm6_4
  __int64 v10; // rbx
  unsigned __int16 v11; // ax
  __int64 (__fastcall **v13)(); // [rsp+30h] [rbp-78h] BYREF
  int v14; // [rsp+38h] [rbp-70h]
  int v15; // [rsp+3Ch] [rbp-6Ch]
  int v16; // [rsp+40h] [rbp-68h]
  float v17; // [rsp+44h] [rbp-64h]
  float v18; // [rsp+48h] [rbp-60h]
  int v19; // [rsp+4Ch] [rbp-5Ch]
  __int64 v20; // [rsp+50h] [rbp-58h]
  int v21; // [rsp+58h] [rbp-50h]
  __int64 v22; // [rsp+5Ch] [rbp-4Ch]
  int v23; // [rsp+64h] [rbp-44h]
  char v24; // [rsp+68h] [rbp-40h]
  _UNKNOWN *retaddr; // [rsp+A8h] [rbp+0h] BYREF

  v4 = &retaddr;
  v5 = *((_QWORD *)self + 124);
  if ( v5 )
  {
    if ( (qword_142AA895B & 4) == 0 || (LOBYTE(v4) = sub_1406056C0(), (_BYTE)v4) )
    {
      LOBYTE(v4) = sub_140897A40(v5, 0, 0);
      if ( (_BYTE)v4 )
      {
        LOBYTE(v4) = *((_BYTE *)self + 1040) - 1;
        if ( (unsigned __int8)v4 > 2u )
        {
          v8 = sub_140B777C0();
          sub_140B81EF0(v8);
          nullsub_108(&unk_142AAB775);
          v9 = fmaxf(0.0, duration);
          if ( **((_DWORD **)self + 113) == 1 )
            sub_14181D7D0((__int64)self);
          if ( *((_DWORD *)self + 52) )
            sub_141806830((__int64)self + 16, 0);
          if ( *((_BYTE *)self + 710) )
            sub_141808420((__int64)self + 592);
          v17 = v9;
          v13 = off_142178A60;
          v18 = v9;
          v14 = -1082130432;
          v15 = -1082130432;
          v16 = -1082130432;
          v19 = 0;
          v20 = 0;
          v22 = 3;
          v23 = 256;
          v24 = 0;
          v21 = 3;
          LOBYTE(v4) = sub_141819E90(self, (float *)position, rotation, &v13);
          if ( *((_BYTE *)self + 514) )
          {
            if ( !*((_BYTE *)self + 515) )
            {
              LOBYTE(v4) = (*(__int64 (__fastcall **)(_QWORD))(**((_QWORD **)self + 124) + 464LL))(*((_QWORD *)self + 124));
              if ( !(_BYTE)v4 )
              {
                LOBYTE(v4) = sub_141821270(self, 10);
                if ( !(_BYTE)v4 )
                {
                  v10 = *((_QWORD *)self + 124);
                  v11 = sub_14181AB30(self);
                  LOBYTE(v4) = std::num_get<wchar_t,std::istreambuf_iterator<wchar_t>>::_Parse_int_with_locale<0>(
                                 v10 + 2608,
                                 v11,
                                 0,
                                 0,
                                 0);
                }
              }
            }
          }
        }
      }
    }
  }
  return (unsigned __int8)v4;
}
