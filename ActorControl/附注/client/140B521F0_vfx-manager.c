__int64 __fastcall sub_140B521F0(__int64 a1)
{
  __int64 v1; // rdx
  void (__fastcall ***i)(__int64, _QWORD); // rbx
  __int64 v4; // rcx
  void (__fastcall ***v5)(__int64, _QWORD); // rsi
  void (__fastcall **v6)(__int64, _QWORD); // rbx
  __int64 result; // rax

  v1 = *(_QWORD *)(a1 + 8);
  for ( i = *(void (__fastcall ****)(__int64, _QWORD))v1;
        i != (void (__fastcall ***)(__int64, _QWORD))v1;
        v1 = *(_QWORD *)(a1 + 8) )
  {
    v4 = (__int64)i[3];
    if ( v4 )
    {
      sub_140391030(v4, 1);
      sub_140391940((__int64)i[3], 0);
      i[3] = 0;
      *((_DWORD *)i + 8) = 0;
    }
    i = (void (__fastcall ***)(__int64, _QWORD))*i;
  }
  **(_QWORD **)(v1 + 8) = 0;
  v5 = *(void (__fastcall ****)(__int64, _QWORD))v1;
  if ( *(_QWORD *)v1 )
  {
    do
    {
      v6 = *v5;
      (*v5[2])((__int64)(v5 + 2), 0);
      Client__System__Memory__MemoryPool__Free(v5);
      v5 = (void (__fastcall ***)(__int64, _QWORD))v6;
    }
    while ( v6 );
  }
  **(_QWORD **)(a1 + 8) = *(_QWORD *)(a1 + 8);
  result = *(_QWORD *)(a1 + 8);
  *(_QWORD *)(result + 8) = result;
  *(_QWORD *)(a1 + 16) = 0;
  return result;
}
