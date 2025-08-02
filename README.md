# &mu;WWVB: a tiny wwvb station

&mu;WWVB is a watch stand that automatically sets the time on atomic wristwatches where regular [WWVB] signal isn’t available. The system acquires the correct time via GPS and sets radio-controlled clocks by emulating the amplitude-modulated WWVB time signal.

![&mu;WWVB watch stand](https://raw.githubusercontent.com/anishathalye/assets/master/micro-wwvb/micro-wwvb.jpg)

For more information, see [the blog post][micro-wwvb-post].

[WWVB]: https://www.nist.gov/pml/time-and-frequency-division/radio-stations/wwvb
[micro-wwvb-post]: https://www.anishathalye.com/2016/12/26/micro-wwvb/

## Software

Software is in the `src/` directory. If you're using macOS to build the firmware image, use [CrossPack].

[Crosspack]: https://www.obdev.at/products/crosspack/index.html

## Electronics

The board design is in the `board/` directory. `microwwvb.brd` and `microwwvb.sch` are the [Autodesk EAGLE] board and schematic. This directory also contains images of the board outline, traces, schematic, and assembled board.

[Autodesk EAGLE]: https://www.autodesk.com/products/eagle/free-download

### BOM

- [ATtiny44A](https://www.microchip.com/en-us/product/ATtiny44A) microcontroller
- [USGlobalSat EM-506](https://web.archive.org/web/20230314174108/https://www.sparkfun.com/products/12751) GPS receiver
- 20 MHz crystal oscillator ([644-1039-1-ND](https://www.digikey.com/en/products/detail/ndk-nihon-dempa-kogyo-co-ltd/LNCD1-20M/1128821))
- LEDs
    - Red ([67-1356-1-ND](https://www.digikey.com/en/products/detail/lumex-opto-components-inc/SML-LX1206IC-TR/229140))
    - Green ([67-1357-1-ND](https://www.digikey.com/en/products/detail/lumex-opto-components-inc/SML-LX1206GC-TR/229139))
    - Blue ([732-4989-1-ND](https://www.digikey.com/en/products/detail/w%C3%BCrth-elektronik/150120BS75000/4489933))
- Resistors
    - 499 &Omega; ([311-499FRCT-ND](https://www.digikey.com/en/products/detail/yageo/RC1206FR-07499RL/728944))
    - 1 k&Omega;, quantity 2 ([311-1.00KFRCT-ND](https://www.digikey.com/en/products/detail/yageo/RC1206FR-071KL/728387))
    - 10 k&Omega; ([311-10.0KFRCT-ND](https://www.digikey.com/en/products/detail/yageo/RC1206FR-0710KL/728483))
- Capacitors
    - 10 pF, quantity 2 ([311-1150-1-ND](https://www.digikey.com/en/products/detail/yageo/CC1206JRNPO9BN100/302884))
    - 1 &mu;F ([445-1423-1-ND](https://www.digikey.com/en/products/detail/tdk-corporation/C3216X7R1H105K160AB/569049))
- Mini USB connector ([H2961CT-ND](https://www.digikey.com/en/products/detail/hirose-electric-co-ltd/UX60A-MB-5ST/597537))
- [JST horizontal 6-Pin connector](https://www.sparkfun.com/jst-sh-horizontal-6-pin-connector-smd.html)
- Pin headers
    - 4-pin ([609-5160-1-ND](https://www.digikey.com/en/products/detail/amphenol-cs-fci/95278-801A04LF/1535898))
    - 6-pin ([609-5161-1-ND](https://www.digikey.com/en/products/detail/amphenol-cs-fci/95278-801A06LF/1535720))

## Enclosure

The CAD files for the physical enclosure are in the `cad/` directory. The top and bottom pieces of the &mu;WWVB station are 3D-printed, and the sides are laser-cut acrylic.
