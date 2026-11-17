char __fastcall sub_14062B500(__int64 a1, __int16 a2, __int64 a3, unsigned __int8 a4)
{
  unsigned int v5; // r14d
  float *v7; // rsi
  float v8; // xmm0_4
  float v9; // xmm6_4
  LARGE_INTEGER v10; // r15
  DWORD v11; // edi
  unsigned __int64 v12; // rax
  __int64 v13; // rdx
  __int64 v14; // r8
  void *NetworkModuleProxy; // rax
  __int64 v16; // rdx
  __int16 v17; // ax
  float v18; // xmm0_4
  unsigned int v19; // xmm1_4
  __int16 v20; // di
  unsigned int v21; // xmm2_4
  __int16 v22; // ax
  float v23; // xmm0_4
  float v24; // xmm1_4
  int v25; // eax
  float v26; // xmm0_4
  float v27; // xmm1_4
  float v29[4]; // [rsp+20h] [rbp-E0h] BYREF
  float v30; // [rsp+30h] [rbp-D0h] BYREF
  float v31; // [rsp+34h] [rbp-CCh]
  float v32; // [rsp+38h] [rbp-C8h]
  int v33; // [rsp+3Ch] [rbp-C4h]
  __int128 v34; // [rsp+40h] [rbp-C0h] BYREF
  unsigned int v35; // [rsp+50h] [rbp-B0h]
  unsigned int v36; // [rsp+54h] [rbp-ACh]
  float v37; // [rsp+58h] [rbp-A8h]
  float v38; // [rsp+5Ch] [rbp-A4h]
  float v39; // [rsp+60h] [rbp-A0h]
  LARGE_INTEGER PerformanceCount; // [rsp+68h] [rbp-98h] BYREF
  int packet; // [rsp+70h] [rbp-90h] BYREF
  __int64 v42; // [rsp+78h] [rbp-88h]
  DWORD v43; // [rsp+90h] [rbp-70h]

  v5 = a4;
  v7 = (float *)sub_1418149B0(*(_QWORD *)(a1 + 16));
  v8 = sub_1418149D0(*(_QWORD *)(a1 + 16));
  v9 = v8;
  v30 = *v7;
  v31 = v7[1];
  v32 = v7[2];
  v33 = 0;
  v29[0] = v8;
  if ( byte_142AB28A1 )
    sub_14181A910(*(void **)(a1 + 16), &v30, v29);
  v10.QuadPart = 0;
  v11 = 0;
  if ( (*(_BYTE *)(*(_QWORD *)(a1 + 16) + 1072LL) & 1) != 0 && !(unsigned __int8)sub_14181C320() )
  {
    v11 = 1;
    if ( (*(_BYTE *)(*(_QWORD *)(a1 + 16) + 1072LL) & 3) == 3 && !(unsigned __int8)sub_14181C320() )
      v11 = 3;
  }
  LOBYTE(v12) = sub_141819800(*(_QWORD *)(a1 + 16));
  if ( (_BYTE)v12 )
    v11 |= 4u;
  if ( v11 != *(_DWORD *)(a1 + 72) )
  {
    *(_DWORD *)(a1 + 72) = v11;
    NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
    packet = 916;
    v42 = 24;
    v43 = v11;
    LOBYTE(v12) = sub_140481E80(NetworkModuleProxy, &packet, 0, 0);
    if ( (byte_142AA895A & 4) != 0 )
    {
      LOBYTE(v12) = (_BYTE)source;
      if ( source )
      {
        v16 = *((unsigned int *)source + 30);
        PerformanceCount.LowPart = v11;
        LOBYTE(v12) = sub_1408492A0(&qword_142AA8218, v16, &PerformanceCount);
      }
    }
  }
  if ( !*(_BYTE *)(a1 + 77)
    && (_BYTE)v5
    && *v7 == *(float *)(a1 + 32)
    && v7[1] == *(float *)(a1 + 36)
    && v7[2] == *(float *)(a1 + 40)
    && v8 == *(float *)(a1 + 44)
    && v30 == *(float *)(a1 + 48)
    && v31 == *(float *)(a1 + 52)
    && v32 == *(float *)(a1 + 56)
    && v29[0] == *(float *)(a1 + 60) )
  {
    *(_WORD *)(a1 + 76) = 0;
    *(_BYTE *)(a1 + 78) = 0;
  }
  else
  {
    v17 = sub_14062BAF0(a1, v13, v14);
    v18 = *v7;
    v19 = *((_DWORD *)v7 + 1);
    v20 = a2 | v17;
    v21 = *((_DWORD *)v7 + 2);
    *(float *)&v34 = v9;
    if ( byte_142AB28A1 )
    {
      *((float *)&v34 + 3) = v18;
      v35 = v19;
      v37 = v30;
      v38 = v31;
      v39 = v32;
      *((float *)&v34 + 1) = v29[0];
      v36 = v21;
      WORD4(v34) = a2 | v17;
      v22 = sub_14062BBC0(a1);
      WORD5(v34) = v22;
      if ( (v20 & 0x4700) != 0 )
        WORD5(v34) = v22 | 0x40;
      sub_14062B900(a1, &v34, v5);
    }
    else
    {
      *((_QWORD *)&v34 + 1) = __PAIR64__(v19, LODWORD(v18));
      v35 = v21;
      WORD2(v34) = a2 | v17;
      WORD3(v34) = sub_14062BBC0(a1);
      sub_14062B850(a1, &v34, v5);
    }
    v23 = v30;
    v24 = v31;
    *(float *)(a1 + 32) = *v7;
    *(float *)(a1 + 36) = v7[1];
    v25 = *((_DWORD *)v7 + 2);
    *(float *)(a1 + 48) = v23;
    v26 = v32;
    *(float *)(a1 + 52) = v24;
    v27 = v29[0];
    *(float *)(a1 + 56) = v26;
    *(float *)(a1 + 60) = v27;
    *(float *)(a1 + 44) = v9;
    *(_DWORD *)(a1 + 40) = v25;
    *(_WORD *)(a1 + 76) = 0;
    *(_BYTE *)(a1 + 78) = 0;
    if ( QueryPerformanceCounter(&PerformanceCount) )
      v10 = PerformanceCount;
    v12 = 1000 * v10.QuadPart / (unsigned __int64)sub_1400D5E50();
    *(_QWORD *)(a1 + 64) = v12;
  }
  return v12;
}
