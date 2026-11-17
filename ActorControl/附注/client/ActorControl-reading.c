void __fastcall HandleActorControl(
        unsigned int entityId,
        unsigned int category,
        unsigned int p1,
        unsigned int p2,
        unsigned int p3,
        unsigned int p4,
        unsigned int p5,
        unsigned int p6,
        unsigned int p7,
        unsigned int p8,
        unsigned __int64 targetId,
        unsigned __int8 isRecorded)
{
  __int64 v12; // rsi
  unsigned int entityId; // edi
  float *v15; // rax
  __int64 v16; // rdx
  __int64 v17; // r8
  __int64 v18; // r9
  __int64 v19; // r14
  bool v20; // bl
  __int64 v21; // rax
  bool v22; // r12
  void *v23; // rbx
  char v24; // al
  char v25; // cl
  bool v26; // cl
  char v27; // si
  void *v28; // r8
  void *v29; // rdx
  unsigned int v30; // ecx
  __int64 v31; // rax
  char v32; // al
  char v33; // cl
  __int64 v34; // rdi
  unsigned int v35; // ebx
  _DWORD *v36; // rax
  __int64 v37; // rax
  int v38; // r15d
  unsigned int v39; // ecx
  __int64 v40; // rcx
  void *v41; // rax
  int v42; // r15d
  unsigned int i; // ebx
  unsigned int k; // ebx
  float *v45; // rbx
  float *v46; // rax
  float v47; // xmm1_4
  float v48; // xmm0_4
  unsigned int j; // ebx
  void *v50; // rax
  int v51; // ecx
  __int64 v52; // rax
  void *v53; // rax
  unsigned int v54; // r8d
  unsigned int v55; // edx
  __int64 v56; // rax
  void *v57; // rax
  unsigned __int8 *v58; // rax
  __int64 v59; // rdi
  unsigned int v60; // eax
  __int64 v61; // rax
  float v62; // xmm6_4
  unsigned int SpellIdForAction; // eax
  float v64; // xmm2_4
  void *v65; // rax
  void *v66; // rax
  void *v67; // rbx
  void *v68; // rax
  void *v69; // rax
  void *v70; // rbx
  unsigned int v71; // eax
  unsigned __int16 v72; // dx
  void *v73; // rax
  void *v74; // rax
  void *v75; // rax
  void *NetworkModuleProxy; // rax
  void *v77; // rax
  __int64 v78; // r8
  void *v79; // rax
  __int64 v80; // r8
  _DWORD *v81; // rbx
  void *v82; // rax
  __int64 v83; // rax
  void *v84; // rcx
  __int64 v85; // rbx
  void *v86; // rax
  void *v87; // rax
  void *v88; // rax
  char v89; // dl
  void *v90; // rdi
  _QWORD *v91; // rax
  _DWORD *v92; // rbx
  void *v93; // rax
  void *v94; // rax
  __int64 v95; // rcx
  __int64 v96; // rbx
  _QWORD *v97; // rax
  void *v98; // rcx
  __int64 v99; // rax
  void *v100; // rax
  __int64 v101; // rbx
  void *v102; // rax
  __int64 v103; // rax
  __int64 v104; // rax
  _BYTE *ObjectByEntityId; // rax
  _BYTE *v106; // rbx
  void *v107; // rax
  __int64 v108; // rax
  void *v109; // rax
  __int64 v110; // rax
  int v111; // r8d
  unsigned int v112; // edx
  void *v113; // rax
  __int64 v114; // rax
  __int64 v115; // rcx
  __int64 v116; // rax
  __int64 v117; // rax
  unsigned int v118; // ecx
  unsigned __int16 *v119; // rax
  unsigned int v120; // ecx
  bool v121; // al
  _DWORD *v122; // rax
  __int64 v123; // rax
  _QWORD *v124; // rax
  __int64 *v125; // rax
  unsigned __int8 *v126; // rax
  __int64 v127; // rax
  void *Group; // rax
  void *PartyMemberByEntityId; // rax
  void *v130; // rax
  void *v131; // rax
  void *v132; // rax
  void *v133; // rax
  __int64 v134; // rax
  __int64 v135; // rax
  void *v136; // rax
  void *v137; // rax
  void *v138; // rax
  void *v139; // rax
  void *v140; // rax
  unsigned int v141; // eax
  __int64 v142; // rax
  __int64 v143; // rax
  unsigned int v144; // ebx
  void *v145; // rax
  _DWORD *v146; // rax
  void *v147; // rax
  __int64 v148; // rax
  _DWORD *v149; // rax
  void *v150; // rax
  _DWORD *v151; // rax
  void *v152; // rax
  __int64 v153; // rax
  _BYTE *v154; // rdx
  bool v155; // cl
  unsigned int v156; // edi
  unsigned int v157; // r12d
  unsigned __int16 *v158; // rax
  unsigned __int16 *v159; // rsi
  __int64 v160; // r13
  __int64 v161; // rbx
  _DWORD *v162; // rbx
  _DWORD *v163; // rbx
  _DWORD *v164; // rbx
  _DWORD *v165; // rbx
  void *v166; // rax
  void *v167; // rax
  void *v168; // rax
  _QWORD **v169; // rax
  int v170; // edx
  void *v171; // rax
  void *v172; // rax
  unsigned int v173; // edi
  unsigned int v174; // esi
  _QWORD *v175; // rax
  _DWORD *v176; // rbx
  void *v177; // rax
  void *v178; // rax
  void *v179; // rax
  _QWORD **v180; // rax
  int v181; // edx
  unsigned int v182; // r14d
  unsigned int v183; // edi
  bool v184; // si
  _QWORD *v185; // rax
  _DWORD *v186; // rbx
  _DWORD *v187; // rbx
  void *v188; // rax
  void *v189; // rax
  void *v190; // rax
  _QWORD **v191; // rax
  int v192; // edx
  void *v193; // rax
  char v194; // cl
  void *v195; // rax
  void *v196; // rax
  void *v197; // rax
  _DWORD *v198; // rbx
  _DWORD *v199; // rbx
  void *v200; // rax
  void *v201; // rax
  _DWORD *v202; // rbx
  _DWORD *v203; // rbx
  void *v204; // rax
  void *v205; // rax
  unsigned int v206; // edi
  _DWORD *v207; // rbx
  _DWORD *v208; // rbx
  void *v209; // rax
  void *v210; // rax
  void *v211; // rax
  int v212; // eax
  unsigned int v213; // edi
  _DWORD *v214; // rbx
  void *v215; // rax
  void *v216; // rax
  void *v217; // rax
  __int64 v218; // rax
  void *v219; // rax
  __int64 v220; // rax
  void *v221; // rax
  __int64 v222; // rax
  void *v223; // rax
  __int64 v224; // rax
  void *v225; // rax
  __int64 v226; // rax
  void *v227; // rax
  __int64 v228; // rax
  __int64 v229; // rax
  __int64 v230; // rax
  __int64 v231; // rax
  __int64 v232; // rax
  __int64 v233; // rax
  __int64 v234; // rax
  void *v235; // rax
  __int64 v236; // rax
  void *v237; // rax
  __int64 v238; // rax
  unsigned int v239; // edx
  unsigned int v240; // ebx
  int v241; // esi
  unsigned __int64 v242; // rax
  unsigned __int8 v243; // cl
  __int64 v244; // rdx
  __int64 *v245; // rcx
  __int64 v246; // rdx
  void *v247; // rax
  char *Gearset; // rax
  void *v249; // rax
  void *v250; // rax
  void *v251; // rax
  void *v252; // rax
  void *v253; // rax
  void *v254; // rax
  void *v255; // rax
  unsigned int m; // r15d
  void *v257; // rax
  void *v258; // rax
  void *v259; // rax
  void *v260; // rdi
  __int64 v261; // rax
  void *v262; // rbx
  __int64 v263; // rax
  __int64 v264; // rbx
  __int64 v265; // rax
  __int64 v266; // rax
  void *v267; // rdi
  int v268; // r15d
  __int64 *v269; // rbx
  __int64 v270; // rax
  void *v271; // rax
  void *v272; // rax
  void *v273; // rax
  void *v274; // rax
  void *v275; // rax
  _BYTE *v276; // rax
  void *v277; // rax
  void *v278; // rax
  void *v279; // rax
  int v280; // r8d
  int v281; // r8d
  void *v282; // rax
  __int64 v283; // rax
  unsigned int v284; // ebx
  void *v285; // rax
  _QWORD *v286; // rax
  int v287; // edx
  void *v288; // rax
  void *InventoryContainer; // rax
  __int64 v290; // rax
  __int64 v291; // rax
  void *v292; // rax
  __int64 v293; // rax
  void *v294; // rax
  void *v295; // r15
  unsigned __int16 TreasureSpotSubKey; // bx
  unsigned __int8 TreasureHuntRank; // al
  __int64 v298; // rax
  void *v299; // rax
  void *v300; // rax
  unsigned int v301; // ebx
  __int64 v302; // rax
  void *v303; // rax
  __int64 v304; // rax
  void *v305; // rax
  void *v306; // rax
  __int64 v307; // rax
  void *v308; // rax
  void *v309; // rax
  __int64 v310; // rax
  __int64 v311; // rax
  __int64 v312; // rax
  __int64 v313; // rax
  __int64 v314; // rax
  __int64 v315; // rax
  __int64 v316; // rax
  __int64 v317; // rax
  __int64 v318; // rax
  _QWORD *v319; // rax
  __int64 v320; // rax
  __int64 v321; // rax
  __int64 v322; // rax
  __int64 v323; // rax
  __int64 v324; // rax
  __int64 v325; // rax
  void *v326; // rax
  __int64 v327; // rax
  void *v328; // rax
  __int64 v329; // rax
  __int64 v330; // rax
  __int64 v331; // rax
  void *v332; // rax
  __int64 v333; // rax
  __int64 v334; // rax
  __int64 v335; // rax
  void *v336; // rax
  void *v337; // rax
  __int64 v338; // rax
  void *v339; // rax
  void *v340; // rax
  __int64 v341; // rax
  __int64 v342; // rax
  __int64 v343; // rax
  void *v344; // rax
  __int64 v345; // rax
  __int64 v346; // rax
  __int64 v347; // rax
  void *v348; // rax
  void *v349; // rax
  __int64 v350; // rax
  __int64 v351; // rax
  __int64 v352; // rax
  __int64 v353; // rax
  void *v354; // rax
  __int64 v355; // rax
  void *v356; // rax
  __int64 v357; // rax
  __int64 v358; // rax
  __int64 v359; // r8
  void *v360; // r10
  __int64 v361; // rax
  _QWORD *v362; // rax
  __int64 v363; // rax
  _QWORD *v364; // rax
  __int64 v365; // rax
  __int64 v366; // rax
  __int64 v367; // rax
  __int64 *v368; // rax
  void *v369; // rdi
  __int16 v370; // bx
  void *v371; // rax
  __int64 v372; // rax
  void *v373; // rax
  __int64 v374; // rax
  __int64 v375; // rax
  void *v376; // rax
  __int64 v377; // rax
  void *v378; // rax
  __int64 v379; // rax
  void *v380; // rax
  __int64 v381; // rax
  void *v382; // rax
  __int64 v383; // rax
  void *v384; // rax
  void *v385; // rax
  __int64 v386; // rax
  void *v387; // rax
  __int64 v388; // rax
  void *v389; // rax
  __int64 v390; // rax
  void *v391; // rax
  __int64 v392; // rax
  void *v393; // rax
  __int64 v394; // rax
  void *v395; // rax
  __int64 v396; // rax
  void *v397; // rax
  __int64 v398; // rax
  void *v399; // rax
  __int64 v400; // rax
  void *v401; // rax
  __int64 v402; // rax
  void *v403; // rax
  __int64 v404; // rax
  void *v405; // rax
  __int64 v406; // rax
  __int64 v407; // rax
  __int64 *v408; // rax
  void *v409; // rax
  __int64 v410; // rax
  void *v411; // rax
  void *v412; // rax
  float *v413; // r13
  void *v414; // rbx
  void *v415; // rax
  void *v416; // rax
  void *v417; // rax
  __int64 v418; // rbx
  void *v419; // rax
  __int64 v420; // rax
  char v421; // si
  __int64 v422; // r14
  __int64 v423; // rdi
  char v424; // bl
  __int64 v425; // rax
  void *v426; // rbx
  void *v427; // rax
  __int64 v428; // rsi
  void *v429; // rdi
  char v430; // bl
  __int64 v431; // rax
  void *v432; // rdi
  void *v433; // rbx
  void *v434; // rax
  void *v435; // rax
  void *v436; // rax
  void *v437; // rax
  __int64 v438; // rax
  __int64 v439; // rsi
  int v440; // eax
  void *v441; // rax
  void *v442; // rax
  void *v443; // rax
  void *v444; // rax
  void *v445; // rax
  _DWORD *v446; // rax
  void *v447; // rax
  void *v448; // rbx
  void *v449; // rax
  void *v450; // rax
  void *v451; // rbx
  void *v452; // rax
  void *v453; // rax
  void *v454; // rbx
  void *v455; // rax
  __int64 v456; // rax
  __int64 v457; // rax
  __int64 v458; // rax
  __int64 v459; // rax
  __int64 v460; // rax
  void *v461; // rax
  void *v462; // rbx
  __int64 v463; // rax
  void *v464; // rax
  void *v465; // rbx
  __int64 v466; // rax
  void *v467; // rax
  void *v468; // rax
  __int64 v469; // rax
  __int64 v470; // rax
  void *v471; // rbx
  float v472; // xmm8_4
  float v473; // xmm7_4
  float v474; // xmm6_4
  char v475; // al
  __int64 v476; // rax
  __int64 v477; // rax
  __int64 v478; // rax
  __int64 v479; // rax
  __int64 v480; // rax
  unsigned __int8 *v481; // rax
  __int64 v482; // rax
  _BYTE *v483; // rax
  __int64 v484; // rax
  _BYTE *v485; // rax
  __int64 v486; // rax
  _BYTE *v487; // rax
  __int64 v488; // rax
  _BYTE *v489; // rax
  __int64 v490; // rax
  _BYTE *v491; // rax
  __int64 v492; // rax
  _BYTE *v493; // rax
  __int64 v494; // rax
  __int64 v495; // rax
  int v496; // r15d
  int v497; // eax
  unsigned __int16 v498; // bx
  __int64 v499; // rax
  __int64 v500; // rax
  __int64 v501; // rax
  __int64 v502; // rax
  __int64 v503; // rax
  __int64 v504; // rax
  int v505; // r15d
  int v506; // eax
  unsigned __int16 v507; // bx
  __int64 v508; // rax
  __int64 v509; // rax
  __int64 v510; // rax
  __int64 *v511; // rax
  __int64 v512; // rcx
  __int16 v513; // dx
  void *v514; // rax
  _QWORD *v515; // rax
  __int64 v516; // rax
  void *v517; // rax
  _QWORD *v518; // rax
  void *v519; // rax
  _QWORD *v520; // rax
  void *v521; // rax
  _QWORD *v522; // rax
  __int64 v523; // rax
  __int64 v524; // rax
  __int64 v525; // rax
  __int64 v526; // rax
  __int64 v527; // rax
  __int64 v528; // rax
  __int64 v529; // rax
  __int64 v530; // rax
  __int64 v531; // rax
  __int64 v532; // rax
  __int64 v533; // rax
  unsigned int v534; // eax
  __int64 v535; // rax
  void *v536; // rax
  void *v537; // rax
  float v538; // xmm6_4
  __int64 v539; // rax
  __int64 v540; // rax
  void *v541; // rax
  __int64 v542; // rax
  __int64 v543; // rax
  __int64 v544; // rbx
  __int64 v545; // rax
  __int64 v546; // rax
  int v547; // edx
  void *v548; // rax
  __int64 v549; // rax
  void *v550; // rax
  _QWORD *v551; // rax
  void *v552; // rax
  void *v553; // rax
  void *v554; // rax
  void *v555; // rbx
  void *v556; // rax
  void *v557; // rax
  void *v558; // rax
  void *v559; // rax
  _QWORD *v560; // rax
  float *v561; // rbx
  float *v562; // rax
  float v563; // xmm1_4
  float v564; // xmm0_4
  void *v565; // rax
  __int64 v566; // rax
  void *v567; // rax
  __int64 v568; // rax
  __int64 v569; // rax
  __int64 v570; // rax
  __int64 v571; // rax
  __int64 v572; // rax
  __int64 v573; // rax
  __int64 v574; // rax
  void *v575; // rax
  __int64 v576; // rax
  __int64 v577; // rax
  __int64 v578; // rax
  void *v579; // rbx
  void *v580; // rax
  void *v581; // rax
  void *v582; // rbx
  void *v583; // rax
  _QWORD *v584; // rax
  _QWORD *v585; // rdi
  __int64 *AsCharacter; // rax
  __int64 *v587; // rbx
  __int64 v588; // rax
  __int64 v589; // rax
  __int64 v590; // rcx
  __int64 v591; // rdx
  __int64 v592; // rax
  __int64 v593; // rbx
  __int64 v594; // rax
  _DWORD *v595; // rbx
  int v596; // eax
  __int64 v597; // rbx
  __int64 v598; // rax
  int v599; // eax
  __int64 v600; // rax
  __int64 v601; // rbx
  int v602; // eax
  __int64 v603; // rax
  void *v604; // rbx
  unsigned int v605; // eax
  float *v606; // rbx
  float *v607; // rax
  float v608; // xmm1_4
  float v609; // xmm0_4
  void *v610; // rax
  void *v611; // rax
  _BYTE *v612; // rax
  void *v613; // rax
  __int64 v614; // rax
  void *v615; // rax
  __int64 v616; // rax
  __int64 v617; // rax
  __int64 v618; // rax
  unsigned __int64 v619; // rax
  int v620; // edx
  __int64 v621; // rax
  __int64 v622; // rax
  __m128i *p_si128; // rcx
  __int64 v624; // r15
  __int64 v625; // rdx
  __int16 v626; // ax
  void *v627; // rax
  bool v628; // zf
  void *v629; // rax
  __int64 v630; // rax
  __int64 v631; // rax
  unsigned int v632; // ecx
  float v633; // xmm0_4
  float v634; // xmm0_4
  float *v635; // r9
  float *v636; // rax
  float v637; // xmm2_4
  float v638; // xmm1_4
  float v639; // xmm0_4
  float v640; // xmm0_4
  float v641; // xmm6_4
  float v642; // xmm0_4
  float v643; // xmm0_4
  float v644; // xmm0_4
  _QWORD *v645; // rbx
  __int64 v646; // rax
  __int64 v647; // rax
  unsigned __int8 v648; // bl
  char v649; // r14
  bool v650; // di
  __int64 v651; // rax
  __int64 v652; // r8
  char v653; // al
  int v654; // edx
  char v655; // al
  __int64 v656; // rax
  __int64 v657; // rax
  __int64 v658; // rax
  __int64 v659; // rax
  __int16 v660; // cx
  void *v661; // rax
  void *v662; // rax
  void *v663; // rax
  void *v664; // rax
  __int64 v665; // rax
  void *v666; // rax
  void *v667; // rax
  void *v668; // rax
  void *v669; // rax
  void *v670; // rax
  void *v671; // rax
  void *v672; // rax
  __int64 v673; // rax
  void *v674; // rax
  __int64 v675; // rax
  void *v676; // rax
  __int64 v677; // rax
  void *v678; // rax
  int v679; // eax
  void *v680; // rax
  __int64 v681; // rbx
  __int64 v682; // rax
  _BYTE *v683; // rax
  unsigned int v684; // eax
  unsigned __int64 v685; // rdx
  void *ObjectByGameObjectId; // rdi
  void *v687; // rax
  unsigned __int64 v688; // rdx
  int v689; // ebx
  __int64 v690; // rax
  void *v691; // rax
  void *v692; // rax
  __int64 v693; // rax
  __int64 v694; // rax
  unsigned int v695; // esi
  unsigned int v696; // r14d
  char v697; // dl
  char v698; // di
  __int64 v699; // rax
  void *v700; // rax
  __int64 v701; // rax
  __int64 v702; // rax
  __int64 v703; // rax
  __int64 v704; // rax
  _QWORD **v705; // rax
  __int64 v706; // rax
  void *v707; // rax
  __int64 v708; // rax
  _QWORD *v709; // rax
  _QWORD *v710; // rax
  void *v711; // rax
  float v712; // xmm6_4
  void *v713; // rax
  void *v714; // rax
  int StatusIndex; // ebx
  __int64 v716; // rax
  __int64 v717; // rax
  unsigned __int64 v718; // rdx
  void *v719; // rax
  _BYTE *v720; // rax
  __int64 v721; // rax
  __int64 v722; // rax
  float *v723; // rbx
  void *v724; // rax
  void *v725; // rax
  void *v726; // rax
  void *v727; // rdi
  void *v728; // rax
  void *v729; // rax
  void *v730; // rbx
  void *v731; // rax
  void *v732; // rax
  __int64 v733; // rax
  __int64 v734; // rax
  void *v735; // rax
  void *v736; // rax
  __int64 v737; // rax
  __int64 v738; // rax
  void *v739; // rax
  void *v740; // rax
  _BYTE *v741; // rax
  void *v742; // rax
  void *v743; // rax
  void *v744; // rax
  void *v745; // rax
  void *v746; // rax
  void *v747; // rax
  void *v748; // rax
  void *v749; // rax
  void *v750; // rax
  __int64 v751; // rax
  __int64 v752; // rax
  __int64 *v753; // rax
  _QWORD **v754; // rax
  unsigned __int16 v755; // dx
  void *v756; // rax
  void *v757; // rbx
  void *v758; // rax
  void *v759; // rax
  __int64 v760; // rax
  __int64 v761; // rax
  void *v762; // rax
  void *v763; // rax
  void *v764; // rax
  void *v765; // rax
  void *v766; // rax
  __time64_t v767; // rbx
  __time64_t v768; // rax
  double v769; // xmm0_8
  bool v770; // cc
  int v771; // ecx
  double v772; // xmm0_8
  int v773; // edx
  __int64 v774; // rax
  __int64 v775; // rdi
  void *v776; // rax
  void *v777; // rax
  void *v778; // rbx
  __int64 v779; // rax
  void *v780; // rax
  __int64 v781; // rax
  __int64 v782; // rax
  void *v783; // rax
  __int64 v784; // rax
  __int64 *v785; // rax
  __int64 v786; // rax
  float *v787; // rsi
  _BYTE *LayoutInstanceStatic; // rax
  _BYTE *v789; // rbx
  __int64 v790; // rdi
  unsigned __int8 (__fastcall *v791)(__int64, _DWORD *); // rbx
  int v792; // xmm7_4
  int v793; // xmm6_4
  float *v794; // rax
  const float *v795; // rax
  float *v796; // rax
  float v797; // xmm6_4
  float *v798; // rax
  const float *v799; // rax
  _BYTE *v800; // rax
  void *v801; // rax
  __int64 v802; // rax
  __int64 *v803; // rax
  __int64 *v804; // rax
  __int64 *v805; // rax
  __int64 *v806; // rax
  __int64 *v807; // rax
  void *v808; // rax
  void *v809; // rax
  void *v810; // rax
  char v811; // al
  char v812; // di
  unsigned int n; // r15d
  void *v814; // rax
  void *v815; // rax
  void *v816; // rax
  void *v817; // rax
  __int64 v818; // rax
  bool v819; // zf
  void *v820; // rax
  __int64 v821; // rax
  void *v822; // rax
  __int64 ItemRowById; // rax
  __int64 v824; // rax
  __int64 v825; // rbx
  void *v826; // rax
  __int64 v827; // rax
  void *v828; // rax
  float *v829; // rbx
  void *v830; // rax
  void *v831; // rax
  void *v832; // rax
  void *v833; // rax
  _QWORD *v834; // rax
  _DWORD *v835; // rax
  __int64 *v836; // rax
  __int64 v837; // rax
  __int64 v838; // rax
  __int64 v839; // rax
  __int64 v840; // rax
  __int64 v841; // rax
  __int64 v842; // rax
  __int64 v843; // rax
  __int64 v844; // rax
  __int64 v845; // rax
  __int64 v846; // rax
  __int64 v847; // rax
  _BYTE *v848; // rax
  void *v849; // rax
  __int64 v850; // rax
  __int64 v851; // rax
  __int64 v852; // rax
  void *v853; // rax
  void *v854; // rax
  _BYTE *v855; // rax
  __int64 v856; // rax
  __int64 v857; // rax
  __int64 v858; // rax
  __int64 v859; // rax
  __int64 v860; // rax
  void *v861; // rax
  void *ContentDirector; // rax
  void *v863; // rax
  void *v864; // rax
  void *v865; // rax
  void *v866; // rax
  void *v867; // rax
  void *v868; // rax
  void *v869; // rax
  void *v870; // rax
  void *v871; // rax
  void *v872; // rax
  __int64 v873; // rax
  __int64 v874; // rax
  __int64 v875; // rax
  __int64 v876; // rax
  void *UIModule; // rbx
  __int64 v878; // rax
  __int64 v879; // rax
  __int64 v880; // rax
  __int64 v881; // rax
  __int64 v882; // rax
  void *v883; // rax
  void *v884; // rax
  _QWORD **AgentByInternalId; // rax
  void *v886; // rax
  void *MassivePcContentDirector; // rax
  __int64 v888; // rax
  __int64 EventHandlerById; // rax
  __int64 v890; // rax
  __int64 v891; // rax
  __int64 v892; // rax
  __int64 v893; // rax
  __int64 v894; // rax
  __int64 v895; // rax
  __int64 v896; // rax
  __int64 v897; // rax
  __int64 v898; // rax
  __int64 v899; // rax
  int value1; // [rsp+28h] [rbp-D8h]
  unsigned int entityIda[2]; // [rsp+70h] [rbp-90h] BYREF
  unsigned int p2; // [rsp+78h] [rbp-88h] BYREF
  int p3; // [rsp+80h] [rbp-80h] BYREF
  int p4; // [rsp+88h] [rbp-78h] BYREF
  int a4; // [rsp+94h] [rbp-6Ch]
  unsigned __int16 v906; // [rsp+98h] [rbp-68h] BYREF
  __int128 value; // [rsp+A0h] [rbp-60h] BYREF
  __int64 v908; // [rsp+B0h] [rbp-50h]
  __int64 v909; // [rsp+B8h] [rbp-48h]
  __int64 v910; // [rsp+C0h] [rbp-40h]
  unsigned __int64 v911[5]; // [rsp+C8h] [rbp-38h] BYREF
  float v912; // [rsp+F0h] [rbp-10h] BYREF
  unsigned int v913; // [rsp+F4h] [rbp-Ch] BYREF
  unsigned int v914; // [rsp+F8h] [rbp-8h] BYREF
  float v915; // [rsp+100h] [rbp+0h] BYREF
  float v916; // [rsp+104h] [rbp+4h]
  float v917; // [rsp+108h] [rbp+8h]
  int v918; // [rsp+10Ch] [rbp+Ch]
  unsigned __int8 v919[8]; // [rsp+110h] [rbp+10h] BYREF
  int v920; // [rsp+118h] [rbp+18h]
  __int16 v921; // [rsp+11Ch] [rbp+1Ch]
  __int64 v922; // [rsp+120h] [rbp+20h]
  _DWORD v923[4]; // [rsp+128h] [rbp+28h] BYREF
  void *pointer[2]; // [rsp+138h] [rbp+38h] BYREF
  __int64 v925; // [rsp+148h] [rbp+48h]
  __int64 v926; // [rsp+150h] [rbp+50h]
  __int64 v927; // [rsp+158h] [rbp+58h]
  float a2[4]; // [rsp+160h] [rbp+60h] BYREF
  _DWORD v929[4]; // [rsp+170h] [rbp+70h] BYREF
  float v930[4]; // [rsp+180h] [rbp+80h] BYREF
  float position[4]; // [rsp+190h] [rbp+90h] BYREF
  float v932[4]; // [rsp+1A0h] [rbp+A0h] BYREF
  _DWORD v933[4]; // [rsp+1B0h] [rbp+B0h] BYREF
  _DWORD v934[4]; // [rsp+1C0h] [rbp+C0h] BYREF
  __int128 v935; // [rsp+1D0h] [rbp+D0h] BYREF
  __int64 v936; // [rsp+1E0h] [rbp+E0h]
  __int64 v937; // [rsp+1E8h] [rbp+E8h]
  __int64 v938; // [rsp+1F0h] [rbp+F0h]
  char v939[8]; // [rsp+1F8h] [rbp+F8h] BYREF
  _QWORD v940[5]; // [rsp+200h] [rbp+100h] BYREF
  unsigned __int64 v941[5]; // [rsp+228h] [rbp+128h] BYREF
  _QWORD options[2]; // [rsp+250h] [rbp+150h] BYREF
  char v943; // [rsp+260h] [rbp+160h]
  bool v944; // [rsp+261h] [rbp+161h]
  __int64 v945; // [rsp+268h] [rbp+168h]
  unsigned __int64 v946[5]; // [rsp+270h] [rbp+170h] BYREF
  unsigned __int64 v947[5]; // [rsp+298h] [rbp+198h] BYREF
  _DWORD v948[4]; // [rsp+2C0h] [rbp+1C0h] BYREF
  unsigned __int64 v949[5]; // [rsp+2D0h] [rbp+1D0h] BYREF
  int v950; // [rsp+2F8h] [rbp+1F8h]
  __int64 v951; // [rsp+2FCh] [rbp+1FCh]
  __int64 v952; // [rsp+304h] [rbp+204h]
  __int64 v953; // [rsp+30Ch] [rbp+20Ch]
  __int64 v954; // [rsp+314h] [rbp+214h]
  _QWORD a1[5]; // [rsp+320h] [rbp+220h] BYREF
  unsigned __int64 v956[5]; // [rsp+348h] [rbp+248h] BYREF
  unsigned __int64 v957[5]; // [rsp+370h] [rbp+270h] BYREF
  unsigned __int64 v958[5]; // [rsp+398h] [rbp+298h] BYREF
  char v959[8]; // [rsp+3C0h] [rbp+2C0h] BYREF
  char v960[8]; // [rsp+3C8h] [rbp+2C8h] BYREF
  char v961[8]; // [rsp+3D0h] [rbp+2D0h] BYREF
  unsigned __int64 v962[5]; // [rsp+3D8h] [rbp+2D8h] BYREF
  __int128 v963; // [rsp+400h] [rbp+300h] BYREF
  __int128 v964; // [rsp+410h] [rbp+310h] BYREF
  unsigned __int64 v965[5]; // [rsp+420h] [rbp+320h] BYREF
  unsigned __int64 v966[5]; // [rsp+448h] [rbp+348h] BYREF
  unsigned __int64 v967[5]; // [rsp+470h] [rbp+370h] BYREF
  unsigned __int64 v968[5]; // [rsp+498h] [rbp+398h] BYREF
  unsigned __int64 v969[5]; // [rsp+4C0h] [rbp+3C0h] BYREF
  unsigned __int64 v970[5]; // [rsp+4E8h] [rbp+3E8h] BYREF
  unsigned __int64 v971[5]; // [rsp+510h] [rbp+410h] BYREF
  unsigned __int64 v972[5]; // [rsp+538h] [rbp+438h] BYREF
  unsigned __int64 v973[5]; // [rsp+560h] [rbp+460h] BYREF
  unsigned __int64 v974[5]; // [rsp+588h] [rbp+488h] BYREF
  unsigned __int64 v975[5]; // [rsp+5B0h] [rbp+4B0h] BYREF
  unsigned __int64 v976[5]; // [rsp+5D8h] [rbp+4D8h] BYREF
  unsigned __int64 v977[5]; // [rsp+600h] [rbp+500h] BYREF
  unsigned __int64 v978[5]; // [rsp+628h] [rbp+528h] BYREF
  unsigned __int64 v979[5]; // [rsp+650h] [rbp+550h] BYREF
  unsigned __int64 v980[5]; // [rsp+678h] [rbp+578h] BYREF
  unsigned __int64 v981[5]; // [rsp+6A0h] [rbp+5A0h] BYREF
  unsigned __int64 v982[5]; // [rsp+6C8h] [rbp+5C8h] BYREF
  unsigned __int64 v983[5]; // [rsp+6F0h] [rbp+5F0h] BYREF
  unsigned __int64 v984[5]; // [rsp+718h] [rbp+618h] BYREF
  unsigned __int64 v985[6]; // [rsp+740h] [rbp+640h] BYREF
  char v986[16]; // [rsp+770h] [rbp+670h] BYREF
  char v987[16]; // [rsp+780h] [rbp+680h] BYREF
  __int64 v988; // [rsp+790h] [rbp+690h] BYREF
  __int64 *v989; // [rsp+798h] [rbp+698h]
  char v990; // [rsp+7A0h] [rbp+6A0h]
  __int64 v991; // [rsp+7A8h] [rbp+6A8h] BYREF
  __int64 *v992; // [rsp+7B0h] [rbp+6B0h]
  char v993; // [rsp+7B8h] [rbp+6B8h]
  __int64 v994; // [rsp+7C0h] [rbp+6C0h] BYREF
  __int64 *v995; // [rsp+7C8h] [rbp+6C8h]
  char v996; // [rsp+7D0h] [rbp+6D0h]
  __int64 v997; // [rsp+7D8h] [rbp+6D8h] BYREF
  __int64 *v998; // [rsp+7E0h] [rbp+6E0h]
  char v999; // [rsp+7E8h] [rbp+6E8h]
  __int64 v1000; // [rsp+7F0h] [rbp+6F0h] BYREF
  __int64 *v1001; // [rsp+7F8h] [rbp+6F8h]
  char v1002; // [rsp+800h] [rbp+700h]
  __int64 v1003; // [rsp+808h] [rbp+708h] BYREF
  __int64 *v1004; // [rsp+810h] [rbp+710h]
  char v1005; // [rsp+818h] [rbp+718h]
  __int64 v1006; // [rsp+820h] [rbp+720h] BYREF
  __int64 *v1007; // [rsp+828h] [rbp+728h]
  char v1008; // [rsp+830h] [rbp+730h]
  __int64 v1009; // [rsp+838h] [rbp+738h] BYREF
  __int64 *v1010; // [rsp+840h] [rbp+740h]
  char v1011; // [rsp+848h] [rbp+748h]
  _DWORD entry[4]; // [rsp+850h] [rbp+750h] BYREF
  __int64 v1013; // [rsp+860h] [rbp+760h]
  __int64 v1014; // [rsp+868h] [rbp+768h] BYREF
  __int64 *v1015; // [rsp+870h] [rbp+770h]
  char v1016; // [rsp+878h] [rbp+778h]
  __int64 v1017; // [rsp+880h] [rbp+780h] BYREF
  __int64 *v1018; // [rsp+888h] [rbp+788h]
  char v1019; // [rsp+890h] [rbp+790h]
  __int64 v1020; // [rsp+898h] [rbp+798h] BYREF
  __int64 *v1021; // [rsp+8A0h] [rbp+7A0h]
  char v1022; // [rsp+8A8h] [rbp+7A8h]
  __int64 v1023; // [rsp+8B0h] [rbp+7B0h] BYREF
  __int64 *v1024; // [rsp+8B8h] [rbp+7B8h]
  char v1025; // [rsp+8C0h] [rbp+7C0h]
  __int64 v1026; // [rsp+8C8h] [rbp+7C8h] BYREF
  __int64 *v1027; // [rsp+8D0h] [rbp+7D0h]
  char v1028; // [rsp+8D8h] [rbp+7D8h]
  __int64 v1029; // [rsp+8E0h] [rbp+7E0h] BYREF
  __int64 *v1030; // [rsp+8E8h] [rbp+7E8h]
  char v1031; // [rsp+8F0h] [rbp+7F0h]
  __int64 v1032; // [rsp+8F8h] [rbp+7F8h] BYREF
  __int64 *v1033; // [rsp+900h] [rbp+800h]
  char v1034; // [rsp+908h] [rbp+808h]
  __int64 v1035; // [rsp+910h] [rbp+810h] BYREF
  __int64 *v1036; // [rsp+918h] [rbp+818h]
  char v1037; // [rsp+920h] [rbp+820h]
  __int64 v1038[2]; // [rsp+928h] [rbp+828h] BYREF
  char v1039; // [rsp+938h] [rbp+838h]
  __int64 v1040[2]; // [rsp+940h] [rbp+840h] BYREF
  char v1041; // [rsp+950h] [rbp+850h]
  __int64 v1042[2]; // [rsp+958h] [rbp+858h] BYREF
  char v1043; // [rsp+968h] [rbp+868h]
  __int64 v1044[2]; // [rsp+970h] [rbp+870h] BYREF
  char v1045; // [rsp+980h] [rbp+880h]
  __int64 v1046[2]; // [rsp+988h] [rbp+888h] BYREF
  char v1047; // [rsp+998h] [rbp+898h]
  __int64 v1048[2]; // [rsp+9A0h] [rbp+8A0h] BYREF
  char v1049; // [rsp+9B0h] [rbp+8B0h]
  __int64 v1050[2]; // [rsp+9B8h] [rbp+8B8h] BYREF
  char v1051; // [rsp+9C8h] [rbp+8C8h]
  __int64 v1052[2]; // [rsp+9D0h] [rbp+8D0h] BYREF
  char v1053; // [rsp+9E0h] [rbp+8E0h]
  __int64 v1054[2]; // [rsp+9E8h] [rbp+8E8h] BYREF
  char v1055; // [rsp+9F8h] [rbp+8F8h]
  __int64 v1056[2]; // [rsp+A00h] [rbp+900h] BYREF
  char v1057; // [rsp+A10h] [rbp+910h]
  __int64 v1058[2]; // [rsp+A18h] [rbp+918h] BYREF
  char v1059; // [rsp+A28h] [rbp+928h]
  __int64 v1060[2]; // [rsp+A30h] [rbp+930h] BYREF
  char v1061; // [rsp+A40h] [rbp+940h]
  __int64 v1062[2]; // [rsp+A48h] [rbp+948h] BYREF
  char v1063; // [rsp+A58h] [rbp+958h]
  __int64 v1064[2]; // [rsp+A60h] [rbp+960h] BYREF
  char v1065; // [rsp+A70h] [rbp+970h]
  __int64 v1066[2]; // [rsp+A78h] [rbp+978h] BYREF
  char v1067; // [rsp+A88h] [rbp+988h]
  __int64 v1068[2]; // [rsp+A90h] [rbp+990h] BYREF
  char v1069; // [rsp+AA0h] [rbp+9A0h]
  __int64 v1070[2]; // [rsp+AA8h] [rbp+9A8h] BYREF
  char v1071; // [rsp+AB8h] [rbp+9B8h]
  __int64 v1072[2]; // [rsp+AC0h] [rbp+9C0h] BYREF
  char v1073; // [rsp+AD0h] [rbp+9D0h]
  __int64 v1074[2]; // [rsp+AD8h] [rbp+9D8h] BYREF
  char v1075; // [rsp+AE8h] [rbp+9E8h]
  __int64 v1076[2]; // [rsp+AF0h] [rbp+9F0h] BYREF
  char v1077; // [rsp+B00h] [rbp+A00h]
  __int64 v1078[2]; // [rsp+B08h] [rbp+A08h] BYREF
  char v1079; // [rsp+B18h] [rbp+A18h]
  __int64 v1080[2]; // [rsp+B20h] [rbp+A20h] BYREF
  char v1081; // [rsp+B30h] [rbp+A30h]
  __int64 v1082[2]; // [rsp+B38h] [rbp+A38h] BYREF
  char v1083; // [rsp+B48h] [rbp+A48h]
  __int64 v1084[2]; // [rsp+B50h] [rbp+A50h] BYREF
  char v1085; // [rsp+B60h] [rbp+A60h]
  __int64 v1086[2]; // [rsp+B68h] [rbp+A68h] BYREF
  char v1087; // [rsp+B78h] [rbp+A78h]
  __int64 v1088[2]; // [rsp+B80h] [rbp+A80h] BYREF
  char v1089; // [rsp+B90h] [rbp+A90h]
  __int64 v1090[2]; // [rsp+B98h] [rbp+A98h] BYREF
  char v1091; // [rsp+BA8h] [rbp+AA8h]
  __int64 v1092[2]; // [rsp+BB0h] [rbp+AB0h] BYREF
  char v1093; // [rsp+BC0h] [rbp+AC0h]
  __int64 v1094[2]; // [rsp+BC8h] [rbp+AC8h] BYREF
  char v1095; // [rsp+BD8h] [rbp+AD8h]
  __int64 v1096[2]; // [rsp+BE0h] [rbp+AE0h] BYREF
  char v1097; // [rsp+BF0h] [rbp+AF0h]
  __int64 v1098[2]; // [rsp+BF8h] [rbp+AF8h] BYREF
  char v1099; // [rsp+C08h] [rbp+B08h]
  __int64 v1100[2]; // [rsp+C10h] [rbp+B10h] BYREF
  char v1101; // [rsp+C20h] [rbp+B20h]
  __int64 v1102[2]; // [rsp+C28h] [rbp+B28h] BYREF
  char v1103; // [rsp+C38h] [rbp+B38h]
  __int64 v1104[2]; // [rsp+C40h] [rbp+B40h] BYREF
  char v1105; // [rsp+C50h] [rbp+B50h]
  __int64 v1106[2]; // [rsp+C58h] [rbp+B58h] BYREF
  char v1107; // [rsp+C68h] [rbp+B68h]
  __int64 v1108[2]; // [rsp+C70h] [rbp+B70h] BYREF
  char v1109; // [rsp+C80h] [rbp+B80h]
  __int64 v1110[2]; // [rsp+C88h] [rbp+B88h] BYREF
  char v1111; // [rsp+C98h] [rbp+B98h]
  __int64 v1112[2]; // [rsp+CA0h] [rbp+BA0h] BYREF
  char v1113; // [rsp+CB0h] [rbp+BB0h]
  __int64 v1114[2]; // [rsp+CB8h] [rbp+BB8h] BYREF
  char v1115; // [rsp+CC8h] [rbp+BC8h]
  __int64 v1116[2]; // [rsp+CD0h] [rbp+BD0h] BYREF
  char v1117; // [rsp+CE0h] [rbp+BE0h]
  _QWORD v1118[2]; // [rsp+CE8h] [rbp+BE8h] BYREF
  char v1119; // [rsp+CF8h] [rbp+BF8h]
  __int64 v1120[2]; // [rsp+D00h] [rbp+C00h] BYREF
  char v1121; // [rsp+D10h] [rbp+C10h]
  __int64 v1122[2]; // [rsp+D18h] [rbp+C18h] BYREF
  char v1123; // [rsp+D28h] [rbp+C28h]
  __int64 v1124[2]; // [rsp+D30h] [rbp+C30h] BYREF
  char v1125; // [rsp+D40h] [rbp+C40h]
  __int64 v1126[2]; // [rsp+D48h] [rbp+C48h] BYREF
  char v1127; // [rsp+D58h] [rbp+C58h]
  __int64 v1128[2]; // [rsp+D60h] [rbp+C60h] BYREF
  char v1129; // [rsp+D70h] [rbp+C70h]
  __int64 v1130[2]; // [rsp+D78h] [rbp+C78h] BYREF
  char v1131; // [rsp+D88h] [rbp+C88h]
  __int64 v1132[2]; // [rsp+D90h] [rbp+C90h] BYREF
  char v1133; // [rsp+DA0h] [rbp+CA0h]
  __int64 v1134[2]; // [rsp+DA8h] [rbp+CA8h] BYREF
  char v1135; // [rsp+DB8h] [rbp+CB8h]
  __int64 v1136[2]; // [rsp+DC0h] [rbp+CC0h] BYREF
  char v1137; // [rsp+DD0h] [rbp+CD0h]
  __int64 v1138[2]; // [rsp+DD8h] [rbp+CD8h] BYREF
  char v1139; // [rsp+DE8h] [rbp+CE8h]
  __int64 v1140[2]; // [rsp+DF0h] [rbp+CF0h] BYREF
  char v1141; // [rsp+E00h] [rbp+D00h]
  __int64 v1142[2]; // [rsp+E08h] [rbp+D08h] BYREF
  char v1143; // [rsp+E18h] [rbp+D18h]
  __int64 v1144[2]; // [rsp+E20h] [rbp+D20h] BYREF
  char v1145; // [rsp+E30h] [rbp+D30h]
  __int64 v1146[2]; // [rsp+E38h] [rbp+D38h] BYREF
  char v1147; // [rsp+E48h] [rbp+D48h]
  __int64 v1148[2]; // [rsp+E50h] [rbp+D50h] BYREF
  char v1149; // [rsp+E60h] [rbp+D60h]
  __int64 v1150[2]; // [rsp+E68h] [rbp+D68h] BYREF
  char v1151; // [rsp+E78h] [rbp+D78h]
  __int64 v1152[2]; // [rsp+E80h] [rbp+D80h] BYREF
  char v1153; // [rsp+E90h] [rbp+D90h]
  __int64 v1154[2]; // [rsp+E98h] [rbp+D98h] BYREF
  char v1155; // [rsp+EA8h] [rbp+DA8h]
  __int64 v1156[2]; // [rsp+EB0h] [rbp+DB0h] BYREF
  char v1157; // [rsp+EC0h] [rbp+DC0h]
  __int64 v1158[2]; // [rsp+EC8h] [rbp+DC8h] BYREF
  char v1159; // [rsp+ED8h] [rbp+DD8h]
  __int64 v1160[2]; // [rsp+EE0h] [rbp+DE0h] BYREF
  char v1161; // [rsp+EF0h] [rbp+DF0h]
  __int64 v1162[2]; // [rsp+EF8h] [rbp+DF8h] BYREF
  char v1163; // [rsp+F08h] [rbp+E08h]
  __int64 v1164[2]; // [rsp+F10h] [rbp+E10h] BYREF
  char v1165; // [rsp+F20h] [rbp+E20h]
  __int64 v1166[2]; // [rsp+F28h] [rbp+E28h] BYREF
  char v1167; // [rsp+F38h] [rbp+E38h]
  __int64 v1168[2]; // [rsp+F40h] [rbp+E40h] BYREF
  char v1169; // [rsp+F50h] [rbp+E50h]
  __int64 v1170[2]; // [rsp+F58h] [rbp+E58h] BYREF
  char v1171; // [rsp+F68h] [rbp+E68h]
  struct tm v1172; // [rsp+F70h] [rbp+E70h] BYREF
  __int64 v1173[3]; // [rsp+F98h] [rbp+E98h] BYREF
  _BYTE self[112]; // [rsp+FB0h] [rbp+EB0h] BYREF
  __int64 v1175[52]; // [rsp+1020h] [rbp+F20h] BYREF
  __int64 v1176; // [rsp+11C0h] [rbp+10C0h] BYREF
  int v1177; // [rsp+11C8h] [rbp+10C8h]
  int v1178; // [rsp+11CCh] [rbp+10CCh]
  __m128i si128; // [rsp+11D0h] [rbp+10D0h] BYREF
  unsigned int v1180; // [rsp+11E0h] [rbp+10E0h]
  unsigned int v1181; // [rsp+11E4h] [rbp+10E4h]
  unsigned int v1182; // [rsp+11E8h] [rbp+10E8h]
  unsigned int v1183; // [rsp+11ECh] [rbp+10ECh]
  _DWORD v1184[4]; // [rsp+11F0h] [rbp+10F0h] BYREF
  _DWORD v1185[4]; // [rsp+1200h] [rbp+1100h] BYREF
  _DWORD payload[4]; // [rsp+1210h] [rbp+1110h] BYREF
  _DWORD instancePlayerCounts[4]; // [rsp+1220h] [rbp+1120h] BYREF
  __int128 v1188; // [rsp+1230h] [rbp+1130h]
  _DWORD v1189[2]; // [rsp+1240h] [rbp+1140h] BYREF
  char v1190; // [rsp+1248h] [rbp+1148h]
  __int16 v1191; // [rsp+1249h] [rbp+1149h]
  __int128 v1192; // [rsp+1250h] [rbp+1150h] BYREF
  __int128 v1193; // [rsp+1260h] [rbp+1160h] BYREF
  __int64 v1194; // [rsp+12C8h] [rbp+11C8h]

  entityId = entityId;
  p3 = p3;
  p4 = p4;
  p1 = p1;
  p2 = p2;
  v15 = (float *)Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, entityId);
  v19 = (__int64)v15;
  if ( dword_142AAB778 == 3 )
    return;
  v1194 = v12;
  if ( category > 0x76C )
  {
    if ( category > 0xC1C )
    {
      if ( category <= 0xD48 )
      {
        if ( category == 3400 )
        {
          sub_140851350(dword_142AAB6F0, p1);
        }
        else
        {
          switch ( category )
          {
            case 0xC1Du:
              sub_140C48BD0(xmmword_142AF8708, p1);
              break;
            case 0xC1Eu:
              sub_140C48CB0((__int64)xmmword_142AF8708, p1, p2, p3);
              break;
            case 0xC1Fu:
              sub_140C48F40((__int64)xmmword_142AF8708);
              break;
            case 0xC80u:
            case 0xC81u:
            case 0xC82u:
            case 0xC83u:
            case 0xC84u:
            case 0xC85u:
            case 0xC86u:
            case 0xC87u:
            case 0xC88u:
            case 0xC8Au:
            case 0xC8Bu:
            case 0xC8Cu:
            case 0xC8Du:
            case 0xC8Eu:
            case 0xC8Fu:
            case 0xC90u:
            case 0xC91u:
            case 0xC92u:
            case 0xC93u:
            case 0xC94u:
            case 0xC95u:
            case 0xC96u:
            case 0xC97u:
            case 0xC98u:
            case 0xC99u:
            case 0xC9Au:
            case 0xC9Bu:
            case 0xC9Du:
            case 0xC9Eu:
            case 0xC9Fu:
            case 0xCA0u:
            case 0xCA1u:
            case 0xCA2u:
            case 0xCA4u:
            case 0xCA5u:
            case 0xCA6u:
            case 0xCA7u:
            case 0xCA8u:
            case 0xCA9u:
            case 0xCAAu:
            case 0xCABu:
            case 0xCADu:
            case 0xCAEu:
              if ( sub_140EA8B30() )
              {
                v874 = sub_140EA8B30();
                sub_140EA9730(v874, category, p1, p2, p3, p4, p5, p6);
              }
              break;
            case 0xC89u:
              if ( sub_140EA8B30() )
              {
                v876 = sub_140EA8B30();
                sub_140EA9730(v876, category, entityId, p1, p2, p3, p4, p5);
              }
              UIModule = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v878 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
              v879 = sub_14048CED0(v878);
              sub_1409FAE90(v879);
              v880 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
              sub_14048CEA0(v880);
              sub_1409F00D0();
              v881 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)UIModule + 296LL))(UIModule);
              v882 = sub_14048CF00(v881);
              sub_140A06BA0(v882);
              break;
            case 0xC9Cu:
              if ( sub_140EA8B30() )
              {
                v875 = sub_140EA8B30();
                sub_140EA9730(v875, category, entityId, p1, p2, p3, p4, p5);
              }
              break;
            case 0xCDAu:
              if ( v15 )
                sub_14088E230((__int64)&qword_142AD9760, (__int64)v15, p1, p2);
              break;
            case 0xCDBu:
              if ( v15 )
                sub_14088E0C0((__int64)&qword_142AD9760, (__int64)v15);
              break;
            case 0xCDCu:
              if ( v15 )
                sub_14088E460((__int64)&qword_142AD9760);
              break;
            case 0xCDDu:
              if ( v15 )
                sub_14088E8A0((__int64)&qword_142AD9760);
              break;
            case 0xCDEu:
              sub_14088E830((__int64)&qword_142AD9760);
              break;
            case 0xCE4u:
              sub_140BE5210((__int64)&byte_142ADF3B8, (__int64)&qword_142ADFA48, p1, p2 != 0);
              break;
            case 0xD16u:
              v883 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v884 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v883 + 296LL))(v883);
              AgentByInternalId = (_QWORD **)Client__UI__Agent__AgentModule__GetAgentByInternalId(v884, 0x34u);
              if ( AgentByInternalId )
                sub_140CE9A40(AgentByInternalId);
              break;
            default:
              goto LABEL_1910;
          }
        }
        return;
      }
      if ( category <= 0xE74 )
      {
        if ( category == 3700 )
        {
          v888 = sub_140B777C0();
          EventHandlerById = j_Client__Game__Event__EventFramework__GetEventHandlerById(v888, 655361);
          if ( EventHandlerById )
            sub_140EA14F0(EventHandlerById, p1, p2);
        }
        else
        {
          switch ( category )
          {
            case 0xD49u:
              sub_140851390(dword_142AAB6F0, p1);
              break;
            case 0xD4Au:
              if ( v15 )
                (*(void (__fastcall **)(float *, __int64))(*(_QWORD *)v15 + 312LL))(v15, 32);
              break;
            case 0xD7Au:
            case 0xD7Bu:
            case 0xD7Cu:
            case 0xD7Du:
            case 0xD7Eu:
            case 0xD7Fu:
              sub_140B2F2B0((__int64)qword_142ADCE78, category, p1, p2, p3, p4, p5);
              break;
            case 0xE10u:
            case 0xE11u:
              v886 = (void *)sub_140B777C0();
              MassivePcContentDirector = Client__Game__Event__EventFramework__GetMassivePcContentDirector(v886);
              if ( MassivePcContentDirector )
                sub_141A237B0((__int64)MassivePcContentDirector, category, p1, p2, p3, p4, p5, p6);
              break;
            default:
              goto LABEL_1910;
          }
        }
        return;
      }
      switch ( category )
      {
        case 0xE75u:
          v898 = sub_140B777C0();
          v899 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v898, 655361);
          if ( v899 )
            sub_140EA1580(v899, p1);
          return;
        case 0xE76u:
          v896 = sub_140B777C0();
          v897 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v896, 655361);
          if ( v897 )
            sub_140EA15C0(v897);
          return;
        case 0xE77u:
          if ( unknown_libname_847() )
          {
            v895 = sub_14198C980();
            sub_14198D0F0(v895, 3703);
          }
          return;
        case 0xEECu:
          dword_142ADFC90 = p1;
          return;
        case 0xFA0u:
          v893 = sub_140B777C0();
          v894 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v893, 721872);
          if ( v894 )
            sub_14199C6A0(v894);
          return;
      }
    }
    else
    {
      if ( category == 3100 )
      {
        sub_140C48F70((__int64)xmmword_142AF8708, p1);
        return;
      }
      if ( category > 0x8CA )
      {
        if ( category <= 0xA28 )
        {
          if ( category == 2600 )
          {
            v853 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v854 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v853 + 296LL))(v853);
            v855 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v854, 0x17Fu);
            if ( v855 )
              sub_140D8AEF0(v855, p1, p2);
          }
          else
          {
            switch ( category )
            {
              case 0x8CBu:
                v848 = (_BYTE *)EXD__McGuffin__Row_14083FA30(p2);
                if ( v848 && *v848 )
                {
                  sub_140BE4B60((__int64)&byte_142ADF3B8, p2, p3 != 0);
                  v849 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
                  v850 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v849 + 64LL))(v849);
                  sub_1400FDA70(v850, p2, p3 == 0);
                }
                break;
              case 0x8FCu:
                if ( sub_140EA6BC0() )
                {
                  v851 = sub_140EA6BC0();
                  sub_140EA6DF0(v851, p1, p2 != 0);
                }
                break;
              case 0x8FDu:
                if ( sub_140EA6BC0() )
                {
                  v852 = sub_140EA6BC0();
                  sub_140EA7BF0(v852, p1);
                }
                break;
              case 0x92Fu:
                v836 = (__int64 *)sub_141780270();
                sub_141781660(v836, p1, p2);
                break;
              case 0x930u:
                v837 = sub_141780270();
                sub_1417816C0(v837, p1);
                break;
              case 0x931u:
                v838 = sub_141780270();
                sub_141781780(v838, p1, p2);
                break;
              case 0x932u:
                v839 = sub_141780270();
                sub_141781880(v839, p1, p2, p3, p4, p5);
                break;
              case 0x933u:
                if ( v15 )
                  sub_14089A730((__int64)v15, p1);
                break;
              case 0x934u:
                sub_141780510(p1, p2 != 0);
                break;
              case 0x935u:
                sub_141780680(p1);
                sub_140848E00((__int64)&qword_142AA8218, p1);
                break;
              case 0x937u:
                sub_141780840(
                  p1,
                  p2,
                  p3,
                  (float)p4 / 1000.0,
                  (float)(int)p5 / 1000.0,
                  (float)(int)p6 / 1000.0);
                break;
              case 0x938u:
                sub_141780A20(p1, p2);
                break;
              case 0x939u:
                sub_141780D00(p1, p2);
                break;
              case 0x93Au:
                sub_141781400(p1);
                break;
              case 0x93Bu:
                v843 = sub_141780270();
                sub_141781CE0(v843, p1, p2, p3);
                break;
              case 0x93Cu:
                v840 = sub_141780270();
                sub_1417851A0(v840, p1, p2);
                if ( p3 )
                {
                  v841 = sub_141780270();
                  sub_141785220(v841, p1, p3);
                }
                break;
              case 0x93Du:
                v844 = sub_141780270();
                sub_141781DD0(v844, p1, p2);
                break;
              case 0x93Eu:
                v845 = sub_141780270();
                sub_141781E80(v845, p1 != 0, p2, p3, p4);
                break;
              case 0x93Fu:
                v842 = sub_141780270();
                sub_141783020(v842, p1, p2, p3, p4, p5, p6);
                break;
              case 0x940u:
                sub_141780BA0(p1, (float)(int)p2 / 1000.0, (float)p3 / 1000.0, (float)p4 / 1000.0);
                break;
              case 0x941u:
                v846 = sub_141780270();
                sub_141782900(v846, p1);
                break;
              case 0x942u:
                v847 = sub_141780270();
                sub_1417821A0(v847, p1);
                break;
              case 0x943u:
                sub_141781420(p1, p2 != 0);
                break;
              case 0x960u:
                sub_140BE4D00((__int64)&byte_142ADF3B8, p1, p2);
                break;
              case 0x9C4u:
                sub_140BE4D70((__int64)&byte_142ADF3B8, p1, p2);
                break;
              default:
                goto LABEL_1910;
            }
          }
          return;
        }
        if ( category <= 0xBB8 )
        {
          if ( category == 3000 )
          {
            if ( unknown_libname_843() )
            {
              v1185[0] = p2;
              v1185[1] = p3;
              v1185[2] = p4;
              v1185[3] = p5;
              v873 = sub_14198A420();
              sub_14198A660(v873, p1, (__int64)v1185, p6);
            }
          }
          else
          {
            switch ( category )
            {
              case 0xA5Au:
                sub_140BCB040(11);
                break;
              case 0xA5Bu:
                v913 = p1;
                sub_140BCB0B0(11, &v913, 1);
                break;
              case 0xA8Cu:
                v861 = (void *)sub_140B777C0();
                ContentDirector = Client__Game__Event__EventFramework__GetContentDirector(v861);
                if ( ContentDirector )
                  sub_140B6C7B0((__int64)ContentDirector, p1, p2, p3);
                break;
              case 0xA8Du:
                v863 = (void *)sub_140B777C0();
                v864 = Client__Game__Event__EventFramework__GetContentDirector(v863);
                if ( v864 )
                  sub_140B6C7D0((__int64)v864, p1);
                break;
              case 0xA8Eu:
                v865 = (void *)sub_140B777C0();
                v866 = Client__Game__Event__EventFramework__GetContentDirector(v865);
                if ( v866 )
                  sub_140B6C7F0((__int64)v866, p1);
                break;
              case 0xA8Fu:
                v867 = (void *)sub_140B777C0();
                v868 = Client__Game__Event__EventFramework__GetContentDirector(v867);
                if ( v868 )
                  sub_140B6C810((__int64)v868, p1, p2 != 0);
                break;
              case 0xA90u:
                v869 = (void *)sub_140B777C0();
                v870 = Client__Game__Event__EventFramework__GetContentDirector(v869);
                if ( v870 )
                  sub_140B6C830((__int64)v870, p1, p2, p3);
                break;
              case 0xA91u:
                v871 = (void *)sub_140B777C0();
                v872 = Client__Game__Event__EventFramework__GetContentDirector(v871);
                if ( v872 )
                  sub_140B6C850((__int64)v872, p1, p2);
                break;
              case 0xAF0u:
                v856 = sub_140B777C0();
                v857 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v856, p1);
                if ( v857 )
                  sub_140DFF6B0(v857, p2, p3, p4, p5, p6);
                break;
              case 0xAF2u:
                if ( qword_142ADE350 )
                {
                  v858 = sub_140B777C0();
                  sub_1417C9F30(v858 + 432);
                }
                break;
              case 0xAF3u:
                if ( qword_142ADE350 )
                {
                  v859 = sub_140B777C0();
                  sub_1417C8D60(v859 + 432);
                }
                break;
              case 0xAF4u:
                if ( qword_142ADE350 )
                {
                  sub_140B777C0();
                  sub_1417C8D80();
                }
                break;
              case 0xAF5u:
                if ( qword_142ADE350 )
                {
                  v860 = sub_140B777C0();
                  sub_140B804C0(v860, p1, p2, p3, p4, p5);
                }
                break;
              case 0xB54u:
                sub_140C4DFC0((__int64)&qword_142ADE980, entityIda, &p2, &p3);
                break;
              case 0xB55u:
                sub_140C4E010(
                  &qword_142ADE980,
                  entityIda,
                  &p2,
                  (const unsigned int *)&p3,
                  (const unsigned int *)&p4);
                v914 = 2;
                v906 = 19743;
                sub_140C4E040((__int64)&qword_142ADE980, &v906, &v914);
                break;
              default:
                goto LABEL_1910;
            }
          }
          return;
        }
      }
      else
      {
        switch ( category )
        {
          case 0x8CAu:
            nullsub_74();
            return;
          case 0x7D0u:
            v835 = (_DWORD *)sub_141A21340();
            if ( v835 )
              sub_141A20020(v835, p1, p2, p3);
            return;
          case 0x7D1u:
            sub_140C44DD0((__int64)&qword_142AF5E80, p1, p2, p3, p4, p5);
            return;
          case 0x834u:
            v833 = (void *)sub_140B777C0();
            v834 = Client__Game__Event__EventFramework__GetContentDirector(v833);
            if ( v834 )
            {
              if ( p1 )
                v19 = 0;
              sub_140B6D010(v834, v19, p2, p3);
            }
            return;
          case 0x835u:
            sub_140B6C870(p1, p2, p3);
            return;
        }
      }
    }
LABEL_1910:
    if ( !sub_140ECDB40()
      || (v890 = sub_140ECDB40(), !sub_140ECF140(v890, category, p1, p2, p3, p4, p5, p6)) )
    {
      if ( !sub_14198E450()
        || (v891 = sub_14198E450(),
            !(*(unsigned __int8 (__fastcall **)(__int64, _QWORD, _QWORD, _QWORD, int, int, unsigned int, unsigned int))(*(_QWORD *)v891 + 48LL))(
               v891,
               category,
               p1,
               p2,
               p3,
               p4,
               p5,
               p6)) )
      {
        if ( sub_140E6B570() )
        {
          v892 = sub_140E6B570();
          sub_140E6B110(v892, entityId, category, p1, p2);
        }
        if ( !sub_140B2B9C0((__int64)&qword_142AA8180, v19, entityId, category, p1)
          && !sub_1408FD3E0(qword_142AA81A0, (void *)v19, entityId, category, p1, p2, p3, p4, p5, p6, targetId) )
        {
          sub_1409034F0(category, p1, p2, p3, p4, p5, p6);
        }
      }
    }
    return;
  }
  if ( category != 1900 )
  {
    switch ( category )
    {
      case 0u:
        if ( !v15 )
          return;
        v20 = (*((_BYTE *)v15 + 3454) & 0x40) != 0;
        if ( p3 == 1 )
        {
          if ( sub_140897A40((__int64)v15, isRecorded, 0) )
          {
            Client__Game__UI__WeaponState__OnActorControlWeaponDrawn(&byte_142ADF3A0, p1 == 1, p2 == 1);
            goto LABEL_12;
          }
        }
        else if ( sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          Client__Game__UI__WeaponState__OnActorControlWeaponDrawn(&byte_142ADF3A0, p1 == 1, 0);
          goto LABEL_12;
        }
        sub_1408BF1E0(v19 + 2608, p1 == 1, p2 == 1);
LABEL_12:
        if ( v20 != ((*(_BYTE *)(v19 + 3454) & 0x40) != 0) )
        {
          v21 = sub_140B777C0();
          sub_140B82050(v21, v19);
        }
        return;
      case 1u:
        sub_140BDBFD0(&byte_142ADF3B0, p1 == 1);
        return;
      case 2u:
        if ( v15 )
          Client__Game__Character__Character__SetMode(v15, p1, p2);
        return;
      case 3u:
        if ( v15 )
        {
          if ( p1 )
          {
            sub_1408D7300((__int64)(v15 + 1772), p2, targetId);
          }
          else if ( !sub_140897A40((__int64)v15, isRecorded, 0) )
          {
            v61 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19);
            sub_1408DEE80(v61);
            v62 = *(float *)(v19 + 192);
            SpellIdForAction = Client__Game__ActionManager__GetSpellIdForAction(4u, p2);
            sub_14090B4D0(
              (unsigned int *)v19,
              4u,
              p2,
              SpellIdForAction,
              targetId,
              (__int64)&dword_142AA1A80,
              v62,
              0,
              0,
              0xE0000000);
          }
        }
        return;
      case 4u:
        if ( v15 )
        {
          v32 = *((_BYTE *)v15 + 468);
          v33 = 0;
          if ( p1 == 1 )
            v33 = 2;
          *(_BYTE *)(v19 + 468) = v32 & 0xFD | v33;
          if ( !p1 )
          {
            *(_BYTE *)(v19 + 469) = 0;
            *(_QWORD *)(v19 + 472) = 0;
          }
          if ( (unsigned int)sub_140626DA0((__int64)&qword_142AAB990) == entityId )
          {
            v34 = qword_14290B8E0;
            v35 = (**(__int64 (__fastcall ***)(__int64))v19)(v19);
            v36 = sub_14090DC20(v19, v939, 1);
            sub_1407B6090(v34, *(unsigned __int16 *)(v19 + 140), (__int64)v36, v35);
          }
          if ( sub_140897A40(v19, isRecorded, 0) )
          {
            sub_140E13730((__int64)byte_142AF9070, 26, p1 == 1);
            dword_1428BC6B0 = 1084227584;
          }
          v37 = sub_140B777C0();
          if ( p1 )
            sub_140B81A10(v37);
          else
            sub_140B81A30(v37);
        }
        return;
      case 5u:
        if ( v15 )
          sub_140857450(0x75u, v15, v15, -1.0, 0, 0);
        return;
      case 6u:
        if ( v15 )
        {
          v22 = 0;
          v23 = 0;
          if ( p1 != -536870912
            && (v23 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(
                        &off_1428BC9F0,
                        p1)) != 0
            || p2 != -536870912
            && (v23 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p2)) != 0 )
          {
            v22 = v19 != (_QWORD)v23;
          }
          v24 = sub_140B2AF50(v19);
          v25 = *(_BYTE *)(v19 + 461);
          v26 = v25 == 2 || v25 == 11;
          v27 = v26;
          if ( (unsigned int)(*(_DWORD *)(v19 + 132) - 3256) <= 1 )
            v27 = 1;
          if ( v22 )
          {
            if ( v24 )
            {
              v28 = v23;
              v29 = (void *)v19;
              if ( v27 )
                v30 = 439;
              else
                v30 = 558;
            }
            else
            {
              v28 = (void *)v19;
              v29 = v23;
              if ( v27 )
                v30 = 615;
              else
                v30 = 557;
            }
          }
          else
          {
            v28 = (void *)v19;
            v29 = (void *)v19;
            v30 = 617;
            if ( !v27 )
              v30 = 559;
          }
          Client__Game__BattleLog__AddActionLogMessage(v30, v29, v28, 0, 0, 0, 0, 0, 0, 100.0);
          if ( (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v19 + 16LL))(v19) == 2 )
          {
            v31 = sub_14196DA50();
            sub_14196DF90(v31, v19);
          }
        }
        return;
      case 7u:
        if ( v15 )
        {
          v38 = 0;
          v39 = ((unsigned int)sub_14089E7C0((__int64)(v15 + 104)) != p1) + 588;
          if ( p2 )
            v38 = p3;
          Client__Game__BattleLog__AddLogMessage3Params(v39, (void *)v19, p1, p2, v38, 100.0);
          v40 = *(_QWORD *)(v19 + 1768);
          if ( v40 )
            sub_14174C380(v40);
        }
        return;
      case 8u:
        sub_141AAA500(entityId, p1);
        return;
      case 9u:
        if ( v15 )
          sub_141AAA2B0(*((_DWORD *)v15 + 30), p1, p2);
        return;
      case 0xAu:
        if ( p4
          && v15
          && sub_140897A40((__int64)v15, isRecorded, 0)
          && (unsigned __int8)sub_140BE03D0((__int64)&byte_142ADF3B8, 0) == p1 )
        {
          *(_BYTE *)(v19 + 459) = p4;
          sub_140BE5D20((__int64)&byte_142ADF3B8, p4);
        }
        for ( i = p3 + 1; i <= p2; ++i )
          sub_141AAA320(entityId, p1, i);
        return;
      case 0xBu:
        v50 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p1);
        if ( v50 )
          Client__Game__BattleLog__AddLogMessage3Params(0x22Bu, v50, p2, p2, 0, 100.0);
        return;
      case 0xCu:
        if ( v15 )
        {
          v51 = p1;
          if ( p1 )
          {
            Client__Game__BattleLog__AddLogMessage3Params(0x225u, v15, p1, p2 / 0x64, 0, 100.0);
            v51 = p1;
          }
          sub_140BDB830((__int64)&qword_142ADF390 + 4, v51, (float)(int)p2 / 100.0);
        }
        return;
      case 0xDu:
        if ( v15 )
          sub_14090D020((__int64)v15, p1, p2, isRecorded);
        return;
      case 0xEu:
        if ( v15 )
          sub_14090A420(v15, p1, p2, 0, 0.0);
        return;
      case 0xFu:
        if ( v15 )
        {
          sub_14090C270((__int64)v15, p2, p3, p4 == 1);
          v534 = Client__Game__ActionManager__GetSpellIdForAction(p2, p3);
          v535 = EXD__Action__Row_140833940(v534);
          if ( p1 )
          {
            if ( v535 && (*(_BYTE *)(v535 + 61) & 0x10) != 0 )
              Client__Game__BattleLog__AddActionLogMessage(p1, (void *)v19, 0, p2, p3, 0, 0, 0, 0, 100.0);
          }
        }
        return;
      case 0x10u:
        sub_1408EDDD0(&off_1428BBEC0, p1, (float)(int)p2 / 100.0, (float)p3 / 100.0);
        return;
      case 0x11u:
        sub_1408EE240(&off_1428BBEC0, p1, p2, (float)p3 / 100.0);
        return;
      case 0x12u:
        sub_1408EF300((__int64)&off_1428BBEC0, p1, 0.0);
        return;
      case 0x14u:
        if ( v15 )
        {
          v124 = (_QWORD *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          sub_1408A5D10(v124, p1, p2);
          v125 = (__int64 *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 632LL))(v19);
          sub_1408A5E40(v125, p1);
        }
        return;
      case 0x15u:
        if ( v15 )
        {
          v126 = (unsigned __int8 *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          sub_1408A66F0(v126, p1, p2, p3, p4 != 0);
        }
        return;
      case 0x16u:
        if ( v15 )
        {
          v127 = (*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          sub_1408A6D30(v127, p1, p2, p3);
        }
        Group = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        PartyMemberByEntityId = Client__Game__Group__GroupManager__Group__GetPartyMemberByEntityId(Group, entityId);
        if ( PartyMemberByEntityId )
          sub_1408A6D30((__int64)PartyMemberByEntityId, p1, p2, p3);
        sub_140C237D0((__int64)&qword_142AE0870, entityId, p1, p2, p3);
        return;
      case 0x17u:
        if ( v15 )
        {
          v130 = (void *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          Client__Game__StatusManager__ProcessHotDot(v130, (void *)v19, p1, p2, p3, p4, 0);
        }
        return;
      case 0x18u:
        dword_142ADF6A0 = p1;
        Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x24u, 0, 0);
        return;
      case 0x1Au:
        if ( v15 )
          *((_BYTE *)v15 + 6528) = (_BYTE)v15[1632] & 0xFE | (p1 == 1);
        return;
      case 0x1Bu:
        dword_1428C2604 = p1;
        return;
      case 0x1Eu:
        if ( v15 )
        {
          sub_1408D44E0((__int64)(v15 + 1738), p1, p2, p3, p4 != 0);
        }
        else
        {
          v446 = (_DWORD *)sub_140B4FDE0((__int64)&off_1428C1B40, entityId);
          if ( v446 && *v446 != 1 && (unsigned int)(*v446 - 2) <= 1 && v446 != (_DWORD *)-8LL )
            *((_BYTE *)v446 + p1 + 656) = p2;
        }
        return;
      case 0x1Fu:
        if ( v15 )
          sub_140909B50((__int64)v15, p1 & 0x7FFFFFFF, p2, p3, p4, (p1 & 0x80000000) != 0);
        return;
      case 0x20u:
        if ( v15 )
        {
          if ( p1 )
          {
            *((_BYTE *)v15 + 7400) |= 0x40u;
            v123 = sub_140B777C0();
            sub_140B7D980(v123, v19);
          }
          else
          {
            *((_BYTE *)v15 + 7400) &= ~0x40u;
          }
        }
        return;
      case 0x21u:
        *((_BYTE *)Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded) + 32733) = p1;
        return;
      case 0x22u:
        if ( v15 )
          sub_1408CC160((_QWORD *)v15 + 817, p1, p2);
        return;
      case 0x23u:
        if ( v15 )
        {
          v115 = (__int64)(v15 + 1634);
          if ( p2 )
            sub_1408CCD60(v115, p1, p2, (unsigned int)p3, p4);
          else
            sub_1408CCE80(v115, p1, 0, 0, 0);
        }
        return;
      case 0x24u:
        if ( !v15 )
          goto LABEL_354;
        if ( !sub_1401E4B20(v15) || !(*(unsigned __int8 (__fastcall **)(__int64))(*(_QWORD *)v19 + 464LL))(v19) )
        {
          *(_BYTE *)(v19 + 155) |= 0x80u;
          if ( (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v19 + 16LL))(v19) == 2
            && *(_DWORD *)(v19 + 132) == 8784 )
          {
            v116 = *(_QWORD *)(v19 + 1664);
            if ( v116 )
              *(_BYTE *)(v116 + 155) |= 0x80u;
          }
          if ( p1 )
            sub_140909F00((__int64 *)v19, 1.0);
          if ( p2 )
            sub_1408BDCB0(v19 + 2608, p2, 0, 0);
        }
        return;
      case 0x25u:
        if ( v15 )
        {
          (*(void (__fastcall **)(float *, __int64))(*(_QWORD *)v15 + 312LL))(v15, 10);
          sub_140909F00((__int64 *)v19, 1.0);
          if ( !p1 )
            return;
          v117 = EXD__BNpcBase__Row_140835260(*(_DWORD *)(v19 + 132));
          if ( !v117 )
            goto LABEL_353;
          v118 = *(unsigned __int8 *)(v117 + 30);
          if ( !*(_BYTE *)(v117 + 30) || v118 == 1 )
          {
            v120 = sub_140B2B160(v19) + 163;
          }
          else
          {
            v119 = (unsigned __int16 *)EXD__BNpcBasePopVfx__Row_1408354A0(v118);
            if ( !v119 )
            {
LABEL_353:
              v121 = sub_140B2B160(v19);
              sub_140857450(v121 + 163, (void *)v19, (void *)v19, -1.0, 0, 0);
              return;
            }
            v120 = *v119;
          }
          sub_140857450(v120, (void *)v19, (void *)v19, -1.0, 0, 0);
          goto LABEL_353;
        }
