# PPUC - Pinball Power-Up Controller

The Pinball Power-Up Controller is designed to enhance the capabilities of classic pinball machines of the 80s and 90s.
It is able to monitor all playfield switches, lights, and solenoids and to trigger and distribute corresponding *events*
to attached sub-systems.
In combination with PIN2DMD and TiltAudio it should be possible to monitor DMD and sound commands, too.
One sub-system is the built-in EffectController which is able to drive additional LEDs, motors, and coils.
Other sub-systems could be video players or audio systems.
The additional effects are bundled per pinball machine in so-called *Pinball Power-Ups* (PPUs).

## Motivation

We want to enable people to be creative and to modernize old pinball machines using today's technology. Our goal is to establish an open and affordable platform for that. Ideally people will publish their game-specific PPUs so others could leverage and potentially improve them. We want to see a growing library of PPUs and a vital homebrew pinball community.  

## Concept

The Pinball Power-Up Controller is a single board that contains two micro controllers, an Ardunino to capture a pinball's events and a Teensy to run effects. (We choose this combination to ease the usage. Anyone should be able to create his own PPUs using the simple Arduino IDE.)
It will be integrated using vendor specific adaptor boards (currently in development: Williams WPC, Data East, Stern SAM and Whitestar).

The controller integrates modified versions of other projects with the permission of their authors:
* https://github.com/sker65/pinball-lw3
* https://github.com/bitfieldlabs/afterglow
* https://github.com/bitfieldlabs/aggi

As mentioned above, the controller uses two different micro controllers. Therefore the code is split into specific and common parts and adjusted versions of existing libraries:
* https://github.com/mkalkbrenner/PPUCInputController
* https://github.com/mkalkbrenner/PPUCEffectController
* https://github.com/mkalkbrenner/PPUCEventDispatcher
* https://github.com/mkalkbrenner/PPUCDistributionController
* https://github.com/mkalkbrenner/WS2812SerialFX
* https://github.com/mkalkbrenner/WavePWM

The Effect Controller should be able to drive hundreds (or thousands?) of LEDs, PWM devices, ... in parallel in a non-blocking way.

## Licence

The code is licenced under GPLv3. Be aware of the fact that your own *Pinball Power-Ups* (PPUs) need to be licenced under a compatible licence.
That doesn't prevent any commercial use, but you need to respect the terms and conditions of GPLv3!

We would appreciate contributions to PPUC itself or as game-specific PPUs.

## Setup Development Environment

```
git clone git@github.com:mkalkbrenner/PPUC.git
cd PPUC
git clone git@github.com:mkalkbrenner/ppu.git
git clone git@github.com:mkalkbrenner/PPUCEventDispatcher.git libs/PPUCEventDispatcher
git clone git@github.com:mkalkbrenner/PPUCInputController.git libs/PPUCInputController
git clone git@github.com:mkalkbrenner/PPUCEffectController.git libs/PPUCEffectController
git clone git@github.com:mkalkbrenner/PPUCDistributionController.git libs/PPUCDistributionController
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
