__int64 __fastcall sub_141AB9A60(__int64 a1, __int64 a2, __int64 **a3)
{
  __int64 v4; // rbp
  int *v5; // r8
  __int64 v6; // rcx
  char v7; // al
  int v8; // eax
  int v9; // eax
  unsigned int v10; // r14d
  int v11; // edi
  int v12; // ebx
  _BYTE *v13; // rax
  __int64 v14; // r8
  _BYTE *v15; // rax
  __int64 v16; // r8
  float x; // xmm6_4
  float y; // xmm7_4
  float z; // xmm8_4
  unsigned int v20; // edx
  void *LayoutInstanceStatic; // rax
  float *v22; // rax
  _OWORD *v23; // rax
  __int128 v24; // xmm0
  __int64 result; // rax
  _BYTE self[144]; // [rsp+70h] [rbp-A8h] BYREF

  v4 = **a3;
  *(_OWORD *)(a1 + 48) = *(_OWORD *)v4;
  *(_OWORD *)(a1 + 64) = *(_OWORD *)(v4 + 16);
  *(_OWORD *)(a1 + 80) = *(_OWORD *)(v4 + 32);
  v5 = (int *)EXD__DynamicEventType__Row_14083FC60(*(unsigned __int8 *)(v4 + 38));
  *(_BYTE *)(a1 + 118) = *(_BYTE *)(v4 + 38);
  v6 = *(_QWORD *)(a1 + 448);
  *(_DWORD *)(a1 + 104) = 60 * *(unsigned __int8 *)(v4 + 41);
  if ( *(_BYTE *)(v4 + 40) >= *(_BYTE *)(v6 + 7551) )
    *(_BYTE *)(a1 + 119) = 1;
  v7 = *(_BYTE *)(v4 + 38);
  if ( v7 == 2 )
  {
    *(_DWORD *)(a1 + 108) = 30;
  }
  else if ( v7 == 4 )
  {
    *(_DWORD *)(a1 + 108) = 360;
  }
  else
  {
    v8 = 180;
    if ( !*(_BYTE *)(a1 + 119) )
      v8 = 60;
    *(_DWORD *)(a1 + 108) = v8;
  }
  if ( *(_BYTE *)(a1 + 119) )
  {
    v9 = 10;
  }
  else
  {
    v9 = 120;
    if ( (*(_BYTE *)(v4 + 45) & 1) == 0 )
      v9 = 10;
  }
  *(_DWORD *)(a1 + 112) = v9;
  v10 = *(_DWORD *)(v4 + 28);
  v11 = *v5;
  if ( !v10 )
    v10 = v5[1];
  v12 = *(_DWORD *)(v4 + 24);
  v13 = Component__Excel__ExcelRow__ResolveStringColumnIndirection((void *)v4);
  sub_140089880((void **)(a1 + 128), v13, v14);
  v15 = Component__Excel__ExcelRow__ResolveStringColumnIndirection((void *)(v4 + 4));
  sub_140089880((void **)(a1 + 232), v15, v16);
  x = 0.0;
  y = 0.0;
  if ( !v12 )
    v12 = v11;
  z = 0.0;
  *(_DWORD *)(a1 + 336) = v12;
  *(_BYTE *)(a1 + 340) = *(_BYTE *)(v4 + 40);
  v20 = *(_DWORD *)(v4 + 8);
  if ( v20 )
  {
    LayoutInstanceStatic = Client__LayoutEngine__LayoutWorld__GetLayoutInstanceStatic(0x2Du, v20, 0);
    if ( LayoutInstanceStatic )
    {
      v22 = (float *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)LayoutInstanceStatic + 512LL))(LayoutInstanceStatic);
      x = *v22;
      y = v22[1];
      z = v22[2];
    }
  }
  else
  {
    x = (float)*(__int16 *)(v4 + 32);
    y = (float)*(__int16 *)(v4 + 34);
    z = (float)*(__int16 *)(v4 + 36);
  }
  v23 = Client__Game__UI__MapMarkerData__SetData(
          self,
          0,
          (void *)(a1 + 128),
          v10,
          x,
          y,
          z,
          0.0,
          territoryTypeId,
          0,
          0,
          0,
          0,
          255);
  *(_OWORD *)(a1 + 368) = *v23;
  *(_OWORD *)(a1 + 384) = v23[1];
  *(_OWORD *)(a1 + 400) = v23[2];
  *(_OWORD *)(a1 + 416) = v23[3];
  v24 = v23[4];
  result = *(unsigned __int16 *)(a1 + 116);
  *(_BYTE *)(a1 + 461) |= 1u;
  *(_OWORD *)(a1 + 432) = v24;
  *(_BYTE *)(a1 + 438) = 2;
  *(_WORD *)(a1 + 436) = result;
  return result;
}
