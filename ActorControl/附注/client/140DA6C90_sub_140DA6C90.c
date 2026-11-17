char __fastcall sub_140DA6C90(__int64 a1, int a2)
{
  unsigned __int8 *Instance; // rax
  unsigned __int8 *v5; // rbp
  __int64 v6; // rax
  __int64 v7; // rdi
  void *UISpace; // rax
  _OWORD *v9; // rax
  _OWORD *v10; // rdi
  __int64 v11; // rax
  void *v12; // rdx
  __int64 v13; // rcx
  void (__fastcall ***v14)(_QWORD, __int64); // rcx
  __int64 v15; // rsi
  void *v16; // rax
  __int64 v17; // rax
  _QWORD *v18; // rdi

  Instance = (unsigned __int8 *)Client__Game__InstanceContent__DynamicEventContainer__GetInstance();
  v5 = Instance;
  if ( Instance )
  {
    if ( (*(unsigned __int8 (__fastcall **)(__int64))(*(_QWORD *)a1 + 48LL))(a1) )
      (*(void (__fastcall **)(__int64))(*(_QWORD *)a1 + 40LL))(a1);
    v6 = (*(__int64 (__fastcall **)(_QWORD))(**(_QWORD **)(a1 + 16) + 64LL))(*(_QWORD *)(a1 + 16));
    Instance = (unsigned __int8 *)(*(__int64 (__fastcall **)(__int64, __int64))(*(_QWORD *)v6 + 72LL))(v6, 10);
    if ( Instance )
    {
      v7 = *(_QWORD *)(a1 + 40);
      if ( v7 )
      {
        Client__System__String__Utf8String__Dtor((void *)(v7 + 24));
        j_Client__System__Memory__IMemorySpace__Free_4(v7, 144);
        *(_QWORD *)(a1 + 40) = 0;
      }
      UISpace = Client__System__Memory__IMemorySpace__GetUISpace();
      v9 = (_OWORD *)sub_14008FB10(144, 0, UISpace, 0);
      v10 = v9;
      if ( v9 )
      {
        *v9 = 0;
        v9[1] = 0;
        v9[2] = 0;
        v9[3] = 0;
        v9[4] = 0;
        v9[5] = 0;
        v9[6] = 0;
        v9[7] = 0;
        v9[8] = 0;
        Client__System__String__Utf8String__Ctor((char *)v9 + 24);
      }
      else
      {
        v10 = 0;
      }
      *(_QWORD *)(a1 + 40) = v10;
      *((_DWORD *)v10 + 1) = a2;
      **(_DWORD **)(a1 + 40) = Client__System__Framework__Framework__GetServerTime() + 30;
      *(_QWORD *)(*(_QWORD *)(a1 + 40) + 128LL) = Component__Exd__ExdModule__GetSheetByIndex(*((_QWORD *)qword_142909910
                                                                                             + 1384));
      v11 = *(_QWORD *)(a1 + 40);
      v12 = *(void **)(v11 + 136);
      if ( v12 )
      {
        v13 = *(_QWORD *)(a1 + 40);
        if ( *(_QWORD *)(v11 + 128) )
        {
          Common__Component__Excel__ExcelSheet__RemoveWaiter(*(void **)(v11 + 128), v12);
          v11 = *(_QWORD *)(a1 + 40);
          v13 = v11;
        }
        v14 = *(void (__fastcall ****)(_QWORD, __int64))(v13 + 136);
        if ( v14 )
        {
          (**v14)(v14, 1);
          *(_QWORD *)(*(_QWORD *)(a1 + 40) + 136LL) = 0;
          v11 = *(_QWORD *)(a1 + 40);
        }
      }
      v15 = 464LL * *(unsigned int *)(v11 + 4);
      v16 = Client__System__Memory__IMemorySpace__GetUISpace();
      v17 = sub_14008FB10(80, 0, v16, 0);
      v18 = (_QWORD *)v17;
      if ( v17 )
      {
        sub_14208B170(v17, 1u, 0);
        v18[6] = 1;
        *v18 = &off_1421CB4A8;
        v18[8] = sub_140DA7070;
        v18[7] = a1;
        v18[9] = 0;
      }
      else
      {
        v18 = 0;
      }
      *(_QWORD *)(*(_QWORD *)(a1 + 40) + 136LL) = v18;
      Common__Component__Excel__ExcelSheetWaiter__EnqueueRowLookup(
        *(void **)(*(_QWORD *)(a1 + 40) + 136LL),
        0,
        v5[v15 + 99]);
      LOBYTE(Instance) = Common__Component__Excel__ExcelSheet__AddWaiter(
                           *(void **)(*(_QWORD *)(a1 + 40) + 128LL),
                           *(void **)(*(_QWORD *)(a1 + 40) + 136LL));
    }
  }
  return (char)Instance;
}
