void setup()
{
  Serial.begin(9600);
  for (int i = 2; i <= 100; i++)
  {
    bool isPrime = true; // assume each value of i is prime until proven otherwise. Any instance of a value of j that is less than i and greater than 1 that is a factor of i means i is Not Prime
    int j = 2; // current factor (denomenator) to be tested on i
    while (j < i && isPrime) //  decrement j in the while loop until a factor (j) is found or get down to 2 stop
    {
      if (i % j == 0) // means i was divisible by j and therefore has a factor, so NOT prime
        isPrime = false; // now we know i is not Prime
      j++;
    }
    if (isPrime) // if (isPrime) i gets printed
      Serial.println(i);
  }
}

void loop()
{
  // no loop needed
}
