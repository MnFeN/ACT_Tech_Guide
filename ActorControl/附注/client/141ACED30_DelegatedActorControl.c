char __fastcall sub_141ACED30(_DWORD *a1, int a2, unsigned int a3, unsigned int a4, unsigned int a5)
{
  void *UIModule; // rax
  void *v7; // rax

  if ( a2 != 3552 )
  {
    if ( a2 != 3553 )
      return 0;
    if ( a3 )
      sub_141ACF340((__int64)a1, a3, a4, 0);
    return 1;
  }
  a1[77] = a3;
  a1[78] = a4;
  if ( !a5 || a1[74] != 3 )
    return 1;
  UIModule = Client__System__Framework__Framework__GetUIModule((void *)qword_142909910);
  if ( UIModule )
  {
    v7 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 88LL))(UIModule);
    Client__UI__Misc__RaptureLogModule__ShowLogMessage(v7, 0x2C47u);
  }
  sub_141ACF340((__int64)a1, a5, 0, 2);
  return 1;
}
