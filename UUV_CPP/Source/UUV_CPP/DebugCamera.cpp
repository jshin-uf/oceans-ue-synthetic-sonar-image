// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugCamera.h"

// Sets default values
ADebugCamera::ADebugCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Add camera component to view during simulation
	UCameraComponent* PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Component"));
	RootComponent = PlayerCamera;

	// Add scene capture component
	Cam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Simulated_Camera"));
	Cam->SetupAttachment(PlayerCamera);
	Cam->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Cam->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f)); // not sure about this part, check later
	Cam->FOVAngle = 120.0f;
	Cam->bCaptureEveryFrame = true;
	if (TextureRenderTarget) Cam->TextureTarget = TextureRenderTarget;
}

// Called when the game starts or when spawned
void ADebugCamera::BeginPlay()
{
	Super::BeginPlay();

	imageNum = 0;
	frameNum = 0;
}

// Called every frame
void ADebugCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (frameNum % 50 == 0 && imageNum < 200)
	{
		// get the image
		Mat frame = GetTextureAsMat();

		// save the image
		char FileName[200];
		sprintf_s(FileName, 200,
			"C:/Users/tonyc/Documents/Unreal Projects/UUV_CPP/Saved/Images/Debug/Img_%d.jpg"
			, imageNum);
		imwrite(FileName, frame);

		imageNum++;

	}
	frameNum++;
}

// Called to bind functionality to input
void ADebugCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to read texture target into a cv::Mat, from Jake
Mat ADebugCamera::GetTextureAsMat()
{
	// Read the pixels from the RenderTarget and store them in a FColor array
	TArray<FColor> Frame;
	FRenderTarget* RenderTarget = TextureRenderTarget->GameThread_GetRenderTargetResource();
	RenderTarget->ReadPixels(Frame);

	// initialize memory for current frame
	Mat frame(TextureRenderTarget->SizeX, TextureRenderTarget->SizeY, CV_8UC3);

	for (int j = 0; j < frame.cols; j++)
	{
		for (int i = 0; i < frame.rows; i++)
		{
			frame.at<cv::Vec3b>(i, j)[0] = Frame[j + i * frame.rows].B;
			frame.at<cv::Vec3b>(i, j)[1] = Frame[j + i * frame.rows].G;
			frame.at<cv::Vec3b>(i, j)[2] = Frame[j + i * frame.rows].R;
		}
	}
	return frame;
}