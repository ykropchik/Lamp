#ifndef EFFECTS
#define EFFECTS

#include <FastLED.h>
#include <CubicBezier.h>
#include <effects/Effect.h>
#include <effects/SparklesEffect.h>
#include <effects/FireEffect.h>
#include <effects/RainbowEffect.h>
#include <effects/ColorEffect.h>
#include <effects/MadnessNoiseEffect.h>
#include <effects/RainbowNoiseEffect.h>
#include <effects/RainbowStripeNoiseEffect.h>
#include <effects/ZebraNoiseEffect.h>
#include <effects/ForestNoiseEffect.h>
#include <effects/OceanNoiseEffect.h>
#include <effects/PlasmaNoiseEffect.h>
#include <effects/CloudsNoiseEffect.h>
#include <effects/LavaNoiseEffect.h>
#include <effects/SnowEffect.h>
#include <effects/SnowStormEffect.h>
#include <effects/StarfallEffect.h>
#include <effects/MatrixEffect.h>
#include <effects/LightersEffect.h>
#include <effects/BallsEffect.h>
#include <effects/WaitingEffect.h>
#include <effects/ColorPulseEffect.h>

// ============= ИНИЦИАЛИЗАЦИЯ РЕЖИМОВ С ДЕФОЛТНЫМИ ЗНАЧЕНИЯМИ ============

inline Effect *effects[] {
	new SparklesEffect(50, 10),
	new FireEffect(10, 0, CRGB(240,127,19)),
	new RainbowEffect(RainbowType::Vertical, 10, 40U),
	new ColorEffect(CRGB(240,127,19)),
	new MadnessNoiseEffect(6, 60),
	new RainbowNoiseEffect(6, 60),
	new ZebraNoiseEffect(6, 60),
	new ForestNoiseEffect(6, 60),
	new OceanNoiseEffect(6, 60),
	new PlasmaNoiseEffect(6, 60),
	new CloudsNoiseEffect(6, 60),
	new LavaNoiseEffect(6, 60),
	new SnowEffect(6, 60),
	new SnowStormEffect(6, 60),
	new StarfallEffect(6, 60),
	new MatrixEffect(6, 60),
	new LightersEffect(6, 60),
	new BallsEffect(6, 60)
};

inline WaitingEffect *waiting = new WaitingEffect();
inline ColorPulseEffect *warning = new ColorPulseEffect(1000, CRGB(255, 204, 0), 100);
inline ColorPulseEffect *error = new ColorPulseEffect(2000, CRGB(255, 5, 5), 100);

#endif