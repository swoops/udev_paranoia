udev_paranoia
=============

This is the old version! There is a new version that is much safer and done
better. Check it out in the main branch.

This program is aimed at calming my paranoia caused by having a USB port that I can
not see. I have been able to compromise computers in seconds with my Rubber Ducky
(http://hakshop.myshopify.com/products/usb-rubber-ducky-deluxe?variant=353378649)
and I don't want the same to happen to me. This program does nothing but
modify the file "/etc/udev/rules.d/11-to_rule_all.rules" (hereafter refered to as
rule-11).  See "Program Flow" below for details.


WARNING: It is your responsibility to remove this rule before shutdown. If 
left in place, you will likely encounter an error upon boot.  Simply
remove the rule-11 file to fix this error.  See instillation instructions.  

Program Flow
------------

  * udev_paranoia exits
      udev_paranoia puts a "block all USB devices" rule inside of the rule-11
      file.
  * block all USB rule in effect and udev_paranoia run without any arguments
      The contents of the rule-11 file are replaced with a rule that denies any
      USB keyboard. udev_paranoia then sleeps 10 seconds and exits.
  * rule-11 file exists and any argument is given (yeah I am lazy):
      udev_paranoia replaces the rule-11 file with one that will allow ANY 
	  USB device. It then sleeps 10 seconds and exits.

Installation
------------
Run the following (installs to /opt/udev_paranoia/ by default):

.. code-block:: bash

    $ make
    $ sudo make install

To add an init script that will remove the rule-11 file at shutdown do this
instead:

.. code-block:: bash

    $ make
    $ sudo make install_init

This is separate because I don't have a great deal of confidence init 
(haha) so please let me know if it messes up.  When I go to Jessie and use
Systemd I will update this to use Systemd as well.


What? Why?
----------
I work for a security company where we are encouraged to break into each
others workstations. We believe a security system left untested can not be
trusted, and this philosophy extends to our employees. This means I keep a USB HID
that will, upon being plugged in, type commands that grant me control of the
computer. No one leaves their computers unlocked :). However, it only takes
2 seconds for the payload to run. Do you ever look away from your computer
for 2 seconds? Can you see EVERY USB device plugged into your computer right now?
Are you sure no one added an extra USB hub behind your computer, or that there
aren't USB extension cables leading out under your desk? Are you vigilant from 9 to
5, 5 days a week? I can't answer all those questions yes, so I made a udev
rule to block ALL USB devices. Unfortunately, this causes a fellow employee to come
around and unplug my fancy USB keyboard, which causes me a big headache. This program
was then made to streamline the process of adding legitimate USB devices.

Security
--------
This program is meant to be run with setuid. That makes it a good target for
privilege escalation. I do not think this program can be used to escalate
privileges if the permissions are set on it correctly (do not allow write on
this file), but "Let the one who thinks he is standing be wary he does not
fall". If you find any vulnerabilities in this program please contact me and
I will try to fix it. I use this program on a daily basis, so I have a stake
in it as well.

Authors
-------
udev_paranoia is developed by Dennis Goodlett (dennis@hurricanelabs.com) and 
can be found here: http://github.com/swoops/udev_paranoia This software is 
released under the GNU Public General License v3 and is provided "as is" 
without warranty of any kind, neither express nor implied.
