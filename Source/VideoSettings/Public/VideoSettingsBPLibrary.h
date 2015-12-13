#pragma once

#include "Engine.h"
#include "VideoSettingsBPLibrary.generated.h"

#define MIN_SCREEN_WIDTH 1024
#define MIN_SCREEN_HEIGHT 768

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UVideoSettingsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	// Get a list of screen resolutions supported on this machine
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static bool GetSupportedScreenResolutions(TArray<FString>& Resolutions);

	// Get currently set screen resolution
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static FString GetScreenResolution();

	// Check whether or not we are currently running in fullscreen mode
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static bool IsInFullscreen();

	// Set the desired screen resolution (does not change it yet)
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetScreenResolution(const int32 Width, const int32 Height, const bool Fullscreen);

	// Change the current screen resolution
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool ChangeScreenResolution(const int32 Width, const int32 Height, const bool Fullscreen);

	// Get the current video quality settings
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool GetVideoQualitySettings(int32& AntiAliasing, int32& Effects, int32& PostProcess, int32& Resolution, int32& Shadow, int32& Texture, int32& ViewDistance);

	// Set the quality settings (not applied nor saved yet)
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetVideoQualitySettings(const int32 AntiAliasing = 3, const int32 Effects = 3, const int32 PostProcess = 3,
			const int32 Resolution = 100, const int32 Shadow = 3, const int32 Texture = 3, const int32 ViewDistance = 3);

	// Check whether or not we have vertical sync enabled
	UFUNCTION(BlueprintPure, Category = "Video Settings")
	static bool IsVSyncEnabled();

	// Set the vertical sync flag
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SetVSyncEnabled(const bool VSync);

	// Confirm and save current video mode (resolution and fullscreen/windowed) as well as quality settings
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool SaveVideoModeAndQuality();

	// Revert to original video settings
	UFUNCTION(BlueprintCallable, Category = "Video Settings")
	static bool RevertVideoMode();

private:

	// Try to get the GameUserSettings object from the engine
	static UGameUserSettings* GetGameUserSettings();
};
