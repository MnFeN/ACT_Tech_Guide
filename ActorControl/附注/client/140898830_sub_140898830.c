void __fastcall sub_140898830(__int64 a1, unsigned int a2, unsigned int a3)
{
  void *v6; // rcx

  if ( (dword_142AAB79C & 0xFFFFFFFD) == 0 && *(char *)(a1 + 154) < 0 )
  {
    v6 = *(void **)(a1 + 264);
    if ( v6 )
    {
      if ( Client__LayoutEngine__Group__SharedGroupLayoutInstance__IsTimelineIndexValid(v6, a2) )
        Client__LayoutEngine__Group__SharedGroupLayoutInstance__PlayTimeline(*(void **)(a1 + 264), a2, a3);
    }
  }
}
