
#include <Arduino.h>
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

#include <Adafruit_NeoPixel.h>

#include <gizmoled.h>

// Only used for noise functions until they add support for the Nano 33 BLE Sense
#include <FastLED.h>

#define TEST_DEVICE 0

const char *defaultDeviceName = PROGMEM "Table";

void ConnectionFX(float frameTime, uint8_t *rgb);
void AnimateBlink(float frameTime);
void AnimateWheel(float frameTime);
void AnimateSparkle(float frameTime);
void AnimateFire(float frameTime);
void AnimatePulse(float frameTime);
void AnimateChristmas(float frameTime);
void AnimateEmpty(float frameTime);
void AnimateWaves(float frameTime);
void AnimateDrops(float frameTime);
void AnimateWipe(float frameTime);


/// BLINK
BEGIN_EFFECT_SETTINGS(blink, EFFECTNAME_BLINK,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 30, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEIN, 0)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEOUT, 1)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_CHECKBOX(fadeIn)
EFFECT_VAR_CHECKBOX(fadeOut)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


/// WHEEL
BEGIN_EFFECT_SETTINGS(wheel, EFFECTNAME_WHEEL,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0, 0xFF, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 50, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWLENGTH, 50, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowLength)
END_EFFECT_SETTINGS()


/// SPARKLE
BEGIN_EFFECT_SETTINGS(sparkle, EFFECTNAME_SPARKLE,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BACKGROUNDBRIGHTNESS, 16, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLORBACKGROUND, 0x11, 0, 0x44)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 10, 1, 50)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWOFFSET, 90, 1, 180)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(backgroundBrightness)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_COLOR(background)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
EFFECT_VAR_SLIDER(rainbowOffset)
END_EFFECT_SETTINGS()


/// FIRE
BEGIN_EFFECT_SETTINGS(fire, EFFECTNAME_FIRE,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BACKGROUNDBRIGHTNESS, 16, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLORBACKGROUND, 0x11, 0, 0x44)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_DECAY, 36, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 25, 1, 50)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SENSITIVITY, 10, 1, 50)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWOFFSET, 90, 1, 180)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(backgroundBrightness)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_COLOR(background)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(decay)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_SLIDER(sensitivity)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
EFFECT_VAR_SLIDER(rainbowOffset)
END_EFFECT_SETTINGS()


/// PULSE
BEGIN_EFFECT_SETTINGS(pulse, EFFECTNAME_PULSE,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR1, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR2, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 10, 1, 60)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 20, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_FADEOUT, 0)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWLENGTH, 30, 1, 60)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_COLOR(color1)
EFFECT_VAR_COLOR(color2)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(fadeOut)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowLength)
END_EFFECT_SETTINGS()


/// CHRISTMAS
BEGIN_EFFECT_SETTINGS(christmas, EFFECTNAME_CHRISTMAS,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 30, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 3, 2, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


/// WAVES
BEGIN_EFFECT_SETTINGS(waves, EFFECTNAME_WAVES,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0xFF)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR1, 0, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 50, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 50, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWOFFSET, 45, 1, 180)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_COLOR(color1)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
EFFECT_VAR_SLIDER(rainbowOffset)
END_EFFECT_SETTINGS()


/// DROPS
BEGIN_EFFECT_SETTINGS(drops, EFFECTNAME_DROPS,
	DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_DECAY, 10, 1, 100)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_LENGTH, 5, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 1)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWSPEED, 10, 1, 100)
)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_SLIDER(decay)
EFFECT_VAR_SLIDER(length)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowSpeed)
END_EFFECT_SETTINGS()


/// WIPE
BEGIN_EFFECT_SETTINGS(wipe, EFFECTNAME_WIPE,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0, 0xFF)
DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR1, 0, 0xFF, 0xFF)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_BRIGHTNESS, 255, 1, 255)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_SPEED, 20, 1, 100)
DECLARE_EFFECT_SETTINGS_CHECKBOX(GizmoLED::VARNAME_RAINBOWENABLED, 0)
DECLARE_EFFECT_SETTINGS_SLIDER(GizmoLED::VARNAME_RAINBOWOFFSET, 45, 1, 180)
)
EFFECT_VAR_COLOR(color)
EFFECT_VAR_COLOR(color1)
EFFECT_VAR_SLIDER(brightness)
EFFECT_VAR_SLIDER(speed)
EFFECT_VAR_CHECKBOX(rainbowEnabled)
EFFECT_VAR_SLIDER(rainbowOffset)
END_EFFECT_SETTINGS()


/// EMPTY
BEGIN_EFFECT_SETTINGS(empty, EFFECTNAME_EMPTY,
	DECLARE_EFFECT_SETTINGS_COLOR(GizmoLED::VARNAME_COLOR, 0xFF, 0xFF, 0)
)
EFFECT_VAR_COLOR(color)
END_EFFECT_SETTINGS()