LABEL_354:
        v122 = (_DWORD *)sub_140B4FDE0((__int64)&off_1428C1B40, entityId);
        if ( v122 )
        {
          if ( *v122 == 1 || (unsigned int)(*v122 - 2) > 1 )
            v122[31] &= ~0x20u;
          else
            v122[27] &= ~0x20u;
        }
        return;
      case 0x26u:
        if ( v15 )
          *((_BYTE *)v15 + 7400) = (_BYTE)v15[1850] & 0x7F | (p1 != 0 ? 0x80 : 0);
        return;
      case 0x27u:
        if ( v15 )
          sub_14090A970((__int64)v15);
        return;
      case 0x28u:
      case 0x2Au:
      case 0x395u:
        return;
      case 0x29u:
        sub_140C4B410((__int64)&qword_142ADE980, p1, p2 != 0);
        sub_140C50030((__int64)&qword_142ADE980);
        v568 = sub_140B777C0();
        sub_140B80B70(v568, 4, 1);
        return;
      case 0x2Bu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          sub_140BE6190((__int64)&byte_142ADF3B8, p1, p2);
          dword_142ADF6A0 = p3;
        }
        return;
      case 0x2Cu:
        if ( v15 && p1 == 36 )
          Client__Game__BattleLog__AddActionLogMessage(0x259u, v15, v15, 1u, 0x24u, p2, 0, 0, 0, 100.0);
        return;
      case 0x2Du:
        if ( v15 )
        {
          if ( !sub_140897A40((__int64)v15, isRecorded, 0) || *(_BYTE *)(v19 + 9060) == 10 )
            sub_1408C9670(v19 + 6800, p1);
          else
            Client__Game__BattleLog__AddActionLogMessage(
              0x1FEu,
              (void *)v19,
              (void *)v19,
              0,
              0,
              p1,
              0,
              0,
              0,
              100.0);
        }
        return;
      case 0x2Eu:
        sub_1408ED6F0((__int64)&off_1428BBEC0, p1);
        return;
      case 0x2Fu:
        if ( v15 )
          sub_1408CCE80((__int64)(v15 + 1634), p1, p2, 0, 0);
        return;
      case 0x30u:
        if ( v15 )
          sub_1408D3BF0((__int64)(v15 + 1738), p1);
        return;
      case 0x31u:
        if ( v15 )
          sub_1408D3C50((__int64)(v15 + 1738), p1, v17);
        return;
      case 0x32u:
        if ( v15 )
        {
          Client__Game__Character__Character__SetTargetId(v15, targetId);
          if ( (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v19 + 16LL))(v19) == 2 )
          {
            v141 = sub_140897EF0(targetId);
            sub_1408CE390(v19 + 6536, v141);
          }
        }
        return;
      case 0x34u:
        if ( v15 )
          sub_140857450(0x76u, v15, v15, -1.0, 0, 0);
        return;
      case 0x35u:
        if ( v15 )
          sub_140857450(0x77u, v15, v15, -1.0, 0, 0);
        return;
      case 0x36u:
        if ( v15 )
        {
          *((_BYTE *)v15 + 154) = *((_BYTE *)v15 + 154) & 0xFE | (p1 != 0);
          sub_140898020((__int64)v15, p1 != 0);
        }
        else if ( entityId != -536870912 )
        {
          ObjectByEntityId = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(
                               qword_1428BCDD0,
                               entityId);
          v106 = ObjectByEntityId;
          if ( ObjectByEntityId )
          {
            ObjectByEntityId[154] = ObjectByEntityId[154] & 0xFE | (p1 != 0);
            sub_140898020((__int64)ObjectByEntityId, p1 != 0);
            v106[155] |= 8u;
          }
        }
        return;
      case 0x37u:
        if ( v15 )
          sub_1408B3D20((__int64)(v15 + 446), p1);
        return;
      case 0x38u:
        v107 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v108 = sub_140B25030((__int64)v107, p1);
        if ( v108 )
          *(_BYTE *)(v108 + 1156) = *(_BYTE *)(v108 + 1156) & 0xFD | (p2 != 0 ? 2 : 0);
        return;
      case 0x39u:
        HIWORD(dword_142AF8950) = p1;
        return;
      case 0x3Au:
        if ( v15 )
          Client__Game__Character__Character__SetSoftTargetId(v15, targetId);
        return;
      case 0x3Bu:
        if ( v15 )
        {
          if ( p1 )
          {
            *((_WORD *)v15 + 1675) = p2;
            Client__Game__Character__TimelineContainer__PlayActionTimeline(v15 + 652, p1, p2, 0);
          }
          else if ( p2 )
          {
            *((_WORD *)v15 + 1675) = p2;
            TimelineContainer_PlayResolvedActionTimeline((__int64)(v15 + 652), p2, 0, 0, 0);
          }
          else
          {
            v755 = *((_WORD *)v15 + 1675);
            if ( v755 )
              sub_1408BE910(v15 + 652, v755, 0);
            *(_WORD *)(v19 + 3350) = 0;
          }
        }
        return;
      case 0x3Cu:
        if ( v15 )
        {
          sub_1408BEA90((__int64)(v15 + 652));
          TimelineContainer_PlayResolvedActionTimeline(v19 + 2608, 3u, 0, 0, 0);
        }
        return;
      case 0x3Du:
        if ( p1 )
        {
          if ( p2 )
            *(float *)&dword_1428C2600 = (float)(int)p2;
          else
            byte_1428C25FC = 1;
        }
        else
        {
          byte_1428C25FC = 0;
          dword_1428C2600 = 0;
        }
        return;
      case 0x3Eu:
        if ( v15 )
          sub_1408BD760((__int64)(v15 + 652), p1, p2, v18);
        return;
      case 0x3Fu:
        if ( v15 )
          sub_1408BD5B0((__int64)(v15 + 652), p1);
        return;
      case 0x41u:
        v447 = (void *)sub_140B777C0();
        v448 = Client__Game__Event__EventFramework__GetContentDirector(v447);
        if ( v448 )
        {
          v449 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, entityId);
          if ( v449 )
            (*(void (__fastcall **)(void *, void *, _QWORD, _QWORD))(*(_QWORD *)v448 + 2448LL))(
              v448,
              v449,
              p1,
              p2);
        }
        return;
      case 0x42u:
        v450 = (void *)sub_140B777C0();
        v451 = Client__Game__Event__EventFramework__GetContentDirector(v450);
        if ( v451 )
        {
          v452 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, entityId);
          if ( v452 )
            (*(void (__fastcall **)(void *, void *, _QWORD, _QWORD))(*(_QWORD *)v451 + 2464LL))(
              v451,
              v452,
              p1,
              p2);
        }
        return;
      case 0x43u:
        v453 = (void *)sub_140B777C0();
        v454 = Client__Game__Event__EventFramework__GetContentDirector(v453);
        if ( v454 )
        {
          v455 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, entityId);
          if ( v455 )
            (*(void (__fastcall **)(void *, void *, _QWORD, _QWORD, int))(*(_QWORD *)v454 + 2456LL))(
              v454,
              v455,
              p1,
              p2,
              p3);
        }
        return;
      case 0x46u:
        if ( v15 )
          sub_1408CE2D0((__int64)(v15 + 1634), p1);
        return;
      case 0x47u:
        if ( v15 )
        {
          v65 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v66 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v65 + 296LL))(v65);
          v67 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v66, 4u);
          if ( v67 && sub_140897A40(v19, isRecorded, 0) )
            sub_140FDB5E0((__int64)v67, p1);
          if ( p2 )
            sub_140857450(0xB9u, (void *)v19, (void *)v19, -1.0, 0, 0);
        }
        return;
      case 0x48u:
        if ( !v15 )
          return;
        v68 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v69 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v68 + 296LL))(v68);
        v70 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v69, 4u);
        v71 = sub_14089E7C0(v19 + 416);
        EXD__ClassJob__Row_140834F60(v71);
        if ( v70 && sub_140897A40(v19, isRecorded, 0) )
          sub_140FDB620((__int64)v70, p1, p3);
        if ( !p2 )
          return;
        v72 = 2231;
        goto LABEL_223;
      case 0x49u:
        if ( v15 )
          sub_14194E8A0((__int64)(v15 + 2200), p1);
        return;
      case 0x4Au:
        if ( v15 )
        {
          v73 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v74 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v73 + 296LL))(v73);
          v75 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v74, 4u);
          if ( v75 )
            sub_140FDB600((__int64)v75, p1);
        }
        return;
      case 0x50u:
        if ( v15 )
        {
          v144 = (unsigned __int16)p3;
          if ( HIWORD(p3) )
            Client__Game__BattleLog__AddActionLogMessage(HIWORD(p3), v15, v15, 0, 0, p1, 0, 3, 0, 100.0);
          else
            Client__Game__BattleLog__AddToScreenLogWithLogMessageId(v15, v15, 504, 0, 0, p1, 0, 3);
          *(_DWORD *)(v19 + 428) = p2;
          if ( v144 )
            sub_140857450(v144, (void *)v19, (void *)v19, -1.0, 0, 0);
        }
        v145 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v146 = Client__Game__Group__GroupManager__Group__GetPartyMemberByEntityId(v145, entityId);
        if ( v146 )
          v146[259] = p2;
        v147 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v148 = sub_140B25030((__int64)v147, entityId);
        if ( v148 )
          *(_DWORD *)(v148 + 1036) = p2;
        sub_140C22FC0((__int64)&qword_142AE0870, entityId, p2);
        return;
      case 0x51u:
        if ( v15 )
          sub_14090A990((__int64)v15);
        return;
      case 0x52u:
        if ( v15 )
          sub_14194D4C0((__int64)(v15 + 1852), (__int64)v15, p1, p2);
        return;
      case 0x53u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          InventoryContainer = Client__Game__InventoryManager__GetInventoryContainer(dword_142AD6000, 0x7D5u);
          sub_1408692D0((__int64)InventoryContainer);
          v290 = sub_1408867A0();
          v291 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v290 + 64LL))(v290);
          *(_BYTE *)(v291 + 34927) |= 1u;
        }
        return;
      case 0x54u:
        sub_1408918E0(&word_142AD5FF8, p1, p2);
        if ( p1 && p3 )
        {
          v293 = sub_1408867A0();
          v294 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v293 + 296LL))(v293);
          v295 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v294, 0x80u);
          if ( v295 )
          {
            TreasureSpotSubKey = Client__Game__EventItemManager__GetTreasureSpotSubKey(&word_142AD5FF8);
            TreasureHuntRank = Client__Game__EventItemManager__GetTreasureHuntRank(&word_142AD5FF8);
            sub_140CF8950(v295, TreasureHuntRank, TreasureSpotSubKey, p3 != 0);
          }
          v298 = sub_1408867A0();
          v299 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v298 + 296LL))(v298);
          v300 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v299, 6u);
          if ( v300 )
            sub_14101A860((__int64)v300, 0, 6, 0, 1);
          v301 = sub_1408919C0();
          sub_1405D57D0(v968);
          v1047 = 0;
          v1046[0] = v301;
          v1046[1] = (__int64)v1046;
          sub_1401EABA0(v968, (__int64)v1046);
          sub_1401E09B0((__int64)v1046);
          v1045 = 0;
          v1044[0] = p1;
          v1044[1] = (__int64)v1044;
          sub_1401EABA0(v968, (__int64)v1044);
          sub_1401E09B0((__int64)v1044);
          v302 = sub_1408867A0();
          v303 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v302 + 88LL))(v302);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v303, 0xEA6u, v968);
          sub_1407AD1F0(v968);
        }
        return;
      case 0x55u:
        if ( v15 )
        {
          if ( sub_140897A40((__int64)v15, isRecorded, 0) )
          {
            sub_140891900(&word_142AD5FF8);
            v304 = sub_1408867A0();
            v305 = (void *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v304 + 296LL))(v304);
            v306 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v305, 0x80u);
            if ( v306 )
              (*(void (__fastcall **)(void *))(*(_QWORD *)v306 + 40LL))(v306);
          }
        }
        return;
      case 0x56u:
        LOBYTE(qword_142AE3734) = p1;
        return;
      case 0x57u:
        if ( p1 )
        {
          v307 = sub_140B777C0();
          sub_1417CEEF0(v307 + 432, p1);
        }
        return;
      case 0x58u:
        v149 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p1);
        if ( v149 )
          v149[107] = p2;
        v150 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v151 = Client__Game__Group__GroupManager__Group__GetPartyMemberByEntityId(v150, p1);
        if ( v151 )
          v151[259] = p2;
        v152 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v153 = sub_140B25030((__int64)v152, p1);
        if ( v153 )
          *(_DWORD *)(v153 + 1036) = p2;
        sub_140C22FC0((__int64)&qword_142AE0870, p1, p2);
        return;
      case 0x59u:
        if ( v15 )
          v15[34] = *(float *)entityIda;
        return;
      case 0x5Au:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          Client__Game__InventoryManager__SetSlotUnblocked(dword_142AD6000, p1, p2);
        return;
      case 0x5Bu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_1408867C0();
        return;
      case 0x5Cu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          if ( p1 == 9999 )
            sub_14088C850((__int64)&qword_142AD9760, 5);
          else
            sub_14088CE00((__int64)&qword_142AD9760, p1);
        }
        return;
      case 0x5Du:
        sub_14088DA80(&qword_142AD9760, p1 != 0);
        return;
      case 0x5Fu:
        sub_140C3B680((__int64)qword_142AE32E0, p1, p2, p3);
        return;
      case 0x60u:
        sub_140C3B710((__int64)qword_142AE32E0, p1, p2, p3);
        return;
      case 0x61u:
        if ( v15 )
          sub_14089F030((__int64)(v15 + 104), p1);
        return;
      case 0x62u:
        if ( v15 )
        {
          v15[2254] = *(float *)entityIda;
          sub_14089DD10((__int64)v15, 0, p1, 3u);
        }
        return;
      case 0x63u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_1408D5C70(v19 + 7040, p1, p2 != 0);
        return;
      case 0x64u:
        v456 = sub_140B777C0();
        sub_140B80E40(v456);
        return;
      case 0x65u:
        v457 = sub_140B777C0();
        sub_140B80E70(v457, p1);
        return;
      case 0x66u:
        if ( v15 )
          sub_1408CC910((__int64)(v15 + 1634), p1, p2);
        return;
      case 0x67u:
        sub_140C01650((__int64)&qword_142AE5040, p1, p2);
        return;
      case 0x68u:
        v458 = sub_140B777C0();
        sub_140B811F0(v458, p1);
        return;
      case 0x69u:
        if ( v15 )
          Client__Game__Object__GameObject__SetEventId(v15, p1);
        return;
      case 0x6Au:
        if ( entityId != -536870912 )
        {
          v567 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, entityId);
          if ( v567 )
            Client__Game__Object__GameObject__SetEventState(v567, p1);
        }
        return;
      case 0x6Bu:
        sub_140C148B0((__int64)&qword_142AEB2F0, p1);
        return;
      case 0x6Cu:
        sub_140C14C50((__int64)&qword_142AEB2F0, p1);
        return;
      case 0x6Du:
        v575 = (void *)sub_140B777C0();
        Client__Game__Event__EventFramework__ProcessDirectorUpdate(v575, p1, p2, p3, p4, p5, p6, p7, p8);
        return;
      case 0x6Eu:
        v576 = sub_140B777C0();
        sub_140B81580(v576, p1);
        return;
      case 0x6Fu:
        sub_1405D57D0(v911);
        if ( !(_DWORD)dword_1428BBBD0 )
        {
          v578 = sub_140B777C0();
          if ( sub_140B839C0(v578) )
          {
            v579 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            (*(void (__fastcall **)(void *, __int64, __int64, __int64, _QWORD, _QWORD))(*(_QWORD *)v579 + 1184LL))(
              v579,
              1,
              24,
              1,
              0,
              0);
            (*(void (__fastcall **)(void *, _QWORD, __int64, __int64, _QWORD, _QWORD))(*(_QWORD *)v579 + 1184LL))(
              v579,
              0,
              24,
              1,
              0,
              0);
          }
        }
        if ( p1 <= 0xE86 )
        {
          if ( p1 != 3718 )
          {
            if ( p1 > 0x606 )
            {
              switch ( p1 )
              {
                case 0x607u:
                  LODWORD(v1176) = p2;
                  v1090[1] = 0;
                  v1090[0] = 0;
                  v1091 = -1;
                  sub_14078F8B0((__int64)v1090, &v1176);
                  sub_1401EABA0(v911, (__int64)v1090);
                  sub_1401E09B0((__int64)v1090);
                  LODWORD(v1176) = p3;
                  v1092[1] = 0;
                  v1092[0] = 0;
                  v1093 = -1;
                  sub_14078F8B0((__int64)v1092, &v1176);
                  sub_1401EABA0(v911, (__int64)v1092);
                  sub_1401E09B0((__int64)v1092);
                  break;
                case 0x608u:
                  LODWORD(v1176) = p2;
                  v1086[1] = 0;
                  v1086[0] = 0;
                  v1087 = -1;
                  sub_14078F8B0((__int64)v1086, &v1176);
                  sub_1401EABA0(v911, (__int64)v1086);
                  sub_1401E09B0((__int64)v1086);
                  LODWORD(v1176) = p3;
                  v1088[1] = 0;
                  v1088[0] = 0;
                  v1089 = -1;
                  sub_14078F8B0((__int64)v1088, &v1176);
                  sub_1401EABA0(v911, (__int64)v1088);
                  sub_1401E09B0((__int64)v1088);
                  break;
                case 0x63Du:
                  LODWORD(v1176) = p2;
                  v1082[1] = 0;
                  v1082[0] = 0;
                  v1083 = -1;
                  sub_14078F8B0((__int64)v1082, &v1176);
                  sub_1401EABA0(v911, (__int64)v1082);
                  sub_1401E09B0((__int64)v1082);
                  LODWORD(v1176) = p3;
                  v1084[1] = 0;
                  v1084[0] = 0;
                  v1085 = -1;
                  sub_14078F8B0((__int64)v1084, &v1176);
                  sub_1401EABA0(v911, (__int64)v1084);
                  sub_1401E09B0((__int64)v1084);
                  break;
                case 0x654u:
                  break;
                default:
                  goto LABEL_1259;
              }
            }
            else if ( p1 == 1542 )
            {
              LODWORD(v1176) = p2;
              v1170[1] = 0;
              v1170[0] = 0;
              v1171 = -1;
              sub_14078F8B0((__int64)v1170, &v1176);
              sub_1401EABA0(v911, (__int64)v1170);
              sub_1401E09B0((__int64)v1170);
              LODWORD(v1176) = p3;
              v1080[1] = 0;
              v1080[0] = 0;
              v1081 = -1;
              sub_14078F8B0((__int64)v1080, &v1176);
              sub_1401EABA0(v911, (__int64)v1080);
              sub_1401E09B0((__int64)v1080);
            }
            else if ( p1 != 955 )
            {
              switch ( p1 )
              {
                case 0x5F6u:
                  LODWORD(v1176) = p2;
                  v1162[1] = 0;
                  v1162[0] = 0;
                  v1163 = -1;
                  sub_14078F8B0((__int64)v1162, &v1176);
                  sub_1401EABA0(v911, (__int64)v1162);
                  sub_1401E09B0((__int64)v1162);
                  LODWORD(v1176) = p3;
                  v1164[1] = 0;
                  v1164[0] = 0;
                  v1165 = -1;
                  sub_14078F8B0((__int64)v1164, &v1176);
                  sub_1401EABA0(v911, (__int64)v1164);
                  sub_1401E09B0((__int64)v1164);
                  LODWORD(v1176) = p4;
                  v1166[1] = 0;
                  v1166[0] = 0;
                  v1167 = -1;
                  sub_14078F8B0((__int64)v1166, &v1176);
                  sub_1401EABA0(v911, (__int64)v1166);
                  sub_1401E09B0((__int64)v1166);
                  LODWORD(v1176) = p5;
                  v1168[1] = 0;
                  v1168[0] = 0;
                  v1169 = -1;
                  sub_14078F8B0((__int64)v1168, &v1176);
                  sub_1401EABA0(v911, (__int64)v1168);
                  sub_1401E09B0((__int64)v1168);
                  break;
                case 0x5F8u:
                  LODWORD(v1176) = p2;
                  v1156[1] = 0;
                  v1156[0] = 0;
                  v1157 = -1;
                  sub_14078F8B0((__int64)v1156, &v1176);
                  sub_1401EABA0(v911, (__int64)v1156);
                  sub_1401E09B0((__int64)v1156);
                  LODWORD(v1176) = p3;
                  v1158[1] = 0;
                  v1158[0] = 0;
                  v1159 = -1;
                  sub_14078F8B0((__int64)v1158, &v1176);
                  sub_1401EABA0(v911, (__int64)v1158);
                  sub_1401E09B0((__int64)v1158);
                  LODWORD(v1176) = p4;
                  v1160[1] = 0;
                  v1160[0] = 0;
                  v1161 = -1;
                  sub_14078F8B0((__int64)v1160, &v1176);
                  sub_1401EABA0(v911, (__int64)v1160);
                  sub_1401E09B0((__int64)v1160);
                  break;
                case 0x5F9u:
                  LODWORD(v1176) = p2;
                  v1152[1] = 0;
                  v1152[0] = 0;
                  v1153 = -1;
                  sub_14078F8B0((__int64)v1152, &v1176);
                  sub_1401EABA0(v911, (__int64)v1152);
                  sub_1401E09B0((__int64)v1152);
                  LODWORD(v1176) = p3;
                  v1154[1] = 0;
                  v1154[0] = 0;
                  v1155 = -1;
                  sub_14078F8B0((__int64)v1154, &v1176);
                  sub_1401EABA0(v911, (__int64)v1154);
                  sub_1401E09B0((__int64)v1154);
                  break;
                case 0x605u:
                  LODWORD(v1176) = p2;
                  v1146[1] = 0;
                  v1146[0] = 0;
                  v1147 = -1;
                  sub_14078F8B0((__int64)v1146, &v1176);
                  sub_1401EABA0(v911, (__int64)v1146);
                  sub_1401E09B0((__int64)v1146);
                  LODWORD(v1176) = p3;
                  v1148[1] = 0;
                  v1148[0] = 0;
                  v1149 = -1;
                  sub_14078F8B0((__int64)v1148, &v1176);
                  sub_1401EABA0(v911, (__int64)v1148);
                  sub_1401E09B0((__int64)v1148);
                  LODWORD(v1176) = p4;
                  v1150[1] = 0;
                  v1150[0] = 0;
                  v1151 = -1;
                  sub_14078F8B0((__int64)v1150, &v1176);
                  sub_1401EABA0(v911, (__int64)v1150);
                  sub_1401E09B0((__int64)v1150);
                  break;
                default:
                  goto LABEL_1259;
              }
            }
          }
          goto LABEL_1273;
        }
        if ( p1 > 0xE8D )
        {
          if ( p1 != 7734 && p1 != 7751 && p1 != 7784 && p1 != 9404 )
            goto LABEL_1259;
        }
        else if ( p1 != 3725 && p1 != 3719 && p1 != 3720 && p1 - 3721 >= 2 )
        {
LABEL_1259:
          sub_1407AD1F0(v911);
          return;
        }
