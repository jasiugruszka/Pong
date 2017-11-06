switch(wp) //wp - licznik
{
  case 1:
  {
    RECT r;
    GetClientRect(kwnd, &r);
    
    if(x+vx+dx > (r.right - r.left) || x +vx < 0)   //sprawdzenie czy sie nie odbija od ściany pionowej
    {
    vx= -vx;
    }
    
    if(y+vy+dx > (r.bottom -r.top) || y+vy < 0)    //sprawdzenie czy sie nie odbija od ściany poziomej
    {
    vy= -vy;
    }
    
    x+= vx; //aktualizacja prędkości piłeczki
    y+= vy;
    
    Invalidate Rect (hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
  }
  break;
}
