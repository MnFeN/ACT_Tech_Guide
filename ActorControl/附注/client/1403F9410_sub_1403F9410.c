__int64 __fastcall sub_1403F9410(__int64 a1)
{
  bool v2; // zf
  __int64 v3; // rax
  __int64 v4; // rsi
  bool v5; // bp
  _DWORD *v6; // rax
  _DWORD *v7; // rdx
  double (__fastcall *v8)(__int64, _QWORD, __int64, _QWORD); // rdx
  __int64 v9; // r8
  double v10; // xmm0_8
  double (__fastcall *v11)(__int64, _QWORD, __int64, _QWORD); // rdx
  __int64 v12; // r8
  double v13; // xmm0_8
  double (__fastcall *v14)(__int64, _QWORD, __int64, _QWORD); // rdx
  __int64 v15; // r8
  double v16; // xmm0_8
  __int64 v17; // r8
  _DWORD *v18; // rcx
  _DWORD *v19; // rdx
  __int64 v20; // rdx
  __int64 v21; // rbx
  __int64 v22; // rcx
  __int64 v23; // rcx
  __int64 v24; // rax
  _DWORD *v25; // rcx
  float v26; // xmm1_4
  float v27; // xmm2_4
  float v28; // xmm0_4
  float v29; // xmm1_4
  float v30; // xmm0_4
  float (__fastcall *v31)(__int64, _QWORD, __int64, _QWORD); // rdx
  double (__fastcall *v32)(__int64, _QWORD, __int64, _QWORD); // rdx
  double v33; // xmm0_8
  float (__fastcall *v34)(__int64, _QWORD, __int64, _QWORD); // rdx
  __int64 v35; // r8
  _DWORD *v36; // rax
  _DWORD *v37; // rdx
  double v38; // xmm0_8
  __int64 v39; // rbx
  __int64 v40; // r8
  float (__fastcall *v41)(__int64, _QWORD, __int64, _QWORD); // rdx
  __int64 v42; // rax
  __int64 result; // rax

  (*(void (__fastcall **)(__int64))(*(_QWORD *)a1 + 304LL))(a1);
  v2 = *(_BYTE *)(a1 + 1053) == 0;
  v3 = *(_QWORD *)(a1 + 872);
  *(_BYTE *)(a1 + 1104) = 0;
  v4 = *(_QWORD *)(v3 + 456);
  v5 = v2 && (*(_WORD *)(*(_QWORD *)(a1 + 504) + 1192LL) & 0x400) != 0;
  v6 = (_DWORD *)(*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 512) + 40LL))(*(_QWORD *)(a1 + 512));
  v7 = *(_DWORD **)(a1 + 1072);
  v7[56] = v6[9];
  v7[57] = v6[10];
  v7[58] = v6[11];
  *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 296LL) ^= (*(_DWORD *)(*(_QWORD *)(a1 + 1072) + 296LL)
                                                ^ (8 * *(unsigned __int8 *)(a1 + 1053)))
                                               & 8;
  v8 = (double (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 144) & 7));
  v10 = v8(v4 + 128, v8, v9, *(unsigned __int8 *)(a1 + 1051));
  *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 304LL) = LODWORD(v10);
  v11 = (double (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 24) & 7));
  v13 = v11(v4 + 8, v11, v12, *(unsigned __int8 *)(a1 + 1046));
  *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 308LL) = LODWORD(v13);
  v14 = (double (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 168) & 7));
  v16 = v14(v4 + 152, v14, v15, *(unsigned __int8 *)(a1 + 1052));
  *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 312LL) = LODWORD(v16);
  *(float *)(*(_QWORD *)(a1 + 1072) + 316LL) = ((float (*)(void))funcs_1403981C6[(**(_DWORD **)(v4 + 176) >> 7) & 3])();
  sub_1403B5AF0();
  v18 = *(_DWORD **)(a1 + 1072);
  v19 = *(_DWORD **)(*((_QWORD *)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)TlsIndex) + 736LL);
  v18[62] = v19[15];
  v18[63] = v19[16];
  v18[64] = v19[17];
  v20 = *(_QWORD *)(a1 + 1072);
  if ( (*(_BYTE *)(v20 + 296) & 0x40) == 0 )
  {
    if ( v5 )
      goto LABEL_24;
    goto LABEL_21;
  }
  v21 = *(_QWORD *)(a1 + 512);
  v22 = *(_QWORD *)(v21 + 600);
  if ( !v22
    || !(*(unsigned __int8 (__fastcall **)(__int64, __int64, _QWORD))(*(_QWORD *)v22 + 296LL))(v22, v20 + 260, 0)
    || (v23 = *(_QWORD *)(v21 + 600)) == 0
    || !(*(unsigned __int8 (__fastcall **)(__int64, __int64, __int64))(*(_QWORD *)v23 + 296LL))(
          v23,
          *(_QWORD *)(a1 + 1072) + 272LL,
          2) )
  {
    v24 = *(_QWORD *)(a1 + 1072);
    *(_QWORD *)(v24 + 260) = qword_142AA27C0;
    *(_DWORD *)(v24 + 268) = dword_142AA27C8;
    v25 = *(_DWORD **)(a1 + 1072);
    v25[68] = v25[65];
    v25[69] = v25[66];
    v25[70] = v25[67];
  }
  v26 = *(float *)(a1 + 1116);
  if ( v26 < 0.0 )
  {
    v30 = *(float *)(a1 + 1112);
    if ( v5 )
      goto LABEL_24;
    if ( v30 >= 0.0 )
    {
LABEL_22:
      *(float *)(*(_QWORD *)(a1 + 1072) + 320LL) = v30;
      goto LABEL_23;
    }
LABEL_21:
    v31 = (float (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 48) & 7));
    v30 = v31(v4 + 32, v31, v17, *(unsigned __int8 *)(a1 + 1047));
    goto LABEL_22;
  }
  v27 = 1.0;
  v28 = (float)(*(float *)(a1 + 464) / 60.0) + *(float *)(a1 + 1120);
  *(float *)(a1 + 1120) = v28;
  if ( v28 < 1.0 )
  {
    v27 = v28;
  }
  else
  {
    *(_DWORD *)(a1 + 1120) = 1065353216;
    *(_DWORD *)(a1 + 1116) = -1082130432;
  }
  v29 = (float)((float)(v26 - *(float *)(a1 + 1112)) * v27) + *(float *)(a1 + 1112);
  *(float *)(a1 + 1112) = v29;
  if ( !v5 )
  {
    *(float *)(*(_QWORD *)(a1 + 1072) + 320LL) = v29;
LABEL_23:
    v32 = (double (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 72) & 7));
    v33 = v32(v4 + 56, v32, v17, *(unsigned __int8 *)(a1 + 1048));
    *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 324LL) = LODWORD(v33);
    v34 = (float (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 120) & 7));
    *(float *)(*(_QWORD *)(a1 + 1072) + 332LL) = v34(v4 + 104, v34, v35, *(unsigned __int8 *)(a1 + 1050));
  }
