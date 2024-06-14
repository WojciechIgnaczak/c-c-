  digitalWrite(LED_RED,HIGH);
  delay(1000);
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,HIGH);
  delay(1000);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,HIGH);
  delay(1000);
  digitalWrite(LED_GREEN,LOW);

  # $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  #define LED_RED 12
#define LED_YELLOW 11
#define LED_GREEN 10
#define POTENCJOMETR A0
int val;
void setup() {
  Serial.begin(9600);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);

  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,LOW);
}

void loop() {
val= analogRead(POTENCJOMETR);
if(val<=400){
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);
}else if(val<=800)
{
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_YELLOW,HIGH);
}else{
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,HIGH);
}
Serial.println(val);
delay(100);
}

# 
#define LED_RED 12
#define LED_YELLOW 11
#define LED_GREEN 10
#define POTENCJOMETR A0
int val;
void setup() {
  Serial.begin(9600);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);

  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,LOW);
}

void loop() {
val= analogRead(POTENCJOMETR);
if(val<=400){
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);
}else if(val<=800)
{
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_YELLOW,HIGH);
}else{
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_GREEN,HIGH);
}
Serial.println(val);
delay(100);
}

na kalse w ktorej okreslany ile przedzialow ma byc
