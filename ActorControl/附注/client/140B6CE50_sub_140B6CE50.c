void *__fastcall sub_140B6CE50(void *director, unsigned int vfx, void *position, float duration, unsigned int actorId)
{
  void *result; // rax

  result = 0;
  if ( actorId == -536870912
    || (result = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, actorId)) != 0 )
  {
    sub_140B51F80((__int64)director + 1288, vfx, (float *)position, duration, 1065353216, 0.0, (__int64)result);
  }
  return result;
}
