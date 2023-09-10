// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NoMand_Knight/NoMand_KnightGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNoMand_KnightGameMode() {}
// Cross Module References
	NOMAND_KNIGHT_API UClass* Z_Construct_UClass_ANoMand_KnightGameMode_NoRegister();
	NOMAND_KNIGHT_API UClass* Z_Construct_UClass_ANoMand_KnightGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_NoMand_Knight();
// End Cross Module References
	void ANoMand_KnightGameMode::StaticRegisterNativesANoMand_KnightGameMode()
	{
	}
	UClass* Z_Construct_UClass_ANoMand_KnightGameMode_NoRegister()
	{
		return ANoMand_KnightGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ANoMand_KnightGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANoMand_KnightGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_NoMand_Knight,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANoMand_KnightGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * The GameMode defines the game being played. It governs the game rules, scoring, what actors\n * are allowed to exist in this game type, and who may enter the game.\n *\n * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of NoMand_KnightCharacter\n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "NoMand_KnightGameMode.h" },
		{ "ModuleRelativePath", "NoMand_KnightGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "The GameMode defines the game being played. It governs the game rules, scoring, what actors\nare allowed to exist in this game type, and who may enter the game.\n\nThis game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of NoMand_KnightCharacter" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANoMand_KnightGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANoMand_KnightGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ANoMand_KnightGameMode_Statics::ClassParams = {
		&ANoMand_KnightGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ANoMand_KnightGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ANoMand_KnightGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ANoMand_KnightGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ANoMand_KnightGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ANoMand_KnightGameMode, 3734707515);
	template<> NOMAND_KNIGHT_API UClass* StaticClass<ANoMand_KnightGameMode>()
	{
		return ANoMand_KnightGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ANoMand_KnightGameMode(Z_Construct_UClass_ANoMand_KnightGameMode, &ANoMand_KnightGameMode::StaticClass, TEXT("/Script/NoMand_Knight"), TEXT("ANoMand_KnightGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANoMand_KnightGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
