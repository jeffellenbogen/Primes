//For more info on prime numbers https://en.wikipedia.org/wiki/List_of_prime_numbers
//Big primes to try: 27644437, 16769023, 331777, 193939, 4409

// Create Prime factorization program that stores into an array and prints all factors including duplicates
// Implement square root instead of stopping at half the prime candidate

const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;
long dataNumber = 0;

static unsigned long start_time, time_ellapsed, toggle_timer_start;
int toggleDelay = 250;

int primeLEDpin = 12;
int notPrimeLEDpin = 7;
int testPin = 4;
bool LEDstate = true;

bool sqrtMode = false;

void getMode()
{
  Serial.println("Choose how to calculate whether an integer is prime...");
  Serial.println("1. halfCandidateMode ");
  Serial.println("2. sqrtMode");

  long modeSelected = getInput();
  if (newData)
  {
    if (modeSelected == 1)
    {
      Serial.println("modeSelected = halfCandidateMode");
      sqrtMode = true;
    }
    else if (modeSelected == 2)
    {
      Serial.println("modeSelected = sqrtMode");
      sqrtMode = false;
    }
    else
    {
      Serial.println("error! selecting sqrtMode automatically");
      sqrtMode = true;
    }
  }
  newData = false;
}


void setup()
{
  
  Serial.begin(9600);
  pinMode(primeLEDpin,OUTPUT);
  pinMode(notPrimeLEDpin,OUTPUT);
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, LOW);
  digitalWrite(primeLEDpin,LOW);
  digitalWrite(notPrimeLEDpin,LOW);
  
  getMode();
}

void loop()
{
   
   long inputedValue = getInput();
   if (newData)
   {
      bool isItPrime = checkPrime(inputedValue);
      printOutResult(inputedValue, isItPrime);
   }
}



void toggleLEDs()
{ 
    digitalWrite(primeLEDpin,LEDstate);
    digitalWrite(notPrimeLEDpin,!LEDstate);
    LEDstate = !LEDstate;
}

/**********************
* getInput will take an input from Serial and determine if an integer was input
***********************/
long getInput(void)
{
  // converting inputed string to long based on  https://forum.arduino.cc/index.php?topic=396450.0
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
   
  if (Serial.available() > 0) 
  {
      rc = Serial.read();
      if (rc != endMarker) 
      {
         receivedChars[ndx] = rc;
         ndx++;
         if (ndx >= numChars) 
         {
           ndx = numChars - 1;
         }
       }
       else 
       {
          receivedChars[ndx] = '\0'; // terminate the string
          ndx = 0;
          newData = true;
       }
   }

   if (newData == true) 
   {
      dataNumber = 0;             // new for this version
      dataNumber = atol(receivedChars);   // new for this version
   }
   return dataNumber;
}





/**********************
* checkPrime will determine if the integer is prime
**********************/
bool checkPrime(long inputedInt)
{
   Serial.println("Checking........");
   digitalWrite(primeLEDpin,LOW);
   digitalWrite(notPrimeLEDpin,LOW);
   start_time = millis();
   toggle_timer_start = start_time;
   bool isPrime = true; // assume each value of i is prime until proven otherwise. Any instance of a value of j that is less than i and greater than 1 that is a factor of i means i is Not Prime
   if (inputedInt < 2)
   {
      time_ellapsed = millis() - start_time;
      return !isPrime;
   }
   long cutOff;
   int j = 2; // the denomenator, j, starts at one less than the numerator, i.
   
   if (sqrtMode) 
     cutOff = long(sqrt(inputedInt));
   else 
     cutOff = inputedInt/2;

   while (j <= (cutOff) && isPrime) //  decrement j in the while loop until a factor (j) is found or get up to half of the number being tested for primeness.
   {
      if (inputedInt % j == 0) // means i was divisible by j and therefore has a factor, so NOT prime
        isPrime = false; // now we know i is not Prime
      j++;

      //This code below pulsed the lights on and off alternating every second, but slows the processing down considerably
      
      if (millis()-toggle_timer_start > toggleDelay)
      {
        toggle_timer_start = millis();
        toggleLEDs();
        //Serial.println("TOGGLE");
      }      
      

   }
   time_ellapsed = millis() - start_time; // comment this out if using pulsing lights during checking...

   return isPrime;
}

/**********************
* printOutResult displays information giving outcone of checkPrime
***********************/
void printOutResult(long inputedInt, bool isItPrime)
{
  Serial.print("The integer ");
  Serial.print(inputedInt);
  Serial.print(" is ");
  if(isItPrime)
  {
    Serial.println("PRIME");
    digitalWrite(primeLEDpin, HIGH);
    digitalWrite(notPrimeLEDpin, LOW);    
  }
  else
  {
    Serial.println("NOT PRIME");
    digitalWrite(primeLEDpin, LOW);
    digitalWrite(notPrimeLEDpin, HIGH);  
  }
  Serial.print("Time to determine prime or not prime is ");
  if (time_ellapsed < 1000) // display time ellapsed in milliseconds
  {
    Serial.print(time_ellapsed); 
    Serial.println(" milliseconds."); 
  }
  else //display time ellapsed in seconds rounded to the thousandth
  {
    Serial.print("about ");
    Serial.print(time_ellapsed/1000);
    Serial.print(".");
    Serial.print(time_ellapsed % 1000); 
    Serial.println(" seconds."); 
  }
    
  newData = false;
  Serial.println("");
  Serial.println("Enter an integer to determine if it is prime or not...");
  
}
