# PPUC - Pinball Power-Up Controller

The Pinball Power-Up Controller family is designed to enhance the capabilities of classic pinball machines of the 80s
and 90s and to drive the hardware of home brew pinball machines.

In existing machines, the controller is able to monitor all playfield switches, lights, and solenoids and to trigger and
distribute corresponding *events* to attached sub-systems.
In combination with PIN2DMD and TiltAudio it is possible to monitor DMD and sound commands, too.

One sub-system is the built-in EffectController which is able to drive additional LEDs, motors, and coils.
Other sub-systems could be video players or audio systems. The additional effects are bundled per pinball machine in
so-called *Pinball Power-Ups* (PPUs).

For homebrew machines there will be additional software to act as "CPU", running the game logic aka rules and
communicating with the controllers. (WIP)

A special variation of that "CPU" will be suitable as replacement for a broken CPU of an existing machine.
The development happens as part of the [PinMAME project](https://github.com/vpinball/pinmame/tree/master/src/ppuc).

## Motivation

We want to enable people to be creative and to modernize old pinball machines using today's technology. Our goal is to
establish an open and affordable platform for that. Ideally people will publish their game-specific PPUs so others could
leverage and potentially improve them. We want to see a growing library of PPUs and a vital homebrew pinball community.  

## Concept

### Enhancing / Modding an existing machine

The Pinball Power-Up Controllers consist of multiple micro controllers to perform several tasks in parallel. The entire
system is modular, so you can choose what you really need. The basic setup consists of a controller to capture a
pinball's events and another independent one to run effects.

We will provide several integrated boards and vendor specific adaptor boards (currently in development: Williams WPC,
Data East, Stern SAM and Whitestar).

These controllers integrate modified versions of other projects with the permission of their authors:
* https://github.com/sker65/pinball-lw3
* https://github.com/bitfieldlabs/afterglow
* https://github.com/bitfieldlabs/aggi

The Effect Controller should be able to drive hundreds (or thousands?) of LEDs, PWM devices, ... in parallel in a
non-blocking way.

### Homebrew machines

WIP

### Replacing a CPU (and drivers)

WIP, see [PinMAME project](https://github.com/vpinball/pinmame/tree/master/src/ppuc).

## Licence

The code is licenced under GPLv3. Be aware of the fact that your own *Pinball Power-Ups* (PPUs) need to be licenced
under a compatible licence.
That doesn't prevent any commercial use, but you need to respect the terms and conditions of GPLv3!

We would appreciate contributions to PPUC itself or as game-specific PPUs.

## Setup Development Environment

todo

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

If the auto-detection of the USB ports during `pio run --target upload` doesn't succeed you need to specify them
explicitly. Run `pio device list` to list the available ports. Force the usage of a specifc USB port during upload:
```
pio run --target upload --device XYZ
```
