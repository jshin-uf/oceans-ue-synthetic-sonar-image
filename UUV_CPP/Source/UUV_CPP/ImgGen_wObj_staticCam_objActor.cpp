// Fill out your copyright notice in the Description page of Project Settings.

#include "ImgGen_wObj_staticCam_objActor.h"

// Sets default values
AImgGen_wObj_staticCam_objActor::AImgGen_wObj_staticCam_objActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Add camera component to view during simulation
	UCameraComponent* PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Component"));
	RootComponent = PlayerCamera;

	// Add directional light 
	DirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Directional_light"));
	DirectionalLight->SetupAttachment(PlayerCamera);
	DirectionalLight->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	FVector LightAngle = FVector(0.0f, 180.0f, 96.0f);
	FRotator LightRotation;
	LightRotation = LightRotation.MakeFromEuler(LightAngle);
	DirectionalLight->SetRelativeRotation(LightRotation);
	//DirectionalLight->SetRelativeRotation(FRotator(180.0f, 0.0f, 96.0f));
	DirectionalLight->SetIntensity(30.0f);

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
void AImgGen_wObj_staticCam_objActor::BeginPlay()
{
	Super::BeginPlay();
	imageNum = 0;
	theta_idx = 0;
	frameNum = 0;
	imageCounter = 0;

	// spawn target actor for each type
	UWorld* world = GetWorld();

	FVector initialLocation;
	FRotator initialRotation;

	initialLocation = FVector(0.0f, 0.0f, -100.0f);
	initialRotation = FRotator(0.0f, 90.0f, 0.0f);

	CylinderTarget = world->SpawnActor(cylinderTagret_BP, &initialLocation, &initialRotation);
	CylinderTarget->SetActorHiddenInGame(true);
	//CylinderTarget->bAutoDestroyWhenFinished = false;

	CubeTarget = world->SpawnActor(cubeTarget_BP, &initialLocation, &initialRotation);
	CubeTarget->SetActorHiddenInGame(true);
	//CubeTarget->bAutoDestroyWhenFinished = false;

	//add other types of targets
	SphereTarget = world->SpawnActor(sphereTarget_BP, &initialLocation, &initialRotation);
	SphereTarget->SetActorHiddenInGame(true);

	ConeTarget = world->SpawnActor(coneTarget_BP, &initialLocation, &initialRotation);
	ConeTarget->SetActorHiddenInGame(true);

	// check if target features exist
	ifstream finCheck;
	finCheck.open(TargetFeaturesFileName);
	int flag = finCheck.is_open();
	finCheck.close();

	if (!flag)
	{
		//GenerateFeatures();
	}
	else
	{
		// load target features from file
		LoadFeaturesFromFile();
		//WriteTargetInfoToCSV(); // test
	}

	//MoveCamera(theta[theta_idx]);
	WriteTargetOrientation();

	target_idx = 0;
	MoveToTarget(target_idx, theta[theta_idx]);
}

// Called every frame
void AImgGen_wObj_staticCam_objActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto start = std::chrono::high_resolution_clock::now()

	int max_image_num = N_target * (N_theta + 1.0) + 5;

	// capture an image on every frames
	if (frameNum % 30 == 0 && imageNum < max_image_num)
	{
		//MoveToTarget(target_idx);
		/*MoveCamera(theta[theta_idx]);*/

		MoveToTarget(target_idx, theta[theta_idx]);
		//MoveToTarget(target_idx, theta[theta_idx] + angleNoise[target_idx*N_theta + theta_idx]);
		// add noise
		//MoveToTarget(target_idx, theta[theta_idx]+ distribution(generator));

		// get the image
		Mat frame = GetTextureAsMat();

		// save the image
		char FileName[200];
		sprintf_s(FileName, 200,
			"E:/Unreal/Release/UUV_CPP/Saved/Images/Img_%d_target_%d_img_%d.jpg"
			, imageNum, target_idx, imageCounter);
		imwrite(FileName, frame);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%d/%d"), imageNum, max_image_num));
		imageCounter++;

		if (theta_idx < N_theta) {
			theta_idx++;
		}
		else if (target_idx < N_target)
		{
			target_idx++;
			/*MoveToTarget(target_idx);*/
			theta_idx = 0;
			imageCounter = 0;
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("All done, safe to exit!")));

		imageNum++;

		/*auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%f", duration)));*/

	}
	else if (imageNum == max_image_num)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Maximum munber of images reached!")));
	}
	frameNum++;
}

