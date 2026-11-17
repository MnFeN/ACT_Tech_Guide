void __fastcall sub_140B52120(void *self, unsigned int vfx, void *source, void *target, float lifetime)
{
  void *AsCharacter; // rax
  double v10; // xmm0_8
  void *v11; // rdi
  _QWORD *v12; // rax
  __int64 v13; // rbx
  __int64 v14; // rcx

  AsCharacter = Client__Game__Object__GameObject__GetAsCharacter(source);
  if ( AsCharacter )
    *(float *)&v10 = sub_14090D980((__int64)AsCharacter);
  else
    v10 = sub_14089CD00(source);
  v11 = sub_140857450(vfx, source, target, *(float *)&v10, 0, 0);
  if ( v11 )
  {
    v12 = sub_140B52410((__int64)self);
    v13 = (__int64)v12;
    if ( v12 )
    {
      v14 = v12[1];
      if ( v14 )
      {
        sub_140391030(v14, 1);
        sub_140391940(*(_QWORD *)(v13 + 8), 0);
      }
      *(float *)(v13 + 16) = lifetime;
      *(_QWORD *)(v13 + 8) = v11;
      sub_140391940((__int64)v11, v13);
    }
  }
}