// EFFECT LIST
BEGIN_EFFECTS()
DECLARE_EFFECT(fire, AnimateFire, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(sparkle, AnimateSparkle, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(blink, AnimateBlink, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(empty, AnimateEmpty, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(wheel, AnimateWheel, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(pulse, AnimatePulse, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(waves, AnimateWaves, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(wipe, AnimateWipe, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(drops, AnimateDrops, GizmoLED::EFFECTTYPE_DEFAULT)
DECLARE_EFFECT(christmas, AnimateChristmas, GizmoLED::EFFECTTYPE_DEFAULT)
END_EFFECTS()

#define LED_BUFFER_SIZE_SIDE 45
#define LED_BUFFER_SIZE_BACK 103
#define LED_BUFFER_SIZE_TOTAL (LED_BUFFER_SIZE_SIDE * 2 + LED_BUFFER_SIZE_BACK)
#define LED_PIN_COLLAR 3

uint8_t *ledBufferCollar;
Adafruit_NeoPixel ledAccessCollar(LED_BUFFER_SIZE_TOTAL,
	LED_PIN_COLLAR, NEO_GRB | NEO_KHZ800);

#define ADD_CLAMPED_COLOR(buffer, position, additiveColor, factor) \
					{buffer[(position) * 3] = min(255, buffer[(position) * 3] + additiveColor[1] * (factor)); \
					buffer[(position) * 3 + 1] = min(255, buffer[(position) * 3 + 1] + additiveColor[0] * (factor)); \
					buffer[(position) * 3 + 2] = min(255, buffer[(position) * 3 + 2] + additiveColor[2] * (factor));}

void StartEffect(int newEffectType, int lastEffectType)
{
	switch (lastEffectType)
	{
	case EFFECTNAME_ACCELERATION:
	{
	}
	break;

	case EFFECTNAME_NOISELEVEL:
	{
	}
	break;
	}

	switch (newEffectType)
	{
	case EFFECTNAME_ACCELERATION:
		break;

	case EFFECTNAME_NOISELEVEL:
		break;
	}
}

void setup()
{
	Serial.begin(115200);
#if TEST_DEVICE
	while (!Serial);
#endif

	// LED init
	ledAccessCollar.begin();
	ledBufferCollar = ledAccessCollar.getPixels();

	GizmoLED::connectionAnimation = ConnectionFX;
	GizmoLED::effectChangedCallback = StartEffect;
	GIZMOLED_SETUP();
}

const int audioDataSize = 128;
uint8_t audioData[audioDataSize] = { 0 };

float audioActivationTimer = 0.0f;
float audioDeactivationTimer = 0.0f;
float audioFadeTimer = 0.0f;
float audioTimeout = 0.0f;
bool isShowingAudio = false;
float audioRainbowTime = 0.0f;

void loop()
{
	GIZMOLED_LOOP();

	extern float frameTime;

	if (Serial && Serial.available() >= audioDataSize)
	{
		Serial.readBytes(audioData, audioDataSize);
		audioTimeout = 5.0f;
	}
	else if (audioTimeout > 0.0f)
	{
		audioTimeout -= frameTime;
		if (audioTimeout <= 0.0f)
		{
			memset(audioData, 0, 128);
		}
	}

	// Alignment check
	//for (int l = 0; l < LED_BUFFER_SIZE_SIDE; ++l)
	//{
	//	ledBufferCollar[l * 3] = 255;
	//	ledBufferCollar[l * 3 + 1] = 0;
	//	ledBufferCollar[l * 3 + 2] = 0;
	//}

	//for (int l = LED_BUFFER_SIZE_SIDE; l < LED_BUFFER_SIZE_SIDE + LED_BUFFER_SIZE_BACK; ++l)
	//{
	//	ledBufferCollar[l * 3] = 0;
	//	ledBufferCollar[l * 3 + 1] = 255;
	//	ledBufferCollar[l * 3 + 2] = 0;
	//}

	//for (int l = LED_BUFFER_SIZE_SIDE + LED_BUFFER_SIZE_BACK; l < LED_BUFFER_SIZE_SIDE * 2 + LED_BUFFER_SIZE_BACK; ++l)
	//{
	//	ledBufferCollar[l * 3] = 0;
	//	ledBufferCollar[l * 3 + 1] = 0;
	//	ledBufferCollar[l * 3 + 2] = 255;
	//}

	int maxNoise = 0;
	for (int n = 0; n < 128; ++n)
	{
		maxNoise = MAX(maxNoise, audioData[n]);
	}
	const bool hasAudio = maxNoise > 1;

	if (isShowingAudio)
	{
		if (hasAudio)
		{
			audioDeactivationTimer = 3.0f;
			audioFadeTimer = 3.0f;
		}
		else
		{
			audioDeactivationTimer -= frameTime;
			if (audioDeactivationTimer <= 0.0f)
			{
				audioDeactivationTimer = 0.0f;
				isShowingAudio = false;
			}
		}
	}
	else
	{
		if (hasAudio)
		{
			audioDeactivationTimer = 3.0f;
			audioActivationTimer += frameTime;
			if (audioActivationTimer >= 3.0f)
			{
				isShowingAudio = true;
				audioActivationTimer = 0;
			}
		}
		else if (audioDeactivationTimer > 0.0f)
		{
			audioDeactivationTimer -= frameTime;
			if (audioDeactivationTimer <= 0.0f)
			{
				audioActivationTimer = 0.0f;
			}
			else
			{
				audioActivationTimer += frameTime;
			}
		}
	}

	if (isShowingAudio)
	{
		/*
	uint8_t adjustedColor[3] =
	{
		blinkSettings::color[0] * brightness,
		blinkSettings::color[1] * brightness,
		blinkSettings::color[2] * brightness,
	};

	if (*blinkSettings::rainbowEnabled != 0)
	{
		const float rainbowSpeed = *blinkSettings::rainbowSpeed / 100.0f;
		blinkRainbowTime += rainbowSpeed * frameTime;
		while (blinkRainbowTime >= 1.0f)
		{
			blinkRainbowTime -= 1.0f;
		}

		HSV2RGB(blinkRainbowTime * 360.0f, 100, brightness * 100.0f, adjustedColor);
		*/

		//uint8_t colA[3] = { 0 };
		//uint8_t colB[3] = { 0 };

		audioRainbowTime += frameTime * 0.02f;
		while (audioRainbowTime >= 1.0f)
		{
			audioRainbowTime -= 1.0f;
		}

		//HSV2RGB(blinkRainbowTime * 360.0f, 100.0f, 100.0f, colA);
		//HSV2RGB(fmod(blinkRainbowTime + 0.333f, 1.0f) * 360.0f, 100.0f, 100.0f, colB);

		const int leftLEDMax = LED_BUFFER_SIZE_SIDE + LED_BUFFER_SIZE_BACK / 2;
		const int rightLEDMax = LED_BUFFER_SIZE_TOTAL;
		const float gradientShift = 0.1777f;
		const float octaveShift = 0.3333f;
		for (int l = 0; l < leftLEDMax; ++l)
		{
			const float vol = audioData[int(l / float(leftLEDMax) * 64)] / 255.0f * 100.0f;
			const float bassBlend = l / float(leftLEDMax);

			if (l < LED_BUFFER_SIZE_SIDE)
				HSV2RGB(fmod(audioRainbowTime + gradientShift * bassBlend + octaveShift, 1.0f) * 360.0f, 100.0f, vol, &ledBufferCollar[l * 3]);
			else
				HSV2RGB(fmod(audioRainbowTime + gradientShift * bassBlend, 1.0f)  * 360.0f, 100.0f, vol, &ledBufferCollar[l * 3]);
		}

		for (int l = leftLEDMax; l < rightLEDMax; ++l)
		{
			const float vol = audioData[127 - int((l - leftLEDMax) / float(rightLEDMax - leftLEDMax) * 64)] / 255.0f * 100.0f;
			const float bassBlend = 1.0f - (l - leftLEDMax) / float(rightLEDMax - leftLEDMax);

			if (l >= rightLEDMax - LED_BUFFER_SIZE_SIDE)
				HSV2RGB(fmod(audioRainbowTime + gradientShift * bassBlend + octaveShift, 1.0f) * 360.0f, 100.0f, vol, &ledBufferCollar[l * 3]);
			else
				HSV2RGB(fmod(audioRainbowTime + gradientShift * bassBlend, 1.0f)  * 360.0f, 100.0f, vol, &ledBufferCollar[l * 3]);
		}
	}
	else if (audioFadeTimer > 0.0f)
	{
		audioFadeTimer -= frameTime;
		const float fade = 1.0f - audioFadeTimer / 3.0f;
		for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
		{
			ledBufferCollar[l * 3] *= fade;
			ledBufferCollar[l * 3 + 1] *= fade;
			ledBufferCollar[l * 3 + 2] *= fade;
		}
	}

	ledAccessCollar.show();
}

void ConnectionFX(float frameTime, float percent)
{
	float brightness = cos(float(2.0f * percent * M_PI * 2 - M_PI)) * 0.5f + 0.5f;
	const uint8_t rgb[] =
	{
		0 * brightness,
		96 * brightness,
		255 * brightness
	};

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		const float amp = 1.0f; // (LED_BUFFER_SIZE_TOTAL - l - 1) / float(LED_BUFFER_SIZE_TOTAL - 1);
		ledBufferCollar[l * 3] = rgb[1] * amp;
		ledBufferCollar[l * 3 + 1] = rgb[0] * amp;;
		ledBufferCollar[l * 3 + 2] = rgb[2] * amp;
	}
}

float blinkTime = 0.0f;
float blinkRainbowTime = 0.0f;

void AnimateBlink(float frameTime)
{
	const float brightness = *blinkSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		blinkSettings::color[0] * brightness,
		blinkSettings::color[1] * brightness,
		blinkSettings::color[2] * brightness,
	};

	if (*blinkSettings::rainbowEnabled != 0)
	{
		const float rainbowSpeed = *blinkSettings::rainbowSpeed / 100.0f;
		blinkRainbowTime += rainbowSpeed * frameTime;
		while (blinkRainbowTime >= 1.0f)
		{
			blinkRainbowTime -= 1.0f;
		}

		HSV2RGB(blinkRainbowTime * 360.0f, 100, brightness * 100.0f, adjustedColor);
	}

	const float pos = blinkTime * (LED_BUFFER_SIZE_TOTAL);
	blinkTime += frameTime * *blinkSettings::speed / 30.0f;
	while (blinkTime >= 1.0f)
	{
		blinkTime -= 1.0f;
	}

	float blinkAmt = 1.0f;
	if (*blinkSettings::fadeOut != 0 && *blinkSettings::fadeIn != 0)
	{
		if (blinkTime > 0.5f)
			blinkAmt = 1.0f - (blinkTime - 0.5f) / 0.5f;
		else
			blinkAmt = blinkTime / 0.5f;
	}
	else if (*blinkSettings::fadeOut != 0)
	{
		blinkAmt = 1.0f - blinkTime;
	}
	else if (*blinkSettings::fadeIn != 0)
	{
		blinkAmt = blinkTime;
	}

	adjustedColor[0] *= blinkAmt;
	adjustedColor[1] *= blinkAmt;
	adjustedColor[2] *= blinkAmt;

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		ledBufferCollar[l * 3] = adjustedColor[1];
		ledBufferCollar[l * 3 + 1] = adjustedColor[0];
		ledBufferCollar[l * 3 + 2] = adjustedColor[2];
	}
}

float wheelTime = 0.0f;

void AnimateWheel(float frameTime)
{
	const float brightness = *wheelSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		wheelSettings::color[0] * brightness,
		wheelSettings::color[1] * brightness,
		wheelSettings::color[2] * brightness,
	};

	const float pos = wheelTime * (LED_BUFFER_SIZE_TOTAL);
	float dt = frameTime * (*wheelSettings::speed / 100.0f);
	dt = MIN(dt, 1.0f);
	wheelTime += dt;
	while (wheelTime >= 1.0f)
	{
		wheelTime -= 1.0f;
	}

	if (*wheelSettings::rainbowEnabled != 0)
	{
		const float rainbowScale = *wheelSettings::rainbowLength / 100.0f;
		for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
		{
			const float ledRotation = fmod((pos + l * rainbowScale), LED_BUFFER_SIZE_TOTAL);
			const float hue = ledRotation / float(LED_BUFFER_SIZE_TOTAL);

			HSV2RGB(fmod(hue * 360.0f, 360.0f), 100, brightness * 100.0f, adjustedColor);
			ledBufferCollar[l * 3] = adjustedColor[1];
			ledBufferCollar[l * 3 + 1] = adjustedColor[0];
			ledBufferCollar[l * 3 + 2] = adjustedColor[2];
		}
	}
	else
	{
		for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
		{
			const int ledRotation = fmod(pos + l, LED_BUFFER_SIZE_TOTAL);
			const float light = abs(ledRotation - (LED_BUFFER_SIZE_TOTAL) / 2) /
				float((LED_BUFFER_SIZE_TOTAL) / 2);

			ledBufferCollar[l * 3] = adjustedColor[1] * light * light;
			ledBufferCollar[l * 3 + 1] = adjustedColor[0] * light * light;
			ledBufferCollar[l * 3 + 2] = adjustedColor[2] * light * light;
		}
	}
}

float fireRainbowTime = 0.0f;
uint8_t fireCache[LED_BUFFER_SIZE_TOTAL] = { 0 };

void AnimateFire(float frameTime)
{
	const float speed = *fireSettings::speed / 50.0f;
	const float decay = *fireSettings::decay / 10.0f;
	const float noiseScale = *fireSettings::length / 50.0f;
	const float length = *fireSettings::sensitivity / 50.0f;
	const float brightness = *fireSettings::brightness / 255.0f;
	const float backgroundBrightness = *fireSettings::backgroundBrightness / 255.0f;

	uint8_t n[LED_BUFFER_SIZE_TOTAL] = { 0 };
	uint8_t nDecay[LED_BUFFER_SIZE_TOTAL] = { 0 };

	fill_raw_noise8(n, LED_BUFFER_SIZE_TOTAL, 1, 0, 64 - 60 * noiseScale, millis() * speed);
	fill_raw_noise8(nDecay, LED_BUFFER_SIZE_TOTAL, 1, 0, 196, millis() * speed * 10);

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		fireCache[l] = MAX(fireCache[l], n[l]);
		if (fireCache[l] > 0)
		{
			fireCache[l] -= MIN(fireCache[l], (nDecay[l] - 96) * frameTime * decay);
		}
		//	Serial.println(String("led: ") + String(l) + String(", noise: ") + String(n[l]));
	}

	const uint8_t minNoise = 200 - length * 200;
	if (*fireSettings::rainbowEnabled)
	{
		const float rainbowSpeed = *fireSettings::rainbowSpeed / 500.0f;
		fireRainbowTime += frameTime * rainbowSpeed;
		while (fireRainbowTime >= 1.0f)
		{
			fireRainbowTime -= 1.0f;
		}

		const float rainbowOffset = *fireSettings::rainbowOffset / 360.0f;
		const float brightnessDelta = (brightness - backgroundBrightness) * 100.0f;
		const float baseBrightness = backgroundBrightness * 100.0f;

		for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
		{
			float light = map(MAX(minNoise, fireCache[l]), minNoise, 255, 0, 255) / 255.0f;
			HSV2RGB(fmod(fireRainbowTime + rainbowOffset * light, 1.0f) * 360.0f, 100.0f, baseBrightness + brightnessDelta * light, ledBufferCollar + l * 3);
		}
	}
	else
	{
		uint8_t adjustedColor[3];
		uint8_t backgroundColor[3];

		adjustedColor[0] = fireSettings::color[0] * brightness;
		adjustedColor[1] = fireSettings::color[1] * brightness;
		adjustedColor[2] = fireSettings::color[2] * brightness;
		backgroundColor[0] = fireSettings::background[0] * backgroundBrightness;
		backgroundColor[1] = fireSettings::background[1] * backgroundBrightness;
		backgroundColor[2] = fireSettings::background[2] * backgroundBrightness;

		const int deltaColor[] =
		{
		  (int)adjustedColor[0] - (int)backgroundColor[0],
		  (int)adjustedColor[1] - (int)backgroundColor[1],
		  (int)adjustedColor[2] - (int)backgroundColor[2]
		};

		for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
		{
			float light = map(MAX(minNoise, fireCache[l]), minNoise, 255, 0, 255) / 255.0f;

			ledBufferCollar[l * 3] = light * deltaColor[1] + (int)backgroundColor[1];
			ledBufferCollar[l * 3 + 1] = light * deltaColor[0] + (int)backgroundColor[0];
			ledBufferCollar[l * 3 + 2] = light * deltaColor[2] + (int)backgroundColor[2];
		}
	}
}

float sparkleRainbowTime = 0.0f;

void AnimateSparkle(float frameTime)
{
	const float speed = *sparkleSettings::speed / 50.0f;
	const float length = *sparkleSettings::length / 50.0f;
	const float brightness = *sparkleSettings::brightness / 255.0f;
	const float backgroundBrightness = *sparkleSettings::backgroundBrightness / 255.0f;

	uint8_t n[LED_BUFFER_SIZE_TOTAL] = { 0 };
	fill_raw_noise8(n, LED_BUFFER_SIZE_TOTAL, 1, 0, 96, millis() * speed);
	//for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	//{
	//	Serial.println(String("led: ") + String(l) + String(", noise: ") + String(n[l]));
	//}

	uint8_t adjustedColor[3];
	uint8_t backgroundColor[3];

	const uint8_t minNoise = 200 - length * 200;
	if (*sparkleSettings::rainbowEnabled)
	{
		const float rainbowSpeed = *sparkleSettings::rainbowSpeed / 500.0f;
		sparkleRainbowTime += frameTime * rainbowSpeed;
		while (sparkleRainbowTime >= 1.0f)
		{
			sparkleRainbowTime -= 1.0f;
		}

		const float rainbowOffset = *sparkleSettings::rainbowOffset / 360.0f;

		HSV2RGB(sparkleRainbowTime * 360.0f, 100.0f, brightness * 100.0f, adjustedColor);
		HSV2RGB(fmod(sparkleRainbowTime + rainbowOffset, 1.0f) * 360.0f, 100.0f, backgroundBrightness * 100.0f, backgroundColor);
	}
	else
	{
		adjustedColor[0] = sparkleSettings::color[0] * brightness;
		adjustedColor[1] = sparkleSettings::color[1] * brightness;
		adjustedColor[2] = sparkleSettings::color[2] * brightness;
		backgroundColor[0] = sparkleSettings::background[0] * backgroundBrightness;
		backgroundColor[1] = sparkleSettings::background[1] * backgroundBrightness;
		backgroundColor[2] = sparkleSettings::background[2] * backgroundBrightness;
	}

	const int deltaColor[] =
	{
	  (int)adjustedColor[0] - (int)backgroundColor[0],
	  (int)adjustedColor[1] - (int)backgroundColor[1],
	  (int)adjustedColor[2] - (int)backgroundColor[2]
	};

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		float light = map(MAX(minNoise, n[l]), minNoise, 255, 0, 255) / 255.0f;

		ledBufferCollar[l * 3] = light * deltaColor[1] + (int)backgroundColor[1];
		ledBufferCollar[l * 3 + 1] = light * deltaColor[0] + (int)backgroundColor[0];
		ledBufferCollar[l * 3 + 2] = light * deltaColor[2] + (int)backgroundColor[2];
	}
}

uint32_t pulseCount = 0;
float pulseTimer = 0.0f;

void AnimatePulse(float frameTime)
{
	float dt = frameTime * (*pulseSettings::speed / 40.0f);
	dt = MIN(1.0f, dt);
	pulseTimer += dt;
	while (pulseTimer >= 1.0f)
	{
		pulseTimer -= 1.0f;
		++pulseCount;
	}

	const float brightness = *pulseSettings::brightness / 255.0f;
	uint8_t adjustedColor1[] =
	{
		pulseSettings::color1[0] * brightness,
		pulseSettings::color1[1] * brightness,
		pulseSettings::color1[2] * brightness
	};
	uint8_t adjustedColor0[] =
	{
		pulseSettings::color2[0] * brightness,
		pulseSettings::color2[1] * brightness,
		pulseSettings::color2[2] * brightness
	};
	int adjustedColorD[] =
	{
		adjustedColor1[0] - adjustedColor0[0],
		adjustedColor1[1] - adjustedColor0[1],
		adjustedColor1[2] - adjustedColor0[2],
	};

	const float pulseLength = float(*pulseSettings::length) / 10.0f;
	const float rainbowLength = float(*pulseSettings::rainbowLength);
	const bool useRainbow = *pulseSettings::rainbowEnabled != 0;
	const bool fadeOut = *pulseSettings::fadeOut != 0;
	if (useRainbow)
	{
		adjustedColorD[0] = 0;
		adjustedColorD[1] = 0;
		adjustedColorD[2] = 0;
	}

#define PULSE_LED_POS(width) \
		const float pos = i / float(width); \
		const float posFull = i / float(width - 1.0f); \
		const float pulseAlignment = pulseLength - pulseTimer * pulseLength; \
		float light = fmod(pos + pulseAlignment, pulseLength) / pulseLength * 1.2f; \
		if (light > 1.0f) \
			light = 1.0f - ((light - 1.0f) / 0.2f); \
		if (useRainbow) \
		{ \
			float hue = fmod(pulseCount * rainbowLength - ((pos + pulseAlignment >= pulseLength) ? rainbowLength : 0.0f), 360.0f); \
			HSV2RGB(hue, 100.0f, brightness * 100.0f, adjustedColor1); \
		} \
		else \
		{ \
			float colMix = fmod(posFull + pulseAlignment, pulseLength) / pulseLength; \
			adjustedColor1[0] = adjustedColor0[0] + adjustedColorD[0] * colMix; \
			adjustedColor1[1] = adjustedColor0[1] + adjustedColorD[1] * colMix; \
			adjustedColor1[2] = adjustedColor0[2] + adjustedColorD[2] * colMix; \
		} \
		if (fadeOut) \
		{ \
			light *= 1.0f - posFull; \
		} \
		light *= light

	for (int i = 0; i < LED_BUFFER_SIZE_TOTAL; ++i)
	{
		PULSE_LED_POS(LED_BUFFER_SIZE_TOTAL);

		ledBufferCollar[i * 3] = adjustedColor1[1] * light;
		ledBufferCollar[i * 3 + 1] = adjustedColor1[0] * light;
		ledBufferCollar[i * 3 + 2] = adjustedColor1[2] * light;
	}
}

float christmasTime = 0.0f;
float christmasRainbowTime = 0.0f;

void AnimateChristmas(float frameTime)
{
	const float brightness = *christmasSettings::brightness / 255.0f;
	uint8_t adjustedColor[3] =
	{
		christmasSettings::color[0] * brightness,
		christmasSettings::color[1] * brightness,
		christmasSettings::color[2] * brightness,
	};

	const int spacing = *christmasSettings::length;
	const int pos = wheelTime * spacing;
	float dt = frameTime * (*christmasSettings::speed / 50.0f);
	dt = MIN(1.0f, dt);
	wheelTime += dt;
	while (wheelTime >= 1.0f)
	{
		wheelTime -= 1.0f;
	}

	if (*christmasSettings::rainbowEnabled != 0)
	{
		const float rainbowSpeed = *christmasSettings::rainbowSpeed / 100.0f;
		christmasRainbowTime += rainbowSpeed * frameTime;
		while (christmasRainbowTime >= 1.0f)
		{
			christmasRainbowTime -= 1.0f;
		}

		HSV2RGB(christmasRainbowTime * 360.0f, 100, brightness * 100.0f, adjustedColor);
	}

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		const float light = ((pos + l) % spacing) == 0 ? 1.0f : 0.0f;
		ledBufferCollar[l * 3] = adjustedColor[1] * light;
		ledBufferCollar[l * 3 + 1] = adjustedColor[0] * light;
		ledBufferCollar[l * 3 + 2] = adjustedColor[2] * light;
	}
}

float emptyAnim = 0.0f;

void AnimateEmpty(float frameTime)
{
	uint8_t adjustedColor[3] =
	{
		emptySettings::color[0],
		emptySettings::color[1],
		emptySettings::color[2],
	};

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		ledBufferCollar[l * 3] = 0;
		ledBufferCollar[l * 3 + 1] = 0;
		ledBufferCollar[l * 3 + 2] = 0;
	}

	emptyAnim += frameTime;
	if (emptyAnim >= 1.0f)
	{
		ledBufferCollar[0] = adjustedColor[1];
		ledBufferCollar[1] = adjustedColor[0];
		ledBufferCollar[2] = adjustedColor[2];
		if (emptyAnim >= 2.0f)
		{
			emptyAnim = 0.0f;
		}
	}
}

