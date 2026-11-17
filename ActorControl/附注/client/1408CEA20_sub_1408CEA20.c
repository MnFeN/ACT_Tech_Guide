__int64 __fastcall sub_1408CEA20(__int64 a1, __int64 a2, char a3)
{
  __int64 v3; // rbx
  float v4; // xmm7_4
  float v5; // xmm0_4
  float v6; // xmm8_4
  unsigned int v7; // r14d
  float v8; // xmm9_4
  float v11; // xmm6_4
  int *v12; // r8
  float v13; // xmm6_4
  unsigned __int8 *v14; // rdx
  _QWORD *v15; // r10
  __int64 v16; // r11
  unsigned __int8 v17; // r9
  int v18; // ecx
  unsigned int v19; // eax
  _BYTE *v20; // rbx
  __int64 v21; // rbx
  __int64 v22; // rcx
  __int64 v23; // rax
  __int64 v24; // rcx
  __int64 v25; // rbx
  void *v26; // rax
  unsigned __int8 IsEntityIdInParty; // al
  _DWORD *v28; // rcx
  __int64 v29; // rax
  __int64 v30; // rbx
  void *v31; // rax
  char v32; // cl
  __int64 v33; // rax
  __int16 v34; // ax
  unsigned __int8 v35; // cl
  __int64 v36; // rdx
  float *v37; // rax
  void *Position; // rax
  int v39; // eax
  _QWORD *v40; // rax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  __int64 v44; // rcx
  char v45; // al
  __int64 v46; // rbx
  unsigned int v47; // eax
  const char *v48; // rdx
  __int64 v49; // rcx
  __int64 v50; // rbx
  unsigned int v51; // eax
  __int64 v52; // rbx
  unsigned int v53; // eax
  void *Director; // rax
  void *v55; // r15
  unsigned int v56; // r12d
  __int64 v57; // rbx
  char v58; // al
  __int64 v59; // rbx
  __int64 v60; // rax
  __int64 v61; // rcx
  __int64 v62; // rcx
  int v63; // eax
  __int64 v64; // r8
  __int64 v65; // r8
  __int64 v66; // r8
  __int64 v67; // rax
  __int64 v68; // rcx
  char v69; // al
  unsigned int v70; // ebx
  _OWORD *v71; // r15
  unsigned int v72; // r15d
  unsigned __int16 *v73; // r13
  __int64 v74; // rbx
  unsigned int v75; // r12d
  __int64 v76; // rax
  __int64 v77; // rax
  int v78; // eax
  unsigned int v79; // r8d
  char *v80; // r9
  char v81; // al
  __int64 v82; // rdx
  __int64 v83; // rbx
  unsigned int v84; // eax
  int v85; // eax
  __int64 v86; // rbx
  char v87; // al
  __int64 v88; // rax
  __int64 v89; // rax
  __int64 v90; // rax
  bool v91; // r15
  __int64 v92; // rax
  __int64 v93; // rcx
  __int64 v94; // rax
  int v95; // ecx
  __int64 v96; // rax
  __int64 v97; // rax
  int v98; // eax
  __int64 v99; // rax
  unsigned __int16 v100; // cx
  __int64 v101; // rax
  __int64 v102; // rbx
  __int16 v103; // r13
  __int64 v104; // r12
  __int64 v105; // rcx
  __int64 v106; // rcx
  __int64 v107; // rdx
  float *v108; // rax
  float *v109; // rbx
  float v110; // xmm6_4
  unsigned int v111; // eax
  __int64 v112; // rax
  unsigned int v113; // ecx
  __m128i v114; // xmm0
  void *v115; // rax
  __int64 v116; // rax
  __int64 v117; // rax
  __int64 v118; // rcx
  __int16 v119; // cx
  __int64 v120; // rax
  __int16 v121; // ax
  __int64 v122; // rax
  unsigned __int8 v123; // dl
  __int16 v124; // dx
  unsigned __int16 v125; // dx
  __int16 v126; // dx
  void *v127; // r15
  float *v128; // rbx
  float *v129; // rax
  float v130; // xmm0_4
  float v131; // xmm1_4
  float v132; // xmm0_4
  int v133; // eax
  unsigned __int8 v134; // dl
  int v135; // ecx
  __int64 v136; // rbx
  __int16 v137; // cx
  bool v138; // r12
  __int64 v139; // rax
  __int64 v140; // rax
  __int64 v141; // rax
  __int64 v142; // rax
  __int64 v143; // rax
  char v144; // cl
  void *UIModule; // rax
  __int64 v146; // rbx
  __int64 v147; // rax
  char v148; // al
  __int64 v149; // rcx
  __int64 v150; // rax
  __int64 v151; // rax
  char v152; // al
  __int64 v153; // rdx
  __int64 v154; // rax
  __int64 v155; // rax
  __int64 v156; // rax
  __int64 v157; // rax
  unsigned __int16 v158; // cx
  __int64 v159; // rax
  __int64 v160; // rax
  __int64 v161; // rax
  unsigned int buddyModelLegs[2]; // [rsp+58h] [rbp-A8h] BYREF
  unsigned __int8 buddyStain[8]; // [rsp+60h] [rbp-A0h] BYREF
  unsigned int buddyModelBody[2]; // [rsp+68h] [rbp-98h] BYREF
  _BYTE self[112]; // [rsp+70h] [rbp-90h] BYREF
  _OWORD modelId[5]; // [rsp+E0h] [rbp-20h] BYREF

  v3 = a2 + 548;
  v4 = *(float *)(a2 + 496);
  v5 = 0.0;
  v6 = *(float *)(a2 + 500);
  v7 = 0;
  v8 = *(float *)(a2 + 504);
  v11 = (float)*(unsigned __int16 *)(a2 + 98);
  v12 = (int *)(a2 + 508);
  memset(modelId, 0, sizeof(modelId));
  v13 = (float)((float)(v11 * 0.0095875263) * 0.0099999998) - 3.1415927;
  if ( a2 != -508 )
  {
    v14 = (unsigned __int8 *)(a2 + 548);
    v15 = modelId;
    v16 = 10;
    do
    {
      v17 = 0;
      if ( v3 )
        v17 = *v14;
      v18 = *v12;
      ++v14;
      v19 = HIWORD(*v12++);
      LOWORD(buddyModelLegs[0]) = v18;
      BYTE2(buddyModelLegs[0]) = v19;
      HIBYTE(buddyModelLegs[0]) = HIBYTE(v18);
      buddyModelLegs[1] = v17;
      *v15++ = *(_QWORD *)buddyModelLegs;
      --v16;
    }
    while ( v16 );
  }
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 144LL) = *(_BYTE *)(a2 + 113);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 145LL) = *(_BYTE *)(a2 + 114);
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9032LL) = *(_DWORD *)(a2 + 60);
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 6968LL) = *(unsigned __int16 *)(a2 + 96);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 465LL) = *(_BYTE *)(a2 + 117);
  Client__Game__Object__GameObject__SetEventId(*(void **)(a1 + 8), *(_DWORD *)(a2 + 64));
  sub_14089A730(*(_QWORD *)(a1 + 8), *(_WORD *)(a2 + 88));
  Client__Game__Object__GameObject__SetEventState(*(void **)(a1 + 8), *(_BYTE *)(a2 + 120));
  Client__Game__Object__GameObject__SetVisibility(*(void **)(a1 + 8), *(_BYTE *)(a2 + 121));
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 136LL) = *(_DWORD *)(a2 + 68);
  if ( (*(unsigned int (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 16LL))(*(_QWORD *)(a1 + 8)) == 1
    || (v20 = *(_BYTE **)(a1 + 8), (*(unsigned int (__fastcall **)(_BYTE *))(*(_QWORD *)v20 + 16LL))(v20) == 2)
    && v20[145] == 3 )
  {
    v25 = *(_QWORD *)(a1 + 8);
    v26 = Client__Game__Group__GroupManager__GetGroupWithCheck(&off_1428C27E0, 1u);
    IsEntityIdInParty = Client__Game__Group__GroupManager__Group__IsEntityIdInParty(
                          v26,
                          *(_DWORD *)(*(_QWORD *)(a1 + 8) + 120LL));
    *(_BYTE *)(v25 + 7394) &= ~1u;
    *(_BYTE *)(v25 + 7394) |= IsEntityIdInParty;
    if ( !IsEntityIdInParty )
    {
      v28 = *(_DWORD **)(v25 + 7384);
      if ( (v28[70] & 0x4000000) != 0 )
        (*(void (__fastcall **)(_DWORD *, __int64))(*(_QWORD *)v28 + 312LL))(v28, 26);
    }
    v29 = *(_QWORD *)(v25 + 7384);
    if ( *(_BYTE *)(v29 + 7056) >= 3u )
      *(_BYTE *)(v29 + 7056) = 2;
    v30 = *(_QWORD *)(a1 + 8);
    v31 = Client__Game__Group__GroupManager__GetGroupWithCheck(&off_1428C27E0, 1u);
    v32 = (2
         * Client__Game__Group__GroupManager__Group__IsEntityIdInAlliance(v31, *(_DWORD *)(*(_QWORD *)(a1 + 8) + 120LL)))
        | *(_BYTE *)(v30 + 7394) & 0xFD;
    v33 = *(_QWORD *)(v30 + 7384);
    *(_BYTE *)(v30 + 7394) = v32;
    if ( *(_BYTE *)(v33 + 7056) >= 3u )
      *(_BYTE *)(v33 + 7056) = 2;
  }
  else
  {
    v21 = *(_QWORD *)(a1 + 8);
    *(_BYTE *)(v21 + 7394) &= ~1u;
    v22 = *(_QWORD *)(v21 + 7384);
    if ( (*(_DWORD *)(v22 + 280) & 0x4000000) != 0 )
    {
      (*(void (__fastcall **)(__int64, __int64))(*(_QWORD *)v22 + 312LL))(v22, 26);
      v22 = *(_QWORD *)(v21 + 7384);
    }
    if ( *(_BYTE *)(v22 + 7056) >= 3u )
      *(_BYTE *)(v22 + 7056) = 2;
    v23 = *(_QWORD *)(a1 + 8);
    v24 = *(_QWORD *)(v23 + 7384);
    *(_BYTE *)(v23 + 7394) &= ~2u;
    if ( *(_BYTE *)(v24 + 7056) >= 3u )
      *(_BYTE *)(v24 + 7056) = 2;
  }
  sub_1408D3920(*(_QWORD *)(a1 + 8) + 6952LL);
  if ( *(_BYTE *)(a2 + 113) == 2 && *(_DWORD *)(a2 + 48) == 952 )
    v34 = 30178;
  else
    v34 = *(_WORD *)(a2 + 94);
  sub_14194D4C0(*(_QWORD *)(a1 + 8) + 7408LL, *(_QWORD *)(a1 + 8), v34, 0);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 6985LL) = *(_BYTE *)(a2 + 130);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 3312LL) = *(_BYTE *)(a2 + 131);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 6986LL) = *(_BYTE *)(a2 + 132);
  v35 = *(_BYTE *)(a2 + 133);
  v36 = *(_QWORD *)(a1 + 8);
  *(_BYTE *)(v36 + 3313) = v35 & 0xF;
  *(_BYTE *)(v36 + 3314) = v35 >> 4;
  Client__Game__Object__GameObject__SetPosition(*(void **)(a1 + 8), v4, v6, v8);
  v37 = *(float **)(a1 + 8);
  v37[4] = v4;
  v37[5] = v6;
  v37[6] = v8;
  v37[7] = 0.0;
  Client__Game__Object__GameObject__SetRotation(*(void **)(a1 + 8), v13);
  *(float *)(*(_QWORD *)(a1 + 8) + 32LL) = v13;
  if ( sub_140897A40(*(_QWORD *)(a1 + 8), 0, 0) )
  {
    sub_1406050A0((__int64)&word_142AA7678);
    Position = Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 8));
    sub_140754FB0((__int64)Position);
    LOBYTE(word_142AB29E6) = 1;
    byte_142AB29E8 = 1;
    sub_14182E250(&qword_142AB28C0);
  }
  v39 = *(_DWORD *)(a2 + 84);
  if ( (v39 & 0x20) != 0 )
  {
    (*(void (__fastcall **)(_QWORD, __int64))(**(_QWORD **)(a1 + 8) + 328LL))(*(_QWORD *)(a1 + 8), 10);
    v39 = *(_DWORD *)(a2 + 84);
  }
  if ( (v39 & 0x400000) != 0 )
    (*(void (__fastcall **)(_QWORD, __int64))(**(_QWORD **)(a1 + 8) + 328LL))(*(_QWORD *)(a1 + 8), 32);
  if ( (*(unsigned int (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 16LL))(*(_QWORD *)(a1 + 8)) == 2
    && *(_BYTE *)(a2 + 114) == 3 )
  {
    v40 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, *(_DWORD *)(a2 + 68));
    if ( v40 )
    {
      if ( v40[208] )
        (*(void (__fastcall **)(_QWORD, __int64))(**(_QWORD **)(a1 + 8) + 328LL))(*(_QWORD *)(a1 + 8), 18);
    }
  }
  v41 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 16LL))(*(_QWORD *)(a1 + 8)) - 1;
  if ( !v41 )
  {
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = 0;
    if ( (qword_142AA895B & 4) == 0 || sub_140897A40(*(_QWORD *)(a1 + 8), 0, 0) )
      goto LABEL_66;
    Client__System__String__Utf8String__Ctor(self);
    if ( (qword_142AA895B & 4) != 0 )
      sub_1408481B0(&qword_142AA8218, *(unsigned __int8 *)(a2 + 119), *(unsigned __int8 *)(a2 + 595), self);
    v59 = *(_QWORD *)(a1 + 8);
    v60 = sub_14008A350((__int64)self);
    sub_1408980F0(v59, v60);
    Client__System__String__Utf8String__Dtor(self);
    goto LABEL_68;
  }
  v42 = v41 - 1;
  if ( !v42 || (v43 = v42 - 1) == 0 )
  {
    v44 = *(unsigned int *)(a2 + 48);
    if ( (_DWORD)v44 != 882 )
    {
      v45 = *(_BYTE *)(a2 + 114);
      switch ( v45 )
      {
        case 3:
          *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = 0;
          v46 = *(_QWORD *)(a1 + 8);
          if ( *(_DWORD *)(a2 + 52) )
          {
            v47 = (*(__int64 (__fastcall **)(_QWORD))(*(_QWORD *)v46 + 16LL))(*(_QWORD *)(a1 + 8));
            v48 = sub_1400E0290(0, *(_DWORD *)(a2 + 52), v47, 1u);
            v49 = v46;
          }
          else
          {
            v49 = *(_QWORD *)(a1 + 8);
            v48 = (const char *)(a2 + 562);
          }
          goto LABEL_67;
        case 9:
          *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = *(_DWORD *)(a2 + 52);
LABEL_49:
          v50 = *(_QWORD *)(a1 + 8);
          v51 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v50 + 16LL))(v50);
          v48 = sub_1400E0290(0, *(_DWORD *)(a2 + 52), v51, 1u);
          v49 = v50;
          goto LABEL_67;
        case 7:
          *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = 0;
          v52 = *(_QWORD *)(a1 + 8);
          v53 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v52 + 24LL))(v52);
          v48 = sub_1400E0290(0, v53, 9u, 1u);
          v49 = v52;
          goto LABEL_67;
        case 6:
          *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = 0;
          sub_1408980F0(*(_QWORD *)(a1 + 8), &unk_142196385);
          Director = Client__Game__RaceChocoboManager__GetDirector(dword_142AF9270);
          v55 = Director;
          if ( !Director )
            goto LABEL_68;
          v56 = (char)sub_140E59350(Director, *(unsigned int *)(*(_QWORD *)(a1 + 8) + 120LL));
          if ( v56 >= (char)sub_140E592D0(v55) || (unsigned __int8)sub_140E593C0(v55, v56) != 1 )
            goto LABEL_68;
          v57 = *(_QWORD *)(a1 + 8);
          v48 = (const char *)sub_140E593F0(v55, v56);
          v49 = v57;