// Called to bind functionality to input
void AImgGen_wObj_staticCam_objActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to read texture target into a cv::Mat, from Jake
Mat AImgGen_wObj_staticCam_objActor::GetTextureAsMat()
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


void AImgGen_wObj_staticCam_objActor::MoveCamera(float theta)
{
	FVector CamAngles;
	FRotator CamRotation;

	CamAngles.X = 0; CamAngles.Y = -90; CamAngles.Z = theta;
	CamRotation = CamRotation.MakeFromEuler(CamAngles);

	CamRotation.Pitch = -90.0; CamRotation.Roll = 0.0; CamRotation.Yaw = theta;
	SetActorRotation(CamRotation);

}

void AImgGen_wObj_staticCam_objActor::GenerateFeatures()
{
	// randomly generate target features and orientations
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0.3, 2.0);
	uniform_real_distribution<double> ang_distribution(0.0, 180.0);
	auto featureDice = bind(distribution, generator);

	for (int targetIter = 0; targetIter < N_target; targetIter++)
	{
		// generate target features
		targetShape[targetIter] = 1;		// only cylinder for now
		targetLength[targetIter] = featureDice();
		targetWidth[targetIter] = featureDice();
		targetHeight[targetIter] = featureDice();
		targetVolumeFactor[targetIter] = cbrt(targetLength[targetIter] * targetWidth[targetIter] * targetHeight[targetIter]);

		// gererate taget orientation
		//targetOrientation[targetIter] = ang_distribution(generator);
		targetOrientation[targetIter] = 0.0; // set target orientation to 0 for now
	}
	// save target features 
	ofstream fout;
	fout.open(TargetFeaturesFileName);
	if (fout.is_open())
	{
		for (int targetIter = 0; targetIter < N_target; targetIter++)
		{
			fout << targetIter + 1 << ",";
			fout << targetShape[targetIter] << ",";
			fout << targetLength[targetIter] << ",";
			fout << targetWidth[targetIter] << ",";
			fout << targetHeight[targetIter] << ",";
			fout << targetVolumeFactor[targetIter] << ",";
			fout << targetOrientation[targetIter] << ",\n";
		}
		fout.close();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Can't open file.")));
	}
}

void AImgGen_wObj_staticCam_objActor::WriteTargetInfoToCSV()
{
	// save target features 
	string TargetFeaturesInfoName = "C:/Users/tonyc/Documents/Unreal Projects/UUV_CPP/Saved/Images/Target_Info.csv";
	ofstream fout;
	fout.open(TargetFeaturesInfoName);
	if (fout.is_open())
	{
		for (int targetIter = 0; targetIter < N_target; targetIter++)
		{
			fout << targetIter + 1 << ",";
			fout << targetShape[targetIter] << ",";
			fout << targetLength[targetIter] << ",";
			fout << targetWidth[targetIter] << ",";
			fout << targetHeight[targetIter] << ",";
			fout << targetVolumeFactor[targetIter] << ",";
			fout << targetOrientation[targetIter] << ",\n";
		}
		fout.close();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Can't open file.")));
	}
	fout.close();
}

