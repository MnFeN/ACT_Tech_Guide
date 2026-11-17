unsigned __int8 __fastcall Client__LayoutEngine__Group__SharedGroupLayoutInstance__PlayTimeline(
        void *self,
        unsigned int index,
        unsigned int a1)
{
  char v3; // di
  void *InstanceBySubId; // rax
  unsigned int v7; // ecx
  unsigned int v8; // esi

  v3 = index;
  if ( index < 0x10 )
  {
    if ( *((_QWORD *)self + 18) == *((_QWORD *)self + 19) )
    {
      *((_BYTE *)self + 356) = 3;
      *((_BYTE *)self + 365) = index;
      *((_DWORD *)self + 93) = a1;
      LOBYTE(InstanceBySubId) = 1;
      return (unsigned __int8)InstanceBySubId;
    }
    v7 = *((unsigned __int8 *)self + index + 340);
    if ( (_BYTE)v7 )
    {
      v8 = v7;
      if ( !(unsigned __int8)sub_140706310(self, v7) )
      {
        InstanceBySubId = Client__LayoutEngine__Group__TimeLineContainer__FindInstanceBySubId(
                            (char *)self + 208,
                            *((_DWORD *)self + 8) | (v8 << (8 * (4 - (((*((_BYTE *)self + 41) >> 4) & 7) + 1)))));
        if ( !InstanceBySubId )
          return (unsigned __int8)InstanceBySubId;
        *((_DWORD *)self + 78) &= 0xFFFFFFF0;
        *((_DWORD *)self + 78) |= v3 & 0xF;
        *((_BYTE *)self + 300) |= 1u;
        sub_1407520F0(InstanceBySubId, 0xFFFFFFFF, a1);
      }
      LOBYTE(InstanceBySubId) = 1;
      return (unsigned __int8)InstanceBySubId;
    }
  }
  LOBYTE(InstanceBySubId) = 0;
  return (unsigned __int8)InstanceBySubId;
}
