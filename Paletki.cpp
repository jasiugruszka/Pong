void DrawLeftPaddle(HDC ptr_hdc)
{
	int LPBottom = LPTop + 80;
	static int x = 100;
	RECT rctB = {20,LPTop,40,LPBottom};
	FillRect(ptr_hdc, &rctB, hbrush);
}


  void DrawRightPaddle(HDC ptr_hdc)
{
	int RPBottom = RPTop + 80;
	static int x = 100;
	RECT rctB = {900,RPTop,9200,RPBottom};
	FillRect(ptr_hdc, &rctB, hBrush);
}