void AImgGen_wObj_staticCam_objActor::LoadFeaturesFromFile()
{
	ifstream fin;
	fin.open(TargetFeaturesFileName);

	if (fin.is_open())
	{
		targetShape[N_target] = {};
		targetLength[N_target] = {};
		targetWidth[N_target] = {};
		targetHeight[N_target] = {};
		targetVolumeFactor[N_target] = {};
		targetOrientation[N_target] = {};

		//get target number
		int targetIter;
		//int counter = 0;
		vector<string> row;
		string line, word;

		// read row and store it in line
		getline(fin, line);

		while (!line.empty())
		{
			row.clear();

			// break words
			stringstream s(line);

			// read data from s, save into word
			while (getline(s, word, ','))
			{
				// add all the column data to a vector
				row.push_back(word);
			}

			targetIter = stoi(row[0]) - 1;
			if (targetIter < N_target)
			{
				targetShape[targetIter] = stoi(row[1]);
				targetLength[targetIter] = stod(row[2]);
				targetWidth[targetIter] = stod(row[3]);
				targetHeight[targetIter] = stod(row[4]);
				targetVolumeFactor[targetIter] = stod(row[5]);
				targetOrientation[targetIter] = stod(row[6]);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Maximum nubmer of targets reached. Stop loading more targets.")));
				break;
			}
			// read row and store it in line
			getline(fin, line);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Can't Load File.")));
	}
	fin.close();

}

void AImgGen_wObj_staticCam_objActor::MoveToTarget(int target_idx, float theta)
{
	FVector cameraLocation = GetActorLocation();
	FVector targetLocation = cameraLocation;
	targetLocation.Y -= 100.0;

	FRotator targetRotatorTemp;
	if (target_idx < N_target)
	{
		if (targetShape[target_idx] == 1)
		{
			// set cylinder target to be visiable
			currentTarget = CylinderTarget;
			CylinderTarget->SetActorHiddenInGame(false);
			CubeTarget->SetActorHiddenInGame(true);
			SphereTarget->SetActorHiddenInGame(true);
			ConeTarget->SetActorHiddenInGame(true);

			//set target size
			currentTarget->SetActorScale3D(FVector(targetLength[target_idx], targetWidth[target_idx], targetHeight[target_idx]));
			// set target location
			targetLocation.Z = 115.0f; // +targetLength[target_idx] * 50.0;
			currentTarget->SetActorLocation(targetLocation);

			// set target rotation
			currentTarget->SetActorRotation(targetRotatorTemp.MakeFromEuler(FVector(0.0f, 90.0f, targetOrientation[target_idx] + theta)));

		}
		else if (targetShape[target_idx] == 2)
		{
			// set cube target to be visable
			currentTarget = CubeTarget;
			CylinderTarget->SetActorHiddenInGame(true);
			CubeTarget->SetActorHiddenInGame(false);
			SphereTarget->SetActorHiddenInGame(true);
			ConeTarget->SetActorHiddenInGame(true);

			//set target size
			currentTarget->SetActorScale3D(FVector(targetLength[target_idx], targetWidth[target_idx], targetHeight[target_idx]));
			// set target location
			targetLocation.Z = 100.0 + targetLength[target_idx] * 50.0; // check
			currentTarget->SetActorLocation(targetLocation);

			currentTarget->SetActorRotation(targetRotatorTemp.MakeFromEuler(FVector(0.0f, 90.0f, targetOrientation[target_idx] + theta)));

		}// target shape
		else if (targetShape[target_idx] == 3)
		{
			// set cube target to be visable
			currentTarget = SphereTarget;
			CylinderTarget->SetActorHiddenInGame(true);
			CubeTarget->SetActorHiddenInGame(true);
			SphereTarget->SetActorHiddenInGame(false);
			ConeTarget->SetActorHiddenInGame(true);

			//set target size
			currentTarget->SetActorScale3D(FVector(targetLength[target_idx], targetWidth[target_idx], targetHeight[target_idx]));
			// set target location
			targetLocation.Z = 100.0 + targetLength[target_idx] * 00.0; // check
			currentTarget->SetActorLocation(targetLocation);

			currentTarget->SetActorRotation(targetRotatorTemp.MakeFromEuler(FVector(0.0f, 90.0f, targetOrientation[target_idx] + theta)));

		}// target shape
		else if (targetShape[target_idx] == 4)
		{
			// set cube target to be visable
			currentTarget = ConeTarget;
			CylinderTarget->SetActorHiddenInGame(true);
			CubeTarget->SetActorHiddenInGame(true);
			SphereTarget->SetActorHiddenInGame(true);
			ConeTarget->SetActorHiddenInGame(false);

			//set target size
			currentTarget->SetActorScale3D(FVector(targetLength[target_idx], targetWidth[target_idx], targetHeight[target_idx]));
			// set target location
			targetLocation.Z = 100.0 + targetLength[target_idx] * 50.0; // check
			currentTarget->SetActorLocation(targetLocation);

			currentTarget->SetActorRotation(targetRotatorTemp.MakeFromEuler(FVector(0.0f, 0.0f, targetOrientation[target_idx] + theta)));

		}// target shape
	} // target_idx < N_target
}

void AImgGen_wObj_staticCam_objActor::WriteTargetOrientation() 
{
	// generate 
	default_random_engine generator;
	uniform_real_distribution<double> distribution(-7.5, 7.5);
	
	// save target features 
	string TargetOrientationName = "C:/Users/tonyc/Documents/Unreal Projects/UUV_CPP/Saved/Images/Target_orientation_noise.csv";
	ofstream fout;
	fout.open(TargetOrientationName);
	if (fout.is_open())
	{
		for (int angIter = 0; angIter < N_theta*N_target; angIter++)
		{	
			angleNoise[angIter] = distribution(generator);
			fout << angleNoise[angIter] << ",\n";
		}
		fout.close();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Can't open file.")));
	}
	fout.close();
}