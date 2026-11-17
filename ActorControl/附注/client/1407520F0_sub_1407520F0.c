unsigned __int8 __fastcall sub_1407520F0(void *self, unsigned int mode, unsigned int elapsedMs)
{
  char v3; // al
  __int64 v7; // rcx
  __int64 v8; // rcx
  unsigned __int8 result; // al

  v3 = *((_BYTE *)self + 92);
  *((_BYTE *)self + 88) &= ~1u;
  if ( (unsigned __int8)(v3 - 5) <= 1u )
  {
    if ( *((_QWORD *)self + 6) )
    {
      sub_1418CA330(qword_142B03048, (char *)self + 48);
      v7 = *((_QWORD *)self + 6);
      if ( v7 )
      {
        if ( _InterlockedExchangeAdd((volatile signed __int32 *)(v7 + 8), 0xFFFFFFFF) == 1 )
        {
          *(_QWORD *)v7 = 0;
          sub_1418C6C80((__int64)self + 48, *((_QWORD *)self + 6));
        }
        *((_QWORD *)self + 6) = 0;
      }
    }
  }
  v8 = *((_QWORD *)self + 6);
  if ( !v8 )
  {
    sub_140751E70(self, *((_QWORD *)self + 9), *((_QWORD *)self + 10));
    v8 = *((_QWORD *)self + 6);
  }
  if ( mode == -1 )
    mode = (*((_BYTE *)self + 88) & 2) == 0;
  result = (mode == 0) + 1;
  *((_BYTE *)self + 92) = result;
  if ( v8 )
  {
    sub_1418C93A0((__int64)qword_142B03048, (__int64)self + 48, mode, 0xFFFFFFFF);
    result = (unsigned __int8)qword_142909910;
    if ( *((float *)qword_142909910 + 1518) != 1.0 )
      result = sub_1418C87D0(qword_142B03048, (char *)self + 48);
    if ( elapsedMs )
      sub_1418CB010((__int64)qword_142B03048, (__int64)self + 48, (float)((float)(int)elapsedMs * 30.0) / 1000.0);
  }
  return result;
}