float wavesRainbowTime = 0.0f;
float wavesTime = 0.0f;

void AnimateWaves(float frameTime)
{
	const float speed = *wavesSettings::speed / 20.0f;
	const float length = 1.0f - *wavesSettings::length / 100.0f;
	const float brightness = *wavesSettings::brightness / 255.0f;

	uint8_t adjustedColor[3];
	uint8_t backgroundColor[3];

	wavesTime += frameTime * speed;

	if (*wavesSettings::rainbowEnabled)
	{
		const float rainbowSpeed = *wavesSettings::rainbowSpeed / 500.0f;
		wavesRainbowTime += frameTime * rainbowSpeed;
		while (wavesRainbowTime >= 1.0f)
		{
			wavesRainbowTime -= 1.0f;
		}

		const float rainbowOffset = *wavesSettings::rainbowOffset / 360.0f;

		HSV2RGB(wavesRainbowTime * 360.0f, 100.0f, brightness * 100.0f, adjustedColor);
		HSV2RGB(fmod(wavesRainbowTime + rainbowOffset, 1.0f) * 360.0f, 100.0f, brightness * 100.0f, backgroundColor);
	}
	else
	{
		adjustedColor[0] = wavesSettings::color[0] * brightness;
		adjustedColor[1] = wavesSettings::color[1] * brightness;
		adjustedColor[2] = wavesSettings::color[2] * brightness;

		backgroundColor[0] = wavesSettings::color1[0] * brightness;
		backgroundColor[1] = wavesSettings::color1[1] * brightness;
		backgroundColor[2] = wavesSettings::color1[2] * brightness;
	}

	const int deltaColor[] =
	{
	  (int)adjustedColor[0] - (int)backgroundColor[0],
	  (int)adjustedColor[1] - (int)backgroundColor[1],
	  (int)adjustedColor[2] - (int)backgroundColor[2]
	};

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		float light = sin(l * length + wavesTime) * 0.5f + 0.5f;
		ledBufferCollar[l * 3] = light * deltaColor[1] + (int)backgroundColor[1];
		ledBufferCollar[l * 3 + 1] = light * deltaColor[0] + (int)backgroundColor[0];
		ledBufferCollar[l * 3 + 2] = light * deltaColor[2] + (int)backgroundColor[2];
	}
}

