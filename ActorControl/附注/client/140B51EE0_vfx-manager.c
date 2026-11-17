void __fastcall sub_140B51EE0(__int64 a1, float a2)
{
  float *v2; // rdi
  float *i; // rbx
  __int64 v4; // rcx
  float v5; // xmm0_4
  float v6; // xmm0_4

  v2 = *(float **)(a1 + 8);
  for ( i = *(float **)v2; i != v2; i = *(float **)i )
  {
    v4 = *((_QWORD *)i + 3);
    if ( v4 )
    {
      v5 = i[8];
      if ( v5 > 0.0 )
      {
        v6 = v5 - a2;
        i[8] = v6;
        if ( v6 <= 0.0 )
        {
          sub_140391030(v4, 1);
          sub_140391940(*((_QWORD *)i + 3), 0);
          *((_QWORD *)i + 3) = 0;
          i[8] = 0.0;
        }
      }
    }
  }
}