LABEL_1273:
        v580 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v581 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v580 + 88LL))(v580);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
          v581,
          p1,
          0,
          0,
          v911);
        goto LABEL_1259;
      case 0x70u:
        v577 = sub_140B777C0();
        sub_140B815F0(v577, p1);
        return;
      case 0x7Bu:
        v617 = sub_140B777C0();
        sub_140B7FC60(v617, p1, p2);
        return;
      case 0x7Cu:
        v618 = sub_140B777C0();
        sub_140B816E0(v618, p1, p2, p3, p4, p5, p6);
        return;
      case 0x80u:
        if ( (p1 & 0xFFFFFFF8) < 0x20 )
        {
          v619 = (unsigned __int64)p1 >> 3;
          v620 = 128 >> (p1 & 7);
          if ( p2 == 1 )
            *((_BYTE *)&qword_142ADE980 + v619 + 3364) |= v620;
          else
            *((_BYTE *)&qword_142ADE980 + v619 + 3364) &= ~(_BYTE)v620;
        }
        return;
      case 0x81u:
        dword_142ADF6B4 = p1;
        byte_142ADF6A4[0] = p2;
        byte_142ADF6A5 = p3;
        byte_142ADF6A6 = p4;
        byte_142ADF6A7 = p5;
        return;
      case 0x82u:
        sub_1419AACC0(p1, p2 == 1);
        v621 = sub_140B777C0();
        sub_140B80CC0(v621);
        goto LABEL_1729;
      case 0x83u:
        sub_1419AA7D0(p1, p2 == 1);
        v622 = sub_140B777C0();
        sub_140B80BC0(v622);
        goto LABEL_1728;
      case 0x87u:
        sub_140BDA380((__int64)&qword_142ADE980, 1u, p1);
        return;
      case 0x89u:
        dword_142ADF6A8[0] = p1;
        dword_142ADF6AC = p2;
        dword_142ADF6B0 = p3;
        sub_140C1EA80((__int64)&qword_142AEF6A8);
        return;
      case 0x8Au:
        if ( v15 )
        {
          v645 = (_QWORD *)(sub_140B777C0() + 432);
          v646 = sub_140B53080(v645);
          if ( v646 )
          {
            if ( *(_DWORD *)(v646 + 32) == p1 )
            {
              sub_1417D97E0((__int64)v645, v19, 0, 0);
              sub_1417D97E0((__int64)v645, v19, 1u, 0);
            }
          }
        }
        return;
      case 0x8Cu:
        v647 = sub_140B777C0();
        sub_140B81930(v647, p1, (unsigned __int16)p2, p3);
        return;
      case 0x8Du:
        v648 = p1;
        v649 = p3 != 0;
        v650 = p2 != 0;
        v651 = LOBYTE(p1) >> 3;
        if ( (unsigned int)v651 < 2 )
        {
          v652 = (unsigned int)v651;
          v653 = *((_BYTE *)&word_142ADD49F + v651);
          v654 = 128 >> (p1 & 7);
          if ( p2 )
            v655 = v654 | v653;
          else
            v655 = ~(_BYTE)v654 & v653;
          *((_BYTE *)&word_142ADD49F + v652) = v655;
          v656 = sub_140B777C0();
          sub_140B80300(v656, v648, v650, v649);
        }
        return;
      case 0x8Eu:
        Client__System__Framework__Framework__GetUIModule(qword_142909910);
        byte_142AB28A1 = p1 == 1;
        return;
      case 0x8Fu:
        byte_1428BC6B4 = p1 != 0;
        return;
      case 0x90u:
        sub_140BE1E50((__int64)&byte_142ADF3B8, p1);
        v658 = sub_140B777C0();
        sub_140B80B70(v658, 512, p2 != 0);
        return;
      case 0x91u:
        sub_140BE1E00((__int64)&byte_142ADF3B8, p1);
        v659 = sub_140B777C0();
        sub_140B80B70(v659, 1024, p2 != 0);
        return;
      case 0x92u:
        *((_BYTE *)&qword_142ADE980 + p1 + 3928) = p2;
        return;
      case 0x93u:
        dword_142ADDB40 = p1;
        return;
      case 0x94u:
        v684 = p1;
        v685 = p1;
        if ( (_BYTE)p3 == 3 )
          v685 = p1 | 0x100000000LL;
        if ( v685 == 3758096384 )
        {
          ObjectByGameObjectId = 0;
        }
        else
        {
          ObjectByGameObjectId = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByGameObjectId(
                                   qword_1428BCDD0,
                                   v685);
          v684 = p1;
        }
        if ( v684 == p2 )
        {
          v687 = ObjectByGameObjectId;
          goto LABEL_1485;
        }
        v688 = p2;
        if ( BYTE1(p3) == 3 )
        {
          v688 = p2 | 0x100000000LL;
        }
        else if ( p2 == 3758096384LL )
        {
          v687 = 0;
          goto LABEL_1485;
        }
        v687 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByGameObjectId(qword_1428BCDD0, v688);
LABEL_1485:
        sub_140857450(p4, ObjectByGameObjectId, v687, -1.0, 0, 0);
        return;
      case 0x95u:
        sub_1419B5C80(p1, p2, p3 == 1);
        return;
      case 0x96u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v253 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v254 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v253 + 296LL))(v253);
          v255 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v254, 0x8Du);
          sub_140CBECB0((__int64)v255);
        }
        return;
      case 0x97u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_140886890();
        return;
      case 0x98u:
        byte_142ADF978 = p1 != 0;
        v693 = sub_140B777C0();
        sub_140B80B70(v693, 4096, 1);
        return;
      case 0x99u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          goto LABEL_652;
        return;
      case 0x9Cu:
        sub_1419F3B90(p1, p2, p3);
        return;
      case 0x9Du:
        sub_1419F3EB0(p1);
        return;
      case 0x9Eu:
        byte_142ADF9B5 = p1;
        return;
      case 0x9Fu:
        dword_142ADDB44 = p1;
        dword_142ADDB48 = p2;
        return;
      case 0xA1u:
        if ( p1 )
          sub_14085BB70(p1);
        else
          sub_14085BC00();
        return;
      case 0xA2u:
        sub_140BE2780((__int64)&byte_142ADF3B8, p1, p2 == 1);
        return;
      case 0xA3u:
        byte_142ADF9B7 = p1;
        return;
      case 0xA4u:
        v694 = LOWORD(p1) >> 3;
        v695 = LOWORD(p1) >> 3;
        v696 = HIBYTE(p3);
        v697 = *((_BYTE *)&qword_142ADE980 + v694 + 4089);
        v698 = 1 << (LOBYTE(p1) - 8 * v694);
        if ( p6 )
        {
          if ( p6 == 1 )
          {
            sub_140BE26D0((__int64)&byte_142ADF3B8, v695, v697 & ~v698);
            sub_140BE2600((__int64)&byte_142ADF3B8, v696, 0);
            sub_140BE2A90((__int64)&byte_142ADF3B8, p4);
          }
        }
        else
        {
          sub_140BE26D0((__int64)&byte_142ADF3B8, v695, v697 | v698);
          if ( p2 == 1 )
          {
            sub_140BE2600((__int64)&byte_142ADF3B8, v696, 1);
            if ( p5 == 1 )
              Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0xCDu, 0, 0);
            sub_140BE2A90((__int64)&byte_142ADF3B8, p4);
            v699 = sub_140B777C0();
            sub_1417CEEF0(v699 + 432, (unsigned __int16)((unsigned int)p3 >> 8));
            Client__Game__ZoneSharedGroupManager__Refresh(&qword_142AA78D8);
          }
        }
        v700 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v700 )
        {
          v701 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v700 + 64LL))(v700);
          sub_1400FC9F0(v701, v695);
        }
        v702 = sub_140B777C0();
        v703 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v702, p1);
        if ( v703 )
          sub_1419F4C90(v703);
        return;
      case 0xA5u:
        sub_140BE2A90((__int64)&byte_142ADF3B8, p1);
        return;
      case 0xA8u:
        if ( entityId != -536870912 )
        {
          v707 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, entityId);
          if ( v707 )
            Client__Game__Object__GameObject__SetVisibility(v707, p1);
        }
        return;
      case 0xA9u:
        sub_140C4D620((__int64)&qword_142ADE980, p1);
        return;
      case 0xAAu:
        sub_140C50780((__int64)&qword_142ADE980, v16, v17);
        return;
      case 0xABu:
        sub_140C50950(&qword_142ADE980, BYTE2(p1), BYTE1(p1), p2, p3, p1, p4, p5);
        return;
      case 0xACu:
        nullsub_165();
        return;
      case 0xADu:
        sub_140C509A0((__int64)&qword_142ADE980);
        return;
      case 0xAEu:
        sub_140C509E0((__int64)&qword_142ADE980, p1);
        return;
      case 0xAFu:
        v708 = sub_140B777C0();
        sub_140B80400(v708, p1);
        return;
      case 0xB0u:
        sub_140BE0AE0((__int64)&byte_142ADF3B8, p1, p2);
        return;
      case 0xB4u:
        sub_1419D0560();
        return;
      case 0xB5u:
        *(float *)&dword_142AF8970 = (float)(int)p1 / 100.0;
        return;
      case 0xB6u:
        sub_140BE5210((__int64)&byte_142ADF3B8, (__int64)&qword_142ADFA48 + 7, p1, p2 != 0);
        return;
      case 0xB7u:
        v756 = (void *)sub_140B777C0();
        v757 = Client__Game__Event__EventFramework__GetContentDirector(v756);
        if ( v757 )
        {
          v934[0] = Common__Math__QuantizedValue__DequantizePositionValue(p2);
          v934[1] = Common__Math__QuantizedValue__DequantizePositionValue(p3);
          v934[2] = Common__Math__QuantizedValue__DequantizePositionValue(p4);
          v934[3] = 0;
          sub_140B6CE50(v757, p1, v934, (float)(int)p5 * 0.001, p6);
        }
        return;
      case 0xB8u:
        v758 = (void *)sub_140B777C0();
        v759 = Client__Game__Event__EventFramework__GetContentDirector(v758);
        if ( v759 )
          sub_140B6CEE0(v759, p1, p2, p3, (float)p4 * 0.001);
        return;
      case 0xB9u:
        v760 = sub_140B777C0();
        v761 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v760, 67114);
        if ( v761 )
          sub_141AAAFE0(v761, p1, p2);
        return;
      case 0xBAu:
        v762 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v763 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v762 + 296LL))(v762);
        v764 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v763, 0x147u);
        sub_140CFD3D0((__int64)v764);
        v765 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v766 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v765 + 88LL))(v765);
        Client__UI__Misc__RaptureLogModule__ShowLogMessage(v766, 0x24AAu);
        return;
      case 0xBBu:
        v922 = p1;
        common_gmtime_s<__int64>();
        v767 = sub_1405E5B90(&v1172.tm_sec);
        common_localtime_s<__int64>(&v1172);
        v768 = sub_1405E5B90(&v1172.tm_sec);
        v769 = difftime64_0(v768, v767);
        v770 = v769 >= 0.0;
        v771 = 14;
        v772 = v769 / -60.0;
        if ( !v770 )
          v771 = -14;
        v773 = 15 * ((v771 - (int)v772) / 15);
        if ( v1172.tm_isdst )
          v773 += 60;
        Client__Game__GameMain__ExecuteCommand(820, v773 + 1440, p1, p2, p3);
        return;
      case 0xBCu:
        sub_140C17480(&qword_142AEB2F0, p1, p2, p3, p4);
        return;
      case 0xBDu:
        v774 = sub_140B777C0();
        v775 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v774, p1);
        if ( v775 )
        {
          v776 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v777 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v776 + 296LL))(v776);
          v778 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v777, 0x155u);
          if ( (*(unsigned __int8 (__fastcall **)(void *))(*(_QWORD *)v778 + 48LL))(v778) )
            sub_140C6C010((__int64)v778, p2);
          else
            sub_140DFC3A0(v775, p2);
        }
        return;
      case 0xBEu:
        if ( unknown_libname_537() )
        {
          v779 = sub_140EB2450();
          sub_140EB27A0(v779, p1, p2 != 0);
        }
        return;
      case 0xBFu:
        if ( unknown_libname_537() )
        {
          v780 = (void *)sub_140EB2450();
          sub_140EB27D0(v780, p1 != 0);
        }
        return;
      case 0xC0u:
        if ( unknown_libname_537() )
        {
          v781 = sub_140EB2450();
          sub_140EB27E0(v781, p1, p2);
        }
        return;
      case 0xC1u:
        if ( unknown_libname_537() )
        {
          v782 = sub_140EB2450();
          sub_140EB27F0(v782, p1 == 0, p2, p3, p4, p5, p6);
        }
        return;
      case 0xC2u:
        v783 = (void *)sub_140B777C0();
        sub_140B81BE0(v783, p1, p2 != 0);
        return;
      case 0xC3u:
        v784 = sub_140B777C0();
        sub_140B81CC0(v784, p1, p2 != 0);
        return;
      case 0xC4u:
        sub_140BE5210((__int64)&byte_142ADF3B8, (__int64)&qword_142ADFAE1 + 5, p1, p2 != 0);
        sub_140C50030((__int64)&qword_142ADE980);
        return;
      case 0xC5u:
        sub_140BE5210((__int64)&byte_142ADF3B8, (__int64)&unk_142ADFAEB, p1, p2 != 0);
        return;
      case 0xC6u:
        if ( unknown_libname_833() )
        {
          v785 = (__int64 *)sub_1419772D0();
          sub_1419773D0(v785, p1, (unsigned int)p3 | ((unsigned __int64)p2 << 32));
        }
        return;
      case 0xC7u:
        if ( qword_142ADE350 )
        {
          v786 = sub_140B777C0();
          sub_140B826E0(v786, p1, 1, 0);
        }
        return;
      case 0xC8u:
        if ( v15 )
          sub_140862A00((__int64)&dword_1428BBBD0, (__int64)v15, p1, p2 != 0, p3, p4);
        return;
      case 0xC9u:
        if ( v15 )
        {
          v64 = v15[48];
          a2[0] = (float)((float)((float)LOWORD(p1) * 3.0518043) * 0.0099999998) - 1000.0;
          a2[1] = (float)((float)((float)(unsigned __int16)p2 * 3.0518043) * 0.0099999998) - 1000.0;
          a2[3] = 0.0;
          a2[2] = (float)((float)((float)(unsigned __int16)p3 * 3.0518043) * 0.0099999998) - 1000.0;
          sub_14181BED0(v15 + 124, a2, v64, 0);
        }
        return;
      case 0xCBu:
        sub_140C1B470((__int64)&qword_142ADFFB0, p1, p2, p3);
        return;
      case 0xCCu:
        sub_140C1B5D0((__int64)&qword_142ADFFB0, p1, p2, p3);
        return;
      case 0xCDu:
        sub_140C1B410((__int64)&qword_142ADFFB0);
        return;
      case 0xD0u:
      case 0x198u:
        sub_140862330((__int64)&dword_1428BBBD0, p1, p2);
        return;
      case 0xD2u:
        instancePlayerCounts[0] = p3;
        instancePlayerCounts[1] = p4;
        instancePlayerCounts[2] = p5;
        instancePlayerCounts[3] = p6;
        v1188 = 0;
        Client__Game__UI__PublicInstance__ShowInstanceSelection(
          dword_142AE2E18,
          p1,
          p2,
          instancePlayerCounts,
          8u);
        return;
      case 0xD3u:
        if ( v15 )
        {
          LOBYTE(v17) = 1;
          sub_1408993E0((__int64 *)v15, 0, v17);
          Client__Game__UI__PublicInstance__CloseInstanceSelection(dword_142AE2E18);
        }
        return;
      case 0xD4u:
        if ( v15 && !sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_1408623F0(
            (__int64)&dword_1428BBBD0,
            v19,
            p1,
            (unsigned __int16)p2,
            p3 != 0,
            p4 != 0,
            isRecorded);
        return;
      case 0xD5u:
        v787 = source;
        if ( source )
        {
          if ( !sub_141805150((__int64)(source + 128)) )
          {
            LayoutInstanceStatic = Client__LayoutEngine__LayoutWorld__GetLayoutInstanceStatic(0x31u, p1, 0);
            v789 = LayoutInstanceStatic;
            if ( LayoutInstanceStatic )
            {
              if ( (LayoutInstanceStatic[120] & 1) != 0 )
              {
                if ( (*(__int64 (__fastcall **)(_BYTE *))(*(_QWORD *)LayoutInstanceStatic + 280LL))(LayoutInstanceStatic) )
                {
                  v790 = (*(__int64 (__fastcall **)(_BYTE *))(*(_QWORD *)v789 + 280LL))(v789);
                  v791 = *(unsigned __int8 (__fastcall **)(__int64, _DWORD *))(*(_QWORD *)v790 + 184LL);
                  v792 = *((_DWORD *)Client__Game__Object__GameObject__GetPosition(v787) + 2);
                  v793 = *((_DWORD *)Client__Game__Object__GameObject__GetPosition(v787) + 1);
                  v923[0] = *(_DWORD *)Client__Game__Object__GameObject__GetPosition(v787);
                  v923[1] = v793;
                  v923[2] = v792;
                  if ( v791(v790, v923) )
                  {
                    if ( (unsigned int)sub_14182DBE0((__int64)&qword_142AB28C0, 6) >= 4 )
                    {
                      v963 = xmmword_1421A8B80;
                      v794 = (float *)Client__Game__Object__GameObject__GetPosition(v787);
                      v795 = (const float *)sub_140B52B90((__int64)v986, v794, (float *)&v963);
                      if ( sub_1418186E0(v787 + 124, &v912, v795) )
                      {
                        v796 = (float *)Client__Game__Object__GameObject__GetPosition(v787);
                        if ( v912 > v796[1] )
                        {
                          *(_QWORD *)v919 = off_142178A68;
                          v920 = 263;
                          v921 = 256;
                          v797 = v787[48];
                          v964 = xmmword_1421A8B80;
                          v798 = (float *)Client__Game__Object__GameObject__GetPosition(v787);
                          v799 = (const float *)sub_140B52B90((__int64)v987, v798, (float *)&v964);
                          sub_14181BED0(v787 + 124, v799, v797, v919);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        return;
      case 0xDCu:
        if ( v15 )
          sub_1418147B0((_DWORD)v15 + 496, 220, p1, p2, p3, p4);
        return;
      case 0xDDu:
        if ( v15 )
          sub_14181F540((__int64)(v15 + 124));
        return;
      case 0xDFu:
        if ( v15 && !sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          position[0] = Common__Math__QuantizedValue__DequantizePositionValue(HIWORD(p1));
          position[1] = Common__Math__QuantizedValue__DequantizePositionValue(p1);
          position[2] = Common__Math__QuantizedValue__DequantizePositionValue(HIWORD(p2));
          position[3] = 0.0;
          v633 = Common__Math__QuantizedValue__DequantizeAngleValue(p2);
          sub_1408C1200((void *)(v19 + 2608), p3, p4, position, v633, 0);
        }
        return;
      case 0xE0u:
        if ( v15 )
        {
          v641 = Common__Math__QuantizedValue__DequantizePositionValue(p2);
          v642 = Common__Math__QuantizedValue__DequantizePositionValue(p1);
          sub_14181D650((void *)(v19 + 496), v642, v641);
        }
        return;
      case 0xE1u:
        if ( v15 )
        {
          v643 = Common__Math__QuantizedValue__DequantizeAngleValue(p1);
          sub_14090AC70((void *)v19, v643, (float)(int)p2 / 10000.0, (float)p3 / 10000.0, 0, 0);
        }
        return;
      case 0xE2u:
        if ( !v15 )
          return;
        v933[0] = Common__Math__QuantizedValue__DequantizePositionValue(p1);
        v933[1] = Common__Math__QuantizedValue__DequantizePositionValue(p2);
        v933[2] = Common__Math__QuantizedValue__DequantizePositionValue(p3);
        v933[3] = 0;
        v644 = Common__Math__QuantizedValue__DequantizeAngleValue(p4);
        sub_14090ABB0((void *)v19, v933, v644, (float)(int)p5 / 10000.0, 0, p6);
LABEL_1428:
        if ( v19 )
          sub_141814B70(v19 + 496, 1);
        return;
      case 0xE3u:
        if ( v15 )
        {
          sub_14181FDB0((__int64)(v15 + 124));
          sub_141808420(v19 + 1088);
        }
        return;
      case 0xE4u:
        if ( v15 )
          sub_14181FDD0((__int64)(v15 + 124));
        return;
      case 0xE5u:
        if ( v15 )
        {
          sub_141820330((__int64)(v15 + 124));
          sub_141820460(v19 + 496);
        }
        return;
      case 0xE7u:
        if ( v15 && sub_140897A40((__int64)v15, 0, 0) )
        {
          v634 = Common__Math__QuantizedValue__DequantizeAngleValue(p3);
          v635 = (float *)Client__Game__Object__GameObject__GetPosition((void *)v19);
          sub_14182E370(&qword_142AB28C0, p1, p2, v635, v634, 1u);
        }
        return;
      case 0xE8u:
        if ( v15 && sub_140897A40((__int64)v15, 0, 0) )
        {
          v915 = Common__Math__QuantizedValue__DequantizePositionValue(p3);
          v916 = Common__Math__QuantizedValue__DequantizePositionValue(p4);
          v917 = Common__Math__QuantizedValue__DequantizePositionValue(p5);
          v918 = 0;
          v636 = (float *)Client__Game__Object__GameObject__GetPosition((void *)v19);
          v637 = v915 - *v636;
          v638 = v916 - v636[1];
          v639 = v917 - v636[2];
          v932[3] = 0.0;
          v932[0] = v637;
          v932[1] = v638;
          v932[2] = v639;
          LODWORD(v640) = sub_1408544E0(v932).m128_u32[0];
          sub_14182E370(&qword_142AB28C0, p1, p2, &v915, v640, 1u);
        }
        return;
      case 0xEBu:
        goto LABEL_1428;
      case 0xECu:
        byte_142AF8D78 = p1;
        return;
      case 0xEDu:
        if ( p1 )
          sub_141835780((__int64)&qword_142AB28B0);
        else
          sub_1418357C0((__int64)&qword_142AB28B0);
        return;
      case 0xEEu:
        sub_1418362E0((__int64)&qword_142AB28B0);
        return;
      case 0xEFu:
        if ( v15 )
          sub_14181FDB0((__int64)(v15 + 124));
        return;
      case 0xF0u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_141819DB0((void *)(v19 + 496), p1);
        return;
      case 0xF1u:
        if ( v15 )
          sub_14181F830((__int64)(v15 + 124), p1, p2, p3, p4);
        return;
      case 0xF2u:
        if ( v15 )
          sub_14181F080((__int64)(v15 + 124), p1, p2, p3);
        return;
      case 0xF3u:
        if ( v15 )
          sub_141820DD0(v15 + 124, p1, p2, p3, p4);
        return;
      case 0xF4u:
        if ( v15 )
          (*(void (__fastcall **)(float *, _QWORD, _QWORD, _QWORD))(*((_QWORD *)v15 + 62) + 48LL))(
            v15 + 124,
            p1,
            p2,
            (unsigned int)p3);
        return;
      case 0xF5u:
        if ( v15 )
          sub_140630A10();
        return;
      case 0xF6u:
        if ( p1 )
        {
          if ( p1 == 1 )
            sub_141836C60((__int64)&qword_142AB28B0);
        }
        else
        {
          sub_141836A30((__int64)&qword_142AB28B0);
        }
        return;
      case 0xFBu:
        v41 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p1);
        if ( v41 )
        {
          v42 = 0;
          if ( p2 )
            v42 = p3;
          Client__Game__BattleLog__AddLogMessage3Params(0x24Cu, v41, 0, p2, v42, 100.0);
        }
        return;
      case 0xFCu:
        if ( v15 && source )
        {
          v45 = (float *)Client__Game__Object__GameObject__GetPosition(source);
          v46 = (float *)Client__Game__Object__GameObject__GetPosition((void *)v19);
          v47 = (float)((float)(v46[2] - v45[2]) * (float)(v46[2] - v45[2]))
              + (float)((float)(*v46 - *v45) * (float)(*v46 - *v45));
          v48 = v47 < 0.0 ? sqrtf(v47) : fsqrt(v47);
          if ( v48 <= 25.0 )
          {
            for ( j = p2 + 1; j <= p1; ++j )
              Client__Game__BattleLog__AddLogMessage3Params(0x53Bu, (void *)v19, 0, j, 0, 100.0);
          }
        }
        return;
      case 0xFDu:
        if ( qword_142909910 )
        {
          if ( !*((_BYTE *)qword_142909910 + 8) )
          {
            NetworkModuleProxy = Client__System__Framework__Framework__GetNetworkModuleProxy(qword_142909910);
            if ( NetworkModuleProxy )
            {
              if ( sub_140481CE0((__int64)NetworkModuleProxy) )
              {
                if ( p1 )
                  Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x6Du, 0, 0);
                if ( p5 )
                  Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x6Cu, 0, 0);
              }
            }
          }
        }
        *(_WORD *)(qword_142AE2BE0 + 12) = LOBYTE(p1);
        if ( p2 )
          *(float *)&dword_142AE2BE8 = (float)p3 / 100.0;
        dword_142AE2C14 = p4;
        byte_142AE2C1A = p6;
        byte_142AE2C18 = p5;
        goto LABEL_1369;
      case 0xFEu:
        sub_140C21730((__int64)&qword_142AE2BE0, p1);
        if ( !v19 )
          return;
        sub_1405D57D0(a1);
        v1000 = p1;
        v1002 = 0;
        v1001 = &v1000;
        sub_1401EABA0(a1, (__int64)&v1000);
        if ( v1001 )
        {
          if ( v1002 == 1 )
          {
            v81 = (_DWORD *)*v1001;
            if ( (int)--v81[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v81);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v81, 112);
            }
          }
          v1001 = 0;
          v1002 = -1;
        }
        v82 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v83 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v82 + 88LL))(v82);
        sub_1409B44A0(v83, 1321, (_WORD *)v19, (__int64)a1);
        sub_1405E2830(a1);
        v84 = (void *)a1[0];
        a1[0] = 0;
        goto LABEL_505;
      case 0xFFu:
        sub_140C217A0((__int64)&qword_142AE2BE0, p1, p2);
        goto LABEL_1369;
      case 0x100u:
        if ( v15 )
        {
          v85 = *((_QWORD *)v15 + 208);
          if ( *((_WORD *)v15 + 836) == 1 )
          {
            if ( v85 )
            {
              if ( p1 )
              {
                if ( p1 == 1 )
                {
                  v87 = (void *)sub_1408B2720((__int64)v960, p2, 0, 0);
                  Client__Game__Character__DrawDataContainer__LoadEquipment((void *)(v85 + 1784), 1u, v87, 0);
                }
                else if ( p1 == 2 )
                {
                  v86 = (void *)sub_1408B2720((__int64)v959, p2, 0, 0);
                  Client__Game__Character__DrawDataContainer__LoadEquipment((void *)(v85 + 1784), 4u, v86, 0);
                }
              }
              else
              {
                v88 = (void *)sub_1408B2720((__int64)v961, p2, 0, 0);
                Client__Game__Character__DrawDataContainer__LoadEquipment((void *)(v85 + 1784), 0, v88, 0);
              }
            }
          }
        }
        return;
      case 0x101u:
        sub_140C23370((__int64)&qword_142AE0870, p5, p3, p4 != 0, p1, p2, isRecorded);
        return;
      case 0x102u:
        if ( v15 )
        {
          if ( p1 && !(*(unsigned __int8 (__fastcall **)(float *))(*(_QWORD *)v15 + 464LL))(v15) )
            sub_1408BDCB0(v19 + 2608, 0x8Fu, 0, 0);
          if ( source )
          {
            v606 = (float *)Client__Game__Object__GameObject__GetPosition(source);
            v607 = (float *)Client__Game__Object__GameObject__GetPosition((void *)v19);
            sub_140B52B50((__int64)&v1176, v607, v606);
            v608 = (float)(*(float *)&v1176 * *(float *)&v1176) + (float)(*(float *)&v1177 * *(float *)&v1177);
            v609 = v608 < 0.0 ? sqrtf(v608) : fsqrt(v608);
            if ( v609 <= 20.0 )
              Client__Game__BattleLog__AddActionLogMessage(0x530u, (void *)v19, (void *)v19, 0, 0, 0, 0, 0, 0, 100.0);
          }
        }
        return;
      case 0x103u:
        if ( v15 )
          Client__Game__BattleLog__AddActionLogMessage(0x538u, v15, v15, 0, 0, 0, 0, 0, 0, 100.0);
        return;
      case 0x104u:
        if ( !isRecorded )
        {
          sub_140C221D0(&qword_142AE2C30, LOBYTE(p1));
          byte_142AE2C38 = p2;
          byte_142AE2C3B = p5 != 0;
          byte_142AE2C39 = p3;
          byte_142AE2C3A = p4;
        }
        *((_BYTE *)Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded) + 32734) = p1;
        *((_BYTE *)Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded) + 32735) = p3;
        *((_BYTE *)Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded) + 32736) = p4;
        return;
      case 0x105u:
        byte_142AE2C19 = p1;
        if ( p2 )
          Client__Game__BattleLog__AddLogMessage3Params(0x1174u, v15, p2, 0, 0, 100.0);
        return;
      case 0x106u:
        sub_140C216D0((__int64)&qword_142AE2BE0, 0, p1);
        sub_140C216D0((__int64)&qword_142AE2BE0, 1u, p2);
        sub_140C216D0((__int64)&qword_142AE2BE0, 2u, p3);
        goto LABEL_1369;
      case 0x107u:
        byte_142AE2C21 = p1 != 0;
        return;
      case 0x108u:
        if ( !v15 )
          return;
        v89 = byte_142AE2C1E;
        if ( p2 != 2 )
          v89 = p2;
        byte_142AE2C1E = v89;
        v90 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p1);
        if ( !v90 )
          return;
        v908 = 0;
        v909 = 0;
        value = 0;
        v910 = 0;
        v91 = Client__System__Memory__MemoryPool__Alloc(0x10u);
        v91[1] = 0;
        *(_QWORD *)&value = v91;
        *v91 = &value;
        v1017 = p2;
        v1019 = 0;
        v1018 = &v1017;
        sub_1401EABA0(&value, (__int64)&v1017);
        if ( v1018 )
        {
          if ( v1019 == 1 )
          {
            v92 = (_DWORD *)*v1018;
            if ( (int)--v92[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v92);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v92, 112);
            }
          }
          v1018 = 0;
          v1019 = -1;
        }
        v93 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v94 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v93 + 88LL))(v93);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
          v94,
          0x29Du,
          (void *)v19,
          v90,
          &value);
        v95 = v910;
        if ( v910 )
        {
          do
          {
            sub_1401E09B0(*(_QWORD *)(*((_QWORD *)&value + 1) + 8 * ((v908 - 1) & (v909 - 1 + v95))));
            v95 = --v910;
          }
          while ( v910 );
          v909 = 0;
        }
        v96 = v908;
        v97 = (_QWORD *)*((_QWORD *)&value + 1);
        while ( v96 )
        {
          v98 = (void *)v97[--v96];
          if ( v98 )
          {
            Client__System__Memory__MemoryPool__Free(v98);
            v97 = (_QWORD *)*((_QWORD *)&value + 1);
          }
        }
        if ( v97 )
          Client__System__Memory__MemoryPool__Free(v97);
        v84 = (void *)value;
        value = 0u;
        v908 = 0;
        goto LABEL_505;
      case 0x109u:
        if ( v15 )
        {
          v99 = EXD__BuddySkill__Row_140837380(p2);
          if ( v99 )
          {
            if ( (*(_BYTE *)(v99 + 7) & 1) != 0 )
              Client__Game__BattleLog__AddActionLogMessage(
                0x52Bu,
                (void *)v19,
                0,
                1u,
                *(unsigned __int16 *)(v99 + 2LL * p1),
                0,
                0,
                0,
                0,
                100.0);
            else
              Client__Game__BattleLog__AddLogMessage3Params(
                0x52Cu,
                (void *)v19,
                *(unsigned __int16 *)(v99 + 2LL * p1),
                0,
                0,
                100.0);
          }
        }
        return;
      case 0x10Au:
        if ( v15 )
          sub_140909F80((__int64)v15, 0.5, v17);
        return;
      case 0x10Bu:
        if ( v15 )
        {
          (*(void (__fastcall **)(float *, __int64))(*(_QWORD *)v15 + 312LL))(v15, 10);
          sub_140909E00((float *)v19, 0.0, 0);
          sub_140909F00((__int64 *)v19, 1.0);
        }
        return;
      case 0x10Cu:
        if ( v15 )
        {
          sub_1405D57D0(v976);
          LODWORD(v1176) = p1;
          v1095 = -1;
          v1094[0] = 0;
          v1094[1] = 0;
          sub_14078F8B0((__int64)v1094, &v1176);
          sub_1401EABA0(v976, (__int64)v1094);
          sub_1401E09B0((__int64)v1094);
          v613 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v614 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v613 + 88LL))(v613);
          sub_1409B44A0(v614, 640, (_WORD *)v19, (__int64)v976);
          sub_1407AD1F0(v976);
        }
        return;
      case 0x10Du:
        if ( v15 )
        {
          sub_1405D57D0(v967);
          LODWORD(v1176) = p1;
          v1097 = -1;
          v1096[0] = 0;
          v1096[1] = 0;
          sub_14078F8B0((__int64)v1096, &v1176);
          sub_1401EABA0(v967, (__int64)v1096);
          sub_1401E09B0((__int64)v1096);
          LODWORD(v1176) = p2;
          v1098[1] = 0;
          v1098[0] = 0;
          v1099 = -1;
          sub_14078F8B0((__int64)v1098, &v1176);
          sub_1401EABA0(v967, (__int64)v1098);
          sub_1401E09B0((__int64)v1098);
          v615 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v616 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v615 + 88LL))(v615);
          sub_1409B44A0(v616, 642, (_WORD *)v19, (__int64)v967);
          sub_1407AD1F0(v967);
        }
        return;
      case 0x10Eu:
        if ( v15 )
        {
          LOBYTE(v17) = 1;
          Client__Game__Character__CompanionContainer__SetupCompanion(v15 + 438, p1, v17);
          if ( sub_140897A40(v19, isRecorded, 0) )
          {
            v52 = sub_140B777C0();
            sub_140B819B0(v52);
            v53 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            if ( v53 )
              (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)v53 + 1000LL))(v53, 16, p1);
          }
        }
        return;
      case 0x10Fu:
        v54 = p2;
        if ( p2 != 1 )
          goto LABEL_111;
        v55 = p1;
        if ( ((unsigned __int8)(1 << (p1 & 7))
            & *((_BYTE *)&qword_142ADE980 + ((unsigned __int64)p1 >> 3) + 106644)) == 0 )
        {
          Client__Game__BattleLog__AddLogMessage3Params(0x261u, v15, p1, 0, 0, 100.0);
          v54 = p2;
LABEL_111:
          v55 = p1;
        }
        sub_140C4CB90((__int64)&qword_142ADE980, v55, v54 != 0);
        return;
      case 0x110u:
        if ( v15 )
          sub_140909F40((__int64 *)v15, 0.30000001);
        return;
      case 0x111u:
        byte_142AE2C1F = p1;
        goto LABEL_1369;
      case 0x112u:
        byte_142AE2C20 = p1;
        goto LABEL_1369;
      case 0x113u:
        dword_142AE2C14 = p1;
        byte_142AE2C19 = p2;
        byte_142AE2C1F = p3;
        byte_142AE2C20 = p4;
