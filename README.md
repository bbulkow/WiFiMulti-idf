# WiFiMulti-idf

# It doesn't work yet

I'm pretty sure I've got include path problems still. Working!

# TL;DR

ESP-IDF component with the WiFi Multi interface ( mostly ) from Arduino.

ESP-IDF 4.1 or better!

Pull requests welcome.

# Why we need WiFiMulti-idf

The ESP32 is a pretty great SOC package. It has two
cores, 240Mhz speed, a meg of DRAM ( sorta ), low power mode, wifi and bluetooth, and can be had in pre-built 
modules at prices between $24 ( Adafruit, Sparkfun ), $10 (Espressif-manufactured boards through 
Mauser and Digikey), or 'knock off' boards for $4 from AliExpress as of 2020.

What's great about ESP32 is the Wifi and the Bluetooth!

Yes, the ESP-IDF wifi interfaces are poor. They mimic the basic Arduino ( and other )
Wifi interfaces that allow you to attach to an AP where you know the password.

Most times, you have a list of APs. The one for your installation location, the 
one from your debugging location, and a backup safety one ( I use my phone ),
because once you get used to debugging over wifi, you don't want to go back.

Thus, I've started a project to get more of the WiFi Multi experience.

# TL;DR about this repo

This repo supports ESP-IDF 4.1 and better. As of this writing, ESP-IDF 4.2 is released,
and master is somewhere beyond that.

Espressif, in its infinite wisdom, has decided to create breaking API changes in minor releases.

The big one, in 4.1, is to separate out the IP interface into something more generic.
While that's a great step forward, it's unclear at the moment the best
way to support 4.0 and 4.1. Since going all the way back to 3.3 is even harder,
I've decided to only support 4.1 and better --- and there's a big honking check,
so compiles fail in an obvious way.

# Gotchas of the ESP system

It's multicore! That means the standard embedded tricks of playing a bit
fast and loose with pointers ( like returning a pointer knowing you won't
get interruped ) are in use here. I've been very careful to make it right.

Scans and connects can't happen at the same time. If you are connecting and try
to scan, it fails, and vice versa. Right now, connects are pioritized way above
scans. I'm not sure that's super right yet, because what should happen if you want
to connect and are scanning is that the scan should terminate.

There is no single clear error returned on an Auth failure. Trying bad passwords
with a couple of my favorite APs resulted generally in 4th phase handshake timeouts,
which were generally considered timeouts of different sorts. That's OK, and probably
better for security, but means we shouldn't try to have logic that checks
for an auth failure and doesn't try again.

# todos

There are lots!

Need to support removing APs. This requires more care in memory managing the list
of APs, right now I cut corners because there is no remove.

Need to support hidden access points. There are plenty of cases where you'd like
to have a hidden AP for an art project, they're just a little more secure.

Mode to support open APs. It would be nice to have a flag that says "try to attach"
and it'll attempt to attach to open APs.

Check to see that internet is actually working, and fall over to another AP
if not in a reasonable time. Right now, we accept that the connection has succeeded
when the AP responds. You might never get an IP address, you might never connect.

Add a 'my network's not working' API call. While it would be good to check if the
open internet is working ( ie, connect to a well known service over HTTP ),
the acid test is if _your_ service works, so an API call which says "not working"
from the application level is far better.

Support shutting down

Test adding an AP while running ( coded to work but not tested )

Support a "low power mode" which uses the low power defaults, and some
kind of shutdowns
