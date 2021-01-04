# ros_modbus

ros_modbus used libmodbus library can do write and read register function.

OS: Linux Ubuntu.

Software: Robot Operating Sysyem, libmodbus.

------

Step1. Download libmodbus.

``` bash
$ wget http://libmodbus.org/site_media/build/libmodbus-3.0.5.tar.gz
```

``` bash
$ sudo chmod 755 libmodbus-3.1.6.tar.gz
```

``` bash
$ tar zxvf libmodbus-3.1.6.tar.gz -C .
```

``` bash
$ cd libmodbus-3.1.6/
```

``` bash
$ ./configure
```

``` bash
$ make
```

``` bash
$ sudo make install
```

Step2. use ros_modbus.

``` bash
$ cd <catkin_ws>/src
```

``` bash
$ git clone https://github.com/qaz9517532846/ros_modbus.git
```

``` bash
$ cd ..
```

``` bash
$ catkin_make
```

-----

Step3. Run use ros_modbus.

``` bash
$ rosrun ros_modbus ros_modbus_tcp
```

-----

# Reference

[1]. libmodbus. https://libmodbus.org/documentation/

------

This repository is for your reference only. copying, patent application, academic journals are strictly prohibited.

Copyright © 2021 ZM Robotics Software Laboratory.
