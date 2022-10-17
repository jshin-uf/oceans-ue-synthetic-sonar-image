// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

// ue4 includes
#include "Runtime/Engine/Classes/Components/SceneCaptureComponent2D.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/DirectionalLightComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// c++ includes/namespace
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <vector>
#include <random>
#include <string>	
using namespace std;

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DebugCamera.generated.h"

UCLASS()
class UUV_CPP_API ADebugCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADebugCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Scene capture component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* Cam;

	// Render target
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTextureRenderTarget2D* TextureRenderTarget;

	// function to get cv::Mat from the texture render target
	Mat GetTextureAsMat();

	int imageNum;
	int frameNum;

};
