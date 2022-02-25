
#include <Servo.h>


class Routine{
  public:
  int count;
  Routine(){}
   Routine(int** frames,int count){
    this->frames = frames;
    this->count=count;
  }
  

  int GetAngle(int total_time,int current_time,int track_id){
    current_time%=total_time;
    int current_frame = (int)((((float)current_time)/((float)total_time))*(count-1));
    
    int frame_duration=total_time/(count-1);
    float subframeposition = ((float)(current_time%frame_duration))/((float)frame_duration);
    subframeposition=min(subframeposition,0.999);
    int start_angle = frames[track_id][current_frame];
    int end_angle = frames[track_id][current_frame+1];
    int range = end_angle-start_angle;
    float angle = start_angle+(range*subframeposition);
    Serial.print(current_frame);
    Serial.print(" ");
    Serial.print(((int)angle));
    Serial.print(" ");
    Serial.print(start_angle);
    Serial.print("->");
    Serial.print(end_angle);
    Serial.print(" ");
    Serial.println(subframeposition);
 
    return (int) angle;
  }
  int** frames;
};

const Routine* routines[5];


class AnimationPlayer{
  public:
  int current=0;
  bool isPlaying=false;
  int st;
  int dur;
  int* last_angles;
  int servo_count;
  Servo* s1;
  AnimationPlayer(int servo_count,int spid){
    servos = new Servo[servo_count];
    last_angles = new int[servo_count];
     this->servo_count=servo_count;
    for(int i=0;i<servo_count;i++){
      servos[i] = Servo();
      servos[i].attach(spid+i);
    }
    LoadRoutines();
    Reset();
    
  }
  void LoadRoutines(){
    
  }
  void Play(int id,int duration){
    
    current=id;
    dur=duration;
    st=millis();
    isPlaying=true;
  }
  void Reset(){
    for(int i =0;i<servo_count;i++){
      last_angles[i]=0;
    }
  }
  void Update(){
    int ct=millis();
    if(isPlaying&&ct-st<dur){
      
      for(int i =0;i<servo_count;i++){
        int angle = routines[current]->GetAngle(dur,ct-st,i);
        if(angle!=last_angles[i]){
          
          servos[i].write(angle);
          last_angles[i]=angle;

        }
      }
    }else{
      isPlaying=false;
      //Reset();
    }
    
  }
  Servo* servos;
};

AnimationPlayer* p;
void setup() {
  int* track = new int[3]{0,90,0};
  int* track2 = new int[3]{0,30,0};
  int** tracks = new int*[5]{track,track2,track,track,track};
  routines[0] = new Routine(tracks,3);

  
  Serial.begin(9600);
  p = new AnimationPlayer(5,3);
 
}

void loop() {
   
    if(p->isPlaying){
      p->Update();
    }else{
      p->Play(0,3000);
    }
   
 }
