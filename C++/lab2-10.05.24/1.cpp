//napisz klase w ktorej bedzie metoda addPin(), wywolanie tej metody do tablicy leds  ktora jest w tej klasie zostanie dodany element


class LedController{
    private:
  		const int capacity =2; 
	    int ledNumber;
	    int leds[2];
  	public:
    	LedController(){ledNumber=0;}
        bool addPin(int x)
        {
          if(ledNumber<capacity){
            leds[ledNumber]=x;
            ledNumber++;
            return true;
          }else{
          	return false;
          }
        }
};
// ==========================================================
const int ledYellow = 7;
const int ledGreen = 6;
const int ledRed = 5;


class LedController{
    private:
  		const int capacity =2; 
	    int ledNumber;
	    int leds[2];
  	public:
    	LedController(){ledNumber=0;}
        bool addPin(int x)
        {
          if(ledNumber<capacity){
            leds[ledNumber]=x;
            ledNumber++;
            pinMode(x,OUTPUT);
            return true;
          }else{
          	return false;
          }
        }
  		void turnALLLEDs(uint8_t state=HIGH);
};


void LedController::turnALLLEDs(uint8_t state){
  for (int i=0;i<ledNumber;i++){
    	digitalWrite(leds[i],state);}
  }


LedController ledContr;
                           
                           
void setup()
{
  Serial.begin(9600);
  
  bool result= ledContr.addPin(ledRed);
  if (!result){
  	Serial.println("No space for LED RED.");
  }
  result= ledContr.addPin(ledGreen);
  if (!result){
  	Serial.println("No space for LED GREEN.");
  }
  result= ledContr.addPin(ledYellow);
  if (!result){
  	Serial.println("No space for LED YELLOW.");
  }
}


void loop()
{
  ledContr.turnALLLEDs();
  delay(1000);
  ledContr.turnALLLEDs(LOW);
  delay(500);
   
}
//========================================================================================
const int ledYellow = 7;
const int ledGreen = 6;
const int ledRed = 5;


class LedController{
    private:
  		int capacity; 
	    int ledNumber;
	    int *leds;
  	public:
    	LedController(int capacity){
          	ledNumber=0;
        	this->capacity=capacity;
          	leds= new int[capacity];
        }
        bool addPin(int x)
        {
          if(ledNumber<capacity){
            leds[ledNumber]=x;
            ledNumber++;
            pinMode(x,OUTPUT);
            return true;
          }else{
          	return false;
          }
        }
  		void turnALLLEDs(uint8_t state=HIGH);
};


void LedController::turnALLLEDs(uint8_t state){
  for (int i=0;i<ledNumber;i++){
    	digitalWrite(leds[i],state);}
  }


LedController ledContr(2);
                           
                           
void setup()
{
  Serial.begin(9600);
  
  bool result= ledContr.addPin(ledRed);
  if (!result){
  	Serial.println("No space for LED RED.");
  }
  result= ledContr.addPin(ledGreen);
  if (!result){
  	Serial.println("No space for LED GREEN.");
  }
  result= ledContr.addPin(ledYellow);
  if (!result){
  	Serial.println("No space for LED YELLOW.");
  }
}


void loop()
{
  ledContr.turnALLLEDs();
  delay(1000);
  ledContr.turnALLLEDs(LOW);
  delay(500);
   
}
//======================
// C++ code
//
const int ledYellow = 7;
const int ledGreen = 6;
const int ledRed = 5;


class LedController{
    private:
  		int capacity; 
	    int ledNumber;
	    int *leds;
  	public:
    	LedController(int capacity){
          	ledNumber=0;
        	this->capacity=capacity;
          	leds= new int[capacity];
        }
  		~LedController()
        {
        	delete [] leds;
        }
        bool addPin(int x)
        {
          if(ledNumber<capacity){
            leds[ledNumber]=x;
            ledNumber++;
            pinMode(x,OUTPUT);
            return true;
          }else{
          	return false;
          }
        }
  		void turnALLLEDs(uint8_t state=HIGH);
};


void LedController::turnALLLEDs(uint8_t state){
  for (int i=0;i<ledNumber;i++){
    	digitalWrite(leds[i],state);}
  }


                           
                           
void setup()
{
  Serial.begin(9600);

}


void loop()
{
  
  LedController ledContr(200);
  bool result= ledContr.addPin(ledRed);
  if (!result){
  	Serial.println("No space for LED RED.");
  }
  result= ledContr.addPin(ledGreen);
  if (!result){
  	Serial.println("No space for LED GREEN.");
  }
  result= ledContr.addPin(ledYellow);
  if (!result){
  	Serial.println("No space for LED YELLOW.");
  }
  ledContr.turnALLLEDs();
  delay(1000);
  ledContr.turnALLLEDs(LOW);
  delay(500);
  Serial.println("ala ma kota i Arduino");
  
}
//==========================================================
//aktywacja i dezaktywacja diody

const int ledRed = 5;
const int ledGreen = 6;
const int ledYellow = 7;


class LedController {
  private:
    int capacity;
    int ledNumber;
    int *leds;
    bool *active;
  public:
    LedController(int capacity) {
      this->capacity = capacity;                           
      ledNumber = 0;
      leds = new int[capacity];
      active = new bool[capacity];
    }
    ~LedController() {		//destruktor
      delete [] leds; 		//free() z języka C
      delete [] active;
    }
    bool addPin(int p);
    void turnAllLEDs(uint8_t state = HIGH); 
    void activateLED(uint8_t p, bool active = true);
};

bool LedController::addPin(int p) {
  int index = ledNumber;
  if (index < capacity) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
    leds[index] = p;
    active[index] = true;
    ledNumber += 1;
    return true;
  }
  return false;
}

void LedController::turnAllLEDs(uint8_t state) {
  for (int i=0; i<ledNumber; i++) {
    if (active[i]){
      digitalWrite(leds[i], state);
    }
  }  
}

void LedController::activateLED(uint8_t p, bool active) {
  for(int i=0; i<ledNumber; i++) {
    if (leds[i] == p){
      this->active[i] = active;
      break;
    }
  }
}




LedController ledContr(5);

void setup() {
  Serial.begin(9600);	//komunikacja przez konsolę szeregową
  bool result = ledContr.addPin(ledRed);
  if (!result){
    Serial.println("No space for red LED");
  }
  
  result = ledContr.addPin(ledGreen);
  if (!result){
    Serial.println("No space for green LED");
  }
  
  result = ledContr.addPin(ledYellow);
  if (!result){
    Serial.println("No space for yellow LED");
  }
  
  ledContr.activateLED(ledGreen, false);
}

void loop() {
  uint8_t l = rand()% 3+5;
  ledContr.activateLED(l, false);
  ledContr.turnAllLEDs();
  delay(1000);
  ledContr.turnAllLEDs(LOW);
  delay(500);
  ledContr.activateLED(l);
}

// ========================================================================
const int ledRed = 5;
const int ledGreen = 6;
const int ledYellow = 7;


class LedController {
  private:
    int capacity;
    int ledNumber;
    int *leds;
    bool *active;
  public:
    LedController(int capacity) {
      this->capacity = capacity;                           
      ledNumber = 0;
      leds = new int[capacity];
      active = new bool[capacity];
    }
    ~LedController() {		//destruktor
      delete [] leds; 		//free() z języka C
      delete [] active;
    }
    bool addPin(int p);
    void turnAllLEDs(uint8_t state = HIGH); 
    void activateLED(uint8_t p, bool active = true);
};

bool LedController::addPin(int p) {
  int index = ledNumber;
  if (index < capacity) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
    leds[index] = p;
    active[index] = true;
    ledNumber += 1;
    return true;
  }
  return false;
}

void LedController::turnAllLEDs(uint8_t state) {
  for (int i=0; i<ledNumber; i++) {
    if (active[i]){
      digitalWrite(leds[i], state);
    }
  }  
}

void LedController::activateLED(uint8_t p, bool active) {
  for(int i=0; i<ledNumber; i++) {
    if (leds[i] == p){
      this->active[i] = active;
      break;
    }
  }
}




LedController ledContr(5);

void setup() {
  Serial.begin(9600);	//komunikacja przez konsolę szeregową
  bool result = ledContr.addPin(ledRed);
  if (!result){
    Serial.println("No space for red LED");
  }
  
  result = ledContr.addPin(ledGreen);
  if (!result){
    Serial.println("No space for green LED");
  }
  
  result = ledContr.addPin(ledYellow);
  if (!result){
    Serial.println("No space for yellow LED");
  }
  
  ledContr.activateLED(ledGreen, false);
}

void loop() {
  uint8_t l = rand()% 3+5;
  ledContr.activateLED(l, false);
  ledContr.turnAllLEDs();
  delay(1000);
  ledContr.turnAllLEDs(LOW);
  delay(500);
  ledContr.activateLED(l);
}
// przebuduj aby zarzadzał obuiekami typu led powinna byc tablica  Led *leds;
class LED{
    int pin;
    bool active;
public:
//ustawic stan itd. aby program dziala tak samo ale klasy maja robic to co maja robic
};



//


class LED {
  int pin;
  bool active;

public:
  LED(int pin) : pin(pin), active(false) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

 void setState(bool state) {
    active = state;
    if (state) {
        digitalWrite(pin, HIGH); // Włącz LED, gdy state == true
    } else {
        digitalWrite(pin, LOW); // Wyłącz LED, gdy state == false
    }
}


  int getPin() const {
    return pin;
  }
};

class LedController {
  int capacity;
  int ledNumber;
  LED *leds;

public:
  LedController(int capacity) : capacity(capacity), ledNumber(0) {
    leds = new LED [capacity];
  }

  ~LedController() {
    for (int i = 0; i < ledNumber; ++i) {
      delete leds[i];
    }
    delete[] leds;
  }

  bool addLED(int pin) {
    if (ledNumber < capacity) {
      leds[ledNumber++] = new LED(pin);
      return true;
    }
    return false;
  }

  void turnAllLEDs(bool state = true) {
    for (int i = 0; i < ledNumber; ++i) {
      leds[i]->setState(state);
    }
  }

  void activateLED(int pin, bool active) {
    for (int i = 0; i < ledNumber; ++i) {
      if (leds[i]->getPin() == pin) {
        leds[i]->setState(active);
        return; // Zakończ po ustawieniu stanu diody
      }
    }
  }
};

const int ledRed = 5;
const int ledGreen = 6;
const int ledYellow = 7;

LedController ledContr(5);

void setup() {
  Serial.begin(9600);

  bool result = ledContr.addLED(ledRed);
  if (!result) {
    Serial.println("No space for red LED");
  }

  result = ledContr.addLED(ledGreen);
  if (!result) {
    Serial.println("No space for green LED");
  }

  result = ledContr.addLED(ledYellow);
  if (!result) {
    Serial.println("No space for yellow LED");
  }

  ledContr.activateLED(ledGreen, false);
}

void loop() {
  uint8_t l = rand() % 3 + 5;
  ledContr.activateLED(l, false);
  ledContr.turnAllLEDs();
  delay(1000);
  ledContr.turnAllLEDs(false);
  delay(500);
  ledContr.activateLED(l, true); // Aktywuj ponownie diodę o numerze pinu l
}