LABEL_67:
          sub_1408980F0(v49, v48);
          goto LABEL_68;
      }
      if ( !(unsigned __int8)sub_140E24C90(v44) )
      {
        v58 = sub_140E25150(*(unsigned int *)(a2 + 48));
        *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = *(_DWORD *)(a2 + 52);
        if ( v58 )
          goto LABEL_66;
        goto LABEL_49;
      }
    }
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = *(_DWORD *)(a2 + 52);
    goto LABEL_66;
  }
  if ( v43 == 7 )
  {
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9016LL) = 0;
LABEL_66:
    v49 = *(_QWORD *)(a1 + 8);
    v48 = (const char *)(a2 + 562);
    goto LABEL_67;
  }
LABEL_68:
  Client__Game__Character__Character__SetTargetId(*(void **)(a1 + 8), *(_QWORD *)a2);
  v61 = *(_QWORD *)(a1 + 8);
  *(_DWORD *)(v61 + 8960) = *(_DWORD *)(a2 + 620);
  *(_WORD *)(v61 + 8964) = *(_WORD *)(a2 + 624);
  *(_BYTE *)(v61 + 8966) = *(_BYTE *)(a2 + 626);
  *(_QWORD *)(*(_QWORD *)(a1 + 8) + 2384LL) = *(_QWORD *)(a2 + 8);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2392LL) = *(_BYTE *)(a2 + 116);
  v62 = *(_QWORD *)(a1 + 8);
  if ( !*(_BYTE *)(v62 + 8960) && !*(_QWORD *)(v62 + 2384) )
  {
    *(_QWORD *)(v62 + 2384) = -1;
    v62 = *(_QWORD *)(a1 + 8);
  }
  if ( sub_140897A40(v62, 0, 0) )
    qword_142AF8958 = *(_QWORD *)(a2 + 8);
  sub_14089E8B0(*(_QWORD *)(a1 + 8) + 416LL, *(unsigned __int8 *)(a2 + 119));
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 132LL) = *(_DWORD *)(a2 + 48);
  if ( *(_BYTE *)(a2 + 114) == 1 )
    goto LABEL_78;
  if ( *(_BYTE *)(a2 + 114) != 2 && *(_BYTE *)(a2 + 114) != 3 )
  {
    if ( *(_BYTE *)(a2 + 114) == 7 )
    {
      v63 = *(_DWORD *)(a2 + 68);
      goto LABEL_79;
    }
    if ( *(_BYTE *)(a2 + 114) != 11 )
      goto LABEL_80;
LABEL_78:
    v63 = *(_DWORD *)(a2 + 60);
LABEL_79:
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9028LL) = v63;
    goto LABEL_80;
  }
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9028LL) = *(_DWORD *)(a2 + 68);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 7400LL) |= 0x20u;
LABEL_80:
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 459LL) = *(_BYTE *)(a2 + 118);
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 428LL) = *(_DWORD *)(a2 + 80);
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 432LL) = *(_DWORD *)(a2 + 76);
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 436LL) = 0;
  *(_DWORD *)(*(_QWORD *)(a1 + 8) + 440LL) = 0;
  *(_WORD *)(*(_QWORD *)(a1 + 8) + 444LL) = 0;
  *(_WORD *)(*(_QWORD *)(a1 + 8) + 446LL) = 0;
  *(_WORD *)(*(_QWORD *)(a1 + 8) + 448LL) = 0;
  *(_WORD *)(*(_QWORD *)(a1 + 8) + 450LL) = 0;
  if ( *(_BYTE *)(EXD__ClassJob__Row_140834F60(*(unsigned __int8 *)(a2 + 119)) + 90) == 32 )
  {
    *(_WORD *)(*(_QWORD *)(a1 + 8) + 444LL) = *(_WORD *)(a2 + 90);
    *(_WORD *)(*(_QWORD *)(a1 + 8) + 446LL) = *(_WORD *)(a2 + 92);
  }
  else if ( *(_BYTE *)(EXD__ClassJob__Row_140834F60(*(unsigned __int8 *)(a2 + 119)) + 90) == 33 )
  {
    *(_WORD *)(*(_QWORD *)(a1 + 8) + 448LL) = *(_WORD *)(a2 + 90);
    *(_WORD *)(*(_QWORD *)(a1 + 8) + 450LL) = *(_WORD *)(a2 + 92);
  }
  else
  {
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 436LL) = *(unsigned __int16 *)(a2 + 90);
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + 440LL) = *(unsigned __int16 *)(a2 + 92);
  }
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 146LL) = *(_BYTE *)(a2 + 595);
  v64 = *(_QWORD *)(a2 + 16);
  if ( v64 )
    Client__Game__Character__DrawDataContainer__LoadWeapon(*(_QWORD *)(a1 + 8) + 1784LL, 0, v64, 0, 1, 0, 0, 0);
  v65 = *(_QWORD *)(a2 + 24);
  if ( v65 )
    Client__Game__Character__DrawDataContainer__LoadWeapon(*(_QWORD *)(a1 + 8) + 1784LL, 1u, v65, 0, 1, 0, 0, 0);
  v66 = *(_QWORD *)(a2 + 32);
  if ( v66 )
    Client__Game__Character__DrawDataContainer__LoadWeapon(*(_QWORD *)(a1 + 8) + 1784LL, 2u, v66, 0, 1, 0, 0, 0);
  sub_1408D19A0(a1, *(unsigned __int8 *)(a2 + 111), *(unsigned __int8 *)(a2 + 112), *(unsigned __int8 *)(a2 + 119));
  if ( *(_BYTE *)(a2 + 113) == 2 )
  {
    v67 = EXD__BNpcBase__Row_140835260(*(_DWORD *)(a2 + 48));
    if ( v67 )
    {
      v68 = *(_QWORD *)(a1 + 8);
      if ( *(_BYTE *)(v67 + 27) == 17 || *(_DWORD *)(v68 + 6968) == 480 )
      {
        *(_BYTE *)(v68 + 7400) |= 0x20u;
        v68 = *(_QWORD *)(a1 + 8);
      }
      if ( (*(_BYTE *)(v67 + 35) & 0x20) != 0 )
        *(_BYTE *)(v68 + 154) |= 4u;
    }
  }
  v69 = 0;
  if ( *(_BYTE *)(a2 + 111) != 10 )
    v69 = (*(_DWORD *)(a2 + 84) & 0x8000) != 0;
  sub_141814340(*(_QWORD *)(a1 + 8) + 496LL, v69);
  sub_141816C00(*(_QWORD *)(a1 + 8) + 496LL);
  v70 = 0;
  v71 = modelId;
  do
  {
    Client__Game__Character__DrawDataContainer__LoadEquipment((void *)(*(_QWORD *)(a1 + 8) + 1784LL), v70++, v71, 0);
    v71 = (_OWORD *)((char *)v71 + 8);
  }
  while ( v70 < 0xA );
  v72 = 0;
  v73 = (unsigned __int16 *)(a2 + 558);
  do
  {
    v74 = *(_QWORD *)(a1 + 8);
    v75 = *v73;
    *(_QWORD *)buddyStain = (__int16)v72;
    if ( *(_WORD *)(v74 + 2LL * (__int16)v72 + 2360) != (_WORD)v75 )
    {
      v76 = EXD__Glasses__Row_140836710(v75);
      if ( !v76
        || (v77 = EXD__GlassesStyle__Row_140836750(*(__int16 *)(v76 + 34))) == 0
        || (_WORD)v72 == *(_WORD *)(v77 + 50) )
      {
        *(_WORD *)(v74 + 2LL * *(_QWORD *)buddyStain + 2360) = v75;
        *(_BYTE *)(v74 + 2368) |= 1u;
      }
    }
    ++v72;
    ++v73;
  }
  while ( v72 < 2 );
  if ( *(_BYTE *)(a2 + 113) == 3 )
  {
    if ( (unsigned __int8)sub_140E24C90(*(unsigned int *)(a2 + 48))
      || (v78 = *(_DWORD *)(a2 + 48), v78 == 1016925)
      || v78 == 1048611 )
    {
      v79 = 0;
      v80 = (char *)(a2 + 594);
      do
      {
        v81 = *v80++;
        v82 = (unsigned __int8)v79++;
        *(_BYTE *)(v82 + *(_QWORD *)(a1 + 8) + 2328) = v81;
      }
      while ( v79 < 0x1A );
      *(_QWORD *)(*(_QWORD *)(a1 + 8) + 1800LL) = *(_QWORD *)(a2 + 16);
      *(_QWORD *)(*(_QWORD *)(a1 + 8) + 1912LL) = *(_QWORD *)(a2 + 24);
    }
  }
  if ( (*(_DWORD *)(a2 + 84) & 0x80000) != 0 )
  {
    v83 = *(_QWORD *)(a1 + 8);
    v84 = sub_14089E7C0(*(_QWORD *)(v83 + 2616) + 416LL);
    if ( (unsigned __int8)sub_140BC2FE0(v84) )
      *(_BYTE *)(v83 + 3315) |= 2u;
  }
  v85 = *(_DWORD *)(a2 + 84);
  if ( (v85 & 1) != 0 )
  {
    sub_1408BF1E0(*(_QWORD *)(a1 + 8) + 2608LL, 1, 0);
    v85 = *(_DWORD *)(a2 + 84);
  }
  if ( (v85 & 2) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 468LL) |= 2u;
    v85 = *(_DWORD *)(a2 + 84);
  }
  if ( (v85 & 0x40) != 0 )
  {
    v86 = *(_QWORD *)(a1 + 8);
    v87 = *(_BYTE *)(v86 + 2358);
    if ( (v87 & 1) == 0 )
    {
      *(_QWORD *)buddyStain = 0;
      *(_BYTE *)(v86 + 2358) = v87 | 1;
      v88 = *(_QWORD *)(v86 + 1792);
      v91 = 1;
      if ( *(_WORD *)(v88 + 452) )
      {
        v89 = *(_QWORD *)(v88 + 2528);
        if ( *(_WORD *)(v89 + 452) )
        {
          v90 = EXD__Transformation__Row_14083D180(*(unsigned __int16 *)(v89 + 452));
          if ( v90 )
          {
            if ( (*(_BYTE *)(v90 + 46) & 0xFB) != 0 )
              v91 = 0;
          }
        }
      }
      v92 = *(_QWORD *)(v86 + 1792);
      v93 = *(unsigned int *)(v92 + 2596);
      if ( (_DWORD)v93 )
      {
        if ( !*(_BYTE *)(v86 + 2358) )
        {
          v91 = 1;
          v94 = EXD__NpcEquip__Row_1408353E0(v93);
          if ( v94 )
          {
            v95 = *(_DWORD *)(v94 + 16);
            *(_QWORD *)buddyModelLegs = (unsigned __int16)v95;
            BYTE2(buddyModelLegs[0]) = BYTE2(v95);
            LOBYTE(v95) = *(_BYTE *)(v94 + 64);
            LOBYTE(buddyModelLegs[1]) = *(_BYTE *)(v94 + 74);
            HIBYTE(buddyModelLegs[0]) = v95;
            *(_QWORD *)buddyStain = *(_QWORD *)buddyModelLegs;
          }
        }
      }
      else
      {
        v96 = *(_QWORD *)(v92 + 2528);
        if ( *(_WORD *)(v96 + 452) )
          EXD__Transformation__Row_14083D180(*(unsigned __int16 *)(v96 + 452));
      }
      if ( (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(v86 + 1792) + 192LL))(*(_QWORD *)(v86 + 1792)) && v91 )
      {
        v97 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(v86 + 1792) + 192LL))(*(_QWORD *)(v86 + 1792));
        (*(void (__fastcall **)(__int64, _QWORD, unsigned __int8 *))(*(_QWORD *)v97 + 552LL))(v97, 0, buddyStain);
      }
    }
  }
  v98 = *(_DWORD *)(a2 + 84);
  if ( (v98 & 0x80u) != 0 )
  {
    Client__Game__Character__DrawDataContainer__HideWeapons((void *)(*(_QWORD *)(a1 + 8) + 1784LL), 1u);
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x100) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 7400LL) |= 0x80u;
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x200) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 7081LL) |= 1u;
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x400) != 0 )
  {
    (*(void (__fastcall **)(_QWORD, __int64))(**(_QWORD **)(a1 + 8) + 328LL))(*(_QWORD *)(a1 + 8), 16);
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x1000) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 7400LL) |= 2u;
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x2000) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 156LL) |= 4u;
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x40000) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 156LL) |= 0x20u;
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x4000) != 0 )
  {
    sub_141820490(*(_QWORD *)(a1 + 8) + 496LL);
    v98 = *(_DWORD *)(a2 + 84);
  }
  if ( (v98 & 0x20000) != 0 )
    (*(void (__fastcall **)(_QWORD, __int64))(**(_QWORD **)(a1 + 8) + 328LL))(*(_QWORD *)(a1 + 8), 14);
  if ( *(_BYTE *)(a2 + 111) == 2 )
  {
    v99 = *(_QWORD *)(a1 + 8);
    v100 = 67;
    if ( *(_BYTE *)(v99 + 3312) == 36 )
    {
      v100 = 7731;
    }
    else if ( (*(_BYTE *)(v99 + 3454) & 0x40) != 0 )
    {
      v100 = 73;
    }
    TimelineContainer_PlayResolvedActionTimeline(v99 + 2608, v100, 0, 0, 0);
  }
  sub_14089EFC0(*(_QWORD *)(a1 + 8) + 416LL, *(unsigned __int8 *)(a2 + 127));
  if ( !a3 )
  {
    v101 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 632LL))(*(_QWORD *)(a1 + 8));
    sub_1408A6D50(v101, a2 + 136);
  }
  v102 = *(_QWORD *)(a1 + 8);
  v103 = *(_WORD *)(a2 + 108);
  v104 = *(unsigned int *)(a2 + 72);
  if ( *(_WORD *)(v102 + 6696) == v103 && *(_QWORD *)(v102 + 6712) == v104 )
  {
    v105 = *(_QWORD *)(v102 + 6704);
    if ( v105 && *(_BYTE *)(v102 + 6698) != 15 )
      sub_140391580(v105, 0.15000001);
  }
  else
  {
    v106 = *(_QWORD *)(v102 + 6704);
    if ( v106 )
    {
      sub_140391030(v106, 1);
      sub_140391940(*(_QWORD *)(v102 + 6704), 0);
      *(_QWORD *)(v102 + 6704) = 0;
    }
  }
  v107 = *(_QWORD *)(v102 + 6544);
  *(_WORD *)(v102 + 6696) = v103;
  *(_QWORD *)(v102 + 6712) = v104;
  *(_BYTE *)(v102 + 6698) = 15;
  nullsub_102((__int64)&unk_142AAB775, v107, 0, v102 + 6696);
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 469LL) = *(_BYTE *)(a2 + 122);
  *(_QWORD *)(*(_QWORD *)(a1 + 8) + 472LL) = *(_QWORD *)(a2 + 40);
  (*(void (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 272LL))(*(_QWORD *)(a1 + 8));
  if ( *(_BYTE *)(a2 + 113) == 1 )
    goto LABEL_204;
  if ( *(_BYTE *)(a2 + 113) != 2 )
  {
    if ( *(_BYTE *)(a2 + 113) == 3 )
    {
      sub_1408D08D0(a1, *(_DWORD *)(a2 + 48));
      goto LABEL_207;
    }
    if ( *(_BYTE *)(a2 + 113) != 10 )
    {
      *(_BYTE *)(*(_QWORD *)(a1 + 8) + 463LL) = 1;
      sub_1408D0270(a1, *(unsigned __int16 *)(a2 + 96), (__int128 *)(a2 + 594), modelId, (unsigned __int16 *)(a2 + 558));
LABEL_206:
      sub_14089DA50(*(_QWORD *)(a1 + 8), 0);
      goto LABEL_207;
    }
LABEL_204:
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 463LL) = 1;
    sub_1408D0270(a1, *(unsigned __int16 *)(a2 + 96), (__int128 *)(a2 + 594), modelId, (unsigned __int16 *)(a2 + 558));
    v121 = *(unsigned __int8 *)(a2 + 115);
    if ( (_BYTE)v121 )
      *(_WORD *)(*(_QWORD *)(a1 + 8) + 6744LL) = v121;
    goto LABEL_206;
  }
  v108 = (float *)EXD__BNpcBase__Row_140835260(*(_DWORD *)(a2 + 48));
  v109 = v108;
  if ( v108 )
  {
    v110 = *v108;
    if ( *(_BYTE *)(a2 + 114) == 1 )
    {
      v115 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(
               &off_1428BC9F0,
               *(_DWORD *)(*(_QWORD *)(a1 + 8) + 9028LL));
      if ( !v115 )
      {
LABEL_193:
        *(_BYTE *)(*(_QWORD *)(a1 + 8) + 461LL) = *((_BYTE *)v109 + 27);
        *(float *)(*(_QWORD *)(a1 + 8) + 424LL) = v110;
        *(_BYTE *)(*(_QWORD *)(a1 + 8) + 468LL) ^= (*(_BYTE *)(*(_QWORD *)(a1 + 8) + 468LL)
                                                  ^ (4 * *((_BYTE *)v109 + 35)))
                                                 & 8;
        *(_BYTE *)(*(_QWORD *)(a1 + 8) + 9068LL) ^= (*(_BYTE *)(*(_QWORD *)(a1 + 8) + 9068LL)
                                                   ^ (8 * *((_BYTE *)v109 + 35)))
                                                  & 8;
        v116 = *(_QWORD *)(a1 + 8);
        if ( *(_BYTE *)(v116 + 461) == 14 )
          *(_BYTE *)(v116 + 3454) |= 8u;
        if ( *((_WORD *)v109 + 9) )
        {
          v117 = EXD__NpcEquip__Row_1408353E0(*((unsigned __int16 *)v109 + 9));
          if ( v117 )
          {
            *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL) ^= (*(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL)
                                                       ^ (16 * *(_BYTE *)(v117 + 84)))
                                                      & 0x10;
            *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL) ^= (*(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL)
                                                       ^ (16 * *(_BYTE *)(v117 + 84)))
                                                      & 0x20;
          }
        }
        v118 = *(_QWORD *)(a1 + 8);
        if ( *(_BYTE *)(v118 + 460) == 2 )
          sub_140606720(v118 + 2624, 48);
        goto LABEL_200;
      }
      v5 = sub_140898BA0(v115);
    }
    else
    {
      if ( *(_BYTE *)(a2 + 114) != 2 )
      {
        if ( *(_BYTE *)(a2 + 114) == 7 )
        {
          v111 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 24LL))(*(_QWORD *)(a1 + 8));
          v112 = EXD__Companion__Row_140836790(v111);
          v113 = *(unsigned __int8 *)(v112 + 42);
          if ( (_BYTE)v113 )
            v114 = _mm_cvtsi32_si128(v113);
          else
            v114 = _mm_cvtsi32_si128(*(unsigned __int8 *)(v112 + 32));
          v110 = (float)(_mm_cvtepi32_ps(v114).m128_f32[0] * v110) / 100.0;
        }
        goto LABEL_193;
      }
      sub_140B2C780(*(_QWORD *)(a1 + 8));
    }
    v110 = v5;
    goto LABEL_193;
  }
