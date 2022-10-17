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
#include <chrono>
using namespace std;

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ImgGen_wObj_staticCam_objActor.generated.h"

UCLASS()
class UUV_CPP_API AImgGen_wObj_staticCam_objActor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AImgGen_wObj_staticCam_objActor();

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

	// Directional light
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDirectionalLightComponent* DirectionalLight;

	// Target as a static mesh actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* CubeTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* CylinderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* SphereTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* ConeTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* TargetMaterial;

	AActor* currentTarget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> cylinderTagret_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> cubeTarget_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> sphereTarget_BP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> coneTarget_BP;

	

	//AStaticMeshActor* Target;

	// function to get cv::Mat from the texture render target
	Mat GetTextureAsMat();

	// function to move camera
	void MoveCamera(float theta);

	// parameters of different views
	//float theta[4] = { 0.0, 45.0, 90.0, 135.0 };
	float theta[12] = { 0.0, 15.0, 30.0, 45.0, 60.0, 75.0, 90.0, 105.0, 120.0, 135.0, 150.0, 165.0};
	static const int N_theta = 12;

	int imageNum;
	int theta_idx;

	static const int N_target = 100;  // total number of targets
	//#define N_target 3	// total number of targets

	double targetShape[N_target] = {};
	double targetLength[N_target] = {};
	double targetWidth[N_target] = {};
	double targetHeight[N_target] = {};
	double targetVolumeFactor[N_target] = {};
	double targetOrientation[N_target] = {};

	int target_idx;

	// function that randomly generat target features and orientations
	void GenerateFeatures();

	// functions that write target information in a csv
	void WriteTargetInfoToCSV();

	// function to load target features from file
	void LoadFeaturesFromFile();

	// featureFileLocation;
	string TargetFeaturesFileName = "E:/Unreal/Release/UUV_CPP/MatlabFiles/Target_Features_AngTest.csv";

	void MoveToTarget(int targetIdx, float the);

	int frameNum;
	int imageCounter;

	FVector test1;
	FVector test2;
	FVector testV;
	bool testB;

	// save target orienation noise and write it to files
	double angleNoise[N_target*N_theta] = {};
	void WriteTargetOrientation();

};
