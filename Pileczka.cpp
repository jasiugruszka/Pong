switch(wp)
{
  case 1:
  {
    RECT r;
    GetClientRect(kwnd, &r);
    
    if(x+vx+dx > (r.right - r.left) || x +vx < 0)
    {
    vx= -vx;
    }
    
    if(y+vy+dx > (r.bottom -r.top) || y+vy < 0)
    {
    vy= -vy;
    }
    
    x+= vx;
    y+= vy;
    
    Invalidate Rect (hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
  }
  break;
}
