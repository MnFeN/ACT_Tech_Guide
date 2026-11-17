void __fastcall sub_1403F2C70(__int64 a1, char *a2, __int64 a3)
{
  char *v3; // r14
  __int64 v4; // rdx
  __int64 v5; // rbx
  __int64 v6; // r13
  float v7; // xmm6_4
  __int64 v8; // rcx
  int *v9; // rax
  __int64 v10; // rsi
  __int64 v11; // rdx
  __int64 v12; // r12
  float *v13; // rax
  float *v14; // rdi
  float v15; // xmm6_4
  float v16; // xmm8_4
  float v17; // xmm9_4
  float v18; // xmm2_4
  float v19; // xmm7_4
  signed int v20; // edx
  __int64 v21; // r9
  unsigned __int64 v22; // rcx
  float *v23; // r8
  int v24; // r10d
  float v25; // xmm11_4
  float v26; // xmm4_4
  float v27; // xmm5_4
  float v28; // xmm10_4
  float v29; // xmm2_4
  int v30; // eax
  float v31; // xmm2_4
  float v32; // xmm3_4
  float v33; // xmm1_4
  float v34; // xmm0_4
  float v35; // xmm2_4
  float v36; // xmm1_4
  float v37; // xmm2_4
  float v38; // xmm0_4
  float v39; // xmm3_4
  float v40; // xmm2_4
  float v41; // xmm1_4
  float v42; // xmm3_4
  float v43; // xmm0_4
  float v44; // xmm2_4
  float v45; // xmm1_4
  float v46; // xmm0_4
  float v47; // xmm3_4
  float *v48; // rcx
  __int64 v49; // rax
  float v50; // xmm6_4
  float v51; // xmm8_4
  float v52; // xmm9_4
  __m128i v53; // xmm2
  float v54; // xmm1_4
  float v55; // xmm0_4
  __int64 v56; // rdx
  float v57; // xmm1_4
  __int64 v58; // rcx
  unsigned int v59; // edi
  float *v60; // rdx
  float *v61; // r15
  float v62; // r12d
  __int64 v63; // rbx
  int v64; // r14d
  float *v65; // rcx
  float i; // xmm1_4
  float *v67; // rdx
  float v68; // xmm5_4
  float v69; // xmm2_4
  bool v70; // zf
  unsigned int v71; // edi
  int v72; // r12d
  float v73; // r15d
  _DWORD *v74; // r14
  __int64 v75; // rbx
  float *v76; // rcx
  float j; // xmm1_4
  __int64 v78; // r9
  float *v79; // rax
  float *v80; // rax
  __int64 v81; // rcx
  int v82; // edx
  int v83; // eax
  __int64 v84; // r8
  float v85; // xmm13_4
  float v86; // xmm4_4
  unsigned int v87; // r11d
  __int64 v88; // rsi
  __int64 v89; // r15
  float v90; // xmm3_4
  __int64 v91; // rdx
  __int64 v92; // rcx
  __int64 v93; // rdi
  char *v94; // r9
  char *v95; // r10
  __int64 v96; // rax
  float v97; // xmm2_4
  float v98; // xmm1_4
  char *v99; // r10
  float v100; // xmm2_4
  char *v101; // r9
  __int64 v102; // rax
  float v103; // xmm2_4
  float *v104; // rax
  float v105; // xmm6_4
  float v106; // xmm7_4
  unsigned int v107; // edi
  int v108; // r15d
  float v109; // xmm8_4
  float v110; // xmm9_4
  float v111; // xmm10_4
  float v112; // xmm11_4
  float v113; // xmm12_4
  float v114; // xmm13_4
  float *v115; // rsi
  float v116; // xmm1_4
  float v117; // xmm1_4
  __int64 v118; // rax
  float v119; // xmm0_4
  __int64 v120; // rdx
  __int64 v121; // rcx
  float v122; // xmm7_4
  float v123; // xmm8_4
  float v124; // xmm9_4
  float v125; // xmm10_4
  float v126; // xmm11_4
  float v127; // xmm12_4
  __int64 v128; // rcx
  __int64 v129; // rdi
  float v130; // xmm13_4
  __int64 v131; // rsi
  float *v132; // r15
  __int64 v133; // r12
  float *v134; // rax
  float v135; // xmm1_4
  float v136; // xmm1_4
  __int64 v137; // rax
  __int64 v138; // rdx
  float v139; // xmm0_4
  float v140; // xmm0_4
  __int64 v141; // rdx
  float v142; // xmm7_4
  unsigned int v143; // edi
  float v144; // xmm8_4
  float v145; // xmm9_4
  float v146; // xmm10_4
  float v147; // xmm11_4
  float v148; // xmm12_4
  float *v149; // rsi
  __int64 v150; // r15
  float *v151; // rax
  float v152; // xmm1_4
  float v153; // xmm1_4
  __int64 v154; // rax
  float v155; // xmm0_4
  __int64 v156; // rdx
  __int64 v157; // rcx
  __int64 v158; // rax
  float v159; // xmm7_4
  float v160; // xmm5_4
  float v161; // xmm8_4
  float v162; // xmm7_4
  float v163; // xmm9_4
  float v164; // xmm2_4
  float v165; // xmm0_4
  __int64 v166; // rsi
  int v167; // r15d
  __int64 v168; // r12
  __int64 v169; // rdi
  int v170; // r8d
  __int64 v171; // rdx
  __int64 v172; // rax
  __int64 v173; // rdx
  __int64 v174; // rax
  float v175; // xmm2_4
  float v176; // xmm5_4
  float v177; // xmm4_4
  float v178; // xmm1_4
  float v179; // xmm3_4
  float v180; // xmm0_4
  float v181; // xmm9_4
  float v182; // xmm7_4
  float v183; // xmm8_4
  float v184; // xmm2_4
  float v185; // xmm0_4
  __int64 v186; // rcx
  float v187; // xmm8_4
  float v188; // xmm9_4
  float v189; // xmm10_4
  float v190; // xmm8_4
  int v191; // r8d
  int v192; // edx
  int v193; // eax
  __int64 v194; // rdx
  __int64 v195; // rsi
  float v196; // xmm2_4
  float v197; // xmm4_4
  float v198; // xmm1_4
  float v199; // xmm3_4
  __int64 v200; // rdx
  unsigned __int8 v201; // [rsp+20h] [rbp-E0h]
  int v202; // [rsp+24h] [rbp-DCh]
  __int64 v203; // [rsp+28h] [rbp-D8h] BYREF
  float v204; // [rsp+30h] [rbp-D0h]
  float v205; // [rsp+34h] [rbp-CCh]
  float *v206; // [rsp+38h] [rbp-C8h]
  __int64 v207; // [rsp+40h] [rbp-C0h]
  __int64 v208; // [rsp+48h] [rbp-B8h]
  char *v209; // [rsp+50h] [rbp-B0h]
  _DWORD v210[2]; // [rsp+60h] [rbp-A0h] BYREF
  int v211; // [rsp+68h] [rbp-98h] BYREF
  float v212[253]; // [rsp+6Ch] [rbp-94h] BYREF

  v3 = a2;
  v209 = a2;
  v4 = *(_QWORD *)(a1 + 1072);
  v5 = a1;
  v208 = a1;
  v6 = *(int *)(v4 + 336);
  if ( (*(_BYTE *)(v4 + 296) & 8) != 0 || (*(_WORD *)(*(_QWORD *)(a1 + 504) + 1192LL) & 0x400) == 0 )
  {
    v201 = 0;
    sub_1403F86B0(a1);
    v4 = *(_QWORD *)(v5 + 1072);
  }
  else
  {
    v201 = 1;
  }
  v7 = 1.0;
  if ( (*(_DWORD *)(v4 + 296) & 0xF00) == 0 && *(_DWORD *)(v5 + 1132) == 3 )
    v7 = (float)((float)(*(float *)(v4 + 240) + *(float *)(v4 + 236)) + *(float *)(v4 + 244)) / 3.0;
  v8 = 64;
  v9 = &v211;
  v10 = 0;
  do
  {
    *((_QWORD *)v9 - 1) = 0;
    *(_QWORD *)v9 = 0;
    v9 += 4;
    --v8;
  }
  while ( v8 );
  v11 = *(_QWORD *)(v5 + 1072);
  v12 = v6;
  if ( (*(_BYTE *)(v11 + 296) & 4) == 0 )
  {
    sub_1403F6140(v5);
    sub_140408700(&v203, *(_QWORD *)(v5 + 1080), (unsigned int)v6);
    v56 = *(_QWORD *)(v5 + 1072);
    v57 = v205;
    if ( (*(_BYTE *)(v56 + 296) & 0x40) == 0 )
    {
      if ( *(float *)(v56 + 304) <= v205 )
        v57 = *(float *)(v56 + 304);
      v57 = v57 * v7;
    }
    if ( v57 < 0.000099999997 )
      goto LABEL_29;
    v58 = *(_QWORD *)(v56 + 360);
    v19 = fminf(*(float *)(*(_QWORD *)(v5 + 1080) + 16LL * ((int)v6 - 1) + 12), v57);
    if ( v58 )
    {
      v59 = 0;
      v61 = (float *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v58 + 40LL))(v58);
      if ( (int)v6 <= 0 )
        goto LABEL_46;
      v62 = v204;
      v63 = v203;
      v64 = 0;
      v206 = (float *)&v211;
      v207 = v6;
      do
      {
        v65 = (float *)(16 * v10 + v63 + 28);
        for ( i = (float)((float)v64 / (float)(v6 - 1)) * v19; i > *v65; ++v10 )
        {
          if ( SLODWORD(v62) < (int)v59 )
            break;
          v65 += 4;
          ++v59;
        }
        sub_14040D1A0(&v203, v60, v59, &v210[4 * v64]);
        v67 = v206;
        ++v64;
        v68 = (float)((float)((float)(*(v206 - 2) * v61[2]) + (float)(*(v206 - 1) * v61[5])) + (float)(*v206 * v61[8]))
            + v61[11];
        v69 = (float)((float)((float)(*(v206 - 2) * v61[1]) + (float)(*(v206 - 1) * v61[4])) + (float)(*v206 * v61[7]))
            + v61[10];
        *(v206 - 2) = (float)((float)((float)(*(v206 - 1) * v61[3]) + (float)(*(v206 - 2) * *v61))
                            + (float)(*v206 * v61[6]))
                    + v61[9];
        *v67 = v68;
        *(v67 - 1) = v69;
        v60 = v67 + 4;
        v70 = v207-- == 1;
        v206 = v60;
      }
      while ( !v70 );
    }
    else
    {
      v71 = 0;
      v72 = 0;
      if ( (int)v6 <= 0 )
      {
LABEL_45:
        v12 = v6;
        goto LABEL_46;
      }
      v73 = v204;
      v74 = v210;
      v75 = v203;
      do
      {
        v76 = (float *)(16 * v10 + v75 + 28);
        for ( j = (float)((float)v72 / (float)(v6 - 1)) * v19; j > *v76; ++v10 )
        {
          if ( SLODWORD(v73) < (int)v71 )
            break;
          v76 += 4;
          ++v71;
        }
        sub_14040D1A0(&v203, v56, v71, v74);
        ++v72;
        v74 += 4;
      }
      while ( v72 < (int)v6 );
    }
    v3 = v209;
    v5 = v208;
    goto LABEL_45;
  }
  LOBYTE(a3) = 1;
  sub_1403F79C0(v5, v11, a3);
  v13 = *(float **)(v5 + 1088);
  v14 = *(float **)(v5 + 1080);
  v15 = *v13 - *v14;
  v16 = v13[1] - v14[1];
  v17 = v13[2] - v14[2];
  v18 = (float)((float)(v16 * v16) + (float)(v15 * v15)) + (float)(v17 * v17);
  if ( v18 < 0.0 )
    v19 = sqrtf(v18);
  else
    v19 = fsqrt(v18);
  if ( v19 < 0.000099999997 )
  {
LABEL_29:
    Client__System__Memory__IMemorySpace__Memset(v3, 0, 96 * v6);
    return;
  }
  v20 = 0;
  v21 = 0;
  if ( v6 < 4 )
  {
    if ( (int)v6 <= 0 )
      goto LABEL_46;
    goto LABEL_21;
  }
  v22 = ((unsigned __int64)(v6 - 4) >> 2) + 1;
  v23 = (float *)&v211;
  v24 = 2;
  v25 = (float)(v6 - 1);
  v21 = 4 * v22;
  v26 = v15 / v19;
  v27 = v16 / v19;
  v28 = v17 / v19;
  do
  {
    v29 = (float)v20;
    v20 += 4;
    v30 = v24 + 1;
    v31 = (float)(v29 / v25) * v19;
    v32 = (float)((float)(v24 - 1) / v25) * v19;
    v33 = (float)(v31 * v26) + *v14;
    v34 = (float)(v31 * v27) + v14[1];
    v35 = (float)(v31 * v28) + v14[2];
    *(v23 - 2) = v33;
    *(v23 - 1) = v34;
    *v23 = v35;
    v36 = (float)(v32 * v26) + *v14;
    v37 = (float)v24;
    v24 += 4;
    v38 = (float)(v32 * v27) + v14[1];
    v39 = (float)(v32 * v28) + v14[2];
    v23[2] = v36;
    v23[3] = v38;
    v40 = (float)(v37 / v25) * v19;
    v23[4] = v39;
    v41 = (float)(v40 * v26) + *v14;
    v42 = (float)((float)v30 / v25) * v19;
    v43 = (float)(v40 * v27) + v14[1];
    v44 = (float)(v40 * v28) + v14[2];
    v23[6] = v41;
    v23[7] = v43;
    v23[8] = v44;
    v45 = (float)(v42 * v26) + *v14;
    v46 = (float)(v42 * v27) + v14[1];
    v47 = (float)(v42 * v28) + v14[2];
    v23[10] = v45;
    v23[11] = v46;
    v23[12] = v47;
    v23 += 16;
    --v22;
  }
  while ( v22 );
  if ( v21 < v6 )
  {
LABEL_21:
    v48 = &v212[4 * v21 - 1];
    v49 = v6 - v21;
    v50 = v15 / v19;
    v51 = v16 / v19;
    v52 = v17 / v19;
    do
    {
      v53 = _mm_cvtsi32_si128(v20++);
      *(float *)v53.m128i_i32 = (float)(_mm_cvtepi32_ps(v53).m128_f32[0] / (float)(v6 - 1)) * v19;
      v54 = (float)(*(float *)v53.m128i_i32 * v50) + *v14;
      v55 = (float)(*(float *)v53.m128i_i32 * v51) + v14[1];
      *(float *)v53.m128i_i32 = (float)(*(float *)v53.m128i_i32 * v52) + v14[2];
      *(v48 - 2) = v54;
      *(v48 - 1) = v55;
      *v48 = *(float *)v53.m128i_i32;
      v48 += 4;
      --v49;
    }
    while ( v49 );
  }