const int dropsCount = 5;
float visualizerDropsTimers[dropsCount] = { 0.0f };
int visualizerDropsPositions[dropsCount] = { 0 };
float dropsRainbowHue[dropsCount] = { 0.0f };

#define DROPS_TIME 1.2f
#define DROPS_FADE_IN 0.2f

float nextDropsHue = 0.0f;
float dropsTriggerTimers[dropsCount] = { 0.0f };
void SimulateDrops(float frameTime)
{
	for (int a = 0; a < dropsCount; ++a)
	{
		dropsTriggerTimers[a] += frameTime * 1.5f * (dropsCount * 2 - a) / float(dropsCount * 2);

		if (dropsTriggerTimers[a] >= 1.0f &&
			visualizerDropsTimers[a] == 0.0f)
		{
			dropsTriggerTimers[a] = 0.0f;

			visualizerDropsPositions[a] = random(0, LED_BUFFER_SIZE_TOTAL);
			visualizerDropsTimers[a] = DROPS_TIME;
			if (*dropsSettings::rainbowEnabled != 0)
			{
				dropsRainbowHue[a] = nextDropsHue;
				nextDropsHue += *dropsSettings::rainbowSpeed;
				while (nextDropsHue >= 360.0f)
				{
					nextDropsHue -= 360.0f;
				}
			}
		}
	}
}

