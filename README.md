# ServoAnimate
An arduino library to animate servos using classic keframe animations

# Usage
## Tacks
tracks are arrays of servo angles
## Routine
a routine is an bunch of tracks
```c++
int* track = new int[3]{0,90,0};
int* track2 = new int[3]{0,30,0};
int** tracks = new int*[5]{track,track2,track,track,track};
routines[0] = new Routine(tracks,3);
```
## Animation Player
plays a routine from the list of routines called `routines`

### Play an animation
```c++
p = new AnimationPlayer(5,3) //(5 servos, each playing a track of length 3)
routinees[0] = new Routine(tracks,3)// tracks from the previous example
p->Play(0,3000) // play routines[0] in 3 secs
```
### In the loop function
```c++
if(p->isPlaying){ //is an animation running
  p-> Update();
}
```
## Servos
servos one through n are defined in an array called servos
```c++
servos[0] = Servo();
servos[0].attach(9); //attach to arduino pin 9
//..
//..
servos[4] = Servo();
servos[4].attach(13);
```
