__int64 __fastcall sub_14182DBE0(__int64 a1, int a2)
{
  unsigned int v4; // ebx
  float *Position; // rsi
  int v6; // r15d
  float v7; // xmm7_4
  float v8; // xmm0_4
  float v9; // xmm6_4
  float v10; // xmm8_4
  float v11; // xmm0_4
  float v12; // xmm0_4
  unsigned int v13; // ecx
  float a2a[2]; // [rsp+30h] [rbp-D0h] BYREF
  float v16; // [rsp+38h] [rbp-C8h]
  int v17; // [rsp+3Ch] [rbp-C4h]
  _DWORD a5[4]; // [rsp+40h] [rbp-C0h] BYREF
  __int64 a3[2]; // [rsp+50h] [rbp-B0h] BYREF
  __int128 v20; // [rsp+60h] [rbp-A0h]
  __int128 v21; // [rsp+70h] [rbp-90h]
  __int64 v22; // [rsp+80h] [rbp-80h]
  int v23; // [rsp+88h] [rbp-78h]
  __int64 v24; // [rsp+90h] [rbp-70h]
  int v25; // [rsp+98h] [rbp-68h]
  __int64 v26; // [rsp+A0h] [rbp-60h]
  int v27; // [rsp+A8h] [rbp-58h]
  __int128 v28; // [rsp+B0h] [rbp-50h]
  char v29; // [rsp+C0h] [rbp-40h]
  __int128 v30; // [rsp+D0h] [rbp-30h]
  char v31; // [rsp+E0h] [rbp-20h]
  int v32; // [rsp+E4h] [rbp-1Ch]
  __int64 v33; // [rsp+E8h] [rbp-18h]
  __int128 v34; // [rsp+F0h] [rbp-10h]
  __int128 v35; // [rsp+100h] [rbp+0h]
  __int128 v36; // [rsp+110h] [rbp+10h]
  __int64 v37; // [rsp+120h] [rbp+20h]
  int v38; // [rsp+128h] [rbp+28h]
  __int64 v39; // [rsp+130h] [rbp+30h]
  int v40; // [rsp+138h] [rbp+38h]
  __int64 v41; // [rsp+140h] [rbp+40h]
  int v42; // [rsp+148h] [rbp+48h]
  __int128 v43; // [rsp+150h] [rbp+50h]
  char v44; // [rsp+160h] [rbp+60h]
  __int128 v45; // [rsp+170h] [rbp+70h]
  char v46; // [rsp+180h] [rbp+80h]
  int v47; // [rsp+184h] [rbp+84h]
  __int64 v48; // [rsp+188h] [rbp+88h]
  int v49; // [rsp+190h] [rbp+90h]
  char v50; // [rsp+194h] [rbp+94h]

  v4 = 0;
  Position = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(*(_QWORD *)(a1 + 32) + 992LL));
  v6 = 0;
  if ( a2 )
  {
    a5[3] = 0;
    do
    {
      v7 = (float)((float)v6 * 6.2831855) / (float)a2;
      v8 = sinf(v7);
      v9 = Position[1] + 0.0;
      v10 = (float)(v8 * 0.2) + *Position;
      v11 = cosf(v7);
      v29 &= 0xF8u;
      v31 &= 0xF0u;
      v44 &= 0xF8u;
      v46 &= 0xF0u;
      *(float *)a5 = v10;
      *(float *)&a5[1] = v9;
      v12 = (float)(v11 * 0.2) + Position[2];
      a2a[0] = v10;
      a2a[1] = v9;
      v17 = 0;
      v20 = 0;
      *(float *)&a5[2] = v12;
      v16 = v12;
      *(_OWORD *)a3 = 0;
      v21 = 0;
      v28 = 0;
      v34 = 0;
      v36 = 0;
      v43 = 0;
      v22 = 0;
      v23 = 0;
      v24 = 0;
      v25 = 0;
      v26 = 0;
      v27 = 0;
      v30 = 0;
      v32 = 0;
      v33 = 0;
      v35 = 0;
      v37 = 0;
      v38 = 0;
      v39 = 0;
      v40 = 0;
      v41 = 0;
      v42 = 0;
      v45 = 0;
      v47 = 0;
      v48 = 0;
      v49 = 0;
      v50 = 0;
      sub_14182D950(a1, a2a, (__int64)a3, Position, (__int64)a5, byte_142AB28A1);
      v13 = v4 + 1;
      if ( (float)((float)((float)(v16 - Position[2]) * (float)(v16 - Position[2]))
                 + (float)((float)(a2a[0] - *Position) * (float)(a2a[0] - *Position))) >= 0.032400001 )
        v13 = v4;
      ++v6;
      v4 = v13;
    }
    while ( v6 < (unsigned int)a2 );
  }
  return v4;
}
