void *__fastcall sub_14090AC70(
        void *actor,
        float angle,
        float distance,
        float duration,
        unsigned __int8 flag,
        int mode)
{
  float v7; // xmm9_4
  float v8; // xmm6_4
  void *result; // rax
  bool v10; // zf
  float v11; // xmm9_4
  float v12; // xmm8_4
  float v13; // xmm6_4
  float v14; // xmm6_4
  unsigned __int8 v15; // dl
  _DWORD v16[4]; // [rsp+30h] [rbp-68h] BYREF

  v7 = sinf(angle) * distance;
  v8 = cosf(angle) * distance;
  result = Client__Game__Object__GameObject__GetPosition(actor);
  v10 = *((_QWORD *)actor + 186) == 0;
  v11 = v7 + *(float *)result;
  v12 = (float)(distance * 0.0) + *((float *)result + 1);
  v13 = v8 + *((float *)result + 2);
  v16[3] = 0;
  *(float *)v16 = v11;
  *(float *)&v16[1] = v12;
  *(float *)&v16[2] = v13;
  v14 = *((float *)actor + 48);
  if ( !v10 && !*((_BYTE *)actor + 152) )
  {
    v15 = 0;
    if ( mode == 1 )
    {
      v15 = 3;
    }
    else if ( mode == 2 )
    {
      v15 = 2;
    }
    LOBYTE(result) = sub_1418149F0((__int64)actor + 496, v15);
    if ( (_BYTE)result )
    {
      *((_DWORD *)actor + 374) = mode;
      LOBYTE(result) = sub_14181A450((char *)actor + 496, v16, v14, duration);
    }
  }
  return result;
}
