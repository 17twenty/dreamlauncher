Dream Launcher
===============

USB Kernel Module and User space app to drive the Dream Cheeky USB Thunder Missile Launcher and accompanies this [Feabhas blog article](http://blog.feabhas.com/2012/10/i-dream-of-a-cheeky-missile-launcher/).

This was based on the work by Matthias Vallentin and his blog article [1] but updated for the newer launcher and with auto registration of the device nodes and tweaks along my way.

Resources:<br />
[1] http://matthias.vallentin.net/blog/2007/04/writing-a-linux-kernel-driver-for-an-unknown-usb-device/<br />
http://www.linuxjournal.com/article/7353?page=0,1<br />
http://blog.milford.io/2012/01/code-example-linux-pyusb-the-dream-cheeky-thunderstorm-usb-missile-launcher/<br />
http://www.linuxforu.com/2011/12/data-transfers-to-from-usb-devices/

Guide:
 * `git clone git@github.com:feabhas/dreamlauncher.git`
 * `make`
 * `insmod launcher_driver.ko`
 * Make sure that usbhid hasn't stolen your device (see blog!)
 * `sudo ./launcher_control -f`