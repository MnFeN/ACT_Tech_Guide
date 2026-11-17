_QWORD *__fastcall sub_140B52410(__int64 a1)
{
  _QWORD *v1; // rbx
  _QWORD *v3; // rax
  _QWORD *v4; // rax
  _QWORD *v5; // rcx

  v1 = *(_QWORD **)(a1 + 8);
  v3 = (_QWORD *)*v1;
  if ( (_QWORD *)*v1 == v1 )
  {
LABEL_4:
    if ( *(_QWORD *)(a1 + 16) == 0xFFFFFFFFLL )
      sub_141D72C8C((__int64)"list too long");
    v4 = Client__System__Memory__MemoryPool__Alloc(0x28u);
    v4[2] = off_1421A8B48;
    v4[3] = 0;
    *((_DWORD *)v4 + 8) = 0;
    ++*(_QWORD *)(a1 + 16);
    v5 = (_QWORD *)v1[1];
    *v4 = v1;
    v4[1] = v5;
    v1[1] = v4;
    *v5 = v4;
    v3 = *(_QWORD **)(*(_QWORD *)(a1 + 8) + 8LL);
  }
  else
  {
    while ( v3[3] )
    {
      v3 = (_QWORD *)*v3;
      if ( v3 == v1 )
        goto LABEL_4;
    }
  }
  return v3 + 2;
}
