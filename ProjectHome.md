Command line tool that uses AMD ADL OverDrive5 interface to control power and fan speed of their GPU boards.

Works on Windows and Linux (if video driver is loaded).

Examples:
<pre>
>overdrive5 -h<br>
Overdrive5 v1.1 - ATI/AMD ADL OverDrive5 Tool<br>
Usage: overdrive5.exe [options]<br>
Options:<br>
-h                      - help<br>
-l                      - list adapters and thermal controllers<br>
-a <#>                  - use adapter <#><br>
-c <#>                  - use thermal controller <#><br>
-f                      - get fan speed<br>
-F <#>                  - set fan speed to <#> %<br>
-J <#>                  - set fan speed to <#> RPM<br>
-g <#>                  - monitor fan speed for <#> seconds<br>
-G                      - set default fan speed<br>
-q                      - get performance levels<br>
-Q                      - get default performance levels<br>
-A                      - get current activity<br>
-p <clk/mem/vddc>       - add a performance level<br>
-P                      - set the performance levels<br>
-S <clk/mem/vddc>       - set the highest performance level<br>
-D                      - set default performance levels<br>
-t                      - get the temperature<br>
-T <#>                  - monitor the temperature for <#> seconds<br>
-w                      - get power control info.<br>
-W <#>                  - set power control value<br>
-v <#>                  - set verbosity level to <#><br>
<br>
>overdrive5 -Aqft<br>
Current Activity:<br>
Engine Clock       = 157.00 MHz<br>
Memory Clock       = 300.00 MHz<br>
Vddc               = 1.062 V<br>
Activity           = 0%<br>
Performance Level  = 0<br>
Bus Speed          = 2.50 GT/s<br>
Bus Lanes          = 16/16<br>
Overdrive parameters:<br>
Number of Performance Levels = 3<br>
Activity Reporting Supported = Yes<br>
Discrete Performance Levels  = Yes<br>
Engine Clock =   80.00 - 1200.00 step   5.00 MHz<br>
Memory Clock =  150.00 - 1400.00 step   5.00 MHz<br>
Vddc         =   1.062 -   1.212 step   0.005 V<br>
Performance level 0:<br>
Engine Clock = 157.00 MHz<br>
Memory Clock = 300.00 MHz<br>
Vddc         = 1.062 V<br>
Performance level 1:<br>
Engine Clock = 600.00 MHz<br>
Memory Clock = 900.00 MHz<br>
Vddc         = 1.112 V<br>
Performance level 2:<br>
Engine Clock = 800.00 MHz<br>
Memory Clock = 1200.00 MHz<br>
Vddc         = 1.212 V<br>
Fan Speed Range = 0 - 100 % or 800 - 5100 RPM, flags = 0xf<br>
Fan Speed = 21% = 1112 RPM, flags = 0x0,0<br>
Temperature = 40.0 C<br>
</pre>
To change performance level 2:
<pre>
>overdrive5 -S 850/1200/1.2 -q<br>
Overdrive parameters:<br>
Number of Performance Levels = 3<br>
Activity Reporting Supported = Yes<br>
Discrete Performance Levels  = Yes<br>
Engine Clock =   80.00 - 1200.00 step   5.00 MHz<br>
Memory Clock =  150.00 - 1400.00 step   5.00 MHz<br>
Vddc         =   1.062 -   1.212 step   0.005 V<br>
Performance level 0:<br>
Engine Clock = 157.00 MHz<br>
Memory Clock = 300.00 MHz<br>
Vddc         = 1.062 V<br>
Performance level 1:<br>
Engine Clock = 600.00 MHz<br>
Memory Clock = 900.00 MHz<br>
Vddc         = 1.112 V<br>
Performance level 2:<br>
Engine Clock = 850.00 MHz<br>
Memory Clock = 1200.00 MHz<br>
Vddc         = 1.200 V<br>
</pre>
To set all performance levels:
<pre>
>overdrive5 -p 157/300/1.062 -p 600/900/1.112 -p 850/1200/1.212 -P<br>
</pre>

To compile:
  1. Set environment variable ADLSDKROOT to point to ADL SDK.
  1. Run build-win.cmd from a VisualStudio/SDK command prompt or build-lnx.sh from Linux