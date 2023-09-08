/*
 * Imprime solo un caracter en una posicion ('x','y')
 */
void printChar(int x, int y, unsigned char c)
{
	gotoxy(x, y); printf("%c", c);
}

/*
 * Imprime una linea horizontal de un mismo caracter 
 * incia en 'x0' y termina en 'x1', todo sobre la linea 'y'
 */
void drawH(int x0, int x1, int y, unsigned char c_line)
{
	for(x0; x0 <= x1; x0++)
	{
		printChar(x0, y, c_line);
	}
}

/*
 * Imprime una linea vertical de un mismo caracter 
 * incia en 'y0' y termina en 'y1', todo sobre la columna 'x'
 */
void drawV(int x, int y0, int y1, unsigned char c_line)
{
	for(y0; y0 <= y1; y0++)
	{
		printChar(x, y0, c_line);
	}
}

/*
 * Imprime una linea horizontal de un mismo caracter, en la linea 'y' 
 * en la posicion 'x0' puede imprimir 'c_left' distinto al resto de la linea
 * en la posicion 'x1' puede imprimir 'c_right' distinto al resto de la linea
 */
void drawHoriz(int x0, int x1, int y, unsigned char c_line, unsigned char c_left, unsigned char c_right)
{
	printChar(x0, y, c_left);
	drawH(x0+1, x1-1, y, c_line);
	printChar(x1, y, c_right);
}

/*
 * Imprime una linea vertical de un mismo caracter, en la linea 'x' 
 * en la posicion 'y0' puede imprimir 'c_top' distinto al resto de la linea
 * en la posicion 'y1' puede imprimir 'c_buttom' distinto al resto de la linea
 */
void drawVerti(int x, int y0, int y1, unsigned char c_line, unsigned char c_top, unsigned char c_buttom)
{
	printChar(x, y0, c_top);
	drawV(x, y0+1, y1-1, c_line);
	printChar(x, y1, c_buttom);
}

/*
 * Construye un marco, con coordenadas iniciales('x0','y0') y coordenadas finales ('x1','y1') 
 * al cual hemos denominado "marco tipo0" 
 */
int windowFrame0(int x0, int y0, int x1, int y1)
{
	if(x0 < 0 || y0 < 0 || x1 <= x0 || y1 <= y0)
	{
		return 0;	
	}
	
	drawHoriz(x0, x1, y0, 196, 218, 191);
	drawV(x0, y0+1, y1-1, 179);
	drawV(x1, y0+1, y1-1, 179);
	drawHoriz(x0, x1, y1, 196, 192, 217);
	
	return 1;
}

/*
 * Construye un marco, con coordenadas iniciales('x0','y0') y coordenadas finales ('x1','y1') 
 * al cual hemos denominado "marco tipo1" 
 */
int windowFrame1(int x0, int y0, int x1, int y1)
{
	if(x0 < 0 || y0 < 0 || x1 <= x0 || y1 <= y0)
	{
		return 0;	
	}
	drawHoriz(x0, x1, y0, 205, 201, 187);
	drawV(x0, y0+1, y1-1, 186);
	drawV(x1, y0+1, y1-1, 186);
	drawHoriz(x0, x1, y1, 205, 200, 188);
	return 1;
}
