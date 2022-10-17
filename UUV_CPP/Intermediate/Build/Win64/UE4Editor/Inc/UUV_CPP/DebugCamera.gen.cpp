// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UUV_CPP/DebugCamera.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDebugCamera() {}
// Cross Module References
	UUV_CPP_API UClass* Z_Construct_UClass_ADebugCamera_NoRegister();
	UUV_CPP_API UClass* Z_Construct_UClass_ADebugCamera();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_UUV_CPP();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
// End Cross Module References
	void ADebugCamera::StaticRegisterNativesADebugCamera()
	{
	}
	UClass* Z_Construct_UClass_ADebugCamera_NoRegister()
	{
		return ADebugCamera::StaticClass();
	}
	struct Z_Construct_UClass_ADebugCamera_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TextureRenderTarget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TextureRenderTarget;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Cam_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Cam;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADebugCamera_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_UUV_CPP,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADebugCamera_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "DebugCamera.h" },
		{ "ModuleRelativePath", "DebugCamera.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADebugCamera_Statics::NewProp_TextureRenderTarget_MetaData[] = {
		{ "Category", "DebugCamera" },
		{ "ModuleRelativePath", "DebugCamera.h" },
		{ "ToolTip", "Render target" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADebugCamera_Statics::NewProp_TextureRenderTarget = { UE4CodeGen_Private::EPropertyClass::Object, "TextureRenderTarget", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(ADebugCamera, TextureRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADebugCamera_Statics::NewProp_TextureRenderTarget_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADebugCamera_Statics::NewProp_TextureRenderTarget_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADebugCamera_Statics::NewProp_Cam_MetaData[] = {
		{ "Category", "DebugCamera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "DebugCamera.h" },
		{ "ToolTip", "Scene capture component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ADebugCamera_Statics::NewProp_Cam = { UE4CodeGen_Private::EPropertyClass::Object, "Cam", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x001000000008000d, 1, nullptr, STRUCT_OFFSET(ADebugCamera, Cam), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ADebugCamera_Statics::NewProp_Cam_MetaData, ARRAY_COUNT(Z_Construct_UClass_ADebugCamera_Statics::NewProp_Cam_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADebugCamera_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebugCamera_Statics::NewProp_TextureRenderTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADebugCamera_Statics::NewProp_Cam,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADebugCamera_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADebugCamera>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADebugCamera_Statics::ClassParams = {
		&ADebugCamera::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_ADebugCamera_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_ADebugCamera_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ADebugCamera_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ADebugCamera_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADebugCamera()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADebugCamera_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADebugCamera, 1246099429);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADebugCamera(Z_Construct_UClass_ADebugCamera, &ADebugCamera::StaticClass, TEXT("/Script/UUV_CPP"), TEXT("ADebugCamera"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADebugCamera);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
