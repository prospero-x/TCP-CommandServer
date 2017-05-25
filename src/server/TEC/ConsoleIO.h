#ifndef CONSOLEIO_H
#define CONSOLEIO_H

typedef enum
{
	ConsoleIO_Reset,
	ConsoleIO_Red,
	ConsoleIO_Green,
	ConsoleIO_Cyan,
} ConsoleIO_Color;

extern int ConsoleIO_IntInput(char *Text, int min, int max, int def);
extern float ConsoleIO_FloatInput(char *Text, float min, float max, float def);
extern unsigned char ConsoleIO_YesNo(char *Text, unsigned char def);
extern void ConsoleIO_SetColor(ConsoleIO_Color Color);
extern void ConsoleIO_Clear(void);

#endif
