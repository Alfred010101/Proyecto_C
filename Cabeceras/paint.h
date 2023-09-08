/*
 * Pinta una linea horizontal 'color' (afecta el color de texto)
 * incia en 'x0' y termina en 'x1', todo sobre la linea 'y'
 */
void paintHoriz(int x0, int x1, int y, int color)
{
	assignColor(color);
	drawH(x0, x1, y, 32);
}

/*
 * Pinta una linea vertical 'color' (afecta el color de texto)
 * incia en 'y0' y termina en 'y1', todo sobre la columna 'x'
 */
void paintVerti(int x, int y0, int y1, int color)
{
	assignColor(color);
	drawV(x, y0, y1, 32);
}


/*
 * Pinta un area delimitada por coordenadas iniciales('x0','y0') y coordenadas finales ('x1','y1') 
 */
int paintArea(int x0, int y0, int x1, int y1, int color)
{
	if(x0 < 0 || y0 < 0 || x1 <= x0 || y1 <= y0 || color < 0)
	{
		return 0;	
	}
	
	for(y0; y0 <= y1; y0++)
	{
		paintHoriz(x0, x1, y0, color);
	}
	return 1;
}
