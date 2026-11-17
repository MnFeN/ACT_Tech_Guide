# ActorControl 附注

[返回分类与参数](../README.md)

本目录提供分类参数的核对依据，包括逐类处理流程、专题说明，以及被引用的代码、数据和图片。

资料以 **7.58 国服，2026.11.03.0000.0000** 为版本基准。附注中的 p1–p8 对应正文的 a1–a8；反编译代码保留原始变量名，便于与处理流程对照。

专题资料可能保留较早的假设及其更正过程。查阅参数时以 [正文](../README.md) 的整理结论为准；“待确认”仍表示证据不足。

## 逐类附注

从 [分类索引](../README.md#category-index) 进入所需分类，再打开其末尾的“附注：处理流程与依据”。869 个分类均提供独立附注。

## 专题说明

| 专题 | 内容 |
| --- | --- |
| [成就奖励领取资格位图：03AD](AchievementRewardEligibilityBitmap.md) | 参数解释与处理依据 |
| [技能动作表现的来源序列号：05E6 p4](ActionPresentationSourceSequence.md) | 参数解释与处理依据 |
| [03A1：追加效果数值飘字的两种样式](AdditionalEffectFlytextStyles.md) | 参数解释与处理依据 |
| [0398 p2.bit31：属性式样确认与重新设定门控](AnimaAllocationFormatConfirmationFlag.md) | 参数解释与处理依据 |
| [人造元灵属性分配与强化点：0398／039E](AnimaGrowthAndEnhancement.md) | 参数解释与处理依据 |
| [炮台弹药槽与技能资格：0385](BallistaAmmoSlots.md) | 参数解释与处理依据 |
| [0385：ActionManager 局部别名的 Microcode 补查](BallistaMicrocodeAliasAudit.md) | 参数解释与处理依据 |
| [炮台弹药的较宽访问与参数转发审计](BallistaPackedAndArgumentFlowAudit.md) | 参数解释与处理依据 |
| [驯兽师三个兽笛选择：0609](BeastmasterBattlehornSelections.md) | 参数解释与处理依据 |
| [0396：直接扫描完整脚本包的补证](BeginnerGuideFullScriptPackAudit.md) | 参数解释与处理依据 |
| [新手教学指导对话进度：0396](BeginnerGuideScriptFlags.md) | 参数解释与处理依据 |
| [0052：基础 Behavior 控制码、覆盖编号与低值边界](BehaviorControlCodeBoundary.md) | 参数解释与处理依据 |
| [冒险者铭牌保存应答：0C1E](CharaCardSaveOperationResults.md) | 参数解释与处理依据 |
| [角色显隐、Alpha 与渲染抑制位](CharacterRendering.md) | 参数解释与处理依据 |
| [0392.bit2：教程完成后的首次回访对白门控](ChocoboTutorialReturnDialogue.md) | 参数解释与处理依据 |
| [00F5：终止本机 ClientPath 布局路线移动](ClientPathMovementStop.md) | 参数解释与处理依据 |
| [0384：1000..1003 命令族的成就请求互证](Command1003AchievementNeighborEvidence.md) | 参数解释与处理依据 |
| [0384：命令 1003 的同号开发命令排除](Command1003NamespaceExclusion.md) | 参数解释与处理依据 |
| [0260 bit3：自定义选项 302 不是 ConfigOption302](ConfigSlot302CustomOptionBoundary.md) | 参数解释与处理依据 |
| [00ED：区域属性碰撞位移请求的确认和重发](ContentAttributeMovementAcknowledgement.md) | 参数解释与处理依据 |
| [0646：Content 场景 BGM](ContentBgmScene.md) | 参数解释与处理依据 |
| [副本特殊等级通知：0x41、0x42、0x43](ContentLevels.md) | 参数解释与处理依据 |
| [0835：获得宝物提示](ContentTreasureItemNotice.md) | 参数解释与处理依据 |
| [03B3 最终飘字模板：自定义 Addon 正文＋数值＋GP 标签](CustomAddonGpFlytextTemplate.md) | 参数解释与处理依据 |
| [00BC：地图与对象名称牌两种图标](CustomTalkMapAndNameplateIcons.md) | 参数解释与处理依据 |
| [038B 周期字段 ctree 读取候选复核](CycleCtreeReadAudit.md) | 参数解释与处理依据 |
| [0091：每日任务受理门控值的初始化来源](DailyQuestAcceptanceInitializationBoundary.md) | 参数解释与处理依据 |
| [0x000E 与 0x05F1 死亡时间轴](DeathTimeline.md) | 参数解释与处理依据 |
| [旧枚举尚未匹配到当前消费者的类别](DefaultHandlers.md) | 参数解释与处理依据 |
| [默认虚分发登记来源补核](DefaultVirtualRegistrationCoverage.md) | 参数解释与处理依据 |
| [0834：副本战斗文本与毫秒时长](DirectorBattleTalkDuration.md) | 参数解释与处理依据 |
| [下坐骑请求应答：0393](DismountRequestAcknowledgement.md) | 参数解释与处理依据 |
| [0114 副本助手编号：按完整 DawnMember ushort 核对，纠正先前拆字节解释](DutyHelperDawnMemberWord.md) | 参数解释与处理依据 |
| [05F6：DutyHelperInfo 参数转发补查](DutyHelperInfoArgumentFlowAudit.md) | 参数解释与处理依据 |
| [05F6：局部别名与第七个栈参数的 Microcode 补查](DutyHelperMicrocodeAliasAudit.md) | 参数解释与处理依据 |
| [05F6：恢复失败栈帧后的 Info 参数流与重叠访问](DutyHelperRepairedFramesAndFieldOverlap.md) | 参数解释与处理依据 |
| [0020：IsDying 濒危状态及任务物品资格](DyingFlagAndQuestItemGate.md) | 参数解释与处理依据 |
| [0939/093B/093E：获得物品与额外奖励提示](DynamicEventItemRewardNotices.md) | 参数解释与处理依据 |
| [动态事件、单挑与倒计时控制](DynamicEvents.md) | 参数解释与处理依据 |
| [073A.p3 / 073C.p1：优雷卡岛内以太之光旗标](EurekaAetheryteFlagBits.md) | 参数解释与处理依据 |
| [073A.p3／073C.p1 bit20：丰水之地艾吉卡剧情资格](EurekaBit20EjikaStoryGate.md) | 参数解释与处理依据 |
| [073A.p3 / 073C.p1：优雷卡商店与武器入口旗标](EurekaCustomTalkFlagConsumers.md) | 参数解释与处理依据 |
| [073B／073A.p2：剧情所用元素等级的独立文本证据](EurekaElementalQualificationText.md) | 参数解释与处理依据 |
| [073A/073C：Microcode 对象来源与旗标读取补查](EurekaMicrocodeFlagFlowAudit.md) | 参数解释与处理依据 |
| [优雷卡剧情与资格三字段：073A／073B／073C](EurekaStoryAndQualification.md) | 参数解释与处理依据 |
| [0AF4：暂停并复位 Event／Battle BGM 场景](EventBattleBgmReset.md) | 参数解释与处理依据 |
| [0x6F：事件失败消息白名单](EventLogWhitelist.md) | 参数解释与处理依据 |
| [0AF2：场景结束选项复位](EventSceneSkipReset.md) | 参数解释与处理依据 |
| [0AF3：处理事件场景任务队列](EventSceneTaskProcessing.md) | 参数解释与处理依据 |
| [0146：事件上下文清理及延后朝向交互对象的请求](EventStateDeferredFacingFlag.md) | 参数解释与处理依据 |
| [事件对象时间轴：0x19A 与 0x1A3](EventTimelines.md) | 参数解释与处理依据 |
| [00D0 / 0198：ExitRange 跨区预请求应答](ExitRangeWarpAcknowledgement.md) | 参数解释与处理依据 |
| [HUD 补充状态缓存：05FC／05FD](ExtraStatusHudCache.md) | 参数解释与处理依据 |
| [时尚品鉴指令完成：076C](FashionCheckCommandCompletion.md) | 参数解释与处理依据 |
| [0931：FateContext 对象参数与脚本名称补查](FateContextMicrocodeAndScriptBoundary.md) | 参数解释与处理依据 |
| [0934：FATE 创建及额外奖励标记](FateCreationBonusFlag.md) | 参数解释与处理依据 |
| [0937：FATE 发起目标及备用 BNpcName 和位置](FateMotivationFallbackName.md) | 参数解释与处理依据 |
| [092F：FATE 对象 EntityId 映射及交互选择资格](FateNpcSelectorFlags.md) | 参数解释与处理依据 |
| [0931：整组访问候选与移位/掩码补查](FatePackedStateReadAudit.md) | 参数解释与处理依据 |
| [0931：全局位移与未归入函数的小段代码补查](FateStateGlobalOverlapAudit.md) | 参数解释与处理依据 |
| [0931：公开 FateState 历史值不能移植到当前枚举](FateStatePublicHistoryBoundary.md) | 参数解释与处理依据 |
| [0931：FATE 状态覆盖与副作用](FateStateTransitions.md) | 参数解释与处理依据 |
| [战果记录登记的两份状态：0A28／0B54／0B55](FieldRecordRegistrationFlags.md) | 参数解释与处理依据 |
| [0391 / 0E77：固定提示音的原生使用场景与音频导出](FixedUiSoundInventoryContexts.md) | 参数解释与处理依据 |
| [浮点数值转换的汇编纠正：03A0／0358](FloatConversionAudit.md) | 参数解释与处理依据 |
| [03EF / 03F1：家具移除结果的轮廓与选择收尾](FurnitureRemovalOutlineCleanup.md) | 参数解释与处理依据 |
| [03EF／03F1：家具移除结果分支的补充核对](FurnitureRemovalResultBranches.md) | 参数解释与处理依据 |
| [0138：采集点次数与服务器许可](GatheringCountAndServerPermission.md) | 参数解释与处理依据 |
| [0138/0139 的采集点附加许可：资源总体与纠错](GatheringPermissionRowPopulation.md) | 参数解释与处理依据 |
| [0136 / 013E：选择对象生成键；0139：撤销服务器许可](GatheringSpawnSelectorControls.md) | 参数解释与处理依据 |
| [05AA：冒险者分队公告用进度](GcArmyAnnouncementProgress.md) | 参数解释与处理依据 |
| [0455：金碟 HUD 阶段的默认分支与宽度](GoldHudPhaseFallbackAndWidth.md) | 参数解释与处理依据 |
| [金碟管理器未知字段：指针返回与大 Shell 边界](GoldManagerFieldMicrocodeAndShellBoundary.md) | 参数解释与处理依据 |
| [金碟内容准备人数：0456 及 0455 阶段切换](GoldSaucerReadinessHud.md) | 参数解释与处理依据 |
| [金碟时间基准与旗标：038F／0390／0392／04B7／04B8](GoldSaucerTimeAndFlags.md) | 参数解释与处理依据 |
| [038F：幻卡大赛开赛气泡提示门控](GoldTournamentAnnouncementGate.md) | 参数解释与处理依据 |
| [军队筹备当日完成位图：0080/0081](GrandCompanySupplyCompletionBitmap.md) | 参数解释与处理依据 |
| [事件工厂注册表与 0AF5 副本相关槽边界](HandlerFactoryRegistryAndInstanceSlotBoundaries.md) | 参数解释与处理依据 |
| [0AF5：四种战斗相关 Director 的合法空槽](HandlerSlot278BattleDirectorEmptyOverrides.md) | 参数解释与处理依据 |
| [0AF5：内容 NPC 与机关派生类的真实槽 278](HandlerSlot278ContentAndGimmickFamilies.md) | 参数解释与处理依据 |
| [0AF5：副本 Director 构造继承链的 295 张主表](HandlerSlot278ContentDirectorConstructorClosure.md) | 参数解释与处理依据 |
| [0AF5：真实 CustomTalk 派生样本的槽 278 边界](HandlerSlot278CustomTalkBoundary.md) | 参数解释与处理依据 |
| [0AF5：CustomTalkResident 真实工厂注册及优先派生覆盖](HandlerSlot278CustomTalkResidentRegistry.md) | 参数解释与处理依据 |
| [0AF5：移动事件、Array 及 CompanyLeveOfficer 的短表边界](HandlerSlot278MovementAndArrayBoundaries.md) | 参数解释与处理依据 |
| [0AF5：主表、附属接口与相邻对象的边界补证](HandlerSlot278PrimaryAndSecondaryBoundaries.md) | 参数解释与处理依据 |
| [0AF5：任务处理器真实槽 278 及锚点遗漏](HandlerSlot278QuestConstructorCoverage.md) | 参数解释与处理依据 |
| [0AF5：完整任务派生注册表与幻境武器进度消费者](HandlerSlot278QuestDerivedRegistryAndPhantomProgress.md) | 参数解释与处理依据 |
| [0AF5：四种通用对话事件的真实主表边界](HandlerSlot278TalkFamilyBoundaries.md) | 参数解释与处理依据 |
| [0AF5：旅行及角色相关事件表的额外边界](HandlerSlot278TravelAndCharacterBoundaries.md) | 参数解释与处理依据 |
| [0AF5：Warp 真实分支与三种短 Lua 表排除](HandlerSlot278WarpAndShortLuaTables.md) | 参数解释与处理依据 |
| [历史 FATE 类别的原始解析器标签与当前版本边界](HistoricalFateDissectorParameterBoundary.md) | 参数解释与处理依据 |
| [00CE/00CF：历史名字冲突与真实发送侧](HistoricalWarpCategoryNameAndSenderConflicts.md) | 参数解释与处理依据 |
| [03F5：将缓存变换重新应用到家具场景对象](HousingCachedTransformApply.md) | 参数解释与处理依据 |
| [03EC 拆房确认与 03F4 搭建结果](HousingDemolitionAndBuildResults.md) | 参数解释与处理依据 |
| [03E9／03EA：住宅建造及外装编辑申请应答](HousingExteriorRequestResponses.md) | 参数解释与处理依据 |
| [住宅部队队徽图案：03F2](HousingFreeCompanyCrest.md) | 参数解释与处理依据 |
| [041A：交流簿子命令与结果](HousingGuestBookSubcommands.md) | 参数解释与处理依据 |
| [041E：服装模特部位关联的在售库存槽号](HousingMannequinMarketSlot.md) | 参数解释与处理依据 |
| [服装模特摆放与雇员选择：041B](HousingMannequinPlacementRetainer.md) | 参数解释与处理依据 |
| [03F9：确认本地家具移动](HousingMoveConfirmation.md) | 参数解释与处理依据 |
| [0423：住宅装修规格与解锁位](HousingRenovationSizesAndUnlocks.md) | 参数解释与处理依据 |
| [住宅特殊家具部件：0407/040F](HousingSpecialFurnitureParts.md) | 参数解释与处理依据 |
| [03F3：临时家具记录及布局模式收尾](HousingTemporaryFurnitureCleanup.md) | 参数解释与处理依据 |
| [0419：仓库数量与搬迁/内部整装条件](HousingWarehouseSummary.md) | 参数解释与处理依据 |
| [苍穹街天工纪念碑时间轴：08FD](HwdMonumentTimelines.md) | 参数解释与处理依据 |
| [室内 HouseId 与附加类型：0418](IndoorHouseIdentityAndType.md) | 参数解释与处理依据 |
| [室内幻卡游戏区资格：040D](IndoorTripleTriadAvailability.md) | 参数解释与处理依据 |
| [0418：室内类型指针流与另一收包来源](IndoorTypeMicrocodeAndFurnitureInitialization.md) | 参数解释与处理依据 |
| [查看装备失败与固定音效：02BF／0391](InspectFailureAndFixedSound.md) | 参数解释与处理依据 |
| [职业量谱默认分发：05EE、05F8、0600](JobGaugeActorControlDispatch.md) | 参数解释与处理依据 |
| [0x012C 生活技能子协议](LifeSkill.md) | 参数解释与处理依据 |
| [012C：钓鱼时间轴队列与上一条鱼的操作许可](LifeSkillFishingQueueAndPermissions.md) | 参数解释与处理依据 |
| [07D0：麻将内部控制队列与最终局提示（部分确认）](MahjongControlQueueAndFinalHand.md) | 参数解释与处理依据 |
| [07D1：多玛方城战玩家战绩摘要](MahjongPlayerSummary.md) | 参数解释与处理依据 |
| [01FF/0200：地图事件分组更新](MapEventUpdateGroups.md) | 参数解释与处理依据 |
| [0DF2：申请驾驶员时的职业 ID 与申请状态](MechaApplicationClassJob.md) | 参数解释与处理依据 |
| [0DFD：机甲驾驶申请响应与入口弹窗](MechaApplicationResponseUi.md) | 参数解释与处理依据 |
| [0DFA：机甲申请提示、字节状态及界面清理](MechaApplicationUiState.md) | 参数解释与处理依据 |
| [0DF4 命令 2：跨区完成后的自动序列事件请求门控](MechaAreaTransitionSequenceGate.md) | 参数解释与处理依据 |
| [0E04：野外探查器的三槽附加效果开关](MechaFieldSearcherEffectToggle.md) | 参数解释与处理依据 |
| [0DFF：机甲任务目标变体](MechaObjectiveVariant.md) | 参数解释与处理依据 |
| [0DF3：驾驶获选/地面参与与延后战斗对白](MechaParticipationAndDelayedBattleTalk.md) | 参数解释与处理依据 |
| [0DFB：参与相关状态清理](MechaParticipationCleanup.md) | 参数解释与处理依据 |
| [0DF5 / 0DF6：驾驶剧情位与到达提示](MechaPilotCutsceneAndArrival.md) | 参数解释与处理依据 |
| [0DF8：按 PopRange 生成组批量退场](MechaPopRangeBatchCleanup.md) | 参数解释与处理依据 |
| [0DF4：进度、贡献、目标显示与地图标记](MechaProgressDisplayConsumers.md) | 参数解释与处理依据 |
| [0E01：停止机甲反应对象生成并清理现存对象](MechaReactionObjectShutdown.md) | 参数解释与处理依据 |
| [0DF9：报名预告/开放及地面支援传送窗口](MechaRegistrationAndTeleportPhases.md) | 参数解释与处理依据 |
| [0DF7：注册场景对象的五项命令](MechaSceneObjectCommands.md) | 参数解释与处理依据 |
| [0E02 / 0E03：三槽对象布局时间轴与束缚集合](MechaSelectedTimelineAndBindSet.md) | 参数解释与处理依据 |
| [Microcode 间接写入的来源标签修正与重跑](MicrocodeStoreAddressFix.md) | 参数解释与处理依据 |
| [无人岛牧场动物捕捉／放生结果日志：0C9E](MjiAnimalCaptureResultMessages.md) | 参数解释与处理依据 |
| [0C94：未知无人岛布尔值的多字节读取补查](MjiBoolean7PackedReadAudit.md) | 参数解释与处理依据 |
| [无人岛探索队委托应答：0C86/0C87/0CAE](MjiExpeditionResponseControls.md) | 参数解释与处理依据 |
| [无人岛庭具编辑应答：0CA6/0CA7](MjiFurnishingEditResults.md) | 参数解释与处理依据 |
| [无人岛素材出售界面刷新：0C88](MjiMaterialExportUiRefresh.md) | 参数解释与处理依据 |
| [无人岛庭具投影可用提示：0CAA](MjiOutdoorFurnishingAvailabilityNotice.md) | 参数解释与处理依据 |
| [无人岛放养宠物收回应答：0C92](MjiRoamingMinionRecall.md) | 参数解释与处理依据 |
| [0C96：无人岛入场许可设置](MjiServerSettingsBitmap.md) | 参数解释与处理依据 |
| [无人岛工房干劲与活动角色：0C83/0C8C](MjiWorkshopGrooveAndActors.md) | 参数解释与处理依据 |
| [0C8C：休息日确认流程也会写环境角色选择缓存](MjiWorkshopRestDayLocalSelector.md) | 参数解释与处理依据 |
| [新月岛知识取得通知：0A5B](MkdLoreUnlockNotification.md) | 参数解释与处理依据 |
| [莫古莫古大收集活动控制：0D7A–0D7F](MoogleCollectionEventControls.md) | 参数解释与处理依据 |
| [0D7F：通知点击后的分类导航与偏移纠正](MoogleNotificationNavigation.md) | 参数解释与处理依据 |
| [0D7F：通知队列与 HUD 的记录来源补查](MoogleNotificationRecordMicrocodeAudit.md) | 参数解释与处理依据 |
| [莫古莫古 SeasonTarget：最新商店章节选择](MoogleSeasonShopVariants.md) | 参数解释与处理依据 |
| [受控移动参数的消费验证](Movement.md) | 参数解释与处理依据 |
| [移动速度覆盖及新手教学旗标：03A0／0396](MovementOverrideAndBeginnerFlags.md) | 参数解释与处理依据 |
| [00EC：后续移动上报附加标记与 00EF 本机合成记录](MovementServerStampAndReplay.md) | 参数解释与处理依据 |
| [0EE2：割草反应对象的批量移除](MowingBatchObjectRemoval.md) | 参数解释与处理依据 |
| [0ED9：实际结算窗口工厂与奖励数量](MowingResultActualAddonAndRewardQuantity.md) | 参数解释与处理依据 |
| [原生 Addon 工厂索引与割草模式横幅](NativeAddonFactoryIndexAndMowingModeBanners.md) | 参数解释与处理依据 |
| [038C：bit14 是拒绝新人频道邀请](NoviceNetworkInvitationRejectionFlag.md) | 参数解释与处理依据 |
| [NPC 外观覆盖缓存：06A4／06A5](NpcAppearanceCacheControls.md) | 参数解释与处理依据 |
| [管弦乐琴播放模式与列表槽：040E/0415](OrchestrionPlaybackModeAndSlot.md) | 参数解释与处理依据 |
| [03AC：配饰模式的调用身份与姿态条件](OrnamentModeCallersAndPoseConditions.md) | 参数解释与处理依据 |
| [配饰模式与周期计数：03AC／038B](OrnamentModesAndCycleCounters.md) | 参数解释与处理依据 |
| [0021：队伍加成五个位的独立 UI 绑定证据](PartyBonusRoleBitBindings.md) | 参数解释与处理依据 |
| [0400：个人房间入口可选中状态](PersonalRoomEntranceTargetability.md) | 参数解释与处理依据 |
| [玩家状态与永结同心旗标：038C／00A2](PlayerStateAndWeddingFlags.md) | 参数解释与处理依据 |
| [038C：byte 写入与完整 DWORD 刷新比较不能混为一层](PlayerStateByteWriteAndNotifyWidth.md) | 参数解释与处理依据 |
| [038C：PlayerState 局部别名的 Microcode 追踪](PlayerStateFlagMicrocodeAliasAudit.md) | 参数解释与处理依据 |
| [038C：64 位读取候选与位操作上下文补查](PlayerStateFlagQwordCandidateAudit.md) | 参数解释与处理依据 |
| [038C：恢复十个栈帧失败候选后的位操作补查](PlayerStateFlagRepairedFramesAudit.md) | 参数解释与处理依据 |
| [038C：SIMD 宽读取补查](PlayerStateFlagSimdOverlapAudit.md) | 参数解释与处理依据 |
| [038C：六个新增具名旗标与副本资格](PlayerStateNamedFlagAccessors.md) | 参数解释与处理依据 |
| [038C.bit15：线下活动专用命令许可](PlayerStateRealEventPermission.md) | 参数解释与处理依据 |
| [038C：保留通用位查询的实际常量索引](PlayerStateSelectedConstantFlagQueryAudit.md) | 参数解释与处理依据 |
| [0354 命令 10／064A p5.byte1：上赛季段位奖励提示门控](PvpPreviousSeasonRewardNoticeGate.md) | 参数解释与处理依据 |
| [PvP 资料参数传递补查](PvpProfileArgumentFlowAudit.md) | 参数解释与处理依据 |
| [0354/064A：PvPProfile 局部别名与公开历史定义补查](PvpProfileMicrocodeAndHistoricalDefinitions.md) | 参数解释与处理依据 |
| [PvP 旧统计及段位附加 byte 的跨宽度补查](PvpProfilePackedFieldAndLeafAudit.md) | 参数解释与处理依据 |
| [0x064A：完整六参数切片](PvpRankPacketSlices.md) | 参数解释与处理依据 |
| [0091/038B：QuestManager 头部别名及三处缺口修复](QuestCycleHeaderMicrocodeAudit.md) | 参数解释与处理依据 |
| [0093/009F：传送事件与状态关联事件的实际消费者](QuestWarpEventAndStatusAssociation.md) | 参数解释与处理依据 |
| [0E00：交互载荷的派生语义不能统一为 Action ID](ReactionInteractionParameterVariants.md) | 参数解释与处理依据 |
| [0E00 注册、资源配对与激活边界](ReactionRegistrationAndActivationBoundary.md) | 参数解释与处理依据 |
| [00F3：相对角色定位、步行/跑步与到位后的双角色动作](RelativeActorMoveAndPairedTimeline.md) | 参数解释与处理依据 |
| [回放管理器的外层 ActorControl：03A3／03A4／03A6](ReplayActorControlOuterPaths.md) | 参数解释与处理依据 |
| [Director 与观战包的回放附加作用](ReplayDirectorChapterSideEffects.md) | 参数解释与处理依据 |
| [复活倒计时与战章变化：0358](ReviveCountdownAndMedals.md) | 参数解释与处理依据 |
| [音频淡变 tick 单位：当前调用链确认为毫秒](SoundDriverFadeMilliseconds.md) | 参数解释与处理依据 |
| [0642：五类场地倒计时的真实文本](SpectatorBattlefieldCountdownLabels.md) | 参数解释与处理依据 |
| [0642 命令 12：观战战斗日志事件与再出击秒数](SpectatorBattleLogEventsAndRespawnSeconds.md) | 参数解释与处理依据 |
| [0642 共享水晶字段到实际 PvPMKSHeader 的消费](SpectatorCrystalHeaderConsumers.md) | 参数解释与处理依据 |
| [0640/0648/0649：观战管理器头部字段的 Microcode 补查](SpectatorHeaderMicrocodeFlowAudit.md) | 参数解释与处理依据 |
| [0640 初始状态及 p4 的事件场景参数](SpectatorInitialStateAndScriptValue.md) | 参数解释与处理依据 |
| [0644：观战名单使用 BattleChara EntityId](SpectatorListEntityIds.md) | 参数解释与处理依据 |
| [064B 成员属性：全局 312 步长补查](SpectatorMemberAttributeStrideAudit.md) | 参数解释与处理依据 |
| [064B：从真实成员向量追踪字段访问](SpectatorMemberRecordMicrocodeAudit.md) | 参数解释与处理依据 |
| [064B 成员 ushort：不依赖 312 步长的读取补查](SpectatorMemberWordReadAudit.md) | 参数解释与处理依据 |
| [0642：加时提示、双方进度及共享 HUD](SpectatorOvertimeAndTeamProgress.md) | 参数解释与处理依据 |
| [0642 命令 8：自定赛结果界面的再战确认](SpectatorRematchConfirmationAndCounts.md) | 参数解释与处理依据 |
| [0649 p1.byte1：结果样式的独立统计列证据](SpectatorResultModeColumnIdentity.md) | 参数解释与处理依据 |
| [0642 命令 0/1：SharedGroup 状态、恢复值与时间轴位图](SpectatorSharedGroupStateAndRestoreMasks.md) | 参数解释与处理依据 |
| [0649 p2 低两位：危急时刻与加时状态快照](SpectatorStateSnapshotBits.md) | 参数解释与处理依据 |
| [观战剩余时间与告警：0640／0642／0643／0647](SpectatorTimeAndWarnings.md) | 参数解释与处理依据 |
| [观战虚槽实际末端：0645 与 0648](SpectatorVirtualEndpoints.md) | 参数解释与处理依据 |
| [0607：SXTBattleLog 的四种反馈文字](SxtBattleFeedbackLocalizedTextures.md) | 参数解释与处理依据 |
| [传送收藏项删除成功通知：0D16](TeleportFavoriteDeletion.md) | 参数解释与处理依据 |
| [00D3：解除临时位置控制原因 bit0 并关闭实例选择](TemporaryPositionControlRelease.md) | 参数解释与处理依据 |
| [0EEC：战术板可用性的 Unix 时间界限](TofuBoardTimeCutoff.md) | 参数解释与处理依据 |
| [神典石计数缓存：0169／017F](TomestoneCaches.md) | 参数解释与处理依据 |
| [宝箱、强欲陷阱计时与界面关闭：06D6／06D7／06D8](TreasureAndLootCountdown.md) | 参数解释与处理依据 |
| [幻卡 NPC 胜利记录与对战室资格：04B5/04B6](TripleTriadNpcWinsAndRoomFlag.md) | 参数解释与处理依据 |
| [UI 通知和显示设置：0325／03A8／02C0／0260](UiNotificationsAndDisplayFlags.md) | 参数解释与处理依据 |
| [0260：UIState 装备设置字段的对象来源补查](UiStateGearFlagsMicrocodeAudit.md) | 参数解释与处理依据 |
| [多变迷宫探索记录完成位：0CE4](VariantNotebookCompletion.md) | 参数解释与处理依据 |
| [萌宠之王两种时钟：0515／051F／0521](VerminionClocksAndSummonDelay.md) | 参数解释与处理依据 |
| [萌宠之王设施启停与剩余强度：0518](VerminionFacilityStateAndStrength.md) | 参数解释与处理依据 |
| [萌宠之王生命与特殊技蓄力：051A](VerminionHealthAndSkillPoints.md) | 参数解释与处理依据 |
| [萌宠之王命中表现：051E](VerminionHitAndCriticalEffects.md) | 参数解释与处理依据 |
| [萌宠之王召唤队列确认：0521](VerminionQueueAcknowledgement.md) | 参数解释与处理依据 |
| [0527.p2：第 9 关粘液胶汇总的特殊分类标志](VerminionSpecialSlimeFilter.md) | 参数解释与处理依据 |
| [萌宠之王关卡与教程：0514 / 0516](VerminionStagesAndTutorial.md) | 参数解释与处理依据 |
| [AVFX 触发编号与连线浮点属性](VfxControls.md) | 参数解释与处理依据 |
| [副本控制器管理的 VFX 及寿命参数](VfxLifetime.md) | 参数解释与处理依据 |
| [00A9：对象可见性频道匹配键](VisibilityChannelKey.md) | 参数解释与处理依据 |
| [02BE：位移失败理由与实际日志](WarpFailureReasonLabels.md) | 参数解释与处理依据 |
| [02BE：WarpInfo 模式别名与后续标量消费者](WarpModeMicrocodeAndScalarConsumers.md) | 参数解释与处理依据 |
| [02BE 请求模式来源与版本边界补查](WarpModeProducerBoundary.md) | 参数解释与处理依据 |
| [永结同心照明与装饰颜色：00B9](WeddingLightingAndDecoration.md) | 参数解释与处理依据 |
| [00A2：网络 p2 不是 low8==1](WeddingNetworkBooleanWidthCorrection.md) | 参数解释与处理依据 |
| [0256：周常进度的历史层数门槛](WeeklyProgressHistoricalThresholds.md) | 参数解释与处理依据 |
| [0261：线框渲染翻转](WireframeRenderingToggle.md) | 参数解释与处理依据 |
| [0DEA：宇宙成果的星球、进度与完成勾选](WksAchievementRowCompletion.md) | 参数解释与处理依据 |
| [星内以太之光解锁位图：0DAE](WksAetheryteUnlockBitmap.md) | 参数解释与处理依据 |
| [0DE0：宇宙紧急情况的两个区域进度](WksEmergencyTwoAreaProgress.md) | 参数解释与处理依据 |
| [宇宙探索历史过场无法播放：0DC0](WksHistoryCutsceneFailure.md) | 参数解释与处理依据 |
| [0DB6：撤下当前宇宙赞誉影像](WksHologramWithdrawal.md) | 参数解释与处理依据 |
| [0E33：宇宙任务物品的评价点与收藏价值分档](WksItemEvaluationTooltip.md) | 参数解释与处理依据 |
| [0E4C 大师任务附加数值：读取路径复核](WksMasterExtraValueReadAudit.md) | 参数解释与处理依据 |
| [0DFC：机甲活动的三项绝对时间](WksMechaEventTimestamps.md) | 参数解释与处理依据 |
| [宇宙计时目标结果的耗时秒数：0DD7.p2](WksMissionElapsedResult.md) | 参数解释与处理依据 |
| [宇宙任务操作禁止标志：0DDD](WksMissionOperationLock.md) | 参数解释与处理依据 |
| [0DD7：结果值 EB0h 的跨宽度补查](WksMissionResultValueOverlapAudit.md) | 参数解释与处理依据 |
| [宇宙任务目标阶段切换：0DD8](WksMissionStageAdvance.md) | 参数解释与处理依据 |
| [宇宙任务窗口与目标结束控制：0DDA/0DDB/0DDC](WksMissionWindowAndCompletionControls.md) | 参数解释与处理依据 |
| [宇宙探索玩家功能提示与访问旗标：0DAC](WksPlayerFeatureFlags.md) | 参数解释与处理依据 |
| [临时宇宙探索任务放弃后的再次受理限制：0DD5](WksProvisionalMissionReacceptanceLock.md) | 参数解释与处理依据 |
| [0FA0：斗兽奇弈入口缓存失效](XbmEntranceCacheInvalidation.md) | 参数解释与处理依据 |

## 代码与数据

- `client/`：被附注引用的反编译代码、汇编、数据和图像等资料。
- `sources/`：被附注直接引用的公开结构代码。

本文档不包含游戏可执行程序、完整 IDA 数据库或回放原文件。
