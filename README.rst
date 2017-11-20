udev_paranoia
=============

Using linux? Have USB ports? Don't want to get hit with one of the many evil
USB devices out there (poisiontap_, usbdriveby_, ducky_, badusb_ and
network_attacks_). Yet you don't want to fill your USB ports with epoxy? Then
use this udev_paranoia to block all new USB devices with a UDEV rule and allow
them temporarily, only as you need them.


.. _poisiontap: PoisonTap
.. _usbdriveby: http://samy.pl/usbdriveby/
.. _ducky: https://hakshop.com/products/usb-rubber-ducky-deluxe
.. _badusb: https://opensource.srlabs.de/projects/badusb
.. _network_attacks: https://www.sternsecurity.com/blog/local-network-attacks-llmnr-and-nbt-ns-poisoning

What it does
------------
.. code-block::

    $ /opt/udev_paranoia -h
    Usage:
    ./udev_paranoia [FLAGS]
    FLAGS:
        -h:   help menu
        -a:   allow all EVERYTHING
        -i:   block only input/hid/hidraw devices
        -b:   block EVERYTHING
        -r:   read current permissions
        -t:   temp permission change wait time (0 for permanent))

By default udev_paranoia wants to block all USB devices. When you want to plug
somethething in run it with -a or -i to temporarily allow USB devices. Adding a
-t0 will perminently allow those devices. Use -r to check what the current status.

The rule is saved in the /tmp directory. So it will disappear upon reboot. This
means the rule will not affect the booting process. It also means you need to
remember (or script) the initialization of the rules. 


Installation
------------
Run the following:

.. code-block:: 

    $ make
    $ sudo make install
    
Uninstall
---------

.. code-block:: 

    $ sudo make uninstall

How it works
------------
A new udev rule is add. The rule can be found in the 11-udev_paranoia.rules
file. This rule checks to see if udev_paranoia is in use via the existence of
the permissions file (/tmp/udev_paranoia_protection). If the file exists then
the rule consults the udev_paranoia_master program before allowing a new device.

Authors
-------
udev_paranoia is developed by Dennis Goodlett (dennis@hurricanelabs.com) and 
can be found here: http://github.com/swoops/udev_paranoia This software is 
released under the GNU Public General License v3 and is provided "as is" 
without warranty of any kind, neither express nor implied.
