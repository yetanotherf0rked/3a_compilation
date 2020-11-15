int pgcd(int p, int q)
{
  while(p != q)
    {
      if(p>q)
	p = p - q;
      else
	q = q - p;
    }
  return p;
}

void main()
{
  int p;
  int q;
  input(p);
  input(q);
  print(pgcd(p,q));
}
