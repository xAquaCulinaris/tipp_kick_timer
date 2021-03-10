#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



#define INCREMENT_PLAYER1_BTN 8
#define DECREMENT_PLAYER1_BTN 9

#define INCREMENT_PLAYER2_BTN 4
#define DECREMENT_PLAYER2_BTN 3

#define START_TIMER_BTN 6



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


bool timer_running = false;

int player1_score = 0;
int player2_score = 0;


//how long total game 
int total_time = 300;

int time_left = 300;


int minutes = 0;
int seconds = 0;


//get value when start button pressed first time
int start_time = 0;

//if timer is paused need to count seconds! (not implemented)
int pause_time = 0;


void setup() {
  Serial.begin(115200);


  //Button pin outs
  pinMode(INCREMENT_PLAYER1_BTN, INPUT_PULLUP);
  pinMode(DECREMENT_PLAYER1_BTN, INPUT_PULLUP);

  pinMode(INCREMENT_PLAYER2_BTN, INPUT_PULLUP);
  pinMode(DECREMENT_PLAYER2_BTN, INPUT_PULLUP);

  pinMode(START_TIMER_BTN, INPUT_PULLUP);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setTextColor(WHITE);

  
 convert_time();
}


void update_display() {
  //clear
  display.clearDisplay();


  //score
  if (player1_score < 10 && player2_score < 10) {
    display.setTextSize(5);
    display.setCursor(20, 0);
  } else {
    display.setTextSize(4);
    display.setCursor(0, 0);
  }
  
  
  display.print(player1_score);
  display.print(":");
  display.print(player2_score);


  //time
  display.setTextSize(2);
  display.setCursor(33, 50);
  
  //minutes
  if (minutes < 10) display.print("0");
  display.print(minutes);
  display.print(":");
  //seconds
  if (seconds < 10) display.print("0");
  display.print(seconds);
  display.display();
}

void convert_time() {
  seconds = time_left % 60;
  minutes = time_left / 60;

  update_display();
}


void increment_player1_score() {
  player1_score += 1;
  update_display();
}

void decrement_player1_score() {
  if (player1_score > 0) {
    player1_score = player1_score - 1;
    update_display();
  }
}

void increment_player2_score() {
  player2_score += 1;
  update_display();
}

void decrement_player2_score() {
  if (player2_score > 0) {
    player2_score = player2_score - 1;
    update_display();
  }
}

bool countdown() {
  int time_played = (millis() - start_time) / 1000;
  time_left = total_time - time_played + pause_time;

  if (time_left <= 0) {
    time_left = 0; 
  }

  convert_time();
}





void loop() {

  if (timer_running) {
    countdown();
  }
  

  if(digitalRead(INCREMENT_PLAYER1_BTN) == LOW) {
    increment_player1_score();
    delay(100);
  }

  if(digitalRead(DECREMENT_PLAYER1_BTN) == LOW) {
    increment_player1_score();
    delay(100);
  }

  if(digitalRead(INCREMENT_PLAYER2_BTN) == LOW) {
    increment_player2_score();
    delay(100);
  }

  if(digitalRead(DECREMENT_PLAYER2_BTN) == LOW) {
    increment_player2_score();
    delay(100);
  }

  if(digitalRead(START_TIMER_BTN) == LOW) {
    if (total_time != time_left) {
      //need to put on first timer start
      start_time = millis();
    }
    
    timer_running = !timer_running;
    delay(100);
  }


  
}
