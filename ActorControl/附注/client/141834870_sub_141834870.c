char __fastcall sub_141834870(__int64 a1)
{
  char v2; // di
  _DWORD *ConfigOption; // rax
  __int64 v4; // rdi
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  unsigned int v8; // eax
  void *v9; // rax
  __int64 ObjectByGameObjectId; // rax
  __int64 v11; // rdi
  __int64 v12; // rax
  char v13; // cl
  __int64 v14; // rdi
  float *v15; // rsi
  __int64 v16; // rax

  v2 = 0;
  if ( *(_BYTE *)(a1 + 1419) )
  {
    if ( source && (*(unsigned __int8 (__fastcall **)(float *))(*(_QWORD *)source + 464LL))(source) )
    {
      *(_BYTE *)(a1 + 1419) = 0;
    }
    else
    {
      v2 = sub_141836A30(a1);
      if ( v2 )
      {
        *(_BYTE *)(a1 + 1419) = 0;
        goto LABEL_28;
      }
    }
  }
  if ( Client__Game__Control__InputManager__GetInputStatus(&unk_1428B84C0, 118) )
    v2 = sub_141836A30(a1);
  if ( !v2 )
  {
    if ( Client__Game__Control__InputManager__GetInputStatus(&unk_1428B84C0, 111) )
    {
      ConfigOption = Common__Configuration__ConfigBase__GetConfigOption((char *)qword_142909910 + 16, 0xE1u);
      if ( !ConfigOption[6]
        || !ConfigOption[8]
        || (v4 = *(_QWORD *)(a1 + 48)) == 0
        || *(_BYTE *)(v4 + 1040) == 1
        || (unsigned int)(*(_DWORD *)(v4 + 208) - 2) > 2
        || *(_BYTE *)(v4 + 257) == 3
        || (sub_1418380B0(&qword_142AB28A8), *(_BYTE *)(v4 + 1040) != 1) )
      {
        if ( Client__Game__Conditions__HasPermission(byte_142AF9070, 0x3E9u, 0, 0) )
        {
          if ( Client__Game__Conditions__HasPermission(byte_142AF9070, 0x60u, 0, 0) )
          {
            if ( !*(_DWORD *)(a1 + 1408) && !*(_BYTE *)(a1 + 438) )
            {
              v5 = *(_QWORD *)(a1 + 48);
              if ( !v5 || (*(_BYTE *)(v5 + 1072) & 1) == 0 )
              {
                v6 = sub_140B777C0();
                if ( *(_QWORD *)(v6 + 18232) == 3758096384LL && !*(_DWORD *)(v6 + 18244) )
                {
                  v7 = sub_140B777C0();
                  v8 = sub_140B83E40(v7);
                  if ( !v8 || !byte_142AF9070[v8] || (unsigned __int8)sub_140E13C30(byte_142AF9070, 1001, v8) )
                    *(_BYTE *)(a1 + 80) = 1;
                }
              }
            }
          }
        }
      }
    }
  }
LABEL_28:
  v9 = (void *)sub_1400D2D70(qword_142909910);
  LOBYTE(ObjectByGameObjectId) = Client__System__Input__InputData__IsInputIdPressed(v9, 349);
  if ( (_BYTE)ObjectByGameObjectId
    || (unsigned __int8)sub_14061AE90(&unk_1428B84C0)
    && (!*(_BYTE *)(a1 + 438)
      ? (LOBYTE(ObjectByGameObjectId) = *(_BYTE *)(a1 + 76))
      : (LOBYTE(ObjectByGameObjectId) = *(_BYTE *)(a1 + 448) & 1),
        (_BYTE)ObjectByGameObjectId) )
  {
    if ( *(_BYTE *)(a1 + 1413) == 3 )
    {
      if ( *(_BYTE *)(a1 + 1112) > 1u )
        goto LABEL_56;
      *(_WORD *)(a1 + 1112) = 1;
    }
    else
    {
      if ( *(_BYTE *)(a1 + 1112) > 3u )
        goto LABEL_56;
      *(_WORD *)(a1 + 1112) = 3;
    }
    *(_QWORD *)(a1 + 1104) = 3758096384LL;
    goto LABEL_56;
  }
  LOBYTE(ObjectByGameObjectId) = Client__UI__UIInputModule__IsInputIdPressed(344);
  if ( (_BYTE)ObjectByGameObjectId )
  {
    ObjectByGameObjectId = sub_140626E10(&qword_142AAB990);
    v11 = ObjectByGameObjectId;
    if ( ObjectByGameObjectId != 3758096384LL )
    {
      if ( (unsigned __int8)sub_14062C3A0(qword_142AAB800)
        || (v12 = sub_1400D2D70(qword_142909910),
            LOBYTE(ObjectByGameObjectId) = sub_140772CE0(v12),
            !(_BYTE)ObjectByGameObjectId)
        && dword_1428B84E8 != 3 )
      {
        v13 = *(_BYTE *)(a1 + 438);
        LOBYTE(ObjectByGameObjectId) = v13 ? *(_BYTE *)(a1 + 448) & 1 : *(_BYTE *)(a1 + 76);
        if ( !(_BYTE)ObjectByGameObjectId )
        {
          LOBYTE(ObjectByGameObjectId) = v13 ? (*(_DWORD *)(a1 + 448) & 2) != 0 : *(_BYTE *)(a1 + 77);
          if ( !(_BYTE)ObjectByGameObjectId )
            LOBYTE(ObjectByGameObjectId) = sub_141833E80(a1 + 1104, a1 + 1232, v11);
        }
      }
    }
  }
LABEL_56:
  v14 = *(_QWORD *)(a1 + 1208);
  if ( v14 != 3758096384LL )
  {
    ObjectByGameObjectId = (__int64)Client__Game__Object__ObjectArrays__GetObjectByGameObjectId(
                                      qword_1428BCDD0,
                                      *(_QWORD *)(a1 + 1208));
    v15 = (float *)ObjectByGameObjectId;
    if ( ObjectByGameObjectId )
    {
      LODWORD(ObjectByGameObjectId) = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)ObjectByGameObjectId + 16LL))(ObjectByGameObjectId);
      if ( (_DWORD)ObjectByGameObjectId == 1 && v15 != source && *(_BYTE *)(a1 + 1112) <= 4u )
      {
        *(_WORD *)(a1 + 1112) = 260;
        *(_QWORD *)(a1 + 1104) = v14;
      }
    }
  }
  if ( !*(_BYTE *)(a1 + 1112) )
  {
    LODWORD(ObjectByGameObjectId) = *(unsigned __int8 *)(a1 + 1413);
    if ( (_BYTE)ObjectByGameObjectId )
    {
      switch ( (_DWORD)ObjectByGameObjectId )
      {
        case 2:
          ObjectByGameObjectId = 1232;
          goto LABEL_72;
        case 3:
          ObjectByGameObjectId = 1120;
          goto LABEL_72;
        case 4:
          ObjectByGameObjectId = 1136;
          goto LABEL_72;
        case 5:
          ObjectByGameObjectId = 1248;
LABEL_72:
          if ( a1 + ObjectByGameObjectId )
          {
            LOBYTE(ObjectByGameObjectId) = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)(a1 + ObjectByGameObjectId)
                                                                              + 8LL))(a1 + ObjectByGameObjectId);
            if ( (_BYTE)ObjectByGameObjectId )
            {
              if ( *(_BYTE *)(a1 + 1112) <= 1u )
              {
                *(_WORD *)(a1 + 1112) = 1;
                *(_QWORD *)(a1 + 1104) = 3758096384LL;
              }
            }
          }
          break;
      }
    }
    if ( *(_QWORD *)(a1 + 1208) != 3758096384LL )
    {
      LOBYTE(ObjectByGameObjectId) = sub_14062C3A0(qword_142AAB800);
      if ( (_BYTE)ObjectByGameObjectId
        || (LOBYTE(ObjectByGameObjectId) = sub_14062C3A0(qword_142AAB800), !(_BYTE)ObjectByGameObjectId)
        && ((v16 = sub_1400D2D70(qword_142909910),
             LOBYTE(ObjectByGameObjectId) = sub_140772CE0(v16),
             (_BYTE)ObjectByGameObjectId)
         || dword_1428B84E8 == 3
         || byte_142AB2A66
         && (LOBYTE(ObjectByGameObjectId) = sub_141830D60(&qword_142AB2A00), (_BYTE)ObjectByGameObjectId)) )
      {
        if ( *(_BYTE *)(a1 + 1112) <= 1u )
        {
          *(_WORD *)(a1 + 1112) = 1;
          *(_QWORD *)(a1 + 1104) = 3758096384LL;
        }
      }
    }
  }
  return ObjectByGameObjectId;
}
