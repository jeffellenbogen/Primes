void setup()
{
  bool isPrime = true;
  Serial.begin(9600);
  for (int i = 2; i <= 100; i++)
  {
    isPrime = true; // assume each value of i is prime until proven otherwise. Any instance of a value of j that is less than i and greater than 1 that is a factor of i means i is Not Prime
    for (int j = i-1; j>=2; j--)
    {
      if (i % j != 0) // if i is not divisible by any value j, still is prime
      {
        //do nothing because i is still possibly prime until proven divisible by some factor j TBD
      }
      else // i % j == 0 means i was divisible by j and therefore has a factor, so NOT prime
        isPrime = false;
    }
    if (isPrime)
      Serial.println(i);
  }
}

void loop()
{

}
