# Open Smart Watch Blog.
#### A blog detailing the development of the OpenSmartWatch project.

## Where have you been? (22/12/2023)

I've not really done much with OSW over the past two months, life has gotten in the way
with this such as keeping up with my CS Course and the progress I have made has largely
been resulting in dead ends.

1) S3/C3
    A few days after the last post, I started looking at buttons to give some form of
    input to OSW however I found that once OSW went to sleep two issues occured.
		A) SysLog calls were no longer shown serially.
   		B) I wasn't able to wake OSW using buttons
   	OSW updates the homescreen every 60 seconds (roughly) as it tries to update the
   	screen at a second or two past the minute i.e 19:11:01 so that the screen always
   	shows the right time. However as I was using a Seeduino XIAO ESP32-C3 instead of
   	an ESP32-S3 I did not have any way to wake up from a sleep state except for a
   	timer. I did float writing a microprogram that listened for button presses in the
   	ESP32's ULP (ULP is a low power processor that runs during sleep) however it turns
   	out that the ESP32-C3 is rediculously cut down compared it's S3 variant.
   	To show exactly what's changed, this is Espressif's (The maker of the ESP32) diagram.
![image](https://github.com/Rarisma/OpenSmartWatch/assets/49795711/e1ce0f71-5191-41e3-af53-e7498d02096c)

	It's missing quite a bit of essential functionality, so the obvious question is why
	aren't we using the S3? Well I bought two and they both broke after flashing OSW.
	Every time I plug them in, I get a mirrad of errors saying the device has malfunctioned.
	I haven't tried them in a linux environment yet but I suspect the same will occur.
	Also the reset button broke on one of S3 boards.
	So for now I'm looking at just doing a very inefficent delay on the C3 which will
	not work in the real world due to battery drain but should allow me to continue
	development until I can switch to another S3 based board or fab my own. When this
	occurs, OSW will likely drop support chips that don't support the same features
	that the S3 does.

2) Dead displays
	A thorn in my side has been damaged displays, I broke my display somehow in early
	december, giving me a very nice line.
![image](https://github.com/Rarisma/OpenSmartWatch/assets/49795711/bbdbea51-aabf-4230-92af-0674d041b029)
	The other day I went to resume OSW developement and now my display cable is dead.
	Dead displays are easy to fix, you just buy another one; it hurt's financially
	but thats life. Display cables are a bit different since all UK based suppliers
	are out of EYESPI cables; so looking at Adafruit Documentation an EYESPI cable
	is described as an "an 18-pin 0.5mm pitch FPC connector" so hopefully the 20
	pack of FPC Cables matching the docs will work fine when it arrives tomorrow.

3) ARM64
	I don't own a working laptop, I have a Surface Pro X (from work) and a gaming
	rig, so when ever I've left my house to go somewhere I haven't been able to
	compile or flash OSW. Previously I was able to however for the past 2+ months
	I haven't been able to compile it due to issues with the Xtensa (ESP32?)
	framework not supporting Win-ARM64; I also wasn't able to get it working with
   	x64/x86 emulation. This wasn't a massive issue, but it did prevent me a few
   	instances though when I didn't have my PC due to being away from home or the
   	time my motherboard failled a couple of months back. This isn't an issue now
   	as I've bought (and im typing this on) a ThinkPad T480 with linux. 

All of these pretty much lead to OSW's development stagnating over the few months
when paired with personal events such as Uni assessments/projects etc. With the
year ending, I expect OSW's development to pick up between now to feb and slow 
down around late Feb - May. Assuming that the prototypes don't keep breaking.

Some work has been done, so lets cover whats changed since the last post:

- Added (and removed) ESP32-S3 support.
- Updated WatchFace:
  	- Updated outdated code comments refering to 10 seconds past minute
  	- Added debugging sleep wake up cause
- Added flag to supress debug messages.
- Delay boot is no longer int (delay timer) and now a bool.
- If delay boot is true, OSW will wait for you to click a button.
- Added Input.cpp to detect two buttons.
- Started migrating from rarisma.net to github pages, the URL will remain rarisma.net.
- Inital work on switching from OpenWeatherMap forecast calls to OneCall API.
- Fix headers to successfully compile on linux. (Switching from \ to /)
- Updated Input.AwaitInput() to take an optional ms timeout.
- Delete PCBs folder since PCB work isn't ongoing until MINIMA is done.
- Delete ButtonTest.cpp
- Add layoutobject and rendertool.cpp
- updated wrong uses of #ifdefs to just be #ifs
- updated APIKeys to be strings instead of char*
- Removed Systeminfo.h and moved content into flags.h

