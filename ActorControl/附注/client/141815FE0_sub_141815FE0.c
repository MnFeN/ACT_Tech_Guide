__m128 __fastcall sub_141815FE0(__int64 a1)
{
  __m128 result; // xmm0
  __m128 v3; // xmm6

  result.m128_f32[0] = sub_14089CCB0(*(_QWORD *)(a1 + 992));
  v3 = result;
  result.m128_f32[0] = fmaxf(sub_14090D980(*(_QWORD *)(a1 + 992)) * 0.082999997, 0.082999997);
  if ( v3.m128_f32[0] <= result.m128_f32[0] )
    return v3;
  return result;
}