LABEL_24:
  v36 = (_DWORD *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)a1 + 56LL))(a1);
  v37 = *(_DWORD **)(a1 + 1072);
  v37[59] = *v36;
  v37[60] = v36[1];
  v37[61] = v36[2];
  v38 = sub_1403E45D0(a1);
  *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 300LL) = LODWORD(v38);
  v39 = *(_QWORD *)(a1 + 1072) + 352LL;
  (*(void (__fastcall **)(__int64, __int64))(a1 + 952))(a1, v39);
  (*(void (__fastcall **)(__int64, __int64))(a1 + 960))(a1, v39);
  (*(void (__fastcall **)(__int64, __int64))(a1 + 968))(a1, v39);
  if ( (*(_BYTE *)(*(_QWORD *)(a1 + 1072) + 296LL) & 1) != 0 && !v5 )
  {
    v41 = (float (__fastcall *)(__int64, _QWORD, __int64, _QWORD))*(&off_1428B52C8 + (*(_DWORD *)(v4 + 96) & 7));
    *(float *)(*(_QWORD *)(a1 + 1072) + 328LL) = v41(v4 + 80, v41, v40, *(unsigned __int8 *)(a1 + 1049));
  }
  if ( *(_DWORD *)(a1 + 1108) == -2 )
  {
    *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 296LL) &= ~4u;
  }
  else
  {
    v42 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(*(_QWORD *)(a1 + 504) + 624LL) + 40LL))(*(_QWORD *)(*(_QWORD *)(a1 + 504) + 624LL));
    *(_DWORD *)(*(_QWORD *)(a1 + 1072) + 296LL) ^= (*(_DWORD *)(*(_QWORD *)(a1 + 1072) + 296LL)
                                                  ^ (4
                                                   * (*(unsigned __int8 (__fastcall **)(_QWORD, __int64, __int64, __int64, _DWORD, __int64))(**(_QWORD **)(*(_QWORD *)(a1 + 504) + 624LL) + 72LL))(
                                                       *(_QWORD *)(*(_QWORD *)(a1 + 504) + 624LL),
                                                       *(_QWORD *)(a1 + 1072) + 260LL,
                                                       *(_QWORD *)(a1 + 1072) + 272LL,
                                                       *(_QWORD *)(a1 + 1072) + 284LL,
                                                       *(char *)(v4 + 1),
                                                       v42)))
                                                 & 4;
  }
  if ( (*(_BYTE *)(*(_QWORD *)(a1 + 1072) + 296LL) & 0x20) != 0 )
    result = sub_1403F57F0(a1);
  else
    result = sub_1403F5C80(a1);
  *(_BYTE *)(a1 + 1053) = 0;
  return result;
}