void AnimateDrops(float frameTime)
{
	SimulateDrops(frameTime);

	const float dropsDecay = *dropsSettings::decay / 100.0f;
	const float dropsLength = *dropsSettings::length;

	for (int l = 0; l < LED_BUFFER_SIZE_TOTAL; ++l)
	{
		ledBufferCollar[l * 3] = 0;
		ledBufferCollar[l * 3 + 1] = 0;
		ledBufferCollar[l * 3 + 2] = 0;
	}

	const float brightness = *dropsSettings::brightness / 255.0f;
	uint8_t adjustedColor[] =
	{
		dropsSettings::color[0] * brightness,
		dropsSettings::color[1] * brightness,
		dropsSettings::color[2] * brightness
	};

	// Update drops data
	const float dropsDecayDt = frameTime * dropsDecay * 10.0f;
	float centerPos = int(dropsLength / 2);
	if ((*dropsSettings::length % 2) == 1)
		centerPos += 1.0f;

	for (int s = 0; s < dropsCount; ++s)
	{
		if (visualizerDropsTimers[s] > 0.0f)
		{
			visualizerDropsTimers[s] -= dropsDecayDt;
			if (visualizerDropsTimers[s] <= 0.0f)
			{
				visualizerDropsTimers[s] = 0.0f;
			}
			else
			{
				if (*dropsSettings::rainbowEnabled != 0)
				{
					HSV2RGB(dropsRainbowHue[s], 100.0f, brightness * 100.0f, adjustedColor);
				}

				int basePos = visualizerDropsPositions[s];
				basePos -= centerPos;
				float dropsB = visualizerDropsTimers[s];
				const float dropFrac = dropsB / DROPS_TIME;
				if (dropsB > 1.0f)
					dropsB = 1.0f - (dropsB - 1.0f) / DROPS_FADE_IN;

				if (basePos < 0)
					basePos += (LED_BUFFER_SIZE_TOTAL);

				for (int i = 0; i < dropsLength; ++i)
				{
					const int pos = (basePos + i) % LED_BUFFER_SIZE_TOTAL;
					float amp = abs(i - centerPos) / centerPos;
					float ampInv = 1.0f - amp;
					amp = powf(amp, 4.0f);
					ampInv = powf(ampInv, 4.0f);

					float ampBlend = dropFrac * (ampInv - amp) + amp;
					ADD_CLAMPED_COLOR(ledBufferCollar, pos, adjustedColor, dropsB * ampBlend);
				}
			}
		}
	}
}

