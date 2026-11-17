void __fastcall sub_140B51F80(__int64 a1, unsigned int a2, float *a3, float a4, int a5, float a6, __int64 a7)
{
  float v11; // xmm3_4
  __int64 v12; // rdi
  float v13; // xmm1_4
  float v14; // xmm0_4
  __int64 v15; // rax
  __int64 v16; // rbx
  __int64 v17; // rcx
  __int128 v18; // [rsp+30h] [rbp-78h] BYREF
  int v19; // [rsp+40h] [rbp-68h]
  int v20; // [rsp+44h] [rbp-64h]
  int v21; // [rsp+48h] [rbp-60h]
  __int64 v22; // [rsp+50h] [rbp-58h]
  int v23; // [rsp+58h] [rbp-50h]
  __int64 v24; // [rsp+60h] [rbp-48h]
  float v25; // [rsp+68h] [rbp-40h]

  if ( a7 )
    v11 = sub_14090D980(a7);
  else
    v11 = *(float *)(qword_142909910 + 6072);
  v12 = sub_140857580(a2, a3, a7, v11, 0x3F800000u, 0);
  if ( v12 )
  {
    LODWORD(v18) = a5;
    v20 = a5;
    v23 = a5;
    *(_QWORD *)((char *)&v18 + 4) = 0;
    v19 = 0;
    v21 = 0;
    v22 = 0;
    v24 = 0;
    v25 = 0.0;
    sub_1402F8A60((float *)&v18, a6);
    v13 = *((float *)&v24 + 1) + a3[1];
    *(float *)&v24 = *(float *)&v24 + *a3;
    v14 = v25 + a3[2];
    *((float *)&v24 + 1) = v13;
    v25 = v14;
    sub_1403913F0(v12, &v18);
    v15 = sub_140B52410(a1);
    v16 = v15;
    if ( v15 )
    {
      v17 = *(_QWORD *)(v15 + 8);
      if ( v17 )
      {
        sub_140391030(v17, 1);
        sub_140391940(*(_QWORD *)(v16 + 8), 0);
      }
      *(float *)(v16 + 16) = a4;
      *(_QWORD *)(v16 + 8) = v12;
      sub_140391940(v12, v16);
    }
  }
}
