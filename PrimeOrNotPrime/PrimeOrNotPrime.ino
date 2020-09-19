const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;
long dataNumber = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter an integer to determine if it is prime or not...");
}

void loop()
{
   long inputedValue = getInputAsLong();
   if (newData)
   {
      bool isItPrime = checkPrime(inputedValue);
      printOutResult(inputedValue, isItPrime);
   }
}


/**********************
* getInteger will take an input from Serial and determine if an integer was input
***********************/
long getInputAsLong(void)
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
   bool isPrime = true; // assume each value of i is prime until proven otherwise. Any instance of a value of j that is less than i and greater than 1 that is a factor of i means i is Not Prime
   if (inputedInt < 2)
      return !isPrime;
   
   int j = 2; // the denomenator, j, starts at one less than the numerator, i.

   while (j < inputedInt/2 && isPrime) //  decrement j in the while loop until a factor (j) is found or get up to half of the number being tested for primeness.
    {
      if (inputedInt % j == 0) // means i was divisible by j and therefore has a factor, so NOT prime
        isPrime = false; // now we know i is not Prime
      j++;
    }
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
    Serial.println("PRIME");
  else
    Serial.println("NOT PRIME");
  newData = false;
  Serial.println("");
  Serial.println("Enter an integer to determine if it is prime or not...");
  
}
