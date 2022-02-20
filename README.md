[![DDraceNetwork](https://ddnet.tw/ddnet-small.png)](https://ddnet.tw) [![](https://github.com/ddnet/ddnet/workflows/Build/badge.svg)](https://github.com/ddnet/ddnet/actions?query=workflow%3ABuild+event%3Apush+branch%3Amaster)

### Taters custom ddnet client with some small modifications

# Features:
### **Display frozen tees in your team on your HUD** 

&nbsp;&nbsp;&nbsp;&nbsp;**-tc_frozen_tees_display**
```
0 - off
1 - on
2 - on + show skin of frozen tees
```

&nbsp;&nbsp;&nbsp;&nbsp;**-tc_max_frozen_display_rows**
```
(1 - 10) adjust the maximum number of tees displayed
```

&nbsp;&nbsp;&nbsp;&nbsp;**-tc_frozen_tees_text**
```
0 - off
1 - on minimal text version of frozen tee HUD
```

### **KoG cl_prediction_margin PATCH**
```
default: 10
cl_prediction_margin will work on KoG, however your hammer will be delayed more as you increase the margin
set this between 15 and 25 if you are having lag, you can put it on a bind if it messes too much with your hammer
```

### **cl_run_on_join works with console**

&nbsp;&nbsp;&nbsp;&nbsp;**-tc_run_on_join_console**
```
0 - output command to chat (normal)
1 - output command to console
```

### **KoG Spectator skin fix**
&nbsp;&nbsp;&nbsp;&nbsp;**-tc_kog_spec_skin**
```
0 - off
1 - on
```

### **Enter freeze delay fix (WIP)**
&nbsp;&nbsp;&nbsp;&nbsp;**-tc_freeze_update_fix**
```
0 - normal
1 - on, you will change to ninja skin as soon as you enter freeze
```

### **Reduce Unfreeze Delay on high ping servers (EXPERIMENTAL)**
&nbsp;&nbsp;&nbsp;&nbsp;**-tc_unfreeze_delay_helper**
```
0 - off
1 - on, removes a portion of the delay after you get hammered/saved on a high ping server. 

ONLY USE ON GORES MAPS! May cause jittering when using with dummy!
```
&nbsp;&nbsp;&nbsp;&nbsp;**-tc_unfreeze_helper_percent**
```
(0-90) default: 30. Choose what percent of your ping should attempt to be removed from the unfreeze delay. 
```
&nbsp;&nbsp;&nbsp;&nbsp;**-tc_unfreeze_helper_limit**
```
(0-500) default: 45. The maximum amount of delay that will be removed, regardless of ping. 
Higher values will likely cause extra jittering after you are unfrozen
```


# Installation:

Download the exe from https://github.com/sjrc6/ddnet/releases/, or build it using the build instuctions from the main repository. 
