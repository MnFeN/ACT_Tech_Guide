__int64 __fastcall sub_1400F19A0(void *self, unsigned int screenImageId)
{
  __int64 result; // rax

  result = EXD__ScreenImage__Row_14083B570(screenImageId);
  if ( result )
  {
    if ( (qword_142AA895B & 4) != 0 && (unsigned __int8)qword_142AA894C < 0x40u )
      return 0;
    else
      return sub_1400F55F0(
               (void **)self,
               *(__int16 *)(result + 8),
               *(_BYTE *)(result + 11) & 1,
               *(_DWORD *)(result + 4));
  }
  return result;
}