float wipeRainbowOffset = 0.0f;
float wipeTime = 0.0f;
int wipeCount = 0;

void AnimateWipe(float frameTime)
{
	const float speed = *wipeSettings::speed / 75.0f;
	const float brightness = *wipeSettings::brightness / 255.0f;
	const float rainbowOffset = *wipeSettings::rainbowOffset;

	uint8_t adjustedColor[3];

	wipeTime += frameTime * speed;
	while (wipeTime >= 1.0f)
	{
		wipeTime -= 1.0f;
		++wipeCount;
		wipeRainbowOffset = fmod(wipeRainbowOffset + rainbowOffset, 360.0f);
	}

	const int wipePos = (LED_BUFFER_SIZE_TOTAL * 2) * wipeTime;

	if (*wipeSettings::rainbowEnabled)
	{
		HSV2RGB(wipeRainbowOffset, 100.0f, brightness * 100.0f, adjustedColor);
	}
	else
	{
		uint8_t *c = (wipeCount % 2) ? wipeSettings::color : wipeSettings::color1;
		adjustedColor[0] = c[0] * brightness;
		adjustedColor[1] = c[1] * brightness;
		adjustedColor[2] = c[2] * brightness;
	}

	for (int l = 0; l < MIN(wipePos, LED_BUFFER_SIZE_TOTAL); ++l)
	{
		ledBufferCollar[l * 3] = adjustedColor[1];
		ledBufferCollar[l * 3 + 1] = adjustedColor[0];
		ledBufferCollar[l * 3 + 2] = adjustedColor[2];
	}
}
