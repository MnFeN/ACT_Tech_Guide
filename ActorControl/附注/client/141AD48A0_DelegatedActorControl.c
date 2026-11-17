char __fastcall sub_141AD48A0(__int64 a1, int a2, unsigned __int8 a3, int a4)
{
  int v7; // edx
  __int64 v9; // rax
  unsigned int v10; // ebx
  __int64 v11; // rax
  int v12; // eax

  v7 = a2 - 3650;
  if ( v7 )
  {
    if ( v7 == 1 )
    {
      sub_141AD4E40(a1, a3, a4);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sub_141AD5750(a1);
    *(_WORD *)(a1 + 32) = a3;
    if ( a3 )
    {
      v9 = sub_140B777C0();
      if ( sub_140B87440(v9, 0) )
      {
        *(_BYTE *)(a1 + 244) |= 0x10u;
        return 1;
      }
      if ( a4 )
      {
        v10 = sub_140ED12C0(6001);
        v11 = sub_140B777C0();
        sub_1417CEEF0(v11 + 432, v10);
        v12 = sub_140ED12C0(6000);
        *(_BYTE *)(a1 + 244) |= 4u;
        *(float *)(a1 + 240) = (float)v12;
        return 1;
      }
      *(_BYTE *)(a1 + 244) |= 2u;
    }
    return 1;
  }
}