LABEL_46:
  v78 = v201;
  if ( !v201 )
  {
    *(float *)(*(_QWORD *)(v5 + 1072) + 324LL) = *(float *)(*(_QWORD *)(v5 + 1072) + 320LL)
                                               * *(float *)(*(_QWORD *)(v5 + 1072) + 324LL);
    *(float *)(*(_QWORD *)(v5 + 1072) + 332LL) = *(float *)(*(_QWORD *)(v5 + 1072) + 320LL)
                                               * *(float *)(*(_QWORD *)(v5 + 1072) + 332LL);
    v79 = (float *)(*(_QWORD *)(v5 + 1072) + 128LL);
    *v79 = *v79 * *(float *)(v5 + 208);
    v79[1] = *(float *)(v5 + 212) * v79[1];
    v79[2] = *(float *)(v5 + 216) * v79[2];
    v79[3] = *(float *)(v5 + 220) * v79[3];
    v80 = *(float **)(v5 + 1072);
    v80[40] = v80[40] * *(float *)(v5 + 208);
    v80[41] = *(float *)(v5 + 212) * v80[41];
    v80[42] = *(float *)(v5 + 216) * v80[42];
    v80[43] = *(float *)(v5 + 220) * v80[43];
  }
  v81 = *(_QWORD *)(v5 + 1072);
  v202 = v6 - 1;
  v82 = 0;
  v83 = *(_DWORD *)(v81 + 296);
  v84 = 1;
  v85 = 1.0 / (float)(v6 - 1);
  v86 = v85;
  if ( (v83 & 0x40) != 0 )
  {
    v86 = (float)(v85 * v19) / *(float *)(v81 + 304);
    if ( (v83 & 0x80u) != 0 )
    {
      v86 = -v86;
      v82 = 2 * v6 - 1;
      v84 = 0xFFFFFFFFLL;
    }
  }
  v87 = 0;
  if ( *(_DWORD *)(v81 + 356) )
  {
    v88 = v82;
    v89 = (int)v84;
    do
    {
      v90 = -0.5;
      if ( (int)v6 > 0 )
      {
        v91 = 32LL * v87;
        v84 = 48 * v89;
        v92 = v87 + 12 * v88;
        v93 = (unsigned int)v6;
        v94 = &v3[4 * v92 + 26];
        v95 = &v3[4 * v92 + 24];
        do
        {
          v96 = *(_QWORD *)(v5 + 1072);
          v97 = (float)((float)(v90 * *(float *)(v96 + v91 + 20)) - (float)(*(float *)(v96 + v91 + 16) * 0.5))
              + *(float *)(v96 + v91 + 28);
          v98 = v90;
          *(_WORD *)v95 = (int)(float)((float)((float)((float)(v90 * *(float *)(v96 + 32LL * v87 + 4))
                                                     - (float)(*(float *)(v96 + 32LL * v87) * 0.5))
                                             + *(float *)(v96 + 32LL * v87 + 12))
                                     * dword_1428B5E90[(*(_DWORD *)(v96 + 296) >> 20) & 3]);
          v99 = &v95[v84];
          LODWORD(v96) = (int)(float)(v97 * dword_1428B5E90[(*(_DWORD *)(*(_QWORD *)(v5 + 1072) + 296LL) >> 20) & 3]);
          v100 = v90;
          v90 = v90 + v86;
          *(_WORD *)v94 = v96;
          v101 = &v94[v84];
          v102 = *(_QWORD *)(v5 + 1072);
          v103 = (float)((float)(v100 * *(float *)(v102 + v91 + 20)) + (float)(*(float *)(v102 + v91 + 16) * 0.5))
               + *(float *)(v102 + v91 + 28);
          *(_WORD *)v99 = (int)(float)((float)((float)((float)(v98 * *(float *)(v102 + 32LL * v87 + 4))
                                                     + (float)(*(float *)(v102 + 32LL * v87) * 0.5))
                                             + *(float *)(v102 + 32LL * v87 + 12))
                                     * dword_1428B5E90[(*(_DWORD *)(v102 + 296) >> 20) & 3]);
          v95 = &v99[v84];
          *(_WORD *)v101 = (int)(float)(v103 * dword_1428B5E90[(*(_DWORD *)(*(_QWORD *)(v5 + 1072) + 296LL) >> 20) & 3]);
          v94 = &v101[v84];
          --v93;
        }
        while ( v93 );
        v81 = *(_QWORD *)(v5 + 1072);
      }
      ++v87;
    }
    while ( v87 < *(_DWORD *)(v81 + 356) );
    v78 = v201;
    v12 = v6;
  }
  if ( (*(_BYTE *)(v81 + 296) & 1) != 0 )
  {
    if ( !(_BYTE)v78 )
    {
      *(float *)(v81 + 328) = *(float *)(v81 + 320) * *(float *)(v81 + 328);
      v104 = (float *)(*(_QWORD *)(v5 + 1072) + 144LL);
      *v104 = *(float *)(v5 + 208) * *v104;
      v104[1] = *(float *)(v5 + 212) * v104[1];
      v104[2] = *(float *)(v5 + 216) * v104[2];
      v104[3] = *(float *)(v5 + 220) * v104[3];
      v81 = *(_QWORD *)(v5 + 1072);
    }
    v105 = 0.0;
    v106 = 0.0;
    v107 = 0;
    v108 = 0;
    v109 = *(float *)(v81 + 328) - *(float *)(v81 + 324);
    v110 = *(float *)(v81 + 144) - *(float *)(v81 + 128);
    v111 = *(float *)(v81 + 148) - *(float *)(v81 + 132);
    v112 = *(float *)(v81 + 152) - *(float *)(v81 + 136);
    v113 = *(float *)(v81 + 156) - *(float *)(v81 + 140);
    v114 = 1.0 / (float)*(int *)(v81 + 340);
    if ( *(int *)(v81 + 340) > 0 )
    {
      v115 = v212;
      do
      {
        v116 = (float)(v111 * v106) + *(float *)(v81 + 132);
        *(float *)&v203 = (float)(v110 * v106) + *(float *)(v81 + 128);
        *((float *)&v203 + 1) = v116;
        v117 = (float)(v113 * v106) + *(float *)(v81 + 140);
        v204 = (float)(v112 * v106) + *(float *)(v81 + 136);
        v205 = v117;
        v118 = sub_1403B01C0(v5, &v203, v84, v78);
        v119 = v106 * v109;
        v106 = v106 + v114;
        ++v108;
        *v115 = v119 + *(float *)(*(_QWORD *)(v5 + 1072) + 324LL);
        v120 = 6LL * v107;
        v121 = 3LL * (v107 + 1);
        v107 += 2;
        v115 += 4;
        *(_QWORD *)&v3[8 * v120 + 16] = v118;
        *(_QWORD *)&v3[16 * v121 + 16] = v118;
        v81 = *(_QWORD *)(v5 + 1072);
      }
      while ( v108 < *(_DWORD *)(v81 + 340) );
    }
    v122 = 0.0;
    v123 = *(float *)(v81 + 332) - *(float *)(v81 + 328);
    v124 = *(float *)(v81 + 160) - *(float *)(v81 + 144);
    v125 = *(float *)(v81 + 164) - *(float *)(v81 + 148);
    v126 = *(float *)(v81 + 168) - *(float *)(v81 + 152);
    v127 = *(float *)(v81 + 172) - *(float *)(v81 + 156);
    v128 = *(int *)(v81 + 340);
    v129 = (unsigned int)(2 * v128);
    v130 = 1.0 / (float)(v6 - v128 - 1);
    if ( v128 < v12 )
    {
      v131 = (unsigned int)(v129 + 1);
      v132 = &v212[4 * v128];
      v133 = v12 - v128;
      do
      {
        v134 = *(float **)(v5 + 1072);
        v135 = (float)(v125 * v122) + v134[37];
        *(float *)&v203 = (float)(v124 * v122) + v134[36];
        *((float *)&v203 + 1) = v135;
        v136 = (float)(v127 * v122) + v134[39];
        v204 = (float)(v126 * v122) + v134[38];
        v205 = v136;
        v137 = sub_1403B01C0(v5, &v203, v84, v78);
        v138 = 6 * v129;
        v139 = v122 * v123;
        v122 = v122 + v130;
        v129 = (unsigned int)(v129 + 2);
        v140 = v139 + *(float *)(*(_QWORD *)(v5 + 1072) + 328LL);
        *(_QWORD *)&v3[8 * v138 + 16] = v137;
        v141 = 6 * v131;
        v131 = (unsigned int)(v131 + 2);
        *v132 = v140;
        v132 += 4;
        *(_QWORD *)&v3[8 * v141 + 16] = v137;
        --v133;
      }
      while ( v133 );
    }
  }
  else
  {
    v105 = 0.0;
    v142 = 0.0;
    v143 = 0;
    v144 = *(float *)(v81 + 332) - *(float *)(v81 + 324);
    v145 = *(float *)(v81 + 160) - *(float *)(v81 + 128);
    v146 = *(float *)(v81 + 164) - *(float *)(v81 + 132);
    v147 = *(float *)(v81 + 168) - *(float *)(v81 + 136);
    v148 = *(float *)(v81 + 172) - *(float *)(v81 + 140);
    if ( v12 > 0 )
    {
      v149 = v212;
      v150 = v12;
      do
      {
        v151 = *(float **)(v5 + 1072);
        v152 = (float)(v146 * v142) + v151[33];
        *(float *)&v203 = (float)(v145 * v142) + v151[32];
        *((float *)&v203 + 1) = v152;
        v153 = (float)(v148 * v142) + v151[35];
        v204 = (float)(v147 * v142) + v151[34];
        v205 = v153;
        v154 = sub_1403B01C0(v5, &v203, v84, v78);
        v155 = v142 * v144;
        v142 = v142 + v85;
        *v149 = v155 + *(float *)(*(_QWORD *)(v5 + 1072) + 324LL);
        v156 = 6LL * v143;
        v157 = 3LL * (v143 + 1);
        v143 += 2;
        v149 += 4;
        *(_QWORD *)&v3[8 * v156 + 16] = v154;
        *(_QWORD *)&v3[16 * v157 + 16] = v154;
        --v150;
      }
      while ( v150 );
    }
  }
  v158 = *(_QWORD *)(v5 + 1072);
  v159 = 0.0;
  v160 = 0.0;
  if ( (unsigned __int8)HIBYTE(*(_WORD *)(v158 + 296)) >> 4 )
  {
    if ( (unsigned __int8)HIBYTE(*(_WORD *)(v158 + 296)) >> 4 != 1 )
    {
      if ( (unsigned __int8)HIBYTE(*(_WORD *)(v158 + 296)) >> 4 != 2 )
        goto LABEL_83;
      v161 = *(float *)(v5 + 36);
      v162 = *(float *)(v5 + 32);
      v163 = *(float *)(v5 + 40);
      v164 = (float)((float)(v162 * v162) + (float)(v161 * v161)) + (float)(v163 * v163);
      if ( v164 >= 0.0 )
        goto LABEL_80;
LABEL_81:
      v165 = sqrtf(v164);
      goto LABEL_82;
    }
    v161 = *(float *)(v5 + 24);
    v162 = *(float *)(v5 + 20);
    v163 = *(float *)(v5 + 28);
    v164 = (float)((float)(v162 * v162) + (float)(v161 * v161)) + (float)(v163 * v163);
    if ( v164 < 0.0 )
      goto LABEL_81;
  }
  else
  {
    v161 = *(float *)(v5 + 12);
    v162 = *(float *)(v5 + 8);
    v163 = *(float *)(v5 + 16);
    v164 = (float)((float)(v162 * v162) + (float)(v161 * v161)) + (float)(v163 * v163);
    if ( v164 < 0.0 )
      goto LABEL_81;
  }
LABEL_80:
  v165 = fsqrt(v164);
LABEL_82:
  v105 = (float)(1.0 / v165) * v162;
  v159 = (float)(1.0 / v165) * v161;
  v160 = (float)(1.0 / v165) * v163;
LABEL_83:
  v166 = 0;
  v167 = 0;
  if ( (int)v6 > 0 )
  {
    v168 = 0;
    do
    {
      v169 = *(_QWORD *)(v5 + 1072);
      v170 = *(_DWORD *)(v169 + 296);
      if ( (v170 & 0x10) == 0 )
      {
        v171 = 0;
        if ( v168 - 1 > -1 )
          v171 = v168 - 1;
        v172 = v6 - 1;
        v173 = 2 * v171;
        if ( v168 + 1 < v6 )
          v172 = v168 + 1;
        v174 = 2 * v172;
        v175 = v212[2 * v173 - 1] - v212[2 * v174 - 1];
        v176 = *(float *)&v210[2 * v173] - *(float *)&v210[2 * v174];
        v177 = *(float *)&v210[2 * v173 + 1] - *(float *)&v210[2 * v174 + 1];
        v178 = v212[4 * v168 - 1] - *(float *)(v169 + 256);
        v179 = *(float *)&v210[4 * v168] - *(float *)(v169 + 248);
        v180 = *(float *)&v210[4 * v168 + 1] - *(float *)(v169 + 252);
        v181 = (float)(v179 * v175) - (float)(v178 * v176);
        v182 = (float)(v178 * v177) - (float)(v180 * v175);
        v183 = (float)(v180 * v176) - (float)(v179 * v177);
        v184 = (float)((float)(v181 * v181) + (float)(v182 * v182)) + (float)(v183 * v183);
        if ( v184 < 0.0 )
        {
          v185 = sqrtf(v184);
          v170 = *(_DWORD *)(v169 + 296);
        }
        else
        {
          v185 = fsqrt(v184);
        }
        if ( v185 >= 0.0000099999997 )
        {
          v105 = (float)(1.0 / v185) * v182;
          v159 = (float)(1.0 / v185) * v181;
          v160 = (float)(1.0 / v185) * v183;
        }
        else
        {
          v105 = *(float *)&qword_142AA27C0;
          v159 = *((float *)&qword_142AA27C0 + 1);
          v160 = *(float *)&dword_142AA27C8;
        }
      }
      v186 = 2 * v168;
      v187 = v212[4 * v168];
      v188 = v187 * v105;
      v189 = v187 * v159;
      v190 = v187 * v160;
      if ( (v170 & 2) != 0 )
      {
        v191 = *(_DWORD *)(v169 + 344);
        v192 = v167;
        if ( v167 >= (int)v6 / 2 )
          v192 = v202;
        if ( v192 < v191 )
          v193 = 255 * v192 / v191;
        else
          LOBYTE(v193) = -1;
      }
      else
      {
        LOBYTE(v193) = -1;
      }
      --v202;
      *(_BYTE *)(v169 + 354) = v193;
      v194 = 6 * v166;
      v195 = (unsigned int)(v166 + 1);
      v196 = v212[4 * v168 - 1];
      v197 = *(float *)&v210[4 * v168] + v188;
      v198 = *(float *)&v210[4 * v168 + 1] - v189;
      ++v167;
      v199 = *(float *)&v210[4 * v168++ + 1] + v189;
      *(float *)&v3[8 * v194] = *(float *)&v210[2 * v186] - v188;
      *(float *)&v3[8 * v194 + 4] = v198;
      *(float *)&v3[8 * v194 + 8] = v196 - v190;
      *(_DWORD *)&v3[8 * v194 + 12] = *(_DWORD *)(*(_QWORD *)(v5 + 1072) + 300LL);
      *(_DWORD *)&v3[8 * v194 + 40] = *(_DWORD *)(*(_QWORD *)(v5 + 1072) + 352LL);
      v200 = 6 * v195;
      v166 = (unsigned int)(v195 + 1);
      *(float *)&v3[8 * v200] = v197;
      *(float *)&v3[8 * v200 + 4] = v199;
      *(float *)&v3[8 * v200 + 8] = v196 + v190;
      *(_DWORD *)&v3[8 * v200 + 12] = *(_DWORD *)(*(_QWORD *)(v5 + 1072) + 300LL);
      *(_DWORD *)&v3[8 * v200 + 40] = *(_DWORD *)(*(_QWORD *)(v5 + 1072) + 352LL);
    }
    while ( v167 < (int)v6 );
  }
}
