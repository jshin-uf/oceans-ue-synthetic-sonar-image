// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UUV_CPP/UUV_CPPGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUUV_CPPGameModeBase() {}
// Cross Module References
	UUV_CPP_API UClass* Z_Construct_UClass_AUUV_CPPGameModeBase_NoRegister();
	UUV_CPP_API UClass* Z_Construct_UClass_AUUV_CPPGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_UUV_CPP();
// End Cross Module References
	void AUUV_CPPGameModeBase::StaticRegisterNativesAUUV_CPPGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AUUV_CPPGameModeBase_NoRegister()
	{
		return AUUV_CPPGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUUV_CPPGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UUV_CPP,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "UUV_CPPGameModeBase.h" },
		{ "ModuleRelativePath", "UUV_CPPGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUUV_CPPGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::ClassParams = {
		&AUUV_CPPGameModeBase::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009002A8u,
		nullptr, 0,
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUUV_CPPGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AUUV_CPPGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUUV_CPPGameModeBase, 1438483135);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUUV_CPPGameModeBase(Z_Construct_UClass_AUUV_CPPGameModeBase, &AUUV_CPPGameModeBase::StaticClass, TEXT("/Script/UUV_CPP"), TEXT("AUUV_CPPGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUUV_CPPGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
