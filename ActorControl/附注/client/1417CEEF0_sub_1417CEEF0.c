double __fastcall sub_1417CEEF0(__int64 a1, unsigned int a2)
{
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 v5; // rax
  void *UIModule; // rax
  void *v7; // rax
  double result; // xmm0_8

  v3 = sub_140B777C0();
  sub_140B882E0(v3, 0);
  v4 = sub_140B777C0();
  if ( !sub_140B88230(v4) || (v5 = sub_140B777C0(), !sub_140B83DA0(v5)) )
  {
    UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
    v7 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 64LL))(UIModule);
    sub_1400F19A0(v7, a2);
  }
  return result;
}
