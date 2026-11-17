void __fastcall sub_140B6CEE0(
        void *director,
        unsigned int vfx,
        unsigned int sourceId,
        unsigned int targetId,
        float duration)
{
  void *ObjectByEntityId; // rdi
  void *v9; // rax

  if ( sourceId != -536870912 )
  {
    ObjectByEntityId = Client__Game__Object__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, sourceId);
    if ( ObjectByEntityId )
    {
      if ( targetId != -536870912 )
      {
        v9 = Client__Game__Object__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, targetId);
        if ( v9 )
          sub_140B52120((char *)director + 1288, vfx, ObjectByEntityId, v9, duration);
      }
    }
  }
}
