// Fill out your copyright notice in the Description page of Project Settings.
using System.IO;
using UnrealBuildTool;

public class UUV_CPP : ModuleRules
{

    // the next two module rules are for convenience, to keep track of directories
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public UUV_CPP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        LoadOpenCV(Target);
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }

    public bool LoadOpenCV(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");

        string LibPath = "";
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
            isLibrarySupported = true;
        }
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString()); System.Console.WriteLine(Err);
        }

        if (isLibrarySupported)
        {
            //Add Include path 
            PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            //Add Static Libraries
            PublicAdditionalLibraries.Add("opencv_world331.lib");

            //Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("opencv_world331.dll");
            PublicDelayLoadDLLs.Add("opencv_ffmpeg331_64.dll");
        }

        PublicDefinitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;

    }
}
