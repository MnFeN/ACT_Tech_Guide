char __fastcall sub_1409041B0(_BYTE *a1, int a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
  __int64 v8; // rdx
  char v9; // di
  char result; // al
  _BYTE v12[8]; // [rsp+20h] [rbp-38h] BYREF
  _DWORD v13[6]; // [rsp+28h] [rbp-30h] BYREF
  int v14; // [rsp+40h] [rbp-18h] BYREF
  int v15; // [rsp+44h] [rbp-14h]

  v8 = (unsigned int)(a2 - 1512);
  v9 = a4;
  switch ( (int)v8 )
  {
    case 0:
      if ( a1[1] == (_BYTE)a3 )
        goto LABEL_13;
      *a1 = a3;
      a1[25] = (_BYTE)a3 == 24;
      sub_140903DA0((__int64)a1);
      result = 1;
      break;
    case 1:
      v14 = a3;
      v15 = a5;
      sub_140903E30(a1, &v14, 2);
      a1[153] = a6;
      a1[154] = a7;
      a1[155] = a8;
      a1[152] = v9;
      result = 1;
      break;
    case 2:
      LOBYTE(v14) = a3 != 0;
      v13[0] = a3;
      v13[3] = a6;
      BYTE1(v14) = a4 != 0;
      v13[4] = a7;
      v13[1] = a4;
      v13[2] = a5;
      BYTE2(v14) = a5 != 0;
      HIBYTE(v14) = a6 != 0;
      LOBYTE(v15) = a7 != 0;
      sub_140903E30(a1, v13, 5);
      sub_1409040D0(a1, (__int64)&v14, 5);
      result = 1;
      break;
    case 3:
      if ( a1[26] != (a3 != 0) )
      {
        a1[26] = a3 != 0;
        if ( a3 && a1[24] )
          LOBYTE(v8) = 1;
        else
          v8 = 0;
        sub_140904500(a1, v8);
        if ( a1[26] == 1 )
          Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0xEFu, 0, 0);
      }
LABEL_13:
      result = 1;
      break;
    case 4:
      v12[0] = a3 != 0;
      v12[1] = a4 != 0;
      sub_1409040D0(a1, (__int64)v12, 2);
      result = 1;
      break;
    case 5:
      a1[154] = a3;
      a1[155] = a4;
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}