LABEL_1369:
        v610 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v611 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v610 + 296LL))(v610);
        v612 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v611, 0x6Eu);
        if ( v612 )
          v612[40] = 1;
        return;
      case 0x114u:
        sub_140C22620((__int64)&qword_142AE2C40, p1, p2, p3);
        return;
      case 0x115u:
        if ( v15 )
          sub_140C229B0((__int64)&qword_142AE2C40, v15, p1);
        return;
      case 0x116u:
        if ( p1 >= 4 )
          Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x5Cu, 0, 0);
        if ( p1 == 8 )
        {
          v77 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          LOBYTE(v78) = 1;
          (*(void (__fastcall **)(void *, __int64, __int64, __int64, int))(*(_QWORD *)v77 + 1440LL))(
            v77,
            120115,
            v78,
            3,
            -1);
        }
        else if ( p1 >= 4 )
        {
          v79 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          LOBYTE(v80) = 1;
          (*(void (__fastcall **)(void *, __int64, __int64, __int64, int))(*(_QWORD *)v79 + 1440LL))(
            v79,
            120114,
            v80,
            3,
            -1);
        }
        return;
      case 0x117u:
        if ( v15 )
        {
          sub_1408AA090((__int64)(v15 + 438), p1, 1);
          if ( sub_140897A40(v19, isRecorded, 0) )
          {
            v56 = sub_140B777C0();
            sub_140B819B0(v56);
            v57 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            if ( v57 )
              (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)v57 + 1000LL))(v57, 16, 0);
          }
        }
        return;
      case 0x122u:
        if ( v15 )
        {
          v438 = EXD__Emote__Row_140836970(p1);
          v439 = v438;
          if ( v438 )
          {
            if ( *(_BYTE *)(v438 + 38) )
            {
              options[0] = off_142178A70;
              options[1] = targetId;
              v945 = 0;
              v943 = p3 & 1 | v943 & 0xF8 | (2 * ((p3 & 2) != 0));
              v944 = (p3 & 8) != 0;
              Client__Game__Control__EmoteController__PlayEmote((void *)(v19 + 1584), p1, options);
              v440 = sub_140B777C0();
              sub_1417C8940(v440 + 432, v19, LOWORD(p1), targetId, v439);
            }
          }
        }
        return;
      case 0x123u:
        if ( v15 )
          sub_140614BE0((__int64)(v15 + 396));
        return;
      case 0x126u:
        sub_141969700((__int64)&qword_142AAB6B0, LOWORD(p1), p2);
        return;
      case 0x127u:
        if ( v15 )
          sub_1406169B0((__int64)(v15 + 396), p1, p2);
        return;
      case 0x12Cu:
        if ( v15 )
          sub_1408C76C0(v15 + 1624, p1, p2, p3, p4);
        return;
      case 0x12Du:
        sub_140E96C10(p1, p2, p3);
        return;
      case 0x12Eu:
        v459 = sub_140B777C0();
        v460 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v459, LOWORD(p1) | 0x30000u);
        if ( v460 )
          *(_BYTE *)(v460 + 778) = p2;
        return;
      case 0x130u:
        v496 = 0;
        v1176 = __PAIR64__(p2, p1);
        v1177 = p3;
        v1178 = p4;
        do
        {
          v497 = v496;
          if ( (v496 & 1) != 0 )
          {
            if ( v496 < 0 )
              v497 = v496 + 1;
            v498 = *((_WORD *)&v1176 + 2 * (v497 >> 1) + 1);
          }
          else
          {
            if ( v496 < 0 )
              v497 = v496 + 1;
            v498 = *((_WORD *)&v1176 + 2 * (v497 >> 1));
          }
          v499 = sub_140B777C0();
          v500 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v499, v498 | 0x30000u);
          if ( v500 )
            sub_140E8B250(v500);
          ++v496;
        }
        while ( v496 < 8 );
        return;
      case 0x131u:
        v461 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v462 = v461;
        if ( v19 && v461 )
        {
          sub_1405D57D0(v978);
          if ( p2 )
          {
            LODWORD(v1176) = p2;
            v1141 = -1;
            v1140[0] = 0;
            v1140[1] = 0;
            sub_14078F8B0((__int64)v1140, &v1176);
            sub_1401EABA0(v978, (__int64)v1140);
            sub_1401E09B0((__int64)v1140);
          }
          v463 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v462 + 88LL))(v462);
          sub_1409B44A0(v463, p1, (_WORD *)v19, (__int64)v978);
          sub_1407AD1F0(v978);
        }
        return;
      case 0x132u:
        v464 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v465 = v464;
        if ( !v19 || !v464 )
          return;
        LODWORD(v1176) = p1;
        sub_1405D57D0(v977);
        v1143 = -1;
        v1142[0] = 0;
        v1142[1] = 0;
        sub_14078F8B0((__int64)v1142, &v1176);
        sub_1401EABA0(v977, (__int64)v1142);
        sub_1401E09B0((__int64)v1142);
        v466 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v465 + 88LL))(v465);
        sub_1409B44A0(v466, 3502, (_WORD *)v19, (__int64)v977);
        v467 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v465 + 296LL))(v465);
        v468 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v467, 0x28u);
        if ( !v468 )
          goto LABEL_1037;
        if ( p2 )
        {
          sub_140FC03D0((__int64)v468, 1u);
          sub_1407AD1F0(v977);
        }
        else
        {
          sub_140FC03D0((__int64)v468, 2u);
LABEL_1037:
          sub_1407AD1F0(v977);
        }
        return;
      case 0x133u:
        v469 = sub_140B777C0();
        v470 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v469, LOWORD(p1) | 0x30000u);
        if ( v470 )
          sub_140E96D40(v470);
        return;
      case 0x134u:
        v476 = sub_140B777C0();
        v477 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v476, LOWORD(p1) | 0x30000u);
        if ( v477 )
          sub_140E96D20(v477, p2, p3 != 0);
        return;
      case 0x135u:
        if ( v15 )
        {
          if ( (*(unsigned __int8 (__fastcall **)(float *))(*(_QWORD *)v15 + 344LL))(v15) )
          {
            if ( p3 != 3758096384LL )
            {
              v471 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByGameObjectId(
                       qword_1428BCDD0,
                       (unsigned int)p3);
              if ( v471 )
              {
                sub_1408BDCB0(v19 + 2608, 0x1F78u, 0, 0);
                if ( entityId == sourceId )
                {
                  sub_1408BDCB0(v19 + 2608, 0x32F0u, 0, 0);
                  sub_1405EBA80(*(_QWORD *)(qword_14290B930 + 48), 0x11u);
                  v472 = *(float *)Client__Game__Object__GameObject__GetPosition(v471);
                  v473 = *((float *)Client__Game__Object__GameObject__GetPosition(v471) + 1);
                  v474 = *((float *)Client__Game__Object__GameObject__GetPosition(v471) + 2);
                  sub_14038C1B0((__int64)v1175);
                  v475 = sub_14090DD20(v19);
                  sub_14038C5E0((__int64)v1175, v475);
                  sub_140394430(
                    (__int64)"vfx/live/gather/eff/gat_ref_pt.avfx",
                    (__int64)v1175,
                    2,
                    0,
                    v472,
                    v473,
                    v474,
                    1065353216,
                    0x3F800000u,
                    1065353216,
                    0,
                    1065353216,
                    -1);
                  nullsub_20();
                }
              }
            }
          }
        }
        return;
      case 0x136u:
        v478 = sub_140B777C0();
        v479 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v478, LOWORD(p1) | 0x30000u);
        if ( v479 )
          sub_140E8AFF0(v479, p2);
        return;
      case 0x137u:
        v480 = sub_140B777C0();
        v481 = (unsigned __int8 *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                                    v480,
                                    LOWORD(p1) | 0x30000u);
        if ( v481 )
          sub_140E8B010(v481, p2 != 0);
        return;
      case 0x138u:
        v492 = sub_140B777C0();
        v493 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v492,
                          LOWORD(p1) | 0x30000u);
        if ( v493 )
          sub_140E8B230(v493, p2);
        return;
      case 0x139u:
        v494 = sub_140B777C0();
        v495 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v494, LOWORD(p1) | 0x30000u);
        if ( v495 )
          sub_140E8B250(v495);
        return;
      case 0x13Au:
        v482 = sub_140B777C0();
        v483 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v482,
                          LOWORD(p1) | 0x30000u);
        if ( v483 )
          sub_140E8B0B0(v483);
        return;
      case 0x13Bu:
        v484 = sub_140B777C0();
        v485 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v484,
                          LOWORD(p1) | 0x30000u);
        if ( v485 )
          sub_140E8B0D0(v485);
        return;
      case 0x13Cu:
        v490 = sub_140B777C0();
        v491 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v490,
                          LOWORD(p1) | 0x30000u);
        if ( v491 )
          sub_140E8B140(v491, p2);
        return;
      case 0x13Eu:
        v486 = sub_140B777C0();
        v487 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v486,
                          LOWORD(p1) | 0x30000u);
        if ( v487 )
          sub_140E8B160(v487, p2);
        return;
      case 0x13Fu:
        v488 = sub_140B777C0();
        v489 = (_BYTE *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                          v488,
                          LOWORD(p1) | 0x30000u);
        if ( v489 )
          sub_140E8B190(v489, p2 != 0);
        return;
      case 0x141u:
        v512 = p1;
        v513 = p3;
        *((_WORD *)&qword_142ADE980 + p1 + 1726) = p2;
        *((_WORD *)&qword_142ADE980 + v512 + 1770) = v513;
        return;
      case 0x142u:
        dword_142ADF898 = p1;
        return;
      case 0x143u:
        sub_140BE1680((__int64)&byte_142ADF3B8, p1, p2);
        return;
      case 0x144u:
        sub_140BE1830((__int64)&byte_142ADF3B8, p1, p2);
        return;
      case 0x145u:
        sub_140BE18F0((__int64)&byte_142ADF3B8, p1);
        v514 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v514 )
        {
          v515 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v514 + 88LL))(v514);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v515, 3522, p1);
        }
        return;
      case 0x146u:
        v516 = sub_140B777C0();
        sub_140B7D270(v516);
        return;
      case 0x147u:
        if ( p2 )
        {
          if ( source )
            TimelineContainer_PlayResolvedActionTimeline((__int64)(source + 652), 0x2EC0u, 0, 0, 0);
          v519 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v520 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v519 + 88LL))(v519);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v520, 5582, p1);
        }
        else
        {
          sub_1400E13A0(3u);
          v517 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v518 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v517 + 88LL))(v517);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v518, 3530, p1);
        }
        return;
      case 0x148u:
        v521 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v522 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v521 + 88LL))(v521);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v522, 3531, p1);
        return;
      case 0x149u:
        sub_1400E10C0(4u, v16, v17);
        return;
      case 0x14Au:
        v523 = sub_140B777C0();
        v524 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v523, 1376257);
        if ( v524 )
          sub_140E90F90(v524, p1, p2);
        return;
      case 0x14Bu:
        v525 = sub_140B777C0();
        v526 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v525, 1376257);
        if ( v526 )
          sub_140E91030(v526, p1, p2);
        return;
      case 0x14Cu:
        v527 = sub_140B777C0();
        v528 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v527, 1376257);
        if ( v528 )
          sub_140E912B0(v528, p1 == 1);
        return;
      case 0x14Du:
        v529 = sub_140B777C0();
        if ( j_Client__Game__Event__EventFramework__GetEventHandlerById(v529, 1376257) )
          sub_140E91490();
        return;
      case 0x14Eu:
        sub_140BF45B0((__int64)&qword_142AE4D00, p1, p2);
        return;
      case 0x14Fu:
        v532 = sub_140B777C0();
        v533 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v532, 655361);
        if ( v533 )
          sub_140EA04D0(v533, p1, p2, p3, p4);
        return;
      case 0x150u:
        sub_140C4D550((__int64)&qword_142ADE980, p1, p2, p3);
        return;
      case 0x151u:
        *((_BYTE *)&qword_142ADE980 + p1 + 3953) = p2;
        return;
      case 0x152u:
        v530 = sub_140B777C0();
        v531 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v530, 1376257);
        if ( v531 )
          sub_140E915A0(v531, p1, p2, p3, p4);
        return;
      case 0x153u:
        if ( v15 )
          sub_1408C6AC0((__int64)(v15 + 1624), 0x11u);
        return;
      case 0x155u:
        si128 = _mm_load_si128((const __m128i *)&xmmword_142135440);
        if ( p2 < 4 )
        {
          sub_1405D57D0(v965);
          LODWORD(v1176) = p1;
          v1106[0] = 0;
          v1106[1] = 0;
          v1107 = -1;
          sub_14078F8B0((__int64)v1106, &v1176);
          sub_1401EABA0(v965, (__int64)v1106);
          sub_1401E09B0((__int64)v1106);
          v1108[1] = 0;
          v1108[0] = 0;
          v1109 = -1;
          sub_14078F8B0((__int64)v1108, &si128.m128i_i32[p2]);
          sub_1401EABA0(v965, (__int64)v1108);
          sub_1401E09B0((__int64)v1108);
          v749 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v750 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v749 + 88LL))(v749);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v750, 0xE06u, v965);
          sub_1407AD1F0(v965);
        }
        return;
      case 0x156u:
        sub_140BE1940((__int64)&byte_142ADF3B8, p1, p2);
        return;
      case 0x157u:
        sub_140BE1AF0((__int64)&byte_142ADF3B8, p1, p2);
        return;
      case 0x158u:
        v751 = sub_140B777C0();
        v752 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v751, 1376257);
        if ( v752 )
          *(_BYTE *)(v752 + 471) = 0;
        return;
      case 0x159u:
        dword_142ADF8D0 = p1;
        return;
      case 0x15Au:
        if ( v15 )
          sub_140890380((__int64)&unk_142AD5FFA, (__int64)v15, p1, p2, p3, p4 != 0);
        return;
      case 0x15Bu:
        if ( v15 && unknown_libname_811() )
        {
          v225 = (void *)sub_1418EE460();
          Statvfs(v225, (void *)v19, p1, p2, p3, p4 != 0);
        }
        return;
      case 0x15Cu:
        if ( v15 && unknown_libname_811() )
        {
          v226 = sub_1418EE460();
          LOBYTE(value1) = p4 & 1;
          sub_1418F0240(v226, (_BYTE *)v19, p1, p2, p3, value1, (p4 & 2) != 0);
        }
        return;
      case 0x15Du:
        if ( v15 && unknown_libname_811() )
        {
          v227 = (void *)sub_1418EE460();
          sub_1418EF420(
            v227,
            (void *)v19,
            p1 | ((unsigned __int64)p2 << 32),
            (unsigned int)p3 | ((unsigned __int64)(unsigned int)p4 << 32));
        }
        return;
      case 0x15Eu:
        if ( v15 && unknown_libname_811() )
        {
          v228 = sub_1418EE460();
          sub_1418EF570(v228, (_BYTE *)v19, p1, p2, p3 != 0, p4);
        }
        return;
      case 0x15Fu:
        if ( v15 && unknown_libname_811() )
        {
          v229 = sub_1418EE460();
          sub_1418EFAE0(v229, v19, p1 != 0, p2);
        }
        return;
      case 0x160u:
        if ( v15 && unknown_libname_811() )
        {
          v230 = sub_1418EE460();
          sub_1418F07E0(v230, v19, p1, p2 != 0, p3, p4);
        }
        return;
      case 0x161u:
        if ( v15 && unknown_libname_811() )
        {
          v231 = sub_1418EE460();
          sub_1418F08D0(v231, v19);
        }
        return;
      case 0x162u:
        if ( v15 && unknown_libname_811() )
        {
          v232 = sub_1418EE460();
          sub_1418F0940(v232, v19, p1);
        }
        return;
      case 0x163u:
        if ( v15 && unknown_libname_811() )
        {
          v233 = sub_1418EE460();
          sub_1418F09B0(v233, v19, p1);
        }
        return;
      case 0x164u:
        if ( v15 && unknown_libname_811() )
        {
          v234 = sub_1418EE460();
          sub_1418F0A80(v234);
        }
        return;
      case 0x165u:
        sub_1408909A0();
        return;
      case 0x166u:
        if ( unknown_libname_811() )
        {
          sub_1418EE460();
          sub_1418F0AD0();
        }
        return;
      case 0x168u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          LOBYTE(v281) = 1;
          sub_140417760(*((_QWORD *)qword_142909910 + 1393), 44, v281);
          if ( p1 )
          {
            v282 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v283 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v282 + 112LL))(v282);
            sub_1407F2820(v283);
          }
LABEL_652:
          sub_140886800();
        }
        return;
      case 0x169u:
        dword_142AD96C8 = p1;
        return;
      case 0x16Au:
        if ( !v15 || !sub_140897A40((__int64)v15, isRecorded, 0) )
          return;
        v284 = p2;
        v285 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v286 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v285 + 88LL))(v285);
        if ( p1 )
          v287 = 1896;
        else
          v287 = 1898;
        goto LABEL_737;
      case 0x16Bu:
        if ( !v15 || !sub_140897A40((__int64)v15, isRecorded, 0) )
          return;
        v284 = p1;
        v288 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v286 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v288 + 88LL))(v288);
        if ( p2 )
          v287 = 1897;
        else
          v287 = 1899;
LABEL_737:
        Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v286, v287, v284);
        sub_140886850();
        return;
      case 0x16Cu:
        if ( v15 )
        {
          sub_1405D57D0(v962);
          v1065 = 0;
          v1064[0] = p1;
          v1064[1] = (__int64)v1064;
          sub_1401EABA0(v962, (__int64)v1064);
          sub_1401E09B0((__int64)v1064);
          v1061 = 0;
          v1060[0] = p2;
          v1060[1] = (__int64)v1060;
          sub_1401EABA0(v962, (__int64)v1060);
          sub_1401E09B0((__int64)v1060);
          v217 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v218 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v217 + 88LL))(v217);
          sub_1409B44A0(v218, 4309, (_WORD *)v19, (__int64)v962);
          if ( p3 )
          {
            v219 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v220 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v219 + 112LL))(v219);
            sub_1407F2820(v220);
          }
          if ( sub_140897A40(v19, isRecorded, 0) )
            sub_140886890();
          sub_1407AD1F0(v962);
        }
        return;
      case 0x16Du:
        if ( v15 )
        {
          sub_1405D57D0(v975);
          v1059 = 0;
          v1058[0] = p1;
          v1058[1] = (__int64)v1058;
          sub_1401EABA0(v975, (__int64)v1058);
          sub_1401E09B0((__int64)v1058);
          v221 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v222 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v221 + 88LL))(v221);
          sub_1409B44A0(v222, 4310, (_WORD *)v19, (__int64)v975);
          if ( p2 )
          {
            v223 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v224 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v223 + 112LL))(v223);
            sub_1407F2820(v224);
          }
          if ( sub_140897A40(v19, isRecorded, 0) )
            sub_140886890();
          sub_1407AD1F0(v975);
        }
        return;
      case 0x172u:
        v194 = dword_142AD96B4;
        if ( p1 == dword_142AD9628 )
          v194 = 1;
        LOBYTE(dword_142AD96B4) = v194;
        if ( p1 == dword_142AD9670 )
          BYTE1(dword_142AD96B4) = 1;
        return;
      case 0x173u:
        dword_142AD96B4 = 0;
        byte_142AD96B8 = 0;
        sub_140868410((__int64)&qword_142AD9620);
        sub_140868410((__int64)&qword_142AD9668);
        return;
      case 0x174u:
        Client__Game__GameMain__ExecuteCommand(404, p1, 0, 0, 0);
        return;
      case 0x175u:
        Client__Game__GameMain__ExecuteCommand(405, p1, 0, 0, 0);
        return;
      case 0x176u:
        Client__Game__GameMain__ExecuteCommand(406, p1, 0, 0, 0);
        return;
      case 0x177u:
        v195 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v196 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v195 + 296LL))(v195);
        v197 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v196, 0x55u);
        if ( v197 )
          (*(void (__fastcall **)(void *))(*(_QWORD *)v197 + 40LL))(v197);
        goto LABEL_516;
      case 0x178u:
LABEL_516:
        sub_140881AD0((__int64)dword_142AD6000);
        return;
      case 0x179u:
        sub_1405D57D0(v966);
        v991 = p1;
        v993 = 0;
        v992 = &v991;
        sub_1401EABA0(v966, (__int64)&v991);
        if ( v992 )
        {
          if ( v993 == 1 )
          {
            v198 = (_DWORD *)*v992;
            if ( (int)--v198[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v198);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v198, 112);
            }
          }
          v992 = 0;
          v993 = -1;
        }
        v994 = p2;
        v996 = 0;
        v995 = &v994;
        sub_1401EABA0(v966, (__int64)&v994);
        if ( v995 )
        {
          if ( v996 == 1 )
          {
            v199 = (_DWORD *)*v995;
            if ( (int)--v199[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v199);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v199, 112);
            }
          }
          v995 = 0;
          v996 = -1;
        }
        v200 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v201 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v200 + 88LL))(v200);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v201, 0x10A4u, v966);
        sub_1407AD1F0(v966);
        sub_1405D57D0(v972);
        v1009 = (unsigned int)p3;
        v1011 = 0;
        v1010 = &v1009;
        sub_1401EABA0(v972, (__int64)&v1009);
        if ( v1010 )
        {
          if ( v1011 == 1 )
          {
            v202 = (_DWORD *)*v1010;
            if ( (int)--v202[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v202);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v202, 112);
            }
          }
          v1010 = 0;
          v1011 = -1;
        }
        v1006 = (unsigned int)p4;
        v1008 = 0;
        v1007 = &v1006;
        sub_1401EABA0(v972, (__int64)&v1006);
        if ( v1007 )
        {
          if ( v1008 == 1 )
          {
            v203 = (_DWORD *)*v1007;
            if ( (int)--v203[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v203);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v203, 112);
            }
          }
          v1007 = 0;
          v1008 = -1;
        }
        v204 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v205 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v204 + 88LL))(v204);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v205, 0x10A5u, v972);
        sub_1407AD1F0(v972);
        return;
      case 0x17Au:
        if ( unknown_libname_536() )
        {
          v292 = (void *)sub_140EB0D70();
          Client__Game__CurrencyManager__SetItemData(v292, p1, p2, p3, p4, p5 != 0);
        }
        return;
      case 0x17Bu:
        sub_140BF4610((__int64)&qword_142AE4D00, p1);
        return;
      case 0x17Cu:
        v501 = sub_140B777C0();
        v502 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v501, LOWORD(p1) | 0x30000u);
        if ( v502 )
          sub_140E8B260(v502, p2, p3, p4, p5, p6);
        return;
      case 0x17Du:
        v503 = sub_140B777C0();
        v504 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v503, LOWORD(p1) | 0x30000u);
        if ( v504 )
          sub_140E8B3D0(v504);
        return;
      case 0x17Eu:
        v505 = 0;
        v1176 = __PAIR64__(p2, p1);
        v1177 = p3;
        v1178 = p4;
        do
        {
          v506 = v505;
          if ( (v505 & 1) != 0 )
          {
            if ( v505 < 0 )
              v506 = v505 + 1;
            v507 = *((_WORD *)&v1176 + 2 * (v506 >> 1) + 1);
          }
          else
          {
            if ( v505 < 0 )
              v506 = v505 + 1;
            v507 = *((_WORD *)&v1176 + 2 * (v506 >> 1));
          }
          v508 = sub_140B777C0();
          v509 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v508, v507 | 0x30000u);
          if ( v509 )
            sub_140E8B3D0(v509);
          ++v505;
        }
        while ( v505 < 8 );
        return;
      case 0x17Fu:
        if ( !p1 )
        {
          unk_142AD96C0 = p2;
          unk_142AD96C4 = p3;
        }
        return;
      case 0x180u:
        v510 = sub_140B777C0();
        v511 = (__int64 *)j_Client__Game__Event__EventFramework__GetEventHandlerById(
                            v510,
                            LOWORD(p1) | 0x30000u);
        if ( v511 )
          sub_140E8B510(v511, p2, p3, p4, p5, p6);
        return;
      case 0x190u:
        sub_140C31F80((__int64)qword_142AE32A0, p1, p2);
        return;
      case 0x191u:
        sub_140C32140((__int64)qword_142AE32A0, p1, p2);
        return;
      case 0x197u:
      case 0x19Cu:
        if ( v15 )
          sub_1408BDCB0((__int64)(v15 + 652), p1, 0, 0);
        return;
      case 0x199u:
        if ( p3 )
          v594 = sub_14196CD40((__int64)qword_142B0D890, p4);
        else
          v594 = sub_141758F50((__int64)&qword_142AFA4F0, entityId);
        v595 = (_DWORD *)v594;
        if ( v594 )
        {
          v596 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v594 + 16LL))(v594);
          if ( v596 == 7 )
          {
            Client__Game__Object__EventObject__SetSharedTimelineState(v595, p1, 0, 0);
          }
          else if ( v596 == 12 )
          {
            sub_141A45F90(v595, p1);
          }
        }
        return;
      case 0x19Au:
        goto LABEL_1332;
      case 0x19Bu:
        if ( v15 )
          sub_1408BE840(v15 + 652, 0, 0);
        return;
      case 0x19Du:
        goto LABEL_1348;
      case 0x19Eu:
        if ( !v15 )
          return;
        v589 = *(_QWORD *)v15;
        v590 = v19;
        v591 = 16;
        if ( p1 != 1 )
          goto LABEL_1319;
        (*(void (__fastcall **)(__int64, __int64))(v589 + 312))(v19, 16);
        if ( p2 )
        {
          sub_140909E00((float *)v19, 0.0, 0);
          sub_140909F00((__int64 *)v19, (float)(int)p2 * 0.1);
        }
        return;
      case 0x19Fu:
        if ( !v15 )
          return;
        v589 = *(_QWORD *)v15;
        v590 = v19;
        v591 = 13;
LABEL_1319:
        (*(void (__fastcall **)(__int64, __int64))(v589 + 328))(v590, v591);
        return;
      case 0x1A0u:
        v592 = sub_141758F50((__int64)&qword_142AFA4F0, entityId);
        v593 = v592;
        if ( v592 && (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v592 + 16LL))(v592) == 7 )
          *(_DWORD *)(v593 + 436) = p1;
        return;
      case 0x1A1u:
        if ( v15 )
        {
          v605 = p1;
          if ( p1 != -536870912 && *(_BYTE *)(v19 + 145) == 5 )
          {
            *(_BYTE *)(v19 + 145) = 11;
            v605 = p1;
          }
          *(_DWORD *)(v19 + 9028) = v605;
        }
        return;
      case 0x1A2u:
        entityId = p3;
LABEL_1348:
        v603 = sub_141758F50((__int64)&qword_142AFA4F0, entityId);
        v604 = (void *)v603;
        if ( v603 && (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v603 + 16LL))(v603) == 7 )
          Client__Game__Object__EventObject__PlayAnimation(v604, LOWORD(p1), (unsigned __int16)p2, 0);
        return;
      case 0x1A3u:
        entityId = p4;
