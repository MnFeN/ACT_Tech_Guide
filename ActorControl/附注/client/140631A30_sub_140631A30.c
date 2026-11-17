char __fastcall sub_140631A30(__int64 a1)
{
  __int64 v2; // rcx
  void *NetworkModuleProxy; // rax
  int packet; // [rsp+20h] [rbp-F68h] BYREF
  __int64 v6; // [rsp+28h] [rbp-F60h]

  v2 = *(_QWORD *)(a1 + 56);
  if ( v2 == a1 + 64 )
  {
    NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
    if ( NetworkModuleProxy )
    {
      packet = 566;
LABEL_10:
      v6 = 24;
      LOBYTE(NetworkModuleProxy) = sub_140481E80(NetworkModuleProxy, &packet, 0, 0);
    }
  }
  else if ( v2 == a1 + 104 )
  {
    NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
    if ( NetworkModuleProxy )
    {
      packet = 507;
      goto LABEL_10;
    }
  }
  else
  {
    LOBYTE(NetworkModuleProxy) = a1 + 80;
    if ( v2 == a1 + 80 )
    {
      NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
      if ( NetworkModuleProxy )
      {
        packet = 764;
        goto LABEL_10;
      }
    }
  }
  *(_QWORD *)(a1 + 56) = 0;
  return (char)NetworkModuleProxy;
}
