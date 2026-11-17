void __fastcall sub_141820DD0(
        void *self,
        unsigned int otherEntityId,
        unsigned int packedOffset,
        unsigned int headingFlags,
        unsigned __int16 actionTimelineId)
{
  void *v8; // rax
  float offset[6]; // [rsp+30h] [rbp-18h] BYREF

  v8 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, otherEntityId);
  if ( v8 )
  {
    offset[0] = (float)BYTE2(packedOffset) / 10.0;
    offset[1] = (float)BYTE1(packedOffset) / 10.0;
    offset[2] = (float)(unsigned __int8)packedOffset / 10.0;
    offset[3] = 0.0;
    sub_141820A40(
      self,
      v8,
      offset,
      (float)((unsigned __int16)headingFlags - 180) * 0.017453292,
      actionTimelineId,
      (headingFlags & 0xFFFF0000) != 0);
  }
}
