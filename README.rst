udev_paranoia
=============

Have USB ports? Don't want to fill em with epoxy? Don't want to get hit
with a one of the many bad USB bad things. Use this to block new USB devices by
default. 

What it does
------------
.. code-block:: bash
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

Installation
------------
Run the following (installs to /opt/udev_paranoia/ by default):

.. code-block:: bash

    $ make
    $ sudo make install

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