LABEL_1332:
        v597 = sub_141758F50((__int64)&qword_142AFA4F0, entityId);
        if ( v597 )
        {
          if ( !p3 || (v598 = sub_140B777C0(), !sub_140B87440(v598, 0)) )
          {
            v599 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v597 + 16LL))(v597);
            if ( v599 == 7 || v599 == 12 )
              (*(void (__fastcall **)(__int64, _QWORD, _QWORD))(*(_QWORD *)v597 + 160LL))(v597, p1, p2);
          }
        }
        return;
      case 0x1A4u:
        goto LABEL_1339;
      case 0x1A5u:
        entityId = p3;
LABEL_1339:
        v600 = sub_141758F50((__int64)&qword_142AFA4F0, entityId);
        v601 = v600;
        if ( v600 )
        {
          v602 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v600 + 16LL))(v600);
          if ( v602 == 7 || v602 == 12 )
            (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v601 + 168LL))(v601, p1);
        }
        return;
      case 0x1F4u:
        if ( v15 )
          sub_140C0E130((__int64)&qword_142AEF600, (__int64)v15, p1);
        return;
      case 0x1F5u:
        Client__Game__TitleList__SetTitleUnlocked(&qword_142AEF608, p1);
        return;
      case 0x1F6u:
        sub_140C0CAE0(&qword_142AEF310, p1, targetId, p2);
        return;
      case 0x1F7u:
        sub_140C0CFC0((__int64)&qword_142AEF310, p1, p2);
        return;
      case 0x1F8u:
        if ( v15 )
          *((_BYTE *)v15 + 464) = p1;
        return;
      case 0x1F9u:
        sub_140C0E000((__int64)&qword_142AEF5F0, p1, p2, p3, p4, p5);
        v443 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v444 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v443 + 296LL))(v443);
        v445 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v444, 4u);
        if ( v445 )
          sub_140FDB660((__int64)v445, LOBYTE(p1), (unsigned __int16)p2, p4);
        return;
      case 0x1FAu:
        sub_140C0CB50();
        return;
      case 0x1FBu:
        word_142ADF68C = LOBYTE(p1);
        return;
      case 0x1FCu:
        sub_140BE11C0((__int64)&byte_142ADF3B8, p1, (unsigned __int8)p2);
        return;
      case 0x1FDu:
        sub_140C4B6A0((__int64)&qword_142ADE980, p1, p2 != 0);
        v569 = sub_140B777C0();
        sub_140B80B70(v569, 8, 1);
        return;
      case 0x1FEu:
        sub_140C4B6E0((__int64)&qword_142ADE980, p1, p2 != 0);
        v570 = sub_140B777C0();
        sub_140B80B70(v570, 16, 1);
        return;
      case 0x1FFu:
        sub_140C15430((__int64)&qword_142AEB2F0, p1, v17, v18);
        v588 = sub_140B777C0();
        sub_140B7E510(v588, p1);
        return;
      case 0x200u:
        sub_140C15E10((__int64)&qword_142AEB2F0);
        return;
      case 0x201u:
        v553 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v554 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v553 + 296LL))(v553);
        v555 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v554, 0x5Cu);
        switch ( p1 )
        {
          case 0u:
            sub_140C1CC90((__int64)&qword_142AE0008, p2, p3 != 0);
            if ( v555 )
              sub_140F34030((__int64)v555, p2, p3 != 0);
            break;
          case 1u:
          case 2u:
          case 3u:
          case 4u:
          case 5u:
          case 6u:
            sub_140C1CC90((__int64)&qword_142AE0008, p2, p3 != 0);
            if ( v555 )
              sub_140F33EB0((__int64)v555, p1);
            break;
          default:
            return;
        }
        return;
      case 0x202u:
        Client__Game__UI__Achievement__ReceiveAchievementProgress(dword_142AE0028, p1, p2, p3);
        return;
      case 0x203u:
        Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x84u, 0, 0);
        Client__Game__UI__Achievement__SetAchievementCompleted(dword_142AE0028, p1);
        v559 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v560 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v559 + 64LL))(v559);
        sub_1400F6C50(v560, p1);
        return;
      case 0x204u:
        sub_140C4B720((__int64)&qword_142ADE980, p1, p2 != 0);
        v571 = sub_140B777C0();
        sub_140B80B70(v571, 32, 1);
        return;
      case 0x205u:
        if ( v15 )
        {
          sub_1405D57D0(v946);
          v1078[0] = p2;
          v1079 = 0;
          v1078[1] = (__int64)v1078;
          sub_1401EABA0(v946, (__int64)v1078);
          sub_1401E09B0((__int64)v1078);
          v1070[0] = (unsigned int)p3;
          v1071 = 0;
          v1070[1] = (__int64)v1070;
          sub_1401EABA0(v946, (__int64)v1070);
          sub_1401E09B0((__int64)v1070);
          v1066[0] = (unsigned int)p4;
          v1067 = 0;
          v1066[1] = (__int64)v1066;
          sub_1401EABA0(v946, (__int64)v1066);
          sub_1401E09B0((__int64)v1066);
          v1069 = 0;
          v1068[0] = p5;
          v1068[1] = (__int64)v1068;
          sub_1401EABA0(v946, (__int64)v1068);
          sub_1401E09B0((__int64)v1068);
          v1073 = 0;
          v1072[0] = p6;
          v1072[1] = (__int64)v1072;
          sub_1401EABA0(v946, (__int64)v1072);
          sub_1401E09B0((__int64)v1072);
          v409 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v410 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v409 + 88LL))(v409);
          sub_1409B44A0(v410, p1, (_WORD *)v19, (__int64)v946);
          sub_1407AD1F0(v946);
        }
        return;
      case 0x206u:
        if ( v15 && source )
        {
          v561 = (float *)Client__Game__Object__GameObject__GetPosition(source);
          v562 = (float *)Client__Game__Object__GameObject__GetPosition((void *)v19);
          sub_140B52B50((__int64)&v1176, v562, v561);
          v563 = (float)(*(float *)&v1176 * *(float *)&v1176) + (float)(*(float *)&v1177 * *(float *)&v1177);
          v564 = v563 < 0.0 ? sqrtf(v563) : fsqrt(v563);
          if ( v564 <= 25.0 && *(_BYTE *)(v19 + 7056) < 2u )
          {
            sub_1405D57D0(v973);
            LODWORD(v1176) = p1;
            v1145 = -1;
            v1144[0] = 0;
            v1144[1] = 0;
            sub_14078F8B0((__int64)v1144, &v1176);
            sub_1401EABA0(v973, (__int64)v1144);
            sub_1401E09B0((__int64)v1144);
            v565 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v566 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v565 + 88LL))(v565);
            sub_1409B44A0(v566, 952, (_WORD *)v19, (__int64)v973);
            sub_1407AD1F0(v973);
          }
        }
        return;
      case 0x207u:
        v441 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v442 = Client__Game__Group__GroupManager__Group__GetPartyMemberByEntityId(v441, p1);
        if ( v442 )
          sub_140B238A0(v442, p2);
        return;
      case 0x208u:
        sub_140BE1C30((__int64)&byte_142ADF3B8, p1, p2);
        sub_140BE1CB0((__int64)&byte_142ADF3B8, p1, p3);
        v657 = sub_140B777C0();
        sub_140B80B70(v657, 256, 1);
        return;
      case 0x209u:
        v660 = word_142AF8954;
        word_142AF8954 = p1;
        if ( v660 != LOWORD(p1) )
        {
          v661 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          if ( v661 )
            (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)v661 + 1000LL))(v661, 13, 0);
        }
        return;
      case 0x20Au:
        sub_140C2F290((__int64)&qword_142AE2D00);
        goto LABEL_1450;
      case 0x20Bu:
        sub_140C2F610((__int64)&qword_142AE2D00, p1);
        sub_1405D57D0(v980);
        LODWORD(v1176) = p1;
        v1103 = -1;
        v1102[0] = 0;
        v1102[1] = 0;
        sub_14078F8B0((__int64)v1102, &v1176);
        sub_1401EABA0(v980, (__int64)v1102);
        sub_1401E09B0((__int64)v1102);
        v662 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v663 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v662 + 88LL))(v662);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v663, 0xEC4u, v980);
        sub_1407AD1F0(v980);
        v664 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v665 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v664 + 64LL))(v664);
        sub_1400F6CE0(v665, p1, p2, p3);
LABEL_1450:
        v666 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v667 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v666 + 296LL))(v666);
        v668 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v667, 0x88u);
        if ( v668 )
          sub_140F57E00((__int64)v668, 0);
        return;
      case 0x20Cu:
        Client__Game__BattleLog__AddLogMessage3Params(3782 - (p1 != 0), 0, 0, 0, 0, 100.0);
        v669 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v670 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v669 + 296LL))(v669);
        v671 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v670, 0x88u);
        if ( v671 )
          sub_140F57E00((__int64)v671, 1);
        return;
      case 0x20Du:
        sub_140C2F140((__int64)&qword_142AE2D00, p1, p2, p3, p4, p5, p6);
        return;
      case 0x20Eu:
        if ( (p1 & 0x80000000) == 0 && (unsigned __int64)(int)p1 < 3 )
          *((_WORD *)&qword_142ADE980 + (int)p1 + 1676) = (unsigned __int8)p2;
        return;
      case 0x20Fu:
      case 0x210u:
        if ( v15 )
        {
          v413 = source;
          v414 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p2);
          sub_1405D57D0(v941);
          LODWORD(v1176) = p3;
          v1126[0] = 0;
          v1126[1] = 0;
          v1127 = -1;
          sub_14078F8B0((__int64)v1126, &v1176);
          sub_1401EABA0(v941, (__int64)v1126);
          sub_1401E09B0((__int64)v1126);
          LODWORD(v1176) = p4;
          v1128[1] = 0;
          v1128[0] = 0;
          v1129 = -1;
          sub_14078F8B0((__int64)v1128, &v1176);
          sub_1401EABA0(v941, (__int64)v1128);
          sub_1401E09B0((__int64)v1128);
          LODWORD(v1176) = p5;
          v1130[1] = 0;
          v1130[0] = 0;
          v1131 = -1;
          sub_14078F8B0((__int64)v1130, &v1176);
          sub_1401EABA0(v941, (__int64)v1130);
          sub_1401E09B0((__int64)v1130);
          LODWORD(v1176) = p6;
          v1132[1] = 0;
          v1132[0] = 0;
          v1133 = -1;
          sub_14078F8B0((__int64)v1132, &v1176);
          sub_1401EABA0(v941, (__int64)v1132);
          sub_1401E09B0((__int64)v1132);
          if ( v414 )
          {
            v415 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v416 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v415 + 88LL))(v415);
            Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
              v416,
              p1,
              v413,
              v414,
              v941);
            sub_1407AD1F0(v941);
          }
          else
          {
            if ( v413 )
            {
              v417 = Client__Game__Group__GroupManager__GetGroupWithCheck(&off_1428C27E0, isRecorded);
              v418 = sub_140B250F0((__int64)v417, p2);
              if ( v418 )
              {
                v419 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
                v420 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v419 + 88LL))(v419);
                v421 = *(_BYTE *)(v418 + 1128);
                v422 = v420;
                v423 = sub_140B23800(v418);
                v424 = (*(__int64 (__fastcall **)(float *))(*(_QWORD *)v413 + 88LL))(v413);
                v425 = (*(__int64 (__fastcall **)(float *, _QWORD))(*(_QWORD *)v413 + 48LL))(v413, 0);
                sub_1409B5260(v422, p1, v425, v424, v423, v421, (__int64)v941, 0, 0);
              }
              else
              {
                v426 = (void *)sub_140838EB0();
                if ( v426 )
                {
                  v427 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
                  v428 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v427 + 88LL))(v427);
                  v429 = Component__Excel__ExcelRow__ResolveStringColumnIndirection(v426);
                  v430 = (*(__int64 (__fastcall **)(float *))(*(_QWORD *)v413 + 88LL))(v413);
                  v431 = (*(__int64 (__fastcall **)(float *, _QWORD))(*(_QWORD *)v413 + 48LL))(v413, 0);
                  sub_1409B5260(v428, p1, v431, v430, (__int64)v429, 0, (__int64)v941, 0, 0);
                }
              }
            }
            sub_1407AD1F0(v941);
          }
        }
        return;
      case 0x211u:
        v436 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v437 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v436 + 88LL))(v436);
        Client__UI__Misc__RaptureLogModule__ShowLogMessage(v437, 0x192u);
        return;
      case 0x212u:
        if ( v15 )
        {
          *((_BYTE *)v15 + 8960) = 0;
          sub_1408B3CD0((__int64)(v15 + 446), -1);
          v142 = sub_140B777C0();
          sub_140B817B0(v142);
          if ( unknown_libname_517() )
          {
            v143 = sub_140E19000();
            sub_140E19790(v143);
          }
        }
        return;
      case 0x213u:
        v139 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v140 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v139 + 296LL))(v139);
        if ( Client__UI__Agent__AgentModule__GetAgentByInternalId(v140, 0x9Au) )
          nullsub_68();
        return;
      case 0x214u:
        if ( v15 )
          Client__Game__BattleLog__AddToScreenLogWithLogMessageId(v15, v15, p1, 0, 0, p2, 0, 0);
        return;
      case 0x215u:
        sub_1405D57D0(v947);
        v1074[0] = p2;
        v1075 = 0;
        v1074[1] = (__int64)v1074;
        sub_1401EABA0(v947, (__int64)v1074);
        sub_1401E09B0((__int64)v1074);
        v1054[0] = (unsigned int)p3;
        v1055 = 0;
        v1054[1] = (__int64)v1054;
        sub_1401EABA0(v947, (__int64)v1054);
        sub_1401E09B0((__int64)v1054);
        LODWORD(v1176) = p4;
        v1121 = -1;
        v1120[0] = 0;
        v1120[1] = 0;
        sub_14078F8B0((__int64)v1120, &v1176);
        sub_1401EABA0(v947, (__int64)v1120);
        sub_1401E09B0((__int64)v1120);
        LODWORD(v1176) = p5;
        v1122[1] = 0;
        v1122[0] = 0;
        v1123 = -1;
        sub_14078F8B0((__int64)v1122, &v1176);
        sub_1401EABA0(v947, (__int64)v1122);
        sub_1401E09B0((__int64)v1122);
        LODWORD(v1176) = p6;
        v1124[1] = 0;
        v1124[0] = 0;
        v1125 = -1;
        sub_14078F8B0((__int64)v1124, &v1176);
        sub_1401EABA0(v947, (__int64)v1124);
        sub_1401E09B0((__int64)v1124);
        v411 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v412 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v411 + 88LL))(v411);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v412, p1, v947);
        sub_1407AD1F0(v947);
        return;
      case 0x216u:
        v739 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v740 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v739 + 296LL))(v739);
        v741 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v740, 0xE3u);
        if ( v741 )
          v741[48] = 1;
        return;
      case 0x217u:
        v742 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v743 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v742 + 296LL))(v742);
        v744 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v743, 0xE2u);
        if ( v744 )
          sub_1405853A0((__int64)v744);
        return;
      case 0x218u:
        if ( !p1 )
        {
          v745 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v746 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v745 + 296LL))(v745);
          v747 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v746, 0xE3u);
          if ( v747 )
            sub_140589430((__int64)v747);
        }
        return;
      case 0x219u:
        if ( qword_142AABA88 && *(_DWORD *)(qword_142AABA88 + 120) == p1 )
          sub_140627270((__int64)&qword_142AAB990);
        return;
      case 0x21Au:
        Client__Game__UI__Achievement__ReceiveNearCompletionAchievements(dword_142AE0028, p1, 0);
        return;
      case 0x21Bu:
        if ( LOWORD(p1) == 894 )
          sub_140C0E670((__int64)&qword_142AEF608);
        else
          sub_140C0E640((__int64)&qword_142AEF608, p1);
        return;
      case 0x21Cu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, p1, 0, 0);
        return;
      case 0x21Du:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v206 = p2;
          sub_1405D57D0(v971);
          v1005 = 0;
          v1003 = p1;
          v1004 = &v1003;
          sub_1401EABA0(v971, (__int64)&v1003);
          if ( v1004 )
          {
            if ( v1005 == 1 )
            {
              v207 = (_DWORD *)*v1004;
              if ( (int)--v207[26] <= 0 )
              {
                Client__System__String__Utf8String__Dtor(v207);
                j_Client__System__Memory__IMemorySpace__Free_4((__int64)v207, 112);
              }
            }
            v1004 = 0;
            v1005 = -1;
          }
          v1016 = 0;
          v1014 = v206;
          v1015 = &v1014;
          sub_1401EABA0(v971, (__int64)&v1014);
          if ( v1015 )
          {
            if ( v1016 == 1 )
            {
              v208 = (_DWORD *)*v1015;
              if ( (int)--v208[26] <= 0 )
              {
                Client__System__String__Utf8String__Dtor(v208);
                j_Client__System__Memory__IMemorySpace__Free_4((__int64)v208, 112);
              }
            }
            v1015 = 0;
            v1016 = -1;
          }
          v209 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v210 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v209 + 88LL))(v209);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v210, 0x3F3u, v971);
          v211 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v212 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v211 + 64LL))(v211);
          sub_1400F1940(v212, 120091, 1, 0, -1);
          sub_1407AD1F0(v971);
        }
        return;
      case 0x21Eu:
        if ( !v15 )
          return;
        if ( !sub_140897A40((__int64)v15, isRecorded, 0) )
          return;
        v156 = p1;
        v157 = p3;
        a4 = p2;
        v158 = (unsigned __int16 *)EXD__MonsterNote__Row_14083B5F0(p1);
        v159 = v158;
        if ( !v158 )
          return;
        v160 = p2;
        v1176 = EXD__MonsterNoteTarget__Row_14083B630(v158[p2 + 4]);
        v161 = v1176;
        if ( !v1176 )
          return;
        sub_1405D57D0(v940);
        v1022 = 0;
        v1020 = p1;
        v1021 = &v1020;
        sub_1401EABA0(v940, (__int64)&v1020);
        if ( v1021 )
        {
          if ( v1022 == 1 )
          {
            v162 = (_DWORD *)*v1021;
            if ( (int)--v162[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v162);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v162, 112);
            }
            v161 = v1176;
          }
          v1021 = 0;
          v1022 = -1;
        }
        v1023 = *(unsigned __int16 *)(v161 + 4);
        v1025 = 0;
        v1024 = &v1023;
        sub_1401EABA0(v940, (__int64)&v1023);
        if ( v1024 )
        {
          if ( v1025 == 1 )
          {
            v163 = (_DWORD *)*v1024;
            if ( (int)--v163[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v163);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v163, 112);
            }
          }
          v1024 = 0;
          v1025 = -1;
        }
        v1028 = 0;
        v1026 = v157;
        v1027 = &v1026;
        sub_1401EABA0(v940, (__int64)&v1026);
        if ( v1027 )
        {
          if ( v1028 == 1 )
          {
            v164 = (_DWORD *)*v1027;
            if ( (int)--v164[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v164);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v164, 112);
            }
          }
          v1027 = 0;
          v1028 = -1;
        }
        v1029 = *((unsigned __int8 *)v159 + v160 + 16);
        v1031 = 0;
        v1030 = &v1029;
        sub_1401EABA0(v940, (__int64)&v1029);
        if ( v1030 )
        {
          if ( v1031 == 1 )
          {
            v165 = (_DWORD *)*v1030;
            if ( (int)--v165[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v165);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v165, 112);
            }
          }
          v1030 = 0;
          v1031 = -1;
        }
        if ( v157 == *((unsigned __int8 *)v159 + v160 + 16) )
        {
          v166 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v167 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v166 + 88LL))(v166);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v167, 0x3EAu, v940);
          v168 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v169 = (_QWORD **)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v168 + 64LL))(v168);
          if ( v156 < 0xF4240 )
            v170 = 0;
          else
            v170 = 3;
          sub_1400F66B0(v169, v170, v156, a4);
          sub_140857450(0xD6u, (void *)v19, (void *)v19, -1.0, 0, 0);
        }
        else if ( v157 )
        {
          v171 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v172 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v171 + 88LL))(v171);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v172, 0x3E9u, v940);
        }
        sub_1405E2830(v940);
        v84 = (void *)v940[0];
        v940[0] = 0;
        goto LABEL_505;
      case 0x21Fu:
        if ( !v15 || !sub_140897A40((__int64)v15, isRecorded, 0) )
          return;
        v173 = p1;
        v174 = p2;
        v936 = 0;
        v937 = 0;
        v935 = 0;
        v938 = 0;
        v175 = Client__System__Memory__MemoryPool__Alloc(0x10u);
        v175[1] = 0;
        *(_QWORD *)&v935 = v175;
        *v175 = &v935;
        v1032 = v173;
        v1033 = &v1032;
        v1034 = 0;
        sub_1401EABA0(&v935, (__int64)&v1032);
        if ( v1033 )
        {
          if ( v1034 == 1 )
          {
            v176 = (_DWORD *)*v1033;
            if ( (int)--v176[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v176);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v176, 112);
            }
          }
          v1033 = 0;
          v1034 = -1;
        }
        v177 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v178 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v177 + 88LL))(v177);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v178, 0x3EBu, &v935);
        v179 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v180 = (_QWORD **)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v179 + 64LL))(v179);
        if ( v173 < 0xF4240 )
          v181 = 1;
        else
          v181 = 4;
        sub_1400F66B0(v180, v181, v173, v174);
        sub_140B2EA40((__int64)&qword_142ADCA10, 1);
        sub_1405E2830(&v935);
        v84 = (void *)v935;
        *(_QWORD *)&v935 = 0;
        goto LABEL_505;
      case 0x220u:
        if ( !v15 || !sub_140897A40((__int64)v15, isRecorded, 0) )
          return;
        v182 = p2;
        v183 = (unsigned __int8)sub_140B2E910(p1);
        v184 = sub_140B2E9F0(p1);
        if ( v184 )
          v183 = (unsigned __int8)sub_140B2E9C0(p1);
        v925 = 0;
        v926 = 0;
        *(_OWORD *)pointer = 0;
        v927 = 0;
        v185 = Client__System__Memory__MemoryPool__Alloc(0x10u);
        v185[1] = 0;
        pointer[0] = v185;
        *v185 = pointer;
        v1035 = v183;
        v1036 = &v1035;
        v1037 = 0;
        sub_1401EABA0(pointer, (__int64)&v1035);
        if ( v1036 )
        {
          if ( v1037 == 1 )
          {
            v186 = (_DWORD *)*v1036;
            if ( (int)--v186[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v186);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v186, 112);
            }
          }
          v1036 = 0;
          v1037 = -1;
        }
        v988 = v182 + 1;
        v990 = 0;
        v989 = &v988;
        sub_1401EABA0(pointer, (__int64)&v988);
        if ( v989 )
        {
          if ( v990 == 1 )
          {
            v187 = (_DWORD *)*v989;
            if ( (int)--v187[26] <= 0 )
            {
              Client__System__String__Utf8String__Dtor(v187);
              j_Client__System__Memory__IMemorySpace__Free_4((__int64)v187, 112);
            }
          }
          v989 = 0;
          v990 = -1;
        }
        v188 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v189 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v188 + 88LL))(v188);
        if ( v184 )
        {
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v189, 0x3EDu, pointer);
          v190 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v191 = (_QWORD **)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v190 + 64LL))(v190);
          v192 = 5;
        }
        else
        {
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v189, 0x3ECu, pointer);
          v193 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v191 = (_QWORD **)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v193 + 64LL))(v193);
          v192 = 2;
        }
        sub_1400F66B0(v191, v192, v183, v182);
        sub_140B2EA70((__int64)&qword_142ADCA10, 1);
        sub_1405E2830(pointer);
        v84 = pointer[0];
        pointer[0] = 0;
