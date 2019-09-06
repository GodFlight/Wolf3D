# Raycast engine

[Download demo](https://github.com/dolovnyak/raycast-engine/raw/master/raycast_demo.zip)
###

![Image alt](https://github.com/GodFlight/Wolf3D/raw/master/image/1.png)
![Image alt](https://github.com/GodFlight/Wolf3D/raw/master/image/2.png)
![Image alt](https://github.com/GodFlight/Wolf3D/raw/master/image/3.png)
Partial implementation of the engine **"Wolfenstein 3D engine"** and its improvement using a cross-platform library for working with multimedia **"SDL2"**.


## Compiling and running
Runs on **OSX**.  
Run `make` and programm will compile.  
Run it with `./wolf3d`.  

## Controls
`ESC` - Close the program.  
`W`/`A`/`S`/`D` - Movement in space.    
`RIGHT` - Camera rotation to the right.  
`LEFT` - Camera rotation to the left.  
`SHIFT` - Acceleration.   
`SPACE` - Turn on/off music.  

## Map file format

```
1   1   1   1  
1   910 9   1  
1   0   0   1  
1   999 0   1  
1   1   1   1  
```

`0`         - **void, wall/flr cast ignore it, physic ignore it**.  
`1`-`99`    - **default walls without states and interactions, can be place several identical id**.  
`900`-`998` - **objects**.  
`999`       - **player position**.
