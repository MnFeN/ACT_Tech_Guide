void __fastcall sub_14090ABB0(
        void *actor,
        void *position,
        float rotation,
        float duration,
        unsigned __int8 flag,
        int mode)
{
  unsigned __int8 v8; // dl

  if ( *((_QWORD *)actor + 186) && !*((_BYTE *)actor + 152) )
  {
    v8 = 0;
    if ( mode == 1 )
    {
      v8 = 3;
    }
    else if ( mode == 2 )
    {
      v8 = 2;
    }
    if ( sub_1418149F0((__int64)actor + 496, v8) )
    {
      *((_DWORD *)actor + 374) = mode;
      sub_14181A450((char *)actor + 496, position, rotation, duration);
    }
  }
}
