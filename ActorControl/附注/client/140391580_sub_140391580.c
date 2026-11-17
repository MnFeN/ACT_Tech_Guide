__int64 __fastcall sub_140391580(__int64 a1, float a2)
{
  __int64 v2; // rcx
  __int64 v3; // rdx
  __int64 result; // rax

  v2 = *(_QWORD *)(a1 + 440);
  if ( v2 )
  {
    *(_BYTE *)(v2 + 196) |= 0x20u;
    v3 = *(_QWORD *)(v2 + 8);
    *(float *)(v2 + 132) = a2;
    if ( v3 )
    {
      result = (unsigned int)_InterlockedExchangeAdd((volatile signed __int32 *)(v3 + 12), 0);
      if ( (_DWORD)result == 1 )
        sub_14037B140(*(_QWORD *)(v2 + 96), a2, 1u);
    }
  }
  return result;
}
