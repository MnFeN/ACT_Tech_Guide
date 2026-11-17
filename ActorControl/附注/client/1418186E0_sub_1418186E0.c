unsigned __int8 __fastcall sub_1418186E0(void *self, float *outHeight, const float *probePosition)
{
  unsigned __int8 result; // al
  __int64 a2[2]; // [rsp+20h] [rbp-B8h] BYREF
  __int128 v6; // [rsp+30h] [rbp-A8h]
  __int128 v7; // [rsp+40h] [rbp-98h]
  __int64 v8; // [rsp+50h] [rbp-88h]
  int v9; // [rsp+58h] [rbp-80h]
  __int64 v10; // [rsp+60h] [rbp-78h]
  int v11; // [rsp+68h] [rbp-70h]
  __int64 v12; // [rsp+70h] [rbp-68h]
  int v13; // [rsp+78h] [rbp-60h]
  __int128 v14; // [rsp+80h] [rbp-58h]
  char v15; // [rsp+90h] [rbp-48h]
  __int128 v16; // [rsp+A0h] [rbp-38h]
  char v17; // [rsp+B0h] [rbp-28h]
  int v18; // [rsp+B4h] [rbp-24h]
  __int64 v19; // [rsp+B8h] [rbp-20h]
  int v20; // [rsp+C0h] [rbp-18h]

  v8 = 0;
  v9 = 0;
  *(_OWORD *)a2 = 0;
  v6 = 0;
  v7 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v15 &= 0xF8u;
  v17 &= 0xF0u;
  v14 = 0;
  v16 = 0;
  v18 = 0;
  v19 = 0;
  result = sub_141818500(self, a2, probePosition);
  if ( result )
  {
    *(_DWORD *)outHeight = v20;
    return 1;
  }
  return result;
}