So here's the near term roadmap:
- Finish Migrating from rarisma.net website to github pages so I don't have to pay Ionos (as much) money
- Implement OTA Updates
- Refine input code
- System Info Menu
- Weather Reports Caching

Also something I might have touched on is that I've noticed RTC drift, however I now confirmed
it. If was to fab a board I'd include an RTC module however for now I've programmed OSW to 
regrab the actual time from the RTC every three or so hours.

That's all for now, have a good one.

## Rendering Improvements (05/11/2023)

Over the past week and a bit I've been working on improving several aspects of OSW such as:   
1) Switching to use a Seeed Studio XIAO   
This took quite some work as I found that initially my code would crash before even   
hitting the welcome to OSW message. This took a day or two but I found that it was due   
to the partitioning change I made to get more app space on the feather. I've added the   
XIAO as a separate environment to the Huzzah   

I also changed to using an EYESPI cable/connector instead of pins, this made the project  
much cleaner as the display is now just a ribbon cable and as a result now the SD card   
works (or seems to at least.) This was quite problematic as I needed an EYESPI BFF for   
the XIAO to be able to use the display with it (why did they name it the BFF???) and I'm  
sure that soldering it upside down didn't help me but thanks someone I know, it now   
works correctly. (Thanks Chris!)   
2) I've done some work to clean up OSW   
	We will get into this at the end of the article   
3) OSW is now a public repo at https://github.com/Rarisma/OpenSmartWatch   
	The repo itself needs some work such as a better gitignore and fixing branches but its   
	a start.   
4) Starting work on a proper development kit.   
	We are still a long way away from building PCB but I want to be able to have a printed   
	plate to mount the screen and eventually buttons to. So I've started work on making a   
	CAD Model, this probably wont go anywhere for at least another week since I'm too busy to  
	mess with my printer until next Saturday at the earliest and I also need to measure   
	the parts it's uses.   

I've also started monitoring the power draw of OSW, and while it's not indicative of   
real world use, it should give a rough estimate though I'm skeptical so I'm not sharing   
my findings in this post until I've actually verified them.   

Here's the stuff that has changed since the last post:   
- Made following changes to boot process:   
- Power on reason is now shown (i.e powered up or woken up via GPIO)   
- Downclock CPU after booting to 80MHz to save power   
- Added code to check if RTC is already set i.e woken from deep sleep scenario   
- Updated Display:   
- Added GetTextWidth code which returns the length of a given string in pixels   
- Use define statements to save on compiled size in the future   
- Removed DisplayType Enum in favor of using a define statement in display.cpp   
- Added Serial as a valid display type   
- Updated TimeSquare to:   
- Added StandardTime watch face   
- TimeSquare will fetch updated weather every 900 seconds (15 Minutes)   
- Put ESP into sleep at the end of the update cycle until the next start of a minute  
- Added code to update display at the start of every minute.   
- Updated platformio.ini to:   
- Show timestamp of incoming log messages   
- Compile OSW with GNU C++ 17   
- Support both Adafruit Huzzah V2 and the XIAO   
- Check AllowWeather is enabled before trying weather calls   
- Removed unused timestamping code in syslog   
- Reimplemented DST option when fetching time via NTP   
- Overhauled Flags.cpp to only be a header file now, renamed some values within it   
- Updated readme   
- Geolocation will now check AllowWeather is true and has an API key.   
- Changed weather to show place names as the first four letters.   
- Very early work on an apps menu and several other views (waiting for button support)   
- Updated Geolocation to add unfinished code for weather forecasts via the OWM API   

Currently a lot of what I'm wanting to do such as OTA need user interaction, which I'm   
waiting on some resistors to arrive since I only have 10K Ohm resistors so they won't work   
I imagine getting 4 buttons to work on a single GPIO is a very hard task and may not be   
possible on just one GPIO.   

There's still some obvious room on the table for improvements into OSW in current state   
such as reducing flickering and working on code to make code less dependent on pixel counts   
I'm also going to keep monitoring power draw. It also seems like OSW is rebooting after some  
length of time so I want to investigate that too.   

One last thing, I'll be moving this over to GitHub pages late December/early Jan since my   
hosting costs are going to go from 2 quid to a tenner so screw that.   
That's all for now, have a good one.   

(PS here are some pictures of the standard time watch face, I really like the look.)   

[Image 0] [Image 1] [Image 2]
