#ifndef __WEATHER_H__
#define __WEATHER_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CWeather
{
	DECLARE_SERIALIZE;

	enum EWeatherState
	{
		EWS_CLEAR,
		EWS_BAD,
		EWS_FADE_OFF,
	};

	EWeatherState eState;
	bool bAutoChangeWeather;							// from AI, not from script
	//bool bActive;													// is weather active
	NTimer::STime timeNextCheck;

	void Off();
	void On();
	
public:
	CWeather();
	void Init();

	void Clear();
	
	bool IsActive() const;
	void Segment();
	
	// turn on/off weather manually
	void Switch( const bool bActive );
	
	// turn on/off automatic weather changes
	void SwitchAutomatic( const bool bSwitchAutomatic );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __WEATHER_H__
