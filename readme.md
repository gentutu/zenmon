## zenmon

### Introduction
`zenmon` is a top-like CLI monitoring tool for AMD Ryzen CPUs written in C. It uses `k10temp` to display the electrical and temperature statistics of the CPU in a way that is pleasing to the eye, at least for me. It also displays generic information related to the overall system load:
* Uptime
* Number of processes
* CPU usage for the past 1, 5 and 15 minutes
* RAM usage
* CPU thread usage
* CPU core MHz

This started as a personal project after I was left unsatisfied with the tools available for monitoring voltages and temperatures on the Ryzen 3000 CPUs.

Late in the development process, after it started looking like an actual top-like tool, I have decided that I might as well make it public. Take it as is, it's not intended to be the end-all system monitor, just a tailored solution for myself.

At this point I would consider it feature-complete. I will certainly maintain/improve its stability/quality, but additional features are not on my roadmap, at least for now.

---
### Preview
<p align="center">
<img src=./res/zenmon.gif width="800" height="440">
</p>

* For the display I use centivolts instead of millivolts for better text alignment; in the code they are millivolts, and the variables associated with them are as named as volts. Yes, it is confusing
* The labeling for the usage and MHz bars are a bit messy, but that's the best way I have found to make them work
* For each Braille graph, the scales, value of each dot and the point at which is turns red can be found in the `cfg` directory. By default they are set to something reasonable, that also works well with the limitations imposed by working with 2x4 "pixels" Braille characters
* The minimum frequency that I get with my setup is 2.2 GHz; this is the reason the frequency bars stay high

---
### Buliding
#### Dependencies
* my shared code [repo](https://github.com/gentutu/common)
    * either clone it at the same level or update the `LIB_DIR` variable in the makefile
* GNU `make`
* *A* Ryzen CPU (see the section below)
* `ncurses` is **not** needed; I did the cursor jumping myself

#### Compatible CPUs
* Supported out-of-the-box:
    * AMD Ryzen 9 3950X and 5950X
* Supported after changing some code:
    * Any other Ryzen CPU that `k10temp` supports with voltage, current and temperature
    * There are no hard dependencies on Ryzen CPUs, so with *slight* reworks of the data acquisition and display components it will work on pretty much anything

#### More on the topic of compatible CPUs
* It all depends on the files `k10temp` exposes; for the supported CPUs the files are as follows:
    * core voltage: in0_input
    * core current: curr1_input
    * soc voltage: in1_input
    * soc current: curr2_input
    * die temperature: temp1_input
    * ctl temperature: temp2_input
    * ccd0 temperature: temp3_input
    * ccd1 temperature: temp4_input
* In case of other Ryzen CPUs, whatever `k10temp` decides to expose can be read by `zenmon`
* At run-time, all the required system files are checked; if any are missing, `zenmon` will notify and exit gracefully
* The only Ryzen CPU I have access to is my 3950X, so this is what I can fully test it on

#### Modifications needed for unsupported CPUs
* The core/thread config can be changed in `zenmon-cfg-load.h` and the windows can be re-structured in `zenmon-num-load.c`
* Remove (or add if you have a Threadripper CPU) the extra file(s) handling (temperatures for missing/extra CCDs)
* The `cfg` directory and `zenmon-types.h` are good starting points; go top-down from there; I am talking about defines (especially for the system files from where I acquire various data) and structure members
* Restructure the content of the windows; see the `zenmon-box`, `zenmon-num` and `zenmon-dot` modules' APIs
* In the `doc` directory there is a basic block diagram of the app structure that might help

#### Steps
> make

---
### Usage
Call it from the newly-created `out` directory and it will run with a sample rate of 1 second. Otherwise, use one of these:
> ./zenmon -h
>
> ./zenmon -r \<sample rate in ms\>

---
### Issues
* This piece of software contains only features

---
### Limitations
I might get to these at some point:
* As mentioned above, the supported CPU list barely exceedes 2 items
* Used memory is calculated as (Total - Free - Buffers - Cached), which also means:
    * `tmpfs` usage is not taken into account
    * I did not get the memory info from `sysinfo` because it has no data on cached RAM
    * other monitoring tools might report slightly different values, but still relatively close

I do not consider the next ones true issues, so they will remain as they are:
* One might say that the way the include and library files are gathered in the makefile is somewhat barbaric
* Average values calculations start after 10 samples; until then they are 0
* In the first polling cycle, CPU thread usage is calculated since startup; this is because of the way `/proc/stat` works

---
### License
Copyright © 2020 Denis Isai

Licensed under the GPLv3: http://www.gnu.org/licenses/gpl-3.0.html

---
### Credits
* The Braille character handling from braille-lib.h and braille-lib.c have been adapted from https://github.com/dcat/tplot