LABEL_505:
        Client__System__Memory__MemoryPool__Free(v84);
        return;
      case 0x221u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v213 = p2;
          sub_1405D57D0(v970);
          v999 = 0;
          v997 = p1;
          v998 = &v997;
          sub_1401EABA0(v970, (__int64)&v997);
          if ( v998 )
          {
            if ( v999 == 1 )
            {
              v214 = (_DWORD *)*v998;
              if ( (int)--v214[26] <= 0 )
              {
                Client__System__String__Utf8String__Dtor(v214);
                j_Client__System__Memory__IMemorySpace__Free_4((__int64)v214, 112);
              }
            }
            v999 = -1;
            v998 = 0;
          }
          v1077 = 0;
          v1076[0] = v213;
          v1076[1] = (__int64)v1076;
          sub_1401EABA0(v970, (__int64)v1076);
          sub_1401E09B0((__int64)v1076);
          v215 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v216 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v215 + 88LL))(v215);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v216, 0x3F4u, v970);
          sub_140B2EAA0((__int64)&qword_142ADCA10, 1);
          sub_1407AD1F0(v970);
        }
        return;
      case 0x226u:
        sub_140C31350((__int64)&qword_142AE2DB8);
        sub_140C2FE90((__int64)&qword_142AE2DB8);
        v672 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v672 )
        {
          v673 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v672 + 64LL))(v672);
          sub_1400FA6E0(v673, 0);
        }
        return;
      case 0x227u:
        sub_140C2FEE0((__int64)&qword_142AE2DB8, p1, p2);
        sub_140C30EE0((__int64)&qword_142AE2DB8, p2);
        return;
      case 0x228u:
        sub_140C2FF30((__int64)&qword_142AE2DB8, p1, p2);
        sub_140C312B0((__int64)&qword_142AE2DB8, p1);
        v674 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v674 )
        {
          v675 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v674 + 64LL))(v674);
          sub_1400FA6E0(v675, 1u);
        }
        return;
      case 0x229u:
        sub_140C2FF50((__int64)&qword_142AE2DB8, p1, p2 != 0);
        if ( p3 == 2 && p2 )
          sub_140C31300((__int64)&qword_142AE2DB8, p1);
        v676 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v676 )
        {
          v677 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v676 + 64LL))(v676);
          sub_1400FA6E0(v677, p3);
        }
        return;
      case 0x22Bu:
        v678 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v679 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v678 + 64LL))(v678);
        sub_1400F1940(v679, 120903, 1, 0, -1);
        v680 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v681 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v680 + 112LL))(v680);
        v682 = sub_140875C10((__int64)dword_142AD6000);
        if ( v682 )
        {
          v683 = (_BYTE *)sub_140869340(v682, p1, 0);
          if ( v683 )
            sub_1407F3190(v681, v683, p2, p3, p4);
        }
        return;
      case 0x23Au:
        sub_14110D490(qword_142AF9820, p1, p2);
        return;
      case 0x23Bu:
        sub_14110D390(qword_142AF9820, p1, p2);
        return;
      case 0x23Cu:
        for ( k = p2 + 1; k <= p1; ++k )
          sub_141AAA610(k);
        return;
      case 0x23Du:
        word_142ADC598 = p1;
        return;
      case 0x23Eu:
        sub_14110D510(qword_142AF9820, p1);
        return;
      case 0x23Fu:
        sub_14110D550(qword_142AF9820, p1);
        return;
      case 0x240u:
        sub_14110D590(qword_142AF9820);
        return;
      case 0x244u:
        sub_140C3C8E0((__int64)&qword_142AF24C0, p1, p2);
        return;
      case 0x245u:
        sub_140C3CA30((__int64)&qword_142AF24C0, p1);
        return;
      case 0x246u:
        sub_140C3CAE0((__int64)&qword_142AF24C0, p1, p2, p3);
        return;
      case 0x247u:
        sub_140C3C880((__int64)&qword_142AF24C0, p1, p2);
        return;
      case 0x256u:
        sub_140BE3100((__int64)&byte_142ADF3B8, p1);
        v726 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v727 = v726;
        if ( v726 )
        {
          v728 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v726 + 296LL))(v726);
          v729 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v728, 0xEAu);
          v730 = v729;
          if ( v729 )
          {
            if ( (*(unsigned __int8 (__fastcall **)(void *))(*(_QWORD *)v729 + 48LL))(v729) )
            {
              (*(void (__fastcall **)(void *))(*(_QWORD *)v730 + 40LL))(v730);
              v731 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v727 + 88LL))(v727);
              Client__UI__Misc__RaptureLogModule__ShowLogMessage(v731, 0x124Eu);
            }
          }
        }
        return;
      case 0x257u:
        if ( v15 )
        {
          v432 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p2);
          v433 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p3);
          sub_1405D57D0(v957);
          LODWORD(v1176) = p4;
          v1134[0] = 0;
          v1134[1] = 0;
          v1135 = -1;
          sub_14078F8B0((__int64)v1134, &v1176);
          sub_1401EABA0(v957, (__int64)v1134);
          sub_1401E09B0((__int64)v1134);
          LODWORD(v1176) = p5;
          v1136[1] = 0;
          v1136[0] = 0;
          v1137 = -1;
          sub_14078F8B0((__int64)v1136, &v1176);
          sub_1401EABA0(v957, (__int64)v1136);
          sub_1401E09B0((__int64)v1136);
          LODWORD(v1176) = p6;
          v1138[1] = 0;
          v1138[0] = 0;
          v1139 = -1;
          sub_14078F8B0((__int64)v1138, &v1176);
          sub_1401EABA0(v957, (__int64)v1138);
          sub_1401E09B0((__int64)v1138);
          if ( v432 && v433 )
          {
            v434 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v435 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v434 + 88LL))(v434);
            Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
              v435,
              p1,
              v432,
              v433,
              v957);
          }
          sub_1407AD1F0(v957);
        }
        return;
      case 0x258u:
        if ( p2 == 1 )
        {
          Client__Game__UI__Achievement__SetAchievementCompleted(dword_142AE0028, p1);
          v556 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v557 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v556 + 296LL))(v556);
          v558 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v557, 0x82u);
          if ( v558 )
            sub_14056C170((__int64)v558, p1, 1);
        }
        Client__Game__UI__Achievement__ReceiveAchievementProgress(dword_142AE0028, p1, p3, p4);
        return;
      case 0x25Fu:
        if ( p1 == -536870912 )
          return;
        v584 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, p1);
        v585 = v584;
        if ( !v584 )
          return;
        AsCharacter = (__int64 *)Client__Game__Object__GameObject__GetAsCharacter(v584);
        v587 = AsCharacter;
        switch ( p2 )
        {
          case 1u:
            goto LABEL_1297;
          case 2u:
            if ( p3 )
              sub_140857450(p3, v585, v585, -1.0, 0, 0);
LABEL_1297:
            if ( v587 )
              sub_140909F40(v587, (float)p4 / 100.0);
            break;
          case 3u:
            if ( AsCharacter )
              sub_1408BDCB0((__int64)(AsCharacter + 326), p3, 0, 0);
            break;
          case 4u:
            if ( AsCharacter )
              sub_1408BEA90((__int64)(AsCharacter + 326));
            break;
          default:
            if ( p2 == 5 && v585[33] )
              (*(void (__fastcall **)(_QWORD *, _QWORD, _QWORD))(*v585 + 160LL))(v585, (unsigned int)p3, 0);
            break;
        }
        return;
      case 0x260u:
        sub_140B530C0((__int64)&qword_142ADE980, p1, 0);
        v235 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v235 )
        {
          v236 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v235 + 144LL))(v235);
          sub_1407C6ED0(v236);
        }
        return;
      case 0x261u:
        v154 = qword_142908620;
        v155 = *((_BYTE *)qword_142908620 + 188657) == 0;
        *((_BYTE *)qword_142908620 + 188657) = v155;
        v154[169080] = v155;
        v154[190056] = v155;
        *((_DWORD *)v154 + 50039) = *((_DWORD *)v154 + 50039) & 0xFFFFFFFE | v155;
        v154[225477] = v155;
        return;
      case 0x262u:
        if ( p2 == -536870912 )
          v582 = 0;
        else
          v582 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, p2);
        if ( p3 == -536870912 )
          v583 = 0;
        else
          v583 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, p3);
        sub_140857450(p1, v582, v583, -1.0, 0, 0);
        return;
      case 0x263u:
        if ( v15 )
        {
          if ( p1 )
            sub_140909F40((__int64 *)v15, (float)(int)p1 * 0.1);
          else
            sub_140909E00(v15, 0.0, 0);
        }
        return;
      case 0x264u:
        if ( v15 )
        {
          sub_1408BEEB0((__int64)(v15 + 652));
          sub_1408B0100((_WORD *)(v19 + 1784), 0);
          sub_1408BDB00(v19 + 2608);
        }
        return;
      case 0x2BCu:
        sub_1408ED080((__int64)&off_1428BBEC0);
        if ( v19 )
        {
          if ( p6 && *(_DWORD *)((*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19) + 8) == p6 )
            sub_14090C270(v19, p2, p3, 1);
          if ( p2 == 1 && (p3 == 43 || p3 == 8767) )
            sub_1408CCE80(v19 + 6536, 1u, 10, 0, 0);
          if ( *(unsigned __int8 *)((*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19) + 68) == p2
            && *(_DWORD *)((*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19) + 72) == p3 )
          {
            v542 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19);
            sub_1408DEEE0(v542);
            if ( p2 != 1
              || (v543 = EXD__Action__Row_140833940(p3), (v544 = v543) == 0)
              || (v545 = EXD__ActionTimeline__RowIndex_140836D00(*(__int16 *)(v543 + 32))) == 0
              || (unsigned __int16)sub_1408BF5C0(v19 + 2608, *(unsigned __int8 *)(v545 + 11), 0) == *(__int16 *)(v544 + 32) )
            {
              sub_1408BEEB0(v19 + 2608);
              sub_1408B0100((_WORD *)(v19 + 1784), 0);
              sub_1408BDB00(v19 + 2608);
            }
          }
          Client__Game__BattleLog__AddActionLogMessage(p1, (void *)v19, 0, p2, p3, 0, 0, 0, 0, 100.0);
        }
        if ( p4 || p5 )
          Client__Game__ActionManager__SetCooldown(
            &off_1428BBEC0,
            p2,
            p3,
            (float)p4 / 100.0,
            (float)(int)p5 / 100.0);
        else
          sub_1408EDE60((__int64)&off_1428BBEC0, p2, p3);
        if ( v19 )
        {
          v546 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19);
          sub_1408DF150(v546, 0, 0, 0);
        }
        v547 = p3;
        if ( (p3 == 2259 || p3 == 2261 || p3 == 2263)
          && qword_142AA81A0[0]
          && (unsigned __int8)(byte_142AA81F8 - 29) <= 1u )
        {
          *(_BYTE *)(qword_142AA81A0[0] + 12) = 0;
          v547 = p3;
        }
        if ( (unsigned int)(v547 - 2469) <= 4 && v19 )
          sub_140872AB0((__int64)dword_142AD6000, v547, 0);
        return;
      case 0x2BDu:
        Client__Game__BattleLog__AddLogMessage3Params(p1, 0, 0, 0, 0, 100.0);
        return;
      case 0x2BEu:
        sub_140862190((__int64)&dword_1428BBBD0, p1, p2 != 0, p3, p4);
        return;
      case 0x2BFu:
        sub_140C19DA0(byte_142ADFD10);
        return;
      case 0x2C0u:
        v548 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *, _QWORD, __int64, __int64, _QWORD, _QWORD))(*(_QWORD *)v548 + 1184LL))(
          v548,
          0,
          90,
          1,
          0,
          0);
        return;
      case 0x2C1u:
        v1184[0] = p2;
        v1184[1] = p3;
        v1184[2] = p4;
        v549 = sub_140B777C0();
        sub_1417C8330(v549 + 432, p1, (__int64)v1184, 3u);
        return;
      case 0x2C2u:
        if ( p1 == 2 )
        {
          if ( v15 )
            Client__Game__BattleLog__AddActionLogMessage(0x21Bu, v15, 0, 2u, p2, 0, 0, 0, 0, 100.0);
        }
        else if ( v15 )
        {
          Client__Game__BattleLog__AddActionLogMessage(0x265u, v15, 0, p1, p2, 0, 0, 0, 0, 100.0);
        }
        return;
      case 0x2C3u:
        v550 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v551 = (_QWORD *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v550 + 88LL))(v550);
        Client__UI__Misc__RaptureLogModule__ShowLogMessageUInt(v551, 1333, 0x1304u);
        return;
      case 0x2C4u:
        v552 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p1);
        if ( v552 )
          Client__Game__BattleLog__AddLogMessage3Params(p2, v552, 1, p3, 0, 100.0);
        return;
      case 0x2C5u:
        sub_140E13AB0((__int64)byte_142AF9070, p1, 0);
        return;
      case 0x321u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          sub_14087B920((__int64)dword_142AD6000, p1, word_142AD8444, (__int64)&word_142AD8444 + 1, 1u);
        return;
      case 0x322u:
        if ( v15 )
        {
          if ( sub_140897A40((__int64)v15, isRecorded, 0) )
          {
            v239 = p2;
            v240 = p3;
            v241 = p4;
            *((_BYTE *)&dword_142AD6000[2321] + 5 * p2 + 2) = 1;
            if ( !v239 )
            {
              v242 = v240 - 689;
              v243 = 1;
              if ( (unsigned int)v242 <= 0x29 && (v244 = 0x20000080001LL, _bittest64(&v244, v242))
                || v240 - 1625 <= 1
                || v240 == 9601
                || v240 == 10969
                || v240 == 10848 )
              {
                v243 = 0;
              }
              LOBYTE(word_142AD8444) = 0;
              sub_14087B920((__int64)dword_142AD6000, p1, 0, (__int64)&word_142AD8444 + 1, v243);
              Client__Game__BattleLog__AddLogMessage3Params(v240, (void *)v19, v241, 0, 0, 100.0);
            }
          }
        }
        return;
      case 0x323u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          LOBYTE(word_142AD8444) = 0;
          sub_14087B920((__int64)dword_142AD6000, p1, 0, (__int64)&word_142AD8444 + 1, 0);
          v245 = (__int64 *)Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v246 = *v245;
          if ( p1 == 100 )
          {
            v252 = (void *)(*(__int64 (__fastcall **)(__int64 *))(v246 + 88))(v245);
            Client__UI__Misc__RaptureLogModule__ShowLogMessage(v252, 0x2FAu);
          }
          else if ( p1 == 254 )
          {
            v251 = (void *)(*(__int64 (__fastcall **)(__int64 *))(v246 + 88))(v245);
            Client__UI__Misc__RaptureLogModule__ShowLogMessage(v251, 0x1F2Du);
          }
          else
          {
            v247 = (void *)(*(__int64 (__fastcall **)(__int64 *))(v246 + 112))(v245);
            Gearset = (char *)Client__UI__Misc__RaptureGearsetModule__GetGearset(v247, p1);
            Client__System__String__Utf8String__Ctor_FromSequence(self, Gearset + 1, 0xFFFFFFFF);
            sub_1405D57D0(v969);
            sub_1405C3F50((__int64)v1173, (__int64)self);
            sub_1401EABA0(v969, (__int64)v1173);
            sub_1401E09B0((__int64)v1173);
            v1056[0] = p1 + 1;
            v1057 = 0;
            v1056[1] = (__int64)v1056;
            sub_1401EABA0(v969, (__int64)v1056);
            sub_1401E09B0((__int64)v1056);
            v249 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v250 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v249 + 88LL))(v249);
            Client__UI__Misc__RaptureLogModule__ShowLogMessageTextParameters(v250, 0x2F7u, v969);
            sub_1407AD1F0(v969);
            Client__System__String__Utf8String__Dtor(self);
          }
        }
        return;
      case 0x324u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
          goto LABEL_1765;
        return;
      case 0x325u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v237 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v238 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v237 + 112LL))(v237);
          sub_1407F3140(v238);
        }
        return;
      case 0x352u:
        for ( m = 0; m < 3; ++m )
        {
          sub_140C25140((__int64)&qword_142AE2C6C, m, 0);
          sub_140C25360((__int64)&qword_142AE2C6C, m, 0);
          nullsub_161();
        }
        sub_140C253C0((__int64)&qword_142AE2C6C, 0);
        sub_140C253E0((__int64)&qword_142AE2C6C, 0);
        sub_140C25420((__int64)&qword_142AE2C6C, 0);
        sub_140C25400((__int64)&qword_142AE2C6C, 0);
        sub_140C25440((__int64)&qword_142AE2C6C, 0);
        goto LABEL_707;
      case 0x353u:
        sub_140C25140((__int64)&qword_142AE2C6C, p1, p3);
        sub_140C25360((__int64)&qword_142AE2C6C, p1, p5);
        nullsub_161();
        v257 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v258 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v257 + 296LL))(v257);
        v259 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v258, 0x87u);
        if ( v259 )
          sub_14107C430((__int64)v259);
        if ( p2 != p3 )
        {
          v260 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          if ( v260 )
          {
            sub_1405D57D0(v985);
            v1053 = 0;
            v1052[0] = p3 - p2;
            v1052[1] = (__int64)v1052;
            sub_1401EABA0(v985, (__int64)v1052);
            sub_1401E09B0((__int64)v1052);
            v261 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v260 + 88LL))(v260);
            sub_1409B44A0(v261, 659, source, (__int64)v985);
            sub_1407AD1F0(v985);
          }
          Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x8Du, 0, 0);
        }
        if ( p4 < p5 )
        {
          v262 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          if ( v262 )
          {
            sub_1405D57D0(v974);
            v1051 = 0;
            v1050[0] = p5;
            v1050[1] = (__int64)v1050;
            sub_1401EABA0(v974, (__int64)v1050);
            sub_1401E09B0((__int64)v1050);
            v263 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v262 + 88LL))(v262);
            sub_1409B44A0(v263, 660, source, (__int64)v974);
            sub_1407AD1F0(v974);
          }
          v264 = qword_142AE2CF8;
          if ( qword_142AE2CF8 )
          {
            memset(v948, 0, sizeof(v948));
            sub_1405D57D0(v949);
            v950 = 1000;
            v951 = 0;
            v952 = 0;
            v953 = 0;
            v954 = 0;
            v948[1] = 150;
            sub_140C477F0(v264, (__int64)v948);
            sub_1407AD1F0(v949);
          }
          else
          {
            v265 = sub_140B777C0();
            sub_1417CEEF0(v265 + 432, 0x96u);
          }
        }
        return;
      case 0x354u:
        switch ( p1 )
        {
          case 0u:
            sub_140C253C0((__int64)&qword_142AE2C6C, p2);
            break;
          case 1u:
            sub_140C253E0((__int64)&qword_142AE2C6C, p2);
            sub_140C25420((__int64)&qword_142AE2C6C, p3);
            break;
          case 2u:
            sub_140C25400((__int64)&qword_142AE2C6C, p2);
            sub_140C25440((__int64)&qword_142AE2C6C, p3);
            break;
          case 3u:
            sub_140C253C0((__int64)&qword_142AE2C6C, 0);
            sub_140C25420((__int64)&qword_142AE2C6C, 0);
            sub_140C25440((__int64)&qword_142AE2C6C, 0);
            qword_142AE2CB0 = 0;
            qword_142AE2CF0 = 0;
            break;
          case 4u:
            dword_142AE2CA0 = p2;
            break;
          case 5u:
            LOWORD(qword_142AE2CB0) = p2;
            break;
          case 6u:
            *((_DWORD *)&qword_142ADE980 + (unsigned __int8)p2 + 4297) = p3;
            break;
          case 7u:
            *((_WORD *)&qword_142ADE980 + (unsigned __int8)p2 + 8601) = p3;
            break;
          case 8u:
            dword_142AE2CE8 = p2;
            dword_142AE2CEC = p3;
            LODWORD(qword_142AE2CF0) = p4;
            HIDWORD(qword_142AE2CF0) = p5;
            break;
          case 9u:
            sub_140C25470(
              (__int64)&qword_142AE2C6C,
              SHIBYTE(p4),
              HIBYTE(p2),
              SBYTE2(p2),
              SHIWORD(p3),
              SBYTE1(p2),
              p2,
              (p4 & 0xFF00) != 0,
              p3,
              BYTE2(p4));
            break;
          case 0xAu:
            byte_142AE2CE4 = p2;
            break;
          default:
            goto LABEL_707;
        }
        goto LABEL_707;
      case 0x355u:
        sub_140C25FE0((__int64)&qword_142AE2C6C, p1, 1);
        v277 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v278 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v277 + 296LL))(v277);
        v279 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v278, 0x87u);
        if ( v279 )
          sub_14107C500((__int64)v279, p1);
        return;
      case 0x356u:
        if ( p2 )
        {
          v267 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          if ( v267 )
          {
            sub_1405D57D0(v958);
            if ( p4 == p3 )
            {
              v269 = v1118;
              v1118[0] = p1;
              v1118[1] = v1118;
              v268 = 658;
              v1119 = 0;
            }
            else
            {
              v1063 = 0;
              v1062[1] = (__int64)v1062;
              v1062[0] = (unsigned int)(p4 - p3);
              v268 = 657;
              sub_1401EABA0(v958, (__int64)v1062);
              sub_1401E09B0((__int64)v1062);
              v1049 = 0;
              v1048[0] = p1;
              v1048[1] = (__int64)v1048;
              sub_1401EABA0(v958, (__int64)v1048);
              sub_1401E09B0((__int64)v1048);
              v1117 = 0;
              v269 = v1116;
              v1116[0] = p5;
              v1116[1] = (__int64)v1116;
            }
            sub_1401EABA0(v958, (__int64)v269);
            sub_1401E09B0((__int64)v269);
            v270 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v267 + 88LL))(v267);
            sub_1409B44A0(v270, v268, source, (__int64)v958);
            sub_1407AD1F0(v958);
          }
          Client__Game__UI__UIState__AnnounceHowTo(&qword_142ADE980, 0x8Du, 0, 0);
        }
        goto LABEL_707;
      case 0x357u:
        sub_140C25140((__int64)&qword_142AE2C6C, p1, p2);
        sub_140C25360((__int64)&qword_142AE2C6C, p1, p3);
        nullsub_161();
LABEL_707:
        v271 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v272 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v271 + 296LL))(v271);
        v273 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v272, 0x87u);
        if ( v273 )
          sub_14107C430((__int64)v273);
        return;
      case 0x358u:
        if ( p1 == sourceId )
          sub_140C0F4D0((__int64)&qword_142ADFCE0, (float)(int)p2 * 0.1, (float)p3 * 0.1, p4, p5);
        if ( sub_140B2C090() )
        {
          sub_141A3E7A0(p1, (float)(int)p2 * 0.1, (float)p3 * 0.1);
          if ( sub_141788BF0() )
          {
            v266 = sub_141788BF0();
            sub_1417887F0(v266);
          }
        }
        return;
      case 0x359u:
        if ( p1 < 2 )
        {
          if ( p2 )
          {
            sub_140C25BA0((__int64)&qword_142AE2C6C, p3);
            sub_140C25BC0((__int64)&qword_142AE2C6C, p4);
          }
          else
          {
            sub_140C25B40((__int64)&qword_142AE2C6C, p3);
            sub_140C25B60((__int64)&qword_142AE2C6C, p4);
          }
        }
        else if ( p1 - 3 <= 1 )
        {
          LOBYTE(v16) = p2 != 0;
          sub_140C25C40((__int64)&qword_142AE2C6C, v16, p1 == 3, p3, p4);
        }
        v274 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v275 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v274 + 296LL))(v274);
        v276 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v275, 0x87u);
        if ( v276 )
          v276[41] = 1;
        return;
      case 0x384u:
        Client__Game__GameMain__ExecuteCommand(1003, p1, 0, 0, 0);
        return;
      case 0x385u:
        if ( v15 )
          sub_1408F1C00((__int64)&off_1428BBEC0, p1, p2);
        return;
      case 0x386u:
        Client__Game__GameMain__QueueActiveFestivals(
          (__int64)&word_142AA7678,
          p1,
          p2,
          p3,
          p4,
          p5,
          p6,
          p7,
          p8);
        return;
      case 0x387u:
        v628 = p2 == 0;
        if ( p2 )
        {
          if ( !Client__Game__UI__PlayerState__IsMountUnlocked(&byte_142ADF3B8, p3) )
          {
            sub_1405D57D0(v979);
            LODWORD(v1176) = p3;
            v1101 = -1;
            v1100[0] = 0;
            v1100[1] = 0;
            sub_14078F8B0((__int64)v1100, &v1176);
            sub_1401EABA0(v979, (__int64)v1100);
            sub_1401E09B0((__int64)v1100);
            v629 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v630 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v629 + 88LL))(v629);
            sub_1409B44A0(v630, 610, (_WORD *)v19, (__int64)v979);
            sub_1407AD1F0(v979);
          }
          v628 = p2 == 0;
        }
        sub_140BE1430((__int64)&byte_142ADF3B8, p1, !v628);
        v631 = sub_140B777C0();
        sub_140B80B70(v631, 0x8000, 1);
        return;
      case 0x388u:
        v632 = 405;
        if ( !p1 )
          v632 = 645;
        Client__Game__BattleLog__AddLogMessage3Params(v632, 0, 0, 0, 0, 100.0);
        return;
      case 0x389u:
        if ( v15 )
          sub_1408F19F0((__int64)&off_1428BBEC0, (int)v15, p1);
        return;
      case 0x38Au:
        word_142ADF8E4 = p1;
        return;
      case 0x38Bu:
        if ( p1 - 1 < 5 )
          word_142ADCE90[p1 - 1] = p2;
        return;
      case 0x38Cu:
        v689 = (unsigned __int8)sub_140BE1EB0((__int64)&byte_142ADF3B8, p1);
        sub_140BE1E90((__int64)&byte_142ADF3B8, p1, p2);
        if ( v689 != p2 )
        {
          v690 = sub_140B777C0();
          sub_140B80B70(v690, 0x80000, 1);
          v691 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          (*(void (__fastcall **)(void *, _QWORD, _QWORD, _QWORD))(*(_QWORD *)v691 + 1848LL))(
            v691,
            p1,
            (unsigned __int8)v689,
            (unsigned __int8)p2);
        }
        return;
      case 0x38Eu:
        v692 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *, _QWORD, _QWORD, _QWORD, int))(*(_QWORD *)v692 + 1384LL))(
          v692,
          p1,
          p2,
          (unsigned int)p3,
          p4);
        return;
      case 0x38Fu:
        if ( sub_140E6B570() )
          *(_WORD *)(sub_140E6B570() + 84) = p1;
        return;
      case 0x391u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          LOBYTE(v280) = 1;
          sub_140417760(*((_QWORD *)qword_142909910 + 1393), 20, v280);
        }
        return;
      case 0x393u:
        if ( p2 )
        {
          if ( p2 == 1 )
          {
            if ( !v15 || v15 != source || *((_WORD *)v15 + 836) )
              sub_140E13AB0((__int64)byte_142AF9070, 0x65u, 0);
          }
          else if ( p2 == 2 )
          {
            Client__Game__BattleLog__AddActionLogMessage(0x352u, 0, 0, 0, 0, 0, 0, 0, 0, 100.0);
          }
          v704 = sub_140B777C0();
          sub_140B819D0(v704);
          if ( unknown_libname_383() )
          {
            v705 = (_QWORD **)sub_140B8CF00();
            sub_140B8D0A0(v705);
          }
        }
        sub_140C4D490((__int64)&qword_142ADE980, p1);
        return;
      case 0x394u:
        v706 = sub_140B777C0();
        sub_140B88E90(v706, p1);
        return;
      case 0x396u:
        byte_142AF8B7E = p1;
        v722 = sub_140B777C0();
        sub_140B80B70(v722, 0x100000, 1);
        return;
      case 0x397u:
        sub_140BE2FD0((__int64)&byte_142ADF3B8, p1, p2 != 0);
        if ( p2 )
        {
          v723 = source;
          sub_1405D57D0(v981);
          LODWORD(v1176) = p3;
          v1105 = -1;
          v1104[0] = 0;
          v1104[1] = 0;
          sub_14078F8B0((__int64)v1104, &v1176);
          sub_1401EABA0(v981, (__int64)v1104);
          sub_1401E09B0((__int64)v1104);
          v724 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v725 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v724 + 88LL))(v724);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
            v725,
            0xD66u,
            v723,
            0,
            v981);
          sub_1407AD1F0(v981);
        }
        return;
      case 0x398u:
        v1189[0] = p1;
        v1189[1] = p2;
        v1190 = p3;
        v1191 = *(_WORD *)((char *)&p3 + 1);
        sub_140893300(byte_142AD9730, v1189);
        return;
      case 0x399u:
        sub_1408933E0((__int64)byte_142AD9730, p1, p2);
        return;
      case 0x39Au:
        sub_140895E20((__int64)&qword_142AD9750, p1);
        return;
      case 0x39Bu:
        sub_140C440D0((__int64)&qword_142AF5E50, p1, p2 != 0);
        return;
      case 0x39Cu:
        p_si128 = &si128;
        si128.m128i_i64[0] = __PAIR64__(p2, p1);
        v624 = 0;
        si128.m128i_i64[1] = __PAIR64__(p4, p3);
        v625 = 8;
        v1180 = p5;
        v1181 = p6;
        v1182 = p7;
        v1183 = p8;
        v1192 = 0;
        v1193 = 0;
        do
        {
          v626 = p_si128->m128i_i16[0];
          p_si128 = (__m128i *)((char *)p_si128 + 4);
          *(_WORD *)((char *)&v1192 + v624) = v626;
          v624 += 2;
          *(_WORD *)((char *)&v1192 + v624 + 14) = p_si128[-1].m128i_i16[7];
          --v625;
        }
        while ( v625 );
        sub_140BE06F0(&byte_142ADF3B8, &v1192, &v1193);
        return;
      case 0x39Du:
        if ( unknown_libname_211() )
        {
          payload[0] = p3;
          payload[1] = p4;
          payload[2] = p5;
          payload[3] = p6;
          v627 = (void *)sub_140844170();
          Client__Game__ServerRequestCallbackManager__ProcessPacket(v627, p1, p2, payload, 4u);
        }
        return;
      case 0x39Eu:
        sub_140893A00((__int64)byte_142AD9730, p1);
        return;
      case 0x39Fu:
        sub_140C4DB40((__int64)&qword_142ADE980, p1, p2, p3, p4);
        return;
      case 0x3A0u:
        *(float *)&dword_142ADFB5C = (float)(int)p1;
        return;
      case 0x3A1u:
        if ( v15 && p1 == 1 )
        {
          if ( p2 )
          {
            Client__Game__BattleLog__AddToScreenLogWithScreenLogKind(v15, v15, 55, 0, 0, 0, p5, 0, 0);
          }
          else
          {
            Client__Game__BattleLog__AddLogMessage3Params(0xE0Bu, v15, p3, p4, p5, 100.0);
            Client__Game__BattleLog__AddToScreenLogWithScreenLogKind((void *)v19, (void *)v19, 56, 0, 0, 0, p5, 0, 0);
          }
        }
        return;
      case 0x3A2u:
        if ( v15 )
          sub_1408AC730((__int64)(v15 + 412), p1, p2, p3, p4);
        return;
      case 0x3A5u:
        byte_142ADFAF0 = p1;
LABEL_1728:
        sub_140C50030((__int64)&qword_142ADE980);
