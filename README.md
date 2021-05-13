# PPUC - Pinball Power-Up Controller

The Pinball Power-Up Controller is designed to enhance the capabilities of classic pinball machines of the 80s and 90s.
It is able to monitor all playfield switches, lights, and solenoids and to trigger and distribute corresponding *events*
to attached sub-systems.
In combination with PIN2DMD and TiltAudio it should be possible to monitor DMD and sound commands, too.
One sub-system is the built-in EffectController which is able to drive additional LEDs, motors, and coils.
Other sub-systems could be video players or audio systems.
The additional effects are bundled per pinball machine in so-called *Pinball Power-Ups* (PPUs).

## Setup Development Environment

```
git clone git@github.com:mkalkbrenner/PPUC.git
cd PPUC
git clone git@github.com:mkalkbrenner/ppu.git
git clone git@github.com:mkalkbrenner/PPUCEventDispatcher.git libs/PPUCEventDispatcher
git clone git@github.com:mkalkbrenner/PPUCInputController.git libs/PPUCInputController
git clone git@github.com:mkalkbrenner/PPUCEffectController.git libs/PPUCEffectController
git clone git@github.com:mkalkbrenner/WS2812SerialFX.git ext_libs/WS2812SerialFX
git clone git@github.com:mkalkbrenner/WavePWM.git ext_libs/WavePWM
```

## Compile & Upload

Example:
```
cd ppu/STTNG/InputController
pio run
pio run --target upload
cd ../EffectController
pio run
pio run --target upload
```

## Troubleshooting

If the autodection of the USB ports during `pio run --target upload` doesn't succeed you need to specify them
explicitly. Run `pio device list` to list the available ports. Force the usage of a specifc USB port during upload:
```
pio run --target upload --device XYZ
```
