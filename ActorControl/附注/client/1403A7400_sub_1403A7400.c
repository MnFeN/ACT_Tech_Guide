__int64 __fastcall sub_1403A7400(__int64 a1, __int64 a2, int a3, char *a4, unsigned int a5)
{
  __int64 v8; // r8
  __int64 v9; // r12
  __int64 v10; // r9
  unsigned int *v11; // rdx
  char *v12; // rsi
  unsigned int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // eax
  __int64 v17; // rbx
  char *v18; // rdi
  unsigned int v19; // r14d
  unsigned int v20; // ebp
  char *v21; // rsi
  _BYTE *v22; // rdi
  int v23; // eax
  char v24; // al
  unsigned int v25; // ecx
  __int64 v26; // rax
  __int64 v27; // rcx
  unsigned int *v28; // rbx
  __int64 v29; // rbx
  char *v30; // rdi
  unsigned int v31; // r14d
  unsigned int v32; // ebp
  char *v33; // rsi
  _BYTE *v34; // rdi
  int v35; // eax
  int v36; // ecx
  unsigned int v37; // ecx
  __int64 v38; // rax
  __int64 v39; // rdi
  char *v40; // rbx
  unsigned int v41; // r14d
  unsigned int v42; // ebp
  char *v43; // rsi
  _BYTE *v44; // rbx
  int v45; // eax
  unsigned int v46; // ecx
  __int64 v47; // rax
  __int64 v48; // rcx
  __int64 v49; // rcx
  int v50; // ecx
  int v51; // ecx
  unsigned int v52; // eax
  unsigned int v53; // eax
  __int64 v54; // rcx
  __int64 v55; // rcx
  __int64 v56; // rcx
  __int64 v57; // rcx
  __int64 v58; // rcx
  __int64 v59; // rcx
  unsigned int v60; // eax
  unsigned int v61; // eax
  char v62; // cl
  unsigned int v63; // r14d
  unsigned int v64; // ebp
  _BYTE *v65; // rsi
  char *v66; // rbx
  _DWORD *v67; // rdi
  _BYTE *v68; // rbx
  int v69; // ecx
  int v70; // ecx
  __int64 v71; // rax
  unsigned int v72; // r10d
  unsigned int v73; // r9d
  __int64 v74; // r8
  char *j; // rdx
  char *v76; // rcx
  _BYTE *v77; // rdx
  int v78; // eax
  __int64 v79; // rax
  unsigned int v80; // r10d
  unsigned int v81; // r8d
  _BYTE *v82; // r9
  char *v83; // rdx
  char *v84; // rcx
  _BYTE *v85; // rdx
  __int64 v86; // rax
  unsigned int v87; // r14d
  unsigned int v88; // ebp
  __int64 v89; // rsi
  int *v90; // rdi
  char *v91; // rbx
  int v92; // eax
  int v93; // ecx
  __int64 v94; // rax
  unsigned int v95; // r10d
  unsigned int v96; // r8d
  _BYTE *v97; // r9
  char *v98; // rdx
  char *v99; // rcx
  _BYTE *v100; // rdx
  __int64 v101; // rax
  unsigned int v102; // r10d
  unsigned int v103; // r9d
  __int64 v104; // r8
  char *v105; // rdx
  char *v106; // rcx
  int *v107; // rdx
  __int64 v108; // rax
  unsigned int v109; // r10d
  unsigned int v110; // r9d
  __int64 v111; // r8
  char *v112; // rdx
  char *v113; // rcx
  _DWORD *v114; // rdx
  __int64 v115; // rax
  unsigned int v116; // r14d
  char *v117; // rbx
  __int64 v118; // rdi
  unsigned int v119; // ebp
  char *v120; // rsi
  _BYTE *v121; // rbx
  int v122; // eax
  int v123; // eax
  int v124; // eax
  int v125; // eax
  int v126; // ecx
  __int64 v127; // rax
  unsigned int v128; // eax
  unsigned int v129; // eax
  char v130; // cl
  char v131; // al
  int v132; // eax
  __int64 v133; // rcx
  __int64 v134; // rcx
  __int64 v135; // rax
  unsigned int v136; // ecx
  _QWORD *v137; // rax
  unsigned int v138; // ecx
  _BYTE *v139; // rax
  unsigned int v140; // ecx
  __int64 v141; // rax
  __int64 v142; // rcx
  __int64 v143; // rcx
  __int64 v144; // rax
  unsigned int v145; // ecx
  _BYTE *v146; // rax
  __int64 v147; // rcx
  __int64 v148; // rcx
  __int64 v149; // rax
  unsigned int v150; // ecx
  __int64 v151; // rax
  unsigned int v152; // ecx
  __int64 v153; // rax
  unsigned int v154; // ecx
  __int64 v155; // rax
  unsigned int v156; // ecx
  __int64 v157; // rax
  __int64 v158; // rcx
  __int64 v159; // rcx
  __int64 v160; // rax
  __int64 v161; // rcx
  __int64 v162; // rcx
  __int64 v163; // rax
  __int64 v164; // rcx
  __int64 v165; // rcx
  __int64 v166; // rax
  void *v167; // rcx
  __int64 v168; // rcx
  int v169; // eax
  unsigned int v170; // eax
  unsigned int v171; // eax
  unsigned __int64 v172; // rax
  unsigned __int64 v173; // r8
  __int64 v174; // rax
  unsigned __int64 v175; // kr20_8
  bool v176; // cf
  int v177; // eax
  unsigned int v178; // eax
  _QWORD *v179; // rdx
  unsigned int v180; // ecx
  unsigned __int64 *v181; // rax
  _QWORD *v182; // rcx
  _QWORD *v183; // rax
  __int64 v184; // rax
  __int64 result; // rax
  float v186; // xmm1_4
  int i; // [rsp+30h] [rbp-68h]
  unsigned int v188; // [rsp+34h] [rbp-64h]
  unsigned int *v189; // [rsp+38h] [rbp-60h]
  char *v191; // [rsp+B8h] [rbp+20h]

  v8 = 0;
  v9 = a1;
  v10 = 0;
  v188 = 0;
  for ( i = 0; (unsigned int)v8 < a5; i = v8 )
  {
    v11 = (unsigned int *)a4;
    v12 = a4 + 8;
    v189 = v11;
    v191 = v12;
    v13 = *v11;
    if ( *v11 > 0x44775072 )
    {
      if ( v13 > 0x526F4F54 )
      {
        if ( v13 > 0x56525952 )
        {
          if ( v13 > 0x62466172 )
          {
            v28 = v11;
            switch ( v13 )
            {
              case 0x624E6561u:
                *(_BYTE *)(v9 + 42) = *(_BYTE *)(v9 + 42) & 0x7F | (*v12 << 7);
                break;
              case 0x62533131u:
                *(_BYTE *)(v9 + 43) ^= (*(_BYTE *)(v9 + 43) ^ (2 * *v12)) & 2;
                break;
              case 0x62534374u:
                *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (*v12 << 6)) & 0x40;
                break;
            }
            goto LABEL_413;
          }
          if ( v13 == 1648779634 )
          {
            v28 = v11;
            *(_BYTE *)(v9 + 43) ^= (*v12 ^ *(_BYTE *)(v9 + 43)) & 1;
            goto LABEL_413;
          }
          if ( v13 != 1448237650 )
          {
            v28 = v11;
            if ( v13 == 1648445031 )
            {
              *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (32 * *v12)) & 0x20;
            }
            else if ( v13 == 1648448589 )
            {
              *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (16 * *v12)) & 0x10;
            }
            goto LABEL_413;
          }
          v50 = v9 + 440;
          goto LABEL_98;
        }
        if ( v13 == 1448237394 )
        {
          v50 = v9 + 416;
          goto LABEL_98;
        }
        if ( v13 <= 0x556E6956 )
        {
          switch ( v13 )
          {
            case 0x556E6956u:
              v28 = v11;
              *(_BYTE *)(v9 + 39) = *v12;
              break;
            case 0x53685554u:
              v28 = v11;
              *(_BYTE *)(v9 + 36) = *v12;
              break;
            case 0x536D706Cu:
              if ( *(_BYTE *)a2 )
              {
                v167 = 0;
                *(_DWORD *)(a2 + 24) = ((*(_DWORD *)(a2 + 24) + 15) & 0xFFFFFFF0) + 224;
              }
              else
              {
                v168 = (*(_DWORD *)(a2 + 20) + 15) & 0xFFFFFFF0;
                v169 = v168 + 224;
                v167 = (void *)(*(_QWORD *)(a2 + 8) + v168);
                *(_DWORD *)(a2 + 20) = v169;
              }
              *(_QWORD *)(v9 + 536) = v167;
              Client__System__Memory__IMemorySpace__Memset(v167, 0, 0xDCu);
              v28 = v189;
              sub_14040ED50(*(_QWORD *)(v9 + 536), v12, v189[1]);
              LODWORD(v8) = i;
              break;
            default:
              v28 = v11;
              if ( v13 == 1431720020 )
                *(_BYTE *)(v9 + 41) = *(_BYTE *)(v9 + 41) & 0x3F | (*v12 << 6);
              break;
          }
          goto LABEL_413;
        }
        v170 = v13 - 1433817934;
        if ( v170 )
        {
          v171 = v170 - 38;
          if ( !v171 )
          {
            v188 = v10 + 1;
            sub_1403A5800(*(_DWORD *)(v9 + 464) + 112 * v10, a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          }
          if ( v171 == 14419166 )
          {
            v50 = v9 + 392;
            goto LABEL_98;
          }
          goto LABEL_297;
        }
        v172 = *v12;
        *(_BYTE *)(v9 + 30) = v172;
        if ( (char)v172 <= 0 )
          goto LABEL_297;
        v173 = v172;
        v175 = v172;
        v174 = 112 * v172;
        if ( !is_mul_ok(v175, 0x70u) )
          v174 = -1;
        v176 = __CFADD__(v174, 8);
        v177 = v174 + 8;
        if ( v176 )
          v177 = -1;
        v178 = (v177 + 7) & 0xFFFFFFF8;
        if ( *(_BYTE *)a2 )
        {
          *(_DWORD *)(a2 + 24) += v178;
          goto LABEL_389;
        }
        v180 = *(_DWORD *)(a2 + 20);
        *(_DWORD *)(a2 + 20) = v180 + v178;
        v181 = (unsigned __int64 *)(*(_QWORD *)(a2 + 8) + v180);
        if ( v181 )
        {
          v179 = v181 + 1;
          *v181 = v173;
          v182 = v181 + 1;
          v183 = v181 + 4;
          do
          {
            *((_DWORD *)v183 + 20) &= 0xFFFFFFF8;
            *v182 = 0;
            v182 += 14;
            *(v183 - 2) = &unk_142AA2778;
            *(v183 - 1) = &unk_142AA2778;
            *v183 = &unk_142AA2778;
            v183[1] = &unk_142AA2778;
            *((_WORD *)v183 + 8) = 0;
            *((_BYTE *)v183 + 18) = 0;
            v183[3] = &unk_142AA2778;
            v183[4] = &unk_142AA2778;
            v183[5] = &unk_142AA2778;
            v183[6] = &unk_142AA2778;
            *((_WORD *)v183 + 28) = 0;
            *((_BYTE *)v183 + 58) = 0;
            v183[8] = &unk_142AA2778;
            v183[9] = &unk_142AA2778;
            v183 += 14;
            --v173;
          }
          while ( v173 );
        }
        else
        {
LABEL_389:
          v179 = 0;
        }
        v28 = v189;
        LODWORD(v8) = i;
        *(_QWORD *)(v9 + 464) = v179;
        goto LABEL_413;
      }
      if ( v13 == 1383026516 )
      {
        v28 = v11;
        *(_BYTE *)(v9 + 26) = *v12;
        goto LABEL_413;
      }
      if ( v13 > 0x4C424152 )
      {
        if ( v13 <= 0x4E654564 )
        {
          if ( v13 == 1315259748 )
          {
            v28 = v11;
            *(_DWORD *)(v9 + 4) = *(_DWORD *)v12;
            goto LABEL_413;
          }
          if ( v13 == 1281975909 )
          {
            sub_14039E4E0(v9 + 44, a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          }
          if ( v13 != 1282426212 )
          {
            v28 = v11;
            if ( v13 == 1282429812 )
              *(_WORD *)(v9 + 20) = *(_WORD *)v12;
            goto LABEL_413;
          }
          *(_WORD *)(v9 + 22) = *(_WORD *)v12;
          goto LABEL_297;
        }
        if ( v13 == 1315263348 )
        {
          v28 = v11;
          *(_DWORD *)v9 = *(_DWORD *)v12;
          goto LABEL_413;
        }
        if ( v13 != 1349670484 )
        {
          if ( v13 == 1380074580 )
          {
            v131 = *v12;
            v28 = v11;
            *(_BYTE *)(v9 + 25) = *v12;
            if ( v131 < 0 )
              *(_BYTE *)(v9 + 25) = 10;
            goto LABEL_413;
          }
          goto LABEL_297;
        }
        v132 = *v12;
        *(_BYTE *)(v9 + 24) = v132;
        switch ( v132 )
        {
          case 1:
            if ( *(_BYTE *)a2 )
              goto LABEL_314;
            v136 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v136 + 8;
            v137 = (_QWORD *)(*(_QWORD *)(a2 + 8) + v136);
            if ( !v137 )
              goto LABEL_315;
            *v137 = 0;
            v28 = v11;
            *(_QWORD *)(v9 + 456) = v137;
            break;
          case 2:
            if ( *(_BYTE *)a2 )
              goto LABEL_314;
            v138 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v138 + 8;
            v139 = (_BYTE *)(*(_QWORD *)(a2 + 8) + v138);
            if ( !v139 )
              goto LABEL_315;
            *v139 = 0;
            v28 = v11;
            *(_QWORD *)(v9 + 456) = v139;
            break;
          case 3:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 256;
              goto LABEL_308;
            }
            v133 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v133 + 256;
            v134 = *(_QWORD *)(a2 + 8) + v133;
            if ( !v134 )
              goto LABEL_308;
            v135 = sub_1403A1140(v134, v11, v8, v10);
            LODWORD(v8) = i;
            v28 = v189;
            *(_QWORD *)(v9 + 456) = v135;
            break;
          case 4:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 48;
              *(_QWORD *)(v9 + 456) = 0;
              v28 = v11;
              break;
            }
            v140 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v140 + 48;
            v141 = *(_QWORD *)(a2 + 8) + v140;
            if ( !v141 )
              goto LABEL_315;
            *(_DWORD *)(v141 + 16) &= 0xFFFFFFF8;
            v28 = v11;
            *(_DWORD *)(v141 + 40) &= 0xFFFFFFF8;
            *(_QWORD *)v141 = &unk_142AA2778;
            *(_QWORD *)(v141 + 8) = &unk_142AA2778;
            *(_QWORD *)(v141 + 24) = &unk_142AA2778;
            *(_QWORD *)(v141 + 32) = &unk_142AA2778;
            *(_QWORD *)(v9 + 456) = v141;
            break;
          case 5:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 352;
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
              break;
            }
            v142 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v142 + 352;
            v143 = *(_QWORD *)(a2 + 8) + v142;
            if ( !v143 )
              goto LABEL_308;
            v144 = sub_1403A2550(v143, v11, v8, v10);
            LODWORD(v8) = i;
            v28 = v189;
            *(_QWORD *)(v9 + 456) = v144;
            break;
          case 6:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 864;
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
              break;
            }
            v147 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v147 + 864;
            v148 = *(_QWORD *)(a2 + 8) + v147;
            if ( !v148 )
              goto LABEL_308;
            v149 = sub_1403A1D10(v148, v11, v8, v10);
            LODWORD(v8) = i;
            v28 = v189;
            *(_QWORD *)(v9 + 456) = v149;
            break;
          case 8:
            if ( *(_BYTE *)a2 )
              goto LABEL_314;
            v150 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v150 + 8;
            v151 = *(_QWORD *)(a2 + 8) + v150;
            if ( !v151 )
              goto LABEL_315;
            *(_DWORD *)v151 = 1065353216;
            v28 = v11;
            *(_BYTE *)(v151 + 4) = 0;
            *(_QWORD *)(v9 + 456) = v151;
            break;
          case 9:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 24;
              *(_QWORD *)(v9 + 456) = 0;
              v28 = v11;
              break;
            }
            v152 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v152 + 24;
            v153 = *(_QWORD *)(a2 + 8) + v152;
            if ( !v153 )
              goto LABEL_315;
            *(_DWORD *)(v153 + 16) &= 0xFFFFFFF8;
            v28 = v11;
            *(_QWORD *)v153 = &unk_142AA2778;
            *(_QWORD *)(v153 + 8) = &unk_142AA2778;
            *(_QWORD *)(v9 + 456) = v153;
            break;
          case 10:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 24;
              *(_QWORD *)(v9 + 456) = 0;
              v28 = v11;
              break;
            }
            v154 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v154 + 24;
            v155 = *(_QWORD *)(a2 + 8) + v154;
            if ( !v155 )
              goto LABEL_315;
            *(_QWORD *)(v155 + 8) = 1065353216;
            *(_QWORD *)v155 = off_14215D2E8;
            v28 = v11;
            *(_BYTE *)(v155 + 16) = 0;
            *(_QWORD *)(v9 + 456) = v155;
            break;
          case 11:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 48;
              *(_QWORD *)(v9 + 456) = 0;
              v28 = v11;
              break;
            }
            v156 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v156 + 48;
            v157 = *(_QWORD *)(a2 + 8) + v156;
            if ( !v157 )
              goto LABEL_315;
            *(_DWORD *)(v157 + 24) &= 0xFFFFFFF8;
            *(_QWORD *)v157 = off_14215D2F0;
            v28 = v11;
            *(_QWORD *)(v157 + 8) = &unk_142AA2778;
            *(_QWORD *)(v157 + 16) = &unk_142AA2778;
            *(_DWORD *)(v157 + 32) = 1065353216;
            *(_QWORD *)(v157 + 36) = 1065353216;
            *(_BYTE *)(v157 + 44) = 0;
            *(_QWORD *)(v9 + 456) = v157;
            break;
          case 12:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 456;
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
              break;
            }
            v158 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v158 + 456;
            v159 = *(_QWORD *)(a2 + 8) + v158;
            if ( !v159 )
              goto LABEL_308;
            v160 = sub_1403A31F0(v159, v11, v8, v10);
            LODWORD(v8) = i;
            v28 = v189;
            *(_QWORD *)(v9 + 456) = v160;
            break;
          case 13:
            if ( *(_BYTE *)a2 )
            {
LABEL_314:
              *(_DWORD *)(a2 + 24) += 8;
LABEL_315:
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
              break;
            }
            v145 = *(_DWORD *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v145 + 8;
            v146 = (_BYTE *)(*(_QWORD *)(a2 + 8) + v145);
            if ( !v146 )
              goto LABEL_315;
            *v146 = -1;
            v28 = v11;
            *(_QWORD *)(v9 + 456) = v146;
            break;
          case 14:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 424;
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
              break;
            }
            v161 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v161 + 424;
            v162 = *(_QWORD *)(a2 + 8) + v161;
            if ( !v162 )
              goto LABEL_308;
            v163 = sub_1403A3830(v162, v11, v8, v10);
            LODWORD(v8) = i;
            v28 = v189;
            *(_QWORD *)(v9 + 456) = v163;
            break;
          case 15:
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 232;
              v28 = v11;
              *(_QWORD *)(v9 + 456) = 0;
            }
            else
            {
              v164 = *(unsigned int *)(a2 + 20);
              *(_DWORD *)(a2 + 20) = v164 + 232;
              v165 = *(_QWORD *)(a2 + 8) + v164;
              if ( v165 )
              {
                v166 = sub_1403A4AB0(v165, v11, v8, v10);
                LODWORD(v8) = i;
                v28 = v189;
                *(_QWORD *)(v9 + 456) = v166;
              }
              else
              {
LABEL_308:
                v28 = v11;
                *(_QWORD *)(v9 + 456) = 0;
              }
            }
            break;
          default:
            goto LABEL_297;
        }
      }
      else if ( v13 == 1279410514 )
      {
        v28 = v11;
        *(_BYTE *)(v9 + 34) = *v12;
      }
      else
      {
        if ( v13 <= 0x46614564 )
        {
          if ( v13 == 1180779876 )
          {
            v28 = v11;
            *(_DWORD *)(v9 + 12) = *(_DWORD *)v12;
          }
          else if ( v13 == 1164867156 )
          {
            v130 = *(_BYTE *)(v9 + 41);
            v28 = v11;
            if ( *(_DWORD *)v12 > 1u )
              *(_BYTE *)(v9 + 41) = v130 & 0xEF;
            else
              *(_BYTE *)(v9 + 41) = v130 ^ (v130 ^ (16 * *(_DWORD *)v12)) & 0x10;
          }
          else
          {
            v28 = v11;
            if ( v13 == 1165377874 )
            {
              *(_BYTE *)(v9 + 32) = *v12;
            }
            else if ( v13 == 1180779088 )
            {
              *(_BYTE *)(v9 + 35) = *v12;
            }
          }
          goto LABEL_413;
        }
        if ( v13 != 1180783476 )
        {
          if ( v13 != 1198678354 )
          {
            v28 = v11;
            if ( v13 == 1215914582 )
              *(_BYTE *)(v9 + 40) = *v12;
            goto LABEL_413;
          }
          v50 = v9 + 64;
          goto LABEL_98;
        }
        v28 = v11;
        *(_DWORD *)(v9 + 8) = *(_DWORD *)v12;
      }
    }
    else if ( v13 == 1148670066 )
    {
      v28 = v11;
      *(_BYTE *)(v9 + 31) = *v12;
    }
    else
    {
      if ( v13 <= 0x544334 )
      {
        if ( v13 == 5522228 )
        {
          if ( *(_BYTE *)a2 )
          {
            *(_DWORD *)(a2 + 24) += 8;
          }
          else
          {
            v59 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v59 + 8;
            v54 = *(_QWORD *)(a2 + 8) + v59;
            if ( v54 )
            {
              *(_WORD *)(v54 + 2) &= 0xFFF0u;
              *(_WORD *)v54 = 0;
              *(_BYTE *)(v54 + 4) = -1;
              *(_QWORD *)(v9 + 496) = v54;
              goto LABEL_123;
            }
          }
          LODWORD(v54) = 0;
          *(_QWORD *)(v9 + 496) = 0;
          goto LABEL_123;
        }
        if ( v13 <= 0x524D54 )
        {
          if ( v13 == 5393748 )
          {
            v28 = v11;
            *(_BYTE *)(v9 + 28) = *v12;
            goto LABEL_413;
          }
          if ( v13 <= 0x415273 )
          {
            if ( v13 != 4280947 )
            {
              v14 = v13 - 21572;
              if ( v14 )
              {
                v15 = v14 - 10;
                if ( v15 )
                {
                  v16 = v15 - 2;
                  if ( v16 )
                  {
                    if ( v16 == 2 )
                    {
                      if ( *(_BYTE *)a2 )
                      {
                        *(_DWORD *)(a2 + 24) += 16;
                      }
                      else
                      {
                        v25 = *(_DWORD *)(a2 + 20);
                        *(_DWORD *)(a2 + 20) = v25 + 16;
                        v17 = *(_QWORD *)(a2 + 8) + v25;
                        if ( v17 )
                        {
                          *(_WORD *)v17 = -256;
                          *(_QWORD *)(v17 + 8) = &unk_142AA2778;
                          goto LABEL_17;
                        }
                      }
                      v17 = 0;
LABEL_17:
                      *(_QWORD *)(v9 + 512) = v17;
                      v18 = v12;
                      v19 = v11[1];
                      v20 = 0;
                      if ( v19 )
                      {
                        while ( 1 )
                        {
                          v21 = v18;
                          v22 = v18 + 8;
                          v23 = *(_DWORD *)v21;
                          if ( *(_DWORD *)v21 > 0x54784E6Fu )
                          {
                            if ( v23 == 1648717409 )
                            {
                              v24 = (*(_BYTE *)v17 ^ *v22) & 1;
                              goto LABEL_33;
                            }
                            if ( v23 == 1649759043 )
                            {
                              v24 = (*(_BYTE *)v17 ^ (2 * *v22)) & 2;
                              goto LABEL_33;
                            }
                          }
                          else
                          {
                            switch ( v23 )
                            {
                              case 1417170543:
                                *(_BYTE *)(v17 + 1) = *v22;
                                break;
                              case 5523028:
                                *(_BYTE *)v17 = *(_BYTE *)v17 & 0x1F | (32 * *v22);
                                break;
                              case 1382118501:
                                sub_1403971D0(v17 + 8, a2, a3, (_DWORD)v22, *((_DWORD *)v21 + 1));
                                break;
                              case 1413694292:
                                v24 = (*(_BYTE *)v17 ^ (4 * *v22)) & 0x1C;
LABEL_33:
                                *(_BYTE *)v17 ^= v24;
                                break;
                            }
                          }
                          v26 = (*((_DWORD *)v21 + 1) + 3) & 0xFFFFFFFC;
                          v20 += v26 + 8;
                          v18 = &v22[v26];
                          if ( v20 >= v19 )
                          {
                            v12 = v191;
                            LODWORD(v8) = i;
                            break;
                          }
                        }
                      }
                      v27 = *(_QWORD *)(v17 + 8);
                      if ( (*(_DWORD *)v27 & 0x1FFFE00) == 0
                        || (*(_DWORD *)v27 & 0x1FFFE00) == 0x200 && *(float *)(v27 + 4) == 0.0 )
                      {
                        *(_BYTE *)(v17 + 1) = -1;
                      }
                      v28 = v189;
                      goto LABEL_413;
                    }
                    goto LABEL_297;
                  }
                  if ( *(_BYTE *)a2 )
                  {
                    *(_DWORD *)(a2 + 24) += 32;
                  }
                  else
                  {
                    v37 = *(_DWORD *)(a2 + 20);
                    *(_DWORD *)(a2 + 20) = v37 + 32;
                    v29 = *(_QWORD *)(a2 + 8) + v37;
                    if ( v29 )
                    {
                      *(_BYTE *)v29 &= 0xC0u;
                      *(_DWORD *)(v29 + 24) &= 0xFFFFFFF8;
                      *(_BYTE *)(v29 + 1) = -1;
                      *(_QWORD *)(v29 + 8) = &unk_142AA2778;
                      *(_QWORD *)(v29 + 16) = &unk_142AA2778;
LABEL_44:
                      *(_QWORD *)(v9 + 528) = v29;
                      v30 = v12;
                      v31 = v11[1];
                      v32 = 0;
                      if ( v31 )
                      {
                        while ( 1 )
                        {
                          v33 = v30;
                          v34 = v30 + 8;
                          v35 = *(_DWORD *)v33;
                          if ( *(_DWORD *)v33 > 0x504F6666u )
                          {
                            if ( v35 == 1417170543 )
                            {
                              *(_BYTE *)(v29 + 1) = *v34;
                            }
                            else if ( v35 == 1648717409 )
                            {
                              *(_BYTE *)v29 ^= (*(_BYTE *)v29 ^ *v34) & 1;
                            }
                            goto LABEL_61;
                          }
                          if ( v35 == 1347380838 )
                            break;
                          switch ( v35 )
                          {
                            case 5522004:
                              *(_BYTE *)v29 ^= (*(_BYTE *)v29 ^ (16 * *v34)) & 0x30;
                              break;
                            case 5523028:
                              *(_BYTE *)v29 ^= (*(_BYTE *)v29 ^ (2 * *v34)) & 0xE;
                              break;
                            case 1347380818:
                              v36 = v29 + 16;
LABEL_56:
                              sub_1403971D0(v36, a2, a3, (_DWORD)v34, *((_DWORD *)v33 + 1));
                              break;
                          }
LABEL_61:
                          v38 = (*((_DWORD *)v33 + 1) + 3) & 0xFFFFFFFC;
                          v32 += v38 + 8;
                          v30 = &v34[v38];
                          if ( v32 >= v31 )
                          {
                            v12 = v191;
                            v28 = v189;
                            LODWORD(v8) = i;
                            goto LABEL_413;
                          }
                        }
                        v36 = v29 + 8;
                        goto LABEL_56;
                      }
LABEL_412:
                      v28 = v11;
                      goto LABEL_413;
                    }
                  }
                  v29 = 0;
                  goto LABEL_44;
                }
                if ( *(_BYTE *)a2 )
                {
                  *(_DWORD *)(a2 + 24) += 16;
                }
                else
                {
                  v46 = *(_DWORD *)(a2 + 20);
                  *(_DWORD *)(a2 + 20) = v46 + 16;
                  v39 = *(_QWORD *)(a2 + 8) + v46;
                  if ( v39 )
                  {
                    *(_WORD *)v39 &= 0xF800u;
                    *(_BYTE *)(v39 + 2) = -1;
                    *(_QWORD *)(v39 + 8) = &unk_142AA2778;
LABEL_66:
                    *(_QWORD *)(v9 + 504) = v39;
                    v40 = v12;
                    v41 = v11[1];
                    v42 = 0;
                    if ( v41 )
                    {
                      do
                      {
                        v43 = v40;
                        v44 = v40 + 8;
                        v45 = *(_DWORD *)v43;
                        if ( *(_DWORD *)v43 > 0x54425654u )
                        {
                          switch ( v45 )
                          {
                            case 1417170543:
                              *(_BYTE *)(v39 + 2) = *v44;
                              break;
                            case 1433817934:
                              *(_WORD *)v39 = *(_WORD *)v39 & 0xFFF1 | (2 * (*v44 & 7));
                              break;
                            case 1648717409:
                              *(_WORD *)v39 = *(_WORD *)v39 & 0xFFFE | *v44 & 1;
                              break;
                          }
                        }
                        else
                        {
                          switch ( v45 )
                          {
                            case 1413633620:
                              *(_WORD *)v39 = *(_WORD *)v39 & 0xFF3F | ((*v44 & 3) << 6);
                              break;
                            case 5523028:
                              *(_WORD *)v39 = *(_WORD *)v39 & 0xF8FF | ((*v44 & 7) << 8);
                              break;
                            case 1313894263:
                              sub_1403971D0(v39 + 8, a2, a3, (_DWORD)v44, *((_DWORD *)v43 + 1));
                              break;
                            case 1413633364:
                              *(_WORD *)v39 = *(_WORD *)v39 & 0xFFCF | (16 * (*v44 & 3));
                              break;
                          }
                        }
                        v47 = (*((_DWORD *)v43 + 1) + 3) & 0xFFFFFFFC;
                        v42 += v47 + 8;
                        v40 = &v44[v47];
                      }
                      while ( v42 < v41 );
                      v9 = a1;
                      v12 = v191;
                      v28 = v189;
                      LODWORD(v8) = i;
                      goto LABEL_413;
                    }
                    goto LABEL_412;
                  }
                }
                v39 = 0;
                goto LABEL_66;
              }
              if ( *(_BYTE *)a2 )
              {
                *(_DWORD *)(a2 + 24) += 16;
              }
              else
              {
                v49 = *(unsigned int *)(a2 + 20);
                *(_DWORD *)(a2 + 20) = v49 + 16;
                v48 = *(_QWORD *)(a2 + 8) + v49;
                if ( v48 )
                {
                  *(_BYTE *)(v48 + 2) = -1;
                  *(_WORD *)v48 &= 0x8000u;
                  *(_QWORD *)(v48 + 8) = &unk_142AA2778;
                  goto LABEL_89;
                }
              }
              v48 = 0;
LABEL_89:
              *(_QWORD *)(v9 + 520) = v48;
              sub_1403A6C70(v48, a2, a3, (_DWORD)v12, v11[1]);
              LODWORD(v8) = i;
              v28 = v189;
              goto LABEL_413;
            }
            v50 = v9 + 80;
LABEL_98:
            sub_1403971D0(v50, a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          }
          switch ( v13 )
          {
            case 0x436F6Cu:
              sub_14039CAE0(v9 + 104, a2, a3, (_DWORD)v12, v11[1]);
              LODWORD(v8) = i;
              v28 = v189;
              goto LABEL_413;
            case 0x477261u:
              v50 = v9 + 56;
              goto LABEL_98;
            case 0x506F73u:
              v51 = v9 + 328;
              goto LABEL_108;
          }
LABEL_297:
          v28 = v11;
          goto LABEL_413;
        }
        if ( v13 <= 0x536854 )
        {
          switch ( v13 )
          {
            case 0x536854u:
              v28 = v11;
              *(_BYTE *)(v9 + 38) = *v12;
              goto LABEL_413;
            case 0x526F74u:
              v51 = v9 + 272;
              break;
            case 0x53636Cu:
              v51 = v9 + 216;
              break;
            default:
              v28 = v11;
              if ( v13 == 5466194 )
                *(_BYTE *)(v9 + 37) = *v12;
              goto LABEL_413;
          }
LABEL_108:
          sub_14039A680(v51, a2, a3, (_DWORD)v12, v11[1]);
          LODWORD(v8) = i;
          v28 = v189;
          goto LABEL_413;
        }
        v52 = v13 - 5522225;
        if ( v52 )
        {
          v53 = v52 - 1;
          if ( v53 )
          {
            if ( v53 != 1 )
              goto LABEL_297;
            if ( *(_BYTE *)a2 )
            {
              *(_DWORD *)(a2 + 24) += 8;
            }
            else
            {
              v55 = *(unsigned int *)(a2 + 20);
              *(_DWORD *)(a2 + 20) = v55 + 8;
              v54 = *(_QWORD *)(a2 + 8) + v55;
              if ( v54 )
              {
                *(_WORD *)(v54 + 2) &= 0xFFF0u;
                *(_WORD *)v54 = 0;
                *(_BYTE *)(v54 + 4) = -1;
                *(_QWORD *)(v9 + 488) = v54;
                goto LABEL_123;
              }
            }
            LODWORD(v54) = 0;
            *(_QWORD *)(v9 + 488) = 0;
LABEL_123:
            sub_1403A6430(v54, a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          }
          if ( *(_BYTE *)a2 )
          {
            *(_DWORD *)(a2 + 24) += 8;
          }
          else
          {
            v56 = *(unsigned int *)(a2 + 20);
            *(_DWORD *)(a2 + 20) = v56 + 8;
            v54 = *(_QWORD *)(a2 + 8) + v56;
            if ( v54 )
            {
              *(_WORD *)(v54 + 2) &= 0xFFF0u;
              *(_WORD *)v54 = 0;
              *(_BYTE *)(v54 + 4) = -1;
              goto LABEL_122;
            }
          }
          v54 = 0;
LABEL_122:
          *(_QWORD *)(v9 + 480) = v54;
          goto LABEL_123;
        }
        if ( *(_BYTE *)a2 )
        {
          *(_DWORD *)(a2 + 24) += 48;
        }
        else
        {
          v58 = *(unsigned int *)(a2 + 20);
          *(_DWORD *)(a2 + 20) = v58 + 48;
          v57 = *(_QWORD *)(a2 + 8) + v58;
          if ( v57 )
          {
            *(_WORD *)v57 = 0;
            *(_WORD *)(v57 + 2) &= 0xF000u;
            *(_DWORD *)(v57 + 40) &= 0xFFFFFFF8;
            *(_QWORD *)(v57 + 8) = 0;
            *(_DWORD *)(v57 + 16) = 0;
            *(_QWORD *)(v57 + 24) = &unk_142AA2778;
            *(_QWORD *)(v57 + 32) = &unk_142AA2778;
            goto LABEL_129;
          }
        }
        v57 = 0;
LABEL_129:
        *(_QWORD *)(v9 + 472) = v57;
        sub_1403A5F00(v57, a2, a3, (_DWORD)v12, v11[1]);
        LODWORD(v8) = i;
        v28 = v189;
        goto LABEL_413;
      }
      if ( v13 <= 0x444F5479 )
      {
        if ( v13 == 1146049657 )
        {
          v28 = v11;
          *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ *v12) & 1;
          goto LABEL_413;
        }
        if ( v13 > 0x41527352 )
        {
          v28 = v11;
          switch ( v13 )
          {
            case 0x43434F54u:
              *(_BYTE *)(v9 + 27) = *v12;
              break;
            case 0x436F6C6Cu:
              *(_BYTE *)(v9 + 41) ^= (*(_BYTE *)(v9 + 41) ^ *v12) & 0xF;
              break;
            case 0x43756C54u:
              *(_BYTE *)(v9 + 29) = *v12;
              break;
          }
          goto LABEL_413;
        }
        if ( v13 == 1095922514 )
        {
          v50 = v9 + 88;
          goto LABEL_98;
        }
        v60 = v13 - 5657176;
        if ( !v60 )
        {
          v50 = v9 + 384;
          goto LABEL_98;
        }
        v61 = v60 - 1;
        if ( !v61 )
        {
          v50 = v9 + 408;
          goto LABEL_98;
        }
        if ( v61 == 1 )
        {
          v50 = v9 + 432;
          goto LABEL_98;
        }
        goto LABEL_297;
      }
      if ( v13 > 0x44704F66 )
      {
        v28 = v11;
        v128 = v13 - 1148404852;
        if ( v128 )
        {
          v129 = v128 - 3;
          if ( v129 )
          {
            if ( v129 == 3833 )
              *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (8 * *v12)) & 8;
          }
          else
          {
            *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (4 * *v12)) & 4;
          }
        }
        else
        {
          *(_BYTE *)(v9 + 42) ^= (*(_BYTE *)(v9 + 42) ^ (2 * *v12)) & 2;
        }
        goto LABEL_413;
      }
      if ( v13 != 1148211046 )
      {
        if ( v13 != 1147237473 )
        {
          if ( v13 == 1147761236 )
          {
            v62 = *(_BYTE *)(v9 + 41);
            v28 = v11;
            if ( *(_DWORD *)v12 > 1u )
              *(_BYTE *)(v9 + 41) = v62 & 0xDF;
            else
              *(_BYTE *)(v9 + 41) = v62 ^ (v62 ^ (32 * *(_DWORD *)v12)) & 0x20;
          }
          else
          {
            v28 = v11;
            if ( v13 == 1147945298 )
              *(_BYTE *)(v9 + 33) = *v12;
          }
          goto LABEL_413;
        }
        switch ( *(_BYTE *)(v9 + 24) )
        {
          case 1:
            v72 = v11[1];
            v73 = 0;
            v74 = *(_QWORD *)(v9 + 456);
            for ( j = v12; v73 < v72; j = &v77[v79] )
            {
              v76 = j;
              v77 = j + 8;
              v78 = *(_DWORD *)v76;
              if ( *(_DWORD *)v76 == 6442326 )
              {
                *(_BYTE *)v74 = *v77;
              }
              else
              {
                switch ( v78 )
                {
                  case 1131302758:
                    *(_DWORD *)(v74 + 4) = *(_DWORD *)v77;
                    break;
                  case 1281848404:
                    *(_BYTE *)(v74 + 3) = *v77;
                    break;
                  case 1649174388:
                    *(_BYTE *)(v74 + 2) = *v77;
                    break;
                  case 1649176419:
                    *(_BYTE *)(v74 + 1) = *v77;
                    break;
                }
              }
              v79 = (*((_DWORD *)v76 + 1) + 3) & 0xFFFFFFFC;
              v73 += v79 + 8;
            }
            goto LABEL_192;
          case 2:
            v80 = v11[1];
            v81 = 0;
            v82 = *(_BYTE **)(v9 + 456);
            v83 = v12;
            if ( !v80 )
              goto LABEL_192;
            do
            {
              v84 = v83;
              v85 = v83 + 8;
              if ( *(_DWORD *)v84 == 1465218644 )
                *v82 = *v85;
              v86 = (*((_DWORD *)v84 + 1) + 3) & 0xFFFFFFFC;
              v81 += v86 + 8;
              v83 = &v85[v86];
            }
            while ( v81 < v80 );
            v28 = v189;
            LODWORD(v8) = i;
            goto LABEL_413;
          case 3:
            v63 = v11[1];
            v64 = 0;
            v65 = *(_BYTE **)(v9 + 456);
            v66 = v191;
            if ( !v63 )
              goto LABEL_411;
            while ( 1 )
            {
              v67 = v66;
              v68 = v66 + 8;
              if ( *v67 == 5006702 )
                break;
              if ( *v67 == 1131375682 )
              {
                v70 = (_DWORD)v65 + 32;
              }
              else
              {
                if ( *v67 != 1131375685 )
                {
                  if ( *v67 != 1281715794 )
                  {
                    if ( *v67 == 1282294612 )
                      *v65 = *v68;
                    goto LABEL_178;
                  }
                  v69 = (_DWORD)v65 + 16;
                  goto LABEL_177;
                }
                v70 = (_DWORD)v65 + 144;
              }
              sub_14039CAE0(v70, a2, a3, (_DWORD)v68, v67[1]);
LABEL_178:
              v71 = (v67[1] + 3) & 0xFFFFFFFC;
              v64 += v71 + 8;
              v66 = &v68[v71];
              if ( v64 >= v63 )
              {
                v12 = v191;
                v28 = v189;
                LODWORD(v8) = i;
                goto LABEL_413;
              }
            }
            v69 = (_DWORD)v65 + 8;
LABEL_177:
            sub_1403971D0(v69, a2, a3, (_DWORD)v68, v67[1]);
            goto LABEL_178;
          case 4:
            v87 = v11[1];
            v88 = 0;
            v89 = *(_QWORD *)(v9 + 456);
            v66 = v191;
            if ( !v87 )
            {
LABEL_411:
              v12 = v66;
              v28 = v11;
              goto LABEL_413;
            }
            while ( 1 )
            {
              v90 = (int *)v66;
              v91 = v66 + 8;
              v92 = *v90;
              if ( *v90 == 5006702 )
              {
                v93 = v89 + 24;
                goto LABEL_207;
              }
              if ( v92 == 5727348 )
              {
                v93 = v89;
                goto LABEL_207;
              }
              if ( v92 == 1281715794 )
                break;
              if ( v92 == 1466201170 )
              {
                v93 = v89 + 8;
LABEL_207:
                sub_1403971D0(v93, a2, a3, (_DWORD)v91, v90[1]);
              }
              v94 = (v90[1] + 3) & 0xFFFFFFFC;
              v88 += v94 + 8;
              v66 = &v91[v94];
              if ( v88 >= v87 )
              {
                v12 = v191;
                v28 = v189;
                LODWORD(v8) = i;
                goto LABEL_413;
              }
            }
            v93 = v89 + 32;
            goto LABEL_207;
          case 5:
            sub_1403A26A0(*(void **)(v9 + 456), v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 6:
            sub_1403A2020(*(_QWORD *)(v9 + 456), a2, a3, v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 8:
            v102 = v11[1];
            v103 = 0;
            v104 = *(_QWORD *)(v9 + 456);
            v105 = v12;
            if ( !v102 )
              goto LABEL_192;
            do
            {
              v106 = v105;
              v107 = (int *)(v105 + 8);
              if ( *(_DWORD *)v106 == 21331 )
              {
                if ( *v107 == 100 )
                  *(_DWORD *)v104 = 1065353216;
                else
                  *(float *)v104 = (float)*v107 / 100.0;
              }
              else if ( *(_DWORD *)v106 == 6442320 )
              {
                *(_BYTE *)(v104 + 4) = *v107 != 0;
              }
              v108 = (*((_DWORD *)v106 + 1) + 3) & 0xFFFFFFFC;
              v103 += v108 + 8;
              v105 = (char *)v107 + v108;
            }
            while ( v103 < v102 );
            v28 = v189;
            LODWORD(v8) = i;
            goto LABEL_413;
          case 9:
            sub_1403A16C0(*(_QWORD *)(v9 + 456), a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 0xA:
            v109 = v11[1];
            v110 = 0;
            v111 = *(_QWORD *)(v9 + 456);
            v112 = v12;
            if ( !v109 )
              goto LABEL_192;
            do
            {
              v113 = v112;
              v114 = v112 + 8;
              if ( *(_DWORD *)v113 == 21331 )
              {
                *(_DWORD *)(v111 + 8) = *v114;
              }
              else if ( *(_DWORD *)v113 == 1145328724 )
              {
                *(_DWORD *)(v111 + 12) = *v114;
              }
              v115 = (*((_DWORD *)v113 + 1) + 3) & 0xFFFFFFFC;
              v110 += v115 + 8;
              v112 = (char *)v114 + v115;
            }
            while ( v110 < v109 );
            v28 = v189;
            LODWORD(v8) = i;
            goto LABEL_413;
          case 0xB:
            sub_1403A2D80(*(_QWORD *)(v9 + 456), a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 0xC:
            sub_1403A3390(*(_QWORD *)(v9 + 456), a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 0xD:
            v95 = v11[1];
            v96 = 0;
            v97 = *(_BYTE **)(v9 + 456);
            v98 = v12;
            if ( v95 )
            {
              do
              {
                v99 = v98;
                v100 = v98 + 8;
                if ( *(_DWORD *)v99 == 5066319 )
                  *v97 = *v100;
                v101 = (*((_DWORD *)v99 + 1) + 3) & 0xFFFFFFFC;
                v96 += v101 + 8;
                v98 = &v100[v101];
              }
              while ( v96 < v95 );
              v28 = v189;
              LODWORD(v8) = i;
            }
            else
            {
LABEL_192:
              v28 = v189;
              LODWORD(v8) = i;
            }
            goto LABEL_413;
          case 0xE:
            sub_1403A39A0(*(_QWORD *)(v9 + 456), a2, a3, (_DWORD)v12, v11[1]);
            LODWORD(v8) = i;
            v28 = v189;
            goto LABEL_413;
          case 0xF:
            v116 = v11[1];
            v117 = v12;
            v118 = *(_QWORD *)(v9 + 456);
            v119 = 0;
            if ( !v116 )
              goto LABEL_412;
            break;
          default:
            goto LABEL_297;
        }
        while ( 2 )
        {
          v120 = v117;
          v121 = v117 + 8;
          v122 = *(_DWORD *)v120;
          if ( *(_DWORD *)v120 > 0x496E74u )
          {
            if ( v122 == 1162038608 )
            {
              v126 = v118 + 208;
            }
            else if ( v122 == 1164198743 )
            {
              v126 = v118 + 184;
            }
            else
            {
              if ( v122 != 1165127506 )
              {
                if ( v122 == 1649567094 )
                  *(_BYTE *)v118 = *v121 != 0;
                goto LABEL_258;
              }
              v126 = v118 + 16;
            }
          }
          else
          {
            if ( v122 != 4812404 )
            {
              v123 = v122 - 4346708;
              if ( v123 )
              {
                v124 = v123 - 131328;
                if ( v124 )
                {
                  v125 = v124 - 69615;
                  if ( v125 )
                  {
                    if ( v125 == 20 )
                    {
                      v126 = v118 + 40;
                      break;
                    }
                  }
                  else
                  {
                    sub_1403A4670(v118 + 88, a2, a3, (_DWORD)v121, *((_DWORD *)v120 + 1));
                  }
                }
                else
                {
                  *(_DWORD *)(v118 + 8) = *(_DWORD *)v121;
                }
              }
              else
              {
                *(_DWORD *)(v118 + 4) ^= (*(_DWORD *)(v118 + 4) ^ *(_DWORD *)v121) & 3;
              }
LABEL_258:
              v127 = (*((_DWORD *)v120 + 1) + 3) & 0xFFFFFFFC;
              v119 += v127 + 8;
              v117 = &v121[v127];
              if ( v119 >= v116 )
              {
                v12 = v191;
                v28 = v189;
                LODWORD(v8) = i;
                goto LABEL_413;
              }
              continue;
            }
            v126 = v118 + 64;
          }
          break;
        }
        sub_1403971D0(v126, a2, a3, (_DWORD)v121, *((_DWORD *)v120 + 1));
        goto LABEL_258;
      }
      v28 = v11;
      *(_DWORD *)(v9 + 16) = *(_DWORD *)v12;
    }
LABEL_413:
    v10 = v188;
    v184 = (v28[1] + 3) & 0xFFFFFFFC;
    v8 = (unsigned int)(v184 + 8 + v8);
    a4 = &v12[v184];
  }
  result = *(char *)(v9 + 24) - 1;
  switch ( *(_BYTE *)(v9 + 24) )
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 8:
    case 9:
    case 0xA:
    case 0xB:
    case 0xC:
      v186 = *(float *)(v9 + 16);
      if ( v186 >= -1.0 )
      {
        if ( v186 > 1.0 )
          *(_DWORD *)(v9 + 16) = 1065353216;
      }
      else
      {
        *(_DWORD *)(v9 + 16) = -1082130432;
      }
      break;
    default:
      result = (unsigned int)result;
      break;
  }
  return result;
}