LABEL_1729:
        v808 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *))(*(_QWORD *)v808 + 64LL))(v808);
        sub_1400FC970();
        return;
      case 0x3A7u:
        v809 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *, _QWORD))(*(_QWORD *)v809 + 1856LL))(v809, LOBYTE(p1));
        byte_142ADFBF0 = p1;
        return;
      case 0x3A8u:
        sub_140BE2040();
        return;
      case 0x3A9u:
        if ( p1 )
          sub_141966490((__int64)&qword_142AA8B18);
        else
          sub_141966510((__int64)&qword_142AA8B18);
        return;
      case 0x3AAu:
        Client__Game__UI__PlayerState__SetOrnamentUnlocked(&byte_142ADF3B8, p1, p2 != 0);
        v810 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)v810 + 1000LL))(v810, 32, 0);
        return;
      case 0x3ACu:
        if ( v15 )
          Client__Game__Character__OrnamentContainer__SetupOrnament(v15 + 600, p1, p2);
        return;
      case 0x3ADu:
        sub_140C1D460((__int64)dword_142AE0028, p1, p2);
        return;
      case 0x3AEu:
        sub_140BE51C0((__int64)&byte_142ADF3B8, p1, p2 != 0);
        if ( p3 )
        {
          v829 = source;
          sub_1405D57D0(v984);
          LODWORD(v1176) = p3;
          v1115 = -1;
          v1114[0] = 0;
          v1114[1] = 0;
          sub_14078F8B0((__int64)v1114, &v1176);
          sub_1401EABA0(v984, (__int64)v1114);
          sub_1401E09B0((__int64)v1114);
          v830 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v831 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v830 + 88LL))(v830);
          Client__UI__Misc__RaptureLogModule__ShowLogMessageSourceObjectTargetObjectTextParameters(
            v831,
            0x16DEu,
            v829,
            0,
            v984);
          sub_1407AD1F0(v984);
        }
        return;
      case 0x3AFu:
        if ( v15 )
          *((_WORD *)v15 + 1226) = p1;
        return;
      case 0x3B0u:
        if ( v15 )
        {
          Client__Game__Character__DrawDataContainer__SetGlasses(v15 + 446, LOWORD(p1), p2);
          v812 = v811;
          for ( n = 0; n < 2; sub_1408B3920(v19 + 1784, n++, 4, p4 == 1) )
            ;
          if ( v812 && sub_140897A40(v19, 1, 0) )
          {
            v814 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            v815 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v814 + 296LL))(v814);
            v816 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v815, 0x1CCu);
            if ( v816 )
              sub_140A89D90((__int64)v816);
            if ( p3 == 1 )
            {
LABEL_1765:
              v817 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
              v818 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v817 + 112LL))(v817);
              sub_1407F2820(v818);
            }
          }
        }
        return;
      case 0x3B1u:
        v819 = p2 == 0;
        if ( p2 )
        {
          sub_1405D57D0(v982);
          LODWORD(v1176) = p1;
          v1111 = -1;
          v1110[0] = 0;
          v1110[1] = 0;
          sub_14078F8B0((__int64)v1110, &v1176);
          sub_1401EABA0(v982, (__int64)v1110);
          sub_1401E09B0((__int64)v1110);
          v820 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v821 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v820 + 88LL))(v820);
          sub_1409B44A0(v821, 10549, (_WORD *)v19, (__int64)v982);
          sub_1407AD1F0(v982);
          v819 = p2 == 0;
        }
        Client__Game__UI__PlayerState__SetGlassesStyleUnlocked(&byte_142ADF3B8, p1, !v819);
        v822 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        (*(void (__fastcall **)(void *, __int64, _QWORD))(*(_QWORD *)v822 + 1000LL))(v822, 36, 0);
        return;
      case 0x3B2u:
        if ( p1 )
        {
          ItemRowById = Component__Exd__ExdModule__GetItemRowById(p1);
          if ( ItemRowById )
          {
            v824 = EXD__ItemAction__Row_140835970(*(unsigned __int16 *)(ItemRowById + 142));
            v825 = v824;
            if ( v824 )
            {
              if ( *(_WORD *)(v824 + 4) )
              {
                sub_1405D57D0(v983);
                LODWORD(v1176) = *(unsigned __int16 *)(v825 + 6);
                v1112[0] = 0;
                v1112[1] = 0;
                v1113 = -1;
                sub_14078F8B0((__int64)v1112, &v1176);
                sub_1401EABA0(v983, (__int64)v1112);
                sub_1401E09B0((__int64)v1112);
                v826 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
                v827 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v826 + 88LL))(v826);
                sub_1409B44A0(v827, *(unsigned __int16 *)(v825 + 4), (_WORD *)v19, (__int64)v983);
                sub_1407AD1F0(v983);
              }
            }
          }
        }
        return;
      case 0x3B3u:
        entry[2] = p2;
        entry[3] = p1;
        entry[0] = 26;
        entry[1] = 369098752;
        v1013 = 0;
        if ( source )
        {
          v828 = (void *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)source + 664LL))(source);
          Client__UI__Misc__ScreenLog__AddScreenLogEntry(v828, entry);
        }
        return;
      case 0x3E8u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v308 = Client__Game__InventoryManager__GetInventoryContainer(dword_142AD6000, 0x7DBu);
          sub_1408692D0((__int64)v308);
          byte_142AD96DD = 0;
        }
        return;
      case 0x3E9u:
        if ( unknown_libname_517() )
        {
          v310 = sub_140E19000();
          sub_140E1BC50(v310, p1, p2);
        }
        return;
      case 0x3EAu:
        if ( unknown_libname_517() )
        {
          v311 = sub_140E19000();
          sub_140E1BD30(v311, p1, p2);
        }
        return;
      case 0x3EBu:
        if ( unknown_libname_517() )
        {
          v312 = sub_140E19000();
          sub_140E1D0D0(v312, p1);
        }
        return;
      case 0x3ECu:
        if ( unknown_libname_517() )
        {
          v313 = sub_140E19000();
          sub_140E1BE20(v313, p1, p2);
        }
        return;
      case 0x3EDu:
        if ( unknown_libname_517() )
        {
          v314 = sub_140E19000();
          sub_140E1BF00(v314, p1);
        }
        return;
      case 0x3EEu:
        if ( unknown_libname_517() )
        {
          v316 = sub_140E19000();
          sub_140E1BF20(v316, p1, SBYTE1(p1), BYTE2(p1));
        }
        return;
      case 0x3EFu:
        if ( unknown_libname_517() )
        {
          v317 = sub_140E19000();
          sub_140E1BAE0(v317, BYTE2(p1), p1, p2);
        }
        return;
      case 0x3F0u:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          v309 = Client__Game__InventoryManager__GetInventoryContainer(dword_142AD6000, 0x7DCu);
          sub_1408692D0((__int64)v309);
        }
        return;
      case 0x3F1u:
        if ( unknown_libname_517() )
        {
          v318 = sub_140E19000();
          sub_140E1D000(v318, p1, p2);
        }
        return;
      case 0x3F2u:
        if ( unknown_libname_517() )
        {
          v319 = (_QWORD *)sub_140E19000();
          sub_140E19800(v319, p2, (unsigned int)p4 | ((unsigned __int64)(unsigned int)p3 << 32));
        }
        return;
      case 0x3F3u:
        if ( unknown_libname_517() )
        {
          v321 = sub_140E19000();
          sub_140E19990(v321, p1 == 0);
        }
        return;
      case 0x3F4u:
        if ( unknown_libname_517() )
        {
          v322 = sub_140E19000();
          if ( p1 )
            sub_140E1BFC0(v322);
          else
            sub_140E1BF90(v322);
        }
        return;
      case 0x3F5u:
        if ( unknown_libname_517() )
        {
          v323 = sub_140E19000();
          sub_140E19BC0(v323, BYTE2(p1), p1, p2);
        }
        return;
      case 0x3F6u:
        if ( unknown_libname_517() )
        {
          v320 = sub_140E19000();
          sub_140E19920(v320, p2, p3);
        }
        return;
      case 0x3F7u:
        if ( unknown_libname_517() )
        {
          v315 = sub_140E19000();
          sub_140E1A5C0(v315, p1);
        }
        return;
      case 0x3F8u:
        if ( unknown_libname_517() )
        {
          v325 = sub_140E19000();
          sub_140E1C140(v325, p1);
        }
        return;
      case 0x3F9u:
        if ( unknown_libname_517() )
        {
          v324 = sub_140E19000();
          sub_140E19A00(v324, BYTE2(p1), p1, p2);
        }
        return;
      case 0x3FAu:
        if ( unknown_libname_517() )
        {
          v326 = (void *)sub_140E19000();
          sub_140E1C050(v326);
        }
        return;
      case 0x3FBu:
        if ( unknown_libname_517() )
        {
          v327 = sub_140E19000();
          sub_140E1C0F0(v327);
        }
        return;
      case 0x3FCu:
        if ( unknown_libname_517() )
        {
          v328 = (void *)sub_140E19000();
          sub_140E1F690(v328, BYTE1(p1), p1, HIBYTE(p1), p2, BYTE2(p2), HIBYTE(p2));
        }
        return;
      case 0x3FDu:
        if ( unknown_libname_517() )
        {
          v329 = sub_140E19000();
          sub_140E1F700(v329, p1, p2, (unsigned __int16)p3, p4, p5);
        }
        return;
      case 0x3FEu:
        if ( unknown_libname_517() )
        {
          v330 = sub_140E19000();
          sub_140E1F720(v330, BYTE1(p1), LOBYTE(p1), HIBYTE(p1));
        }
        return;
      case 0x3FFu:
        if ( unknown_libname_517() )
        {
          v331 = sub_140E19000();
          sub_140E1F7C0(v331, p1);
        }
        return;
      case 0x400u:
        if ( unknown_libname_517() )
        {
          v332 = (void *)sub_140E19000();
          sub_140E1FB20(v332, p1 != 0);
        }
        return;
      case 0x401u:
        if ( unknown_libname_517() )
        {
          v333 = sub_140E19000();
          sub_140E20070(v333);
        }
        return;
      case 0x402u:
        if ( unknown_libname_517() )
        {
          v334 = sub_140E19000();
          sub_140E200D0(v334, p1 != 0);
        }
        return;
      case 0x403u:
        if ( unknown_libname_517() )
        {
          sub_1405D57D0(v956);
          v1042[0] = p2;
          v1043 = 0;
          v1042[1] = (__int64)v1042;
          sub_1401EABA0(v956, (__int64)v1042);
          sub_1401E09B0((__int64)v1042);
          v1040[0] = (unsigned int)p3;
          v1041 = 0;
          v1040[1] = (__int64)v1040;
          sub_1401EABA0(v956, (__int64)v1040);
          sub_1401E09B0((__int64)v1040);
          v1038[0] = (unsigned int)p4;
          v1039 = 0;
          v1038[1] = (__int64)v1038;
          sub_1401EABA0(v956, (__int64)v1038);
          sub_1401E09B0((__int64)v1038);
          v335 = sub_140E19000();
          sub_140E201A0(v335, p1, (__int64)v956);
          sub_1407AD1F0(v956);
        }
        return;
      case 0x404u:
        v336 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        v337 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v336 + 88LL))(v336);
        Client__UI__Misc__RaptureLogModule__ShowLogMessage(v337, p1);
        return;
      case 0x405u:
        if ( unknown_libname_517() )
        {
          v338 = sub_140E19000();
          sub_140E1FF90(v338, p1, p2 != 0);
        }
        return;
      case 0x406u:
        if ( unknown_libname_517() )
        {
          v339 = (void *)sub_140E19000();
          sub_140E205B0(v339, p1);
        }
        return;
      case 0x407u:
        if ( unknown_libname_517() )
        {
          v340 = (void *)sub_140E19000();
          sub_140E205D0(v340, p1, HIBYTE(p1), p2, BYTE2(p2), HIBYTE(p2));
        }
        return;
      case 0x408u:
        if ( unknown_libname_517() )
        {
          sub_140E19000();
          nullsub_172();
        }
        return;
      case 0x409u:
        if ( unknown_libname_517() )
        {
          v341 = sub_140E19000();
          sub_140E20690(v341, p1);
        }
        return;
      case 0x40Au:
        if ( unknown_libname_517() )
        {
          v342 = sub_140E19000();
          sub_140E1D520(v342, LOBYTE(p1), p2 != 0);
        }
        return;
      case 0x40Bu:
        if ( unknown_libname_517() )
        {
          v343 = sub_140E19000();
          sub_140E1D3C0(v343, p1, p2, p3 != 0);
        }
        return;
      case 0x40Cu:
        if ( unknown_libname_517() )
        {
          v344 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v344) )
            sub_140E4BA00();
        }
        return;
      case 0x40Du:
        if ( unknown_libname_517() )
        {
          v345 = sub_140E19000();
          sub_140E1D610(v345, p1 != 0);
        }
        return;
      case 0x40Eu:
        if ( unknown_libname_517() )
        {
          v346 = sub_140E19000();
          sub_140E1D630(v346, LOWORD(p1), HIWORD(p1), p2, p3, p4);
        }
        return;
      case 0x40Fu:
        if ( unknown_libname_517() )
        {
          v347 = sub_140E19000();
          sub_140E20B10(v347, p3, HIBYTE(p1), p1, SBYTE1(p2), p2, SBYTE2(p2));
        }
        return;
      case 0x411u:
        if ( unknown_libname_517() )
        {
          v348 = (void *)sub_140E19000();
          sub_140E20A20(v348, p1, p2, BYTE2(p2), HIBYTE(p2));
        }
        return;
      case 0x412u:
        if ( unknown_libname_517() )
        {
          v349 = (void *)sub_140E19000();
          sub_140E20A50(v349, p1, p2, p3, p4);
        }
        return;
      case 0x413u:
        if ( unknown_libname_517() )
        {
          v350 = sub_140E19000();
          sub_140E20A70(v350, p1);
        }
        return;
      case 0x414u:
        if ( unknown_libname_517() )
        {
          v351 = sub_140E19000();
          sub_140E1D660(v351, p1 != 0);
        }
        return;
      case 0x415u:
        if ( unknown_libname_517() )
        {
          v352 = sub_140E19000();
          sub_140E1D680(v352, p1 != 0, p2);
        }
        return;
      case 0x416u:
        if ( unknown_libname_517() )
        {
          v353 = sub_140E19000();
          sub_140E1D6E0(v353);
        }
        return;
      case 0x417u:
        if ( unknown_libname_517() )
        {
          v354 = (void *)sub_140E19000();
          sub_140E20D50(v354, p1 == 1);
        }
        return;
      case 0x418u:
        if ( unknown_libname_517() )
        {
          v355 = sub_140E19000();
          sub_140E1CAB0(v355, p2 | ((unsigned __int64)p1 << 32), p3);
        }
        return;
      case 0x419u:
        if ( unknown_libname_517() )
        {
          v356 = (void *)sub_140E19000();
          sub_140E1E270(
            v356,
            HIBYTE(p1) != 0,
            BYTE2(p1),
            BYTE1(p1),
            p1,
            BYTE2(p2) != 0,
            p2,
            HIWORD(p3),
            p3,
            p4,
            HIBYTE(p2) != 0);
        }
        return;
      case 0x41Au:
        if ( unknown_libname_517() )
        {
          v357 = sub_140E19000();
          if ( sub_140E20E10(v357) )
          {
            v358 = sub_140E19000();
            v360 = (void *)sub_140E20E30(v358);
            switch ( p1 )
            {
              case 0u:
                sub_140E17310(v360, p2, p3);
                break;
              case 2u:
                sub_140E174E0((__int64)v360, p2, p3, p4, p5 != 0, p6 != 0);
                break;
              case 3u:
                sub_140E177C0((__int64)v360, p2, 0);
                break;
              case 4u:
                LOBYTE(v359) = p3 != 0;
                sub_140E17E70((__int64 *)v360, p2, v359);
                break;
              case 5u:
                sub_140E17F30(v360, p2);
                break;
              case 6u:
                sub_140E17FA0(v360, p2);
                break;
              case 7u:
                sub_140E18010((__int64 *)v360, p2);
                break;
              default:
                return;
            }
          }
        }
        return;
      case 0x41Bu:
        if ( unknown_libname_517() )
        {
          v407 = sub_140E19000();
          sub_140E20D90(v407, p1 == 1);
        }
        return;
      case 0x41Cu:
        if ( unknown_libname_517() )
        {
          v361 = sub_140E19000();
          v362 = (_QWORD *)sub_140E20DD0(v361);
          if ( v362 )
            sub_140E18750(v362);
        }
        return;
      case 0x41Du:
        if ( unknown_libname_517() )
        {
          v363 = sub_140E19000();
          v364 = (_QWORD *)sub_140E20DD0(v363);
          if ( v364 )
            sub_140E18A30(v364);
        }
        return;
      case 0x41Eu:
        if ( unknown_libname_517() )
        {
          v365 = sub_140E19000();
          v366 = sub_140E20DD0(v365);
          if ( v366 )
            sub_140E185E0(v366, p1, p2, p3);
        }
        return;
      case 0x41Fu:
        if ( unknown_libname_517() )
        {
          v367 = sub_140E19000();
          v368 = (__int64 *)sub_140E20DD0(v367);
          if ( v368 )
            sub_140E18A90(v368, p1);
        }
        return;
      case 0x420u:
        v369 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, targetId);
        if ( v369 )
        {
          v370 = sub_140E252D0(p1);
          sub_1408C0D30((__int64)v369 + 2608, v370);
          sub_1408C0B90((__int64)v369 + 2608, v370);
        }
        return;
      case 0x421u:
        if ( unknown_libname_517() && v19 )
        {
          v371 = (void *)sub_140E19000();
          sub_140E20FA0(v371, (void *)v19, p2 | ((unsigned __int64)p1 << 32), p3 != 0);
        }
        return;
      case 0x422u:
        if ( unknown_libname_517() )
        {
          v372 = sub_140E19000();
          sub_140E21090(v372, p1 != 0);
        }
        return;
      case 0x423u:
        if ( unknown_libname_517() )
        {
          v373 = (void *)sub_140E19000();
          sub_140E21210(v373, p1 != 0, p2, p3, p4, p5);
        }
        return;
      case 0x424u:
        if ( unknown_libname_517() )
        {
          v374 = sub_140E19000();
          sub_140E21410(v374, p1 != 0);
        }
        return;
      case 0x425u:
        if ( unknown_libname_517() )
        {
          v375 = sub_140E19000();
          sub_140E21320(v375, p1 != 0, p2);
        }
        return;
      case 0x42Eu:
        if ( unknown_libname_517() )
        {
          v376 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v376) )
          {
            v377 = sub_140E19000();
            sub_140E41FD0(*(_QWORD *)(v377 + 24) + 104LL, p1);
          }
        }
        return;
      case 0x42Fu:
        if ( unknown_libname_517() )
        {
          v378 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v378) )
          {
            v379 = sub_140E19000();
            sub_140E42010(*(_QWORD *)(v379 + 24) + 104LL);
          }
        }
        return;
      case 0x430u:
      case 0x431u:
        if ( unknown_libname_517() )
        {
          v380 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v380) )
          {
            v381 = sub_140E19000();
            sub_140E42020(*(_QWORD *)(v381 + 24) + 104LL, p1, p2, p3, p4, p5);
          }
        }
        return;
      case 0x432u:
        if ( unknown_libname_517() )
        {
          v382 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v382) )
          {
            v383 = sub_140E19000();
            sub_140E42200(*(_QWORD *)(v383 + 24) + 104LL, p1, p2, p3, p4, p5);
          }
        }
        return;
      case 0x433u:
        if ( unknown_libname_517() )
        {
          v384 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v384) )
          {
            v385 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
            if ( v385 )
            {
              v386 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v385 + 64LL))(v385);
              sub_1400FBAB0(v386);
            }
          }
        }
        return;
      case 0x434u:
        if ( unknown_libname_517() )
        {
          v387 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v387) )
          {
            v388 = sub_140E19000();
            sub_140E45F70(*(_QWORD *)(v388 + 24) + 10592LL, p1);
          }
        }
        return;
      case 0x435u:
        if ( unknown_libname_517() )
        {
          v389 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v389) )
          {
            v390 = sub_140E19000();
            sub_140E45F90(*(_QWORD *)(v390 + 24) + 10592LL);
          }
        }
        return;
      case 0x436u:
        if ( unknown_libname_517() )
        {
          v391 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v391) )
          {
            v392 = sub_140E19000();
            sub_140E45FB0(*(_QWORD *)(v392 + 24) + 10592LL, p1, p2, p3, p4, p5, p6);
          }
        }
        return;
      case 0x437u:
        if ( unknown_libname_517() )
        {
          v393 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v393) )
          {
            v394 = sub_140E19000();
            sub_140E460A0(*(_QWORD *)(v394 + 24) + 10592LL, p1, p2, p3);
          }
        }
        return;
      case 0x438u:
        if ( unknown_libname_517() )
        {
          v395 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v395) )
          {
            v396 = sub_140E19000();
            sub_140E46180(*(_QWORD *)(v396 + 24) + 10592LL, p1, p2, p3, p4, p5);
          }
        }
        return;
      case 0x44Du:
        sub_140E51C40((__int64)dword_142AF9270, p1, p2);
        return;
      case 0x44Eu:
        sub_140E51C60((__int64)dword_142AF9270, p1);
        return;
      case 0x44Fu:
        sub_140E51C70((__int64)dword_142AF9270, p1, p2);
        return;
      case 0x450u:
        sub_140E51CA0((__int64)dword_142AF9270, p1, p2);
        return;
      case 0x451u:
        sub_140E51CC0((__int64)dword_142AF9270, p1);
        return;
      case 0x452u:
        sub_140E51CD0((__int64)dword_142AF9270, p1);
        return;
      case 0x453u:
        sub_140E51CE0((__int64)dword_142AF9270, p1, p2);
        return;
      case 0x454u:
        sub_140E51D00((__int64)dword_142AF9270, p1);
        return;
      case 0x4B1u:
        sub_140C407B0((__int64)&qword_142AF26D8, p1);
        return;
      case 0x4B2u:
        sub_140C40950((__int64)&qword_142AF26D8, p1);
        return;
      case 0x4B3u:
        sub_140C40BB0((__int64)&qword_142AF26D8, p1);
        return;
      case 0x4B4u:
        sub_140C4B7E0((__int64)&qword_142ADE980, p1, p2 != 0, 1);
        v572 = sub_140B777C0();
        sub_140B80B70(v572, 0x200000, 1);
        return;
      case 0x4B5u:
        sub_140C4BD90((__int64)&qword_142ADE980, p1, p2 != 0);
        v573 = sub_140B777C0();
        sub_140B80B70(v573, 0x20000, 1);
        return;
      case 0x4B6u:
        byte_142AF8B79 = p1;
        v574 = sub_140B777C0();
        sub_140B80B70(v574, 0x40000, 1);
        sub_140C50030((__int64)&qword_142ADE980);
        return;
      case 0x514u:
      case 0x515u:
      case 0x516u:
      case 0x517u:
      case 0x518u:
      case 0x519u:
      case 0x51Au:
      case 0x51Bu:
      case 0x51Cu:
      case 0x51Du:
      case 0x51Eu:
      case 0x51Fu:
      case 0x520u:
      case 0x521u:
      case 0x522u:
      case 0x526u:
      case 0x527u:
      case 0x528u:
        v58 = (unsigned __int8 *)sub_140E829D0(&dword_142AF926C);
        v59 = (__int64)v58;
        if ( v58 )
        {
          switch ( category )
          {
            case 0x527u:
              sub_140E7A120(v58, p1 / 0x64, p1 % 0x64, p2, p3, p4, p5, p6);
              break;
            case 0x521u:
              sub_140E79AB0((__int64)v58, p1, p2, (float)p3 / 100.0, p4);
              break;
            case 0x514u:
              v58[1581] = p1;
              break;
            case 0x516u:
              sub_140E78360((__int64)v58, p1);
              break;
            case 0x515u:
              sub_140E788F0((__int64)v58, p1, p2, p3);
              break;
            case 0x518u:
              v60 = p1;
              if ( !p1 )
              {
                sub_140E78D30(v59, p2, p3);
                v60 = 0;
              }
              if ( v60 == 1 )
              {
                sub_140E78C80(v59, p2, p3, p4);
                v60 = p1;
              }
              if ( v60 == 2 )
              {
                sub_140E78FC0(v59, p2, p3);
                v60 = p1;
              }
              if ( v60 == 3 )
                sub_140E790C0(v59, p2, p3, p4);
              break;
            case 0x519u:
              sub_140E78190((__int64)v58, p1, p2, p3);
              break;
            case 0x51Du:
              sub_140E777E0((__int64)v58, p1, p2, p3 == 1);
              break;
            case 0x51Eu:
              sub_140E77A20((__int64)v58, p1, p2 == 1);
              break;
            case 0x528u:
              sub_140E7A320((__int64)v58, p1);
              break;
            case 0x51Au:
              sub_140E77710((__int64)v58, p1, p2, p3, p4, p5);
              break;
            case 0x520u:
              sub_140E79300((__int64)v58);
              break;
            case 0x51Fu:
              sub_140E79C50((__int64)v58, (float)(int)p1);
              break;
            case 0x522u:
              sub_140E78FC0((__int64)v58, p1, p2);
              break;
            case 0x51Bu:
              sub_140E79610(
                v58,
                p1,
                p2,
                (float)((float)p3 / 100.0) - 2000.0,
                (float)((float)p4 / 100.0) - 2000.0);
              break;
            case 0x51Cu:
              sub_140E79780(
                v58,
                p1,
                p2,
                (float)((float)p3 / 100.0) - 2000.0,
                (float)((float)p4 / 100.0) - 2000.0,
                p5);
              break;
            case 0x526u:
              sub_140E7A020(
                v58,
                p1,
                p2,
                (float)((float)p3 / 100.0) - 2000.0,
                (float)((float)p4 / 100.0) - 2000.0,
                (float)(int)p5);
              break;
          }
        }
        return;
      case 0x524u:
        if ( v15 )
        {
          if ( p1 )
            sub_1408BDCB0((__int64)(v15 + 652), LOWORD(p1) + 3, 0, 0);
          if ( p2 )
            sub_1408580E0(p2, (void *)v19, (float)p3);
        }
        return;
      case 0x525u:
        if ( v15 )
          sub_1408580E0(p1, v15, (float)(int)p2);
        return;
      case 0x578u:
        if ( unknown_libname_517() )
        {
          v397 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v397) )
          {
            v398 = sub_140E19000();
            sub_140E47650(*(_QWORD *)(v398 + 24), p1, p2, p3);
          }
        }
        return;
      case 0x579u:
        if ( unknown_libname_517() )
        {
          v399 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v399) )
          {
            v400 = sub_140E19000();
            sub_140E477A0(
              *(_QWORD *)(v400 + 24),
              LOBYTE(p1),
              (unsigned __int8)p2,
              (unsigned __int8)p3,
              p4,
              p5,
              p6);
          }
        }
        return;
      case 0x57Au:
        if ( unknown_libname_517() )
        {
          v401 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v401) )
          {
            v402 = sub_140E19000();
            sub_140E478E0(*(_QWORD *)(v402 + 24));
          }
        }
        return;
      case 0x57Bu:
        if ( unknown_libname_517() )
        {
          v403 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v403) )
          {
            v404 = sub_140E19000();
            sub_140E47930(*(_QWORD *)(v404 + 24));
          }
        }
        return;
      case 0x57Cu:
        if ( unknown_libname_517() )
        {
          v405 = (void *)sub_140E19000();
          if ( Client__Game__HousingManager__IsInWorkshop(v405) )
          {
            v406 = sub_140E19000();
            sub_140E47850(*(_QWORD *)(v406 + 24), p1);
          }
        }
        return;
      case 0x5AAu:
        if ( unknown_libname_376() && *(_QWORD *)sub_140B1AE60() )
        {
          v408 = (__int64 *)sub_140B1AE60();
          sub_140B18EA0(*v408, p1);
        }
        return;
      case 0x5ABu:
        sub_140BE3110((__int64)&byte_142ADF3B8, p1, p2, p3, p4);
        return;
      case 0x5ACu:
        byte_142ADF9C8 = p1 != 0;
        return;
      case 0x5DCu:
      case 0x5DDu:
      case 0x5DEu:
        if ( v15 )
          sub_1409092C0((__int64)v15, category, p1, p2, p3, p4);
        return;
      case 0x5DFu:
        if ( v15 )
        {
          v709 = (_QWORD *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          sub_1408A5DB0(v709, p1, p2);
          v710 = (_QWORD *)(*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 632LL))(v19);
          sub_1408A5F00(v710, p1);
        }
        return;
      case 0x5E5u:
        sub_140B2C270(p1, p2, p3);
        return;
      case 0x5E6u:
        v712 = v15[48];
        v713 = Client__Game__Object__GameObject__GetPosition(v15);
        sub_14090B4D0(
          (unsigned int *)v19,
          1u,
          p1,
          p1,
          (unsigned int)p3 | ((unsigned __int64)p2 << 32),
          (__int64)v713,
          v712,
          p4,
          0,
          0xE0000000);
        return;
      case 0x5E7u:
        if ( p1 == 858 || p1 == 865 )
        {
          v714 = (void *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          StatusIndex = Client__Game__StatusManager__GetStatusIndex(v714, p1, 0xE0000000);
          if ( StatusIndex >= 0 )
            *(_WORD *)((*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 632LL))(v19)
                     + 16LL * (unsigned int)StatusIndex
                     + 10) = 0;
        }
        return;
      case 0x5EFu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) && (isRecorded || (qword_142AA895B & 4) == 0) )
        {
          v716 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 656LL))(v19);
          v717 = sub_140900B10(v716, p1, p2);
          if ( v717 )
          {
            v718 = *(_QWORD *)(v717 + 24);
            if ( v718 != 3758096384 )
            {
              v719 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByGameObjectId(
                       qword_1428BCDD0,
                       v718);
              if ( v719 )
              {
                v720 = Client__Game__Object__GameObject__GetAsCharacter(v719);
                if ( v720 )
                {
                  if ( v720[7076] )
                  {
                    v721 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 656LL))(v19);
                    sub_140900C90(v721, p1, p2);
                  }
                }
              }
            }
          }
        }
        return;
      case 0x5F0u:
        sub_1408EE430((__int64)&off_1428BBEC0, p1, p2);
        sub_141883720(qword_142B02C80, 1u);
        return;
      case 0x5F1u:
        if ( v15 )
          sub_14090A420(
            v15,
            p3,
            0,
            p1,
            (float)((float)((float)(unsigned __int16)p2 * 0.0095875263) * 0.0099999998) - 3.1415927);
        return;
      case 0x5F2u:
        if ( v15 )
        {
          sub_14090C270((__int64)v15, 1, p1, 1);
          v536 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v537 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v536 + 296LL))(v536);
          if ( Client__UI__Agent__AgentModule__GetAgentByInternalId(v537, 4u) )
            nullsub_181();
          v538 = (float)(int)p2;
          v539 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)v19 + 648LL))(v19);
          if ( v539 )
          {
            *(_DWORD *)(v539 + 348) = LOWORD(p1);
            *(float *)(v539 + 352) = v538;
          }
          v540 = EXD__Action__Row_140833940(p1);
          if ( p1 && v540 && (*(_BYTE *)(v540 + 61) & 0x10) != 0 )
          {
            v541 = Client__Game__Character__CharacterManager__LookupBattleCharaByEntityId(&off_1428BC9F0, p3);
            Client__Game__BattleLog__AddActionLogMessage(0x5C0u, v541, (void *)v19, 1u, p1, 0, 0, 0, 0, 100.0);
            Client__Game__BattleLog__AddActionLogMessage(0x21Cu, (void *)v19, 0, 1u, p1, 0, 0, 0, 0, 100.0);
          }
        }
        return;
      case 0x5F3u:
        if ( v15 )
          sub_140909F80((__int64)v15, 0.2, v17);
        return;
      case 0x5F4u:
        if ( v15 )
        {
          (*(void (__fastcall **)(float *, __int64))(*(_QWORD *)v15 + 312LL))(v15, 10);
          sub_140909FC0((__int64 *)v19, 0.0);
          sub_140909E00((float *)v19, 0.5, 0);
        }
        return;
      case 0x5F5u:
        *((_DWORD *)&qword_142ADE980 + LOBYTE(p1) + 4275) = p2;
        return;
      case 0x5F6u:
        byte_142AE2C4A = p1 != 0;
        return;
      case 0x5F7u:
        if ( v15 )
        {
          v72 = 5631;
LABEL_223:
          TimelineContainer_PlayResolvedActionTimeline(v19 + 2608, v72, 0, 0, 0);
        }
        return;
      case 0x5F9u:
        if ( v15 )
          sub_14090A9F0((__int64)v15, p1);
        return;
      case 0x5FAu:
        if ( v15 )
          *((_BYTE *)v15 + 462) = p1;
        return;
      case 0x5FBu:
        if ( v15 )
          sub_1408B8D40((__int64)(v15 + 630), p1);
        return;
      case 0x5FCu:
        sub_140BE3AE0((__int64)&byte_142ADF3B8, p3, p1, *(float *)&p2);
        return;
      case 0x5FDu:
        sub_140BE3BA0((__int64)&byte_142ADF3B8, p2, p1);
        return;
      case 0x5FEu:
        v109 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v110 = sub_140B25030((__int64)v109, entityId);
        if ( v110 )
        {
          v111 = p3;
          v112 = p2;
          *(_BYTE *)(v110 + 1129) = p1;
          *(_DWORD *)(v110 + 1036) = v112;
          *(_DWORD *)(v110 + 1040) = v111;
        }
        return;
      case 0x5FFu:
        v113 = Client__Game__Group__GroupManager__GetGroup(&off_1428C27E0, isRecorded);
        v114 = sub_140B25030((__int64)v113, entityId);
        if ( v114 )
          *(_DWORD *)(v114 + 1036) = p1;
        return;
      case 0x601u:
        sub_1408EDE10((__int64)&off_1428BBEC0, p1, (float)(int)p2 / 100.0);
        return;
      case 0x602u:
        v929[0] = p1;
        v929[1] = p2;
        v929[2] = p3;
        v929[3] = 0;
        sub_140631CA0((__int64)&qword_1428B8560, v929, *(float *)&p4, *(float *)&p5);
        return;
      case 0x603u:
        if ( source )
        {
          v930[0] = *(float *)entityIda;
          LODWORD(v930[1]) = p2;
          LODWORD(v930[2]) = p3;
          v930[3] = 0.0;
          sub_140631CE0((__int64)&qword_1428B8560, (__int64)source, v930);
        }
        return;
      case 0x604u:
        if ( v15 )
        {
          v131 = (void *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          Client__Game__StatusManager__ProcessHotDot(v131, (void *)v19, p1, 4, p2, p3, p4);
        }
        return;
      case 0x605u:
        if ( v15 )
        {
          v132 = (void *)(*(__int64 (__fastcall **)(float *))(*(_QWORD *)v15 + 632LL))(v15);
          Client__Game__StatusManager__ProcessHotDot(v132, (void *)v19, p1, 3, p2, p3, p4);
        }
        return;
      case 0x606u:
        if ( entityId != -536870912 )
        {
          v100 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByEntityId(qword_1428BCDD0, entityId);
          v101 = (__int64)v100;
          if ( v100 )
          {
            if ( (*(unsigned int (__fastcall **)(void *))(*(_QWORD *)v100 + 16LL))(v100) == 11 )
              sub_141758790(v101, p1);
          }
        }
        return;
      case 0x607u:
        v102 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
        if ( v102 )
        {
          v103 = (*(__int64 (__fastcall **)(void *))(*(_QWORD *)v102 + 296LL))(v102);
          v104 = sub_14048D110(v103);
          sub_140CE6A50(v104, p1);
        }
        return;
      case 0x609u:
        sub_1408EF0B0(&off_1428BBEC0, p1, p2, p3);
        return;
      case 0x60Au:
        if ( v15 )
        {
          v711 = sub_140857450(p1, v15, v15, -1.0, 0, 0);
          sub_1408CBEE0(v19 + 6536, 13, (__int64)v711);
        }
        return;
      case 0x60Bu:
        if ( v15 && sub_140897A40((__int64)v15, isRecorded, 0) )
        {
          sub_1408D5D90(v19 + 7040, p1, p2);
          if ( unknown_libname_831() )
          {
            v133 = (void *)sub_1419738D0();
            Client__Game__XBMManager__SetPetUnlocked(v133, p3);
          }
          v134 = sub_140B777C0();
          v135 = j_Client__Game__Event__EventFramework__GetEventHandlerById(v134, 721872);
          if ( v135 )
            sub_14199C6A0(v135);
          v136 = Client__System__Framework__Framework__GetUIModule(qword_142909910);
          v137 = (void *)(*(__int64 (__fastcall **)(void *))(*(_QWORD *)v136 + 296LL))(v136);
          v138 = Client__UI__Agent__AgentModule__GetAgentByInternalId(v137, 0x1F4u);
          if ( v138 )
            sub_140AAA880((__int64)v138);
        }
        return;
      case 0x60Cu:
        if ( p1 != 3758096384LL )
        {
          v748 = Client__Game__Object__GameObjectManager__ObjectArrays__GetObjectByGameObjectId(
                   qword_1428BCDD0,
                   p1);
          if ( v748 )
            sub_140629BE0((__int64)&qword_142AAB990, (__int64)v748);
        }
        return;
      case 0x60Eu:
        sub_140891E20((__int64)&word_142AD5FF8);
        sub_140890FD0((__int64)&word_142AD5FF8, 0x1E8C67u);
        return;
      case 0x60Fu:
        sub_140891E40((__int64)&word_142AD5FF8);
        return;
      case 0x640u:
        Client__Game__SpectatorManager__Initialize(p1, p2, p3, p4);
        return;
      case 0x641u:
        sub_141788BC0();
        return;
      case 0x642u:
        if ( sub_141788BF0() )
        {
          v732 = (void *)sub_141788BF0();
          sub_1417884F0(v732, p1, p2, p3, p4, p5);
        }
        return;
      case 0x643u:
        if ( sub_141788BF0() )
        {
          v733 = sub_141788BF0();
          sub_141788660(v733, (float)(int)p1);
        }
        return;
      case 0x644u:
        sub_140C2B440((__int64)&qword_142AF22D0, p1, p2, p3 != 0);
        return;
      case 0x645u:
        if ( sub_141788BF0() )
        {
          v734 = sub_141788BF0();
          sub_1417887C0(v734);
        }
        return;
      case 0x646u:
        sub_14085BD90(p1, 0, 0, 0, 0, 0);
        return;
      case 0x647u:
        if ( sub_141788BF0() )
        {
          v735 = (void *)sub_141788BF0();
          Client__Game__SpectatorManager__ShowSpectatorUI(v735, (float)(int)p1);
        }
        return;
      case 0x648u:
        if ( sub_141788BF0() )
        {
          v736 = (void *)sub_141788BF0();
          sub_1417887D0(v736, p1, p2);
        }
        return;
      case 0x649u:
        if ( sub_14178A9C0() )
        {
          v737 = sub_14178A9C0();
          sub_141789160(v737, p1, p2, p3, p4, p5);
        }
        return;
      case 0x64Au:
        sub_140C24F70((__int64)&qword_142AE2C6C, p1, p2, p3, p4, p5, p6);
        return;
      case 0x64Bu:
        if ( sub_14178A9C0() )
        {
          v738 = sub_14178A9C0();
          sub_1417897A0(v738, p1, p2);
        }
        else
        {
          sub_141A3E720(p1, p2);
        }
        return;
      case 0x672u:
        sub_140B1DD00(&word_142ADC5B0, p1);
        return;
      case 0x673u:
        sub_140B1DD10((__int64)&word_142ADC5B0, p1, p2, p3, p4);
        return;
      case 0x6A4u:
        if ( unknown_libname_829() )
        {
          v753 = (__int64 *)sub_14196F4B0();
          sub_14196F840(v753, p1);
        }
        return;
      case 0x6A5u:
        if ( unknown_libname_829() )
        {
          v754 = (_QWORD **)sub_14196F4B0();
          sub_14196FFC0(v754);
        }
        return;
      case 0x6D6u:
        sub_140C3BB30((__int64)qword_142AE32E0, p1, (float)(int)p2 * 0.001, (float)p3 * 0.001);
        return;
      case 0x6D7u:
        sub_140C3BC20((__int64)qword_142AE32E0, p1);
        return;
      case 0x6D8u:
        sub_140C3BCC0((__int64)qword_142AE32E0, p1);
        return;
      case 0x708u:
        if ( unknown_libname_220() )
        {
          v800 = (_BYTE *)sub_140893BC0();
          sub_140893E30(v800, p1, p2, p3, p4, p5 != 0);
        }
        return;
      case 0x709u:
        if ( v15 && unknown_libname_220() )
        {
          v801 = (void *)sub_140893BC0();
          sub_140893CC0(v801, (void *)v19, p1 != 0, p2 != 0);
        }
        return;
      case 0x70Au:
        if ( v15 && unknown_libname_220() )
        {
          v802 = sub_140893BC0();
          sub_1408951B0(v802);
        }
        return;
      case 0x73Au:
        if ( unknown_libname_378() )
        {
          v803 = (__int64 *)sub_140B1F200();
          sub_140B1F4A0(v803, p1);
          v804 = (__int64 *)sub_140B1F200();
          sub_140B1F510(v804, p2);
          v805 = (__int64 *)sub_140B1F200();
          sub_140B1F570(v805, p3);
        }
        return;
      case 0x73Bu:
        if ( unknown_libname_378() )
        {
          v806 = (__int64 *)sub_140B1F200();
          sub_140B1F510(v806, p1);
        }
        return;
      case 0x73Cu:
        if ( unknown_libname_378() )
        {
          v807 = (__int64 *)sub_140B1F200();
          sub_140B1F570(v807, p1);
        }
        return;
      default:
        goto LABEL_1910;
    }
  }
  if ( unknown_libname_377() )
  {
    v832 = Client__Game__FashionCheckManager__Instance();
    sub_140B1C160((__int64)v832);
  }
}