LABEL_200:
  *(_BYTE *)(*(_QWORD *)(a1 + 8) + 463LL) = 1;
  sub_1408D0270(a1, *(unsigned __int16 *)(a2 + 96), (__int128 *)(a2 + 594), modelId, (unsigned __int16 *)(a2 + 558));
  if ( v109 )
  {
    v119 = *((_WORD *)v109 + 10);
    if ( v119 )
      *(_WORD *)(*(_QWORD *)(a1 + 8) + 6744LL) = v119;
  }
  sub_14089DA50(*(_QWORD *)(a1 + 8), v109);
  v120 = sub_14196DA50();
  sub_14196DDB0(v120, *(_QWORD *)(a1 + 8), v109);
LABEL_207:
  v122 = *(_QWORD *)(a1 + 8);
  if ( (*(_BYTE *)(a2 + 84) & 8) != 0 )
  {
    *(_BYTE *)(v122 + 154) &= ~1u;
    v123 = 0;
  }
  else
  {
    *(_BYTE *)(v122 + 154) |= 1u;
    v123 = 1;
  }
  sub_140898020(*(_QWORD *)(a1 + 8), v123);
  if ( *(_WORD *)(a2 + 100) )
  {
    sub_140C217E0(buddyModelBody, 0, *(unsigned __int8 *)(a2 + 123));
    sub_140C217E0(buddyModelLegs, 1, *(unsigned __int8 *)(a2 + 124));
    sub_140C217E0(buddyStain, 2, *(unsigned __int8 *)(a2 + 125));
    Client__Game__Character__MountContainer__CreateAndSetupMount(
      (void *)(*(_QWORD *)(a1 + 8) + 1648LL),
      *(_WORD *)(a2 + 100),
      0,
      buddyModelBody[0],
      buddyModelLegs[0],
      buddyStain[0],
      *(_BYTE *)(a2 + 126),
      0);
  }
  v124 = *(_WORD *)(a2 + 102);
  if ( v124 )
    Client__Game__Character__CompanionContainer__SetupCompanion((void *)(*(_QWORD *)(a1 + 8) + 1752LL), v124, 0);
  v125 = *(_WORD *)(a2 + 104);
  if ( v125 )
    sub_1408AA090(*(_QWORD *)(a1 + 8) + 1752LL, v125, 0);
  v126 = *(_WORD *)(a2 + 106);
  if ( v126 )
  {
    Client__Game__Character__OrnamentContainer__SetupOrnament((void *)(*(_QWORD *)(a1 + 8) + 2400LL), v126, 3u);
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2468LL) = 0;
  }
  if ( (*(_BYTE *)(a2 + 84) & 0x10) != 0 && *(_BYTE *)(a2 + 114) == 3 )
  {
    if ( source )
    {
      v127 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(
               &off_1428BC9F0,
               *(_DWORD *)(a2 + 68));
      v128 = (float *)Client__Game__Object__GameObject__GetPosition(source);
      v129 = (float *)Client__Game__Object__GameObject__GetPosition(*(void **)(a1 + 8));
      if ( v127 )
      {
        v130 = v129[2] - v128[2];
        v131 = (float)((float)(*v129 - *v128) * (float)(*v129 - *v128)) + (float)(v130 * v130);
        v132 = v131 < 0.0 ? sqrtf(v131) : fsqrt(v131);
        if ( v132 <= 20.0 )
          Client__Game__BattleLog__AddActionLogMessage(0x52Fu, v127, *(void **)(a1 + 8), 0, 0, 0, 0, 0, 0, 100.0);
      }
    }
  }
  if ( (*(_BYTE *)(a2 + 84) & 4) != 0 )
    sub_140908E10(*(_QWORD *)(a1 + 8), 1);
  (*(void (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 112LL))(*(_QWORD *)(a1 + 8));
  (*(void (__fastcall **)(_QWORD, _QWORD))(**(_QWORD **)(a1 + 8) + 120LL))(
    *(_QWORD *)(a1 + 8),
    *(unsigned __int8 *)(*(_QWORD *)(a1 + 8) + 149LL));
  (*(void (__fastcall **)(_QWORD, _QWORD))(**(_QWORD **)(a1 + 8) + 128LL))(
    *(_QWORD *)(a1 + 8),
    *(unsigned __int8 *)(*(_QWORD *)(a1 + 8) + 150LL));
  v133 = *(_DWORD *)(a2 + 84);
  if ( (v133 & 0x800) != 0 )
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL) |= 0x10u;
    v133 = *(_DWORD *)(a2 + 84);
  }
  if ( (v133 & 0x100000) != 0 )
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + 2359LL) |= 0x20u;
  if ( sub_140897A40(*(_QWORD *)(a1 + 8), 0, 0) )
  {
    v134 = (*(_BYTE *)(*(_QWORD *)(a1 + 8) + 3454LL) & 0x40) != 0;
    if ( v134 != byte_142ADF3A0 )
    {
      Client__Game__UI__WeaponState__SetUnsheathed(&byte_142ADF3A0, v134, 0, 0);
      Client__Game__UI__WeaponState__ExtendAutoSheatheTimer(&byte_142ADF3A0);
    }
  }
  v135 = *(_DWORD *)(a2 + 84);
  if ( (v135 & 0x200000) != 0 )
  {
    do
    {
      v136 = *(_QWORD *)(a1 + 8) + 1784LL;
      v137 = *(_WORD *)(v136 + 2LL * (__int16)v7 + 580);
      if ( (v137 & 0x10) == 0 )
      {
        v138 = v137 != 0;
        *(_WORD *)(v136 + 2LL * (__int16)v7 + 580) = v137 | 0x10;
        v139 = *(_QWORD *)(v136 + 8);
        if ( !*(_WORD *)(v139 + 452)
          || (v140 = *(_QWORD *)(v139 + 2528), *(_WORD *)(v140 + 452))
          && (v141 = EXD__Transformation__Row_14083D180(*(unsigned __int16 *)(v140 + 452))) != 0
          && *(_BYTE *)(v141 + 46) == 5 )
        {
          if ( v138 != (*(_WORD *)(v136 + 2LL * (__int16)v7 + 580) != 0) )
            *(_BYTE *)(v136 + 584) |= 1u;
        }
      }
      ++v7;
    }
    while ( v7 < 2 );
    v135 = *(_DWORD *)(a2 + 84);
  }
  v142 = *(_QWORD *)(a1 + 8);
  *(_BYTE *)(v142 + 7400) &= ~2u;
  *(_BYTE *)(v142 + 7400) |= 2 * ((v135 & 0x1000) != 0);
  v143 = *(_QWORD *)(a1 + 8);
  v144 = *(_BYTE *)(v143 + 9060);
  if ( v144 == 3 || v144 == 11 )
  {
    sub_1408BBCE0(v143 + 2608);
    v143 = *(_QWORD *)(a1 + 8);
  }
  if ( (*(_DWORD *)(a2 + 84) & 0x10000) != 0 )
    *(_BYTE *)(v143 + 7400) |= 0x40u;
  UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
  v146 = *(_QWORD *)(a1 + 8);
  if ( UIModule
    && (v147 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 312LL))(UIModule),
        (unsigned __int8)sub_14077B420(v147, *(_QWORD *)(a1 + 8))) )
  {
    v148 = 4;
  }
  else
  {
    v148 = 0;
  }
  *(_BYTE *)(v146 + 7394) &= ~4u;
  *(_BYTE *)(v146 + 7394) |= v148;
  if ( (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 680LL))(*(_QWORD *)(a1 + 8)) )
  {
    if ( sub_1400E1C70() )
    {
      v150 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 680LL))(*(_QWORD *)(a1 + 8));
      sub_1419F8120(v150, *(unsigned __int8 *)(a2 + 128));
      v151 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 680LL))(*(_QWORD *)(a1 + 8));
      sub_1419F8150(v151, *(unsigned __int8 *)(a2 + 129));
    }
    else
    {
      LOBYTE(v149) = 1;
      v152 = sub_1400E1CB0(v149);
      v153 = **(_QWORD **)(a1 + 8);
      if ( v152 == 1 )
      {
        v154 = (*(__int64 (**)(void))(v153 + 680))();
        sub_1419F8180(v154, *(unsigned __int8 *)(a2 + 128));
      }
      else
      {
        v155 = (*(__int64 (**)(void))(v153 + 680))();
        sub_1419F81B0(v155, *(unsigned __int8 *)(a2 + 128));
        v156 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 8) + 680LL))(*(_QWORD *)(a1 + 8));
        sub_1419F81E0(v156, *(unsigned __int8 *)(a2 + 129));
      }
    }
  }
  if ( sub_140EA8B30() && *(_BYTE *)(sub_140EA8B30() + 6) )
  {
    v157 = sub_140EA8B30();
    sub_140EAA700(v157, *(_QWORD *)(a1 + 8));
  }
  if ( sub_140ECDB40() )
  {
    v158 = dword_142AAB790;
    if ( territoryTypeId )
      v158 = territoryTypeId;
    if ( sub_140ED1090(v158) )
    {
      v159 = sub_140ECDB40();
      sub_140ECDF10(v159, *(_DWORD **)(a1 + 8));
    }
  }
  if ( sub_14198E450() )
  {
    v160 = sub_14198E450();
    sub_14198E8F0(v160, *(_QWORD *)(a1 + 8));
  }
  v161 = sub_140E19000();
  return sub_140E19450(v161, *(_QWORD *)(a1 + 8), *(unsigned int *)(a2 + 60));
}
