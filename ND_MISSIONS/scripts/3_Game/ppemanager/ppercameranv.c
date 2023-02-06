modded class PPERequester_CameraNV extends PPERequester_GameplayBase
{
	/*
	static const int NV_NO_BATTERY= 0; //darkness
	static const int NV_DEFAULT_OPTICS = 1;
	static const int NV_DEFAULT_GLASSES = 2;
	static const int NV_PUMPKIN = 3;
	static const int NV_TRANSITIVE = 4; //resets EV during camera transitions
	*/
	
	
	static const int NV_DEFAULT_OPTICS_RAD_LOW = 11;
	static const int NV_DEFAULT_OPTICS_RAD_MEDIUM = 12;
	static const int NV_DEFAULT_OPTICS_RAD_HIGH = 13;
	static const int NV_DEFAULT_OPTICS_RAD_VERYHIGH = 14;

	static const int NV_DEFAULT_GLASSES_RAD_LOW = 21;
	static const int NV_DEFAULT_GLASSES_RAD_MEDIUM = 22;
	static const int NV_DEFAULT_GLASSES_RAD_HIGH = 23;
	static const int NV_DEFAULT_GLASSES_RAD_VERYHIGH = 24;	

	static const int NV_DAYTIME_RAD_LOW = 31;
	static const int NV_DAYTIME_RAD_MEDIUM = 32;
	static const int NV_DAYTIME_RAD_HIGH = 33;
	static const int NV_DAYTIME_RAD_VERYHIGH = 34;	

	
	const float ALP_SHARPNESS_LOW = 8.0;
	const float ALP_SHARPNESS_MEDIUM = 4.5;
	const float ALP_SHARPNESS_HIGH = 3.0;
	const float ALP_SHARPNESS_VERYHIGH = 2.0;

	const float ALP_GRAINSIZE_LOW = 0.95;
	const float ALP_GRAINSIZE_MEDIUM = 0.9;
	const float ALP_GRAINSIZE_HIGH = 0.8;
	const float ALP_GRAINSIZE_VERYHIGH = 0.5;	
	
/*	
	const float ALP_SHARPNESS_LOW = 7.0;
	const float ALP_SHARPNESS_MEDIUM = 3.5;
	const float ALP_SHARPNESS_HIGH = 2.5;
	const float ALP_SHARPNESS_VERYHIGH = 2.0;

	const float ALP_GRAINSIZE_LOW = 0.95;
	const float ALP_GRAINSIZE_MEDIUM = 0.9;
	const float ALP_GRAINSIZE_HIGH = 0.8;
	const float ALP_GRAINSIZE_VERYHIGH = 0.5;	
*/		

	override protected void OnStart(Param par = null)
	{

		SetRequesterUpdating(true);

		if (! SetNVModeALP( Param1<int>.Cast(par).param1 ) )
		{
			SetNVMode(Param1<int>.Cast(par).param1);	
		}
			
	}

	
	
	bool SetNVModeALP(int mode)
	{
		
#ifdef NAMALSK_TERRAIN
		switch (mode)
		{
			case NV_DEFAULT_OPTICS_RAD_LOW: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 25, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;			
			case NV_DEFAULT_OPTICS_RAD_MEDIUM: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 25, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_OPTICS_RAD_HIGH: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 25, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;			
			case NV_DEFAULT_OPTICS_RAD_VERYHIGH: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_VERYHIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_VERYHIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 25, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;		
			case NV_DEFAULT_GLASSES_RAD_LOW: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 10, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_GLASSES_RAD_MEDIUM: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 10, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_GLASSES_RAD_HIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 10, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;	
			case NV_DEFAULT_GLASSES_RAD_VERYHIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_VERYHIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_VERYHIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 10, 550, PPOperators.SET );
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;		
			case NV_DAYTIME_RAD_LOW: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 1.5, 550, PPOperators.SET );
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);			
			return 1;				
			case NV_DAYTIME_RAD_MEDIUM: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 1.5, 550, PPOperators.SET );
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);			
			return 1;				
			case NV_DAYTIME_RAD_HIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 1.5, 550, PPOperators.SET );
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);				
			return 1;	
			case NV_DAYTIME_RAD_VERYHIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat( PPEExceptions.EYEACCOM, PPEEyeAccomodationNative.PARAM_INTENSITY, false, 1.5, 550, PPOperators.SET );
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_VERYHIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_VERYHIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);	
			return 1;					
		}			
#else			
		switch (mode)
		{
			case NV_DEFAULT_OPTICS_RAD_LOW: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_OPTIC,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_OPTICS_RAD_MEDIUM: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_OPTIC,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_OPTICS_RAD_HIGH: //optic on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_OPTIC,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,2.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;		
			case NV_DEFAULT_GLASSES_RAD_LOW: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_GLASSES_RAD_MEDIUM: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DEFAULT_GLASSES_RAD_HIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;	
			case NV_DEFAULT_GLASSES_RAD_VERYHIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,7.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_VERYHIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_VERYHIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,2.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;			
			case NV_DAYTIME_RAD_LOW: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,2.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_LOW,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_LOW,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DAYTIME_RAD_MEDIUM: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,2.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_MEDIUM,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_MEDIUM,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;				
			case NV_DAYTIME_RAD_HIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,2.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_HIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_HIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;	
			case NV_DAYTIME_RAD_VERYHIGH: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{0.0,1.0,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,2.0,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,ALP_SHARPNESS_VERYHIGH,PPEFilmGrain.L_1_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,ALP_GRAINSIZE_VERYHIGH,PPEFilmGrain.L_2_TOXIC_TINT,PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,3.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,1.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			return 1;					
		}	
#endif			
		return 0;
	}


}