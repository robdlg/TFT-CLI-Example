# TFT-CLI-Example
Basic example of LILYGO T-Dongle-S3 display control using SpacehuhnTech SimpleCLI Library

## Example
At a Linux terminal with the T-Dongle-S3 at `/dev/ttyACM0`, `echo` may be invoked to send the command.
```
$ echo 'color -bg red -txt yellow' > /dev/ttyACM0
```
Note: In the example code, both arguments are required.

## References
* https://github.com/Xinyuan-LilyGO/T-Dongle-S3
* https://github.com/adafruit/Adafruit-ST7735-Library
* https://github.com/SpacehuhnTech/SimpleCLI
