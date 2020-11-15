void main()
{
  int n;
  int fact;

  n = 3;
  fact = 1;
  do {
    fact = fact*n;
    n = n - 1;
  } while(n>0);
  //compute 3!
  
  print(fact);
}
