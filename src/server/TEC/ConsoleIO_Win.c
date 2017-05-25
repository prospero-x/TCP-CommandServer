/*==============================================================================*/
/** @file       ConsoleIO_Win.c
    @brief      This file is not part of the MeComAPI.
    @author     Meerstetter Engineering GmbH: Marc Luethi / Thomas Braun
    @version    v0.42

    This file contains some functions used by the Demo Application to control
    the console and be able to enter some bool, int and float values.

*/
/*==============================================================================*/
/*                          IMPORT                                              */
/*==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConsoleIO.h"

using namespace System;
#using "System.dll"

/*==============================================================================*/
/*                          DEFINITIONS/DECLARATIONS                            */
/*==============================================================================*/


/*==============================================================================*/
/*                          STATIC FUNCTION PROTOTYPES                          */
/*==============================================================================*/

/*==============================================================================*/
/*                          EXTERN VARIABLES                                    */
/*==============================================================================*/

/*==============================================================================*/
/*                          STATIC  VARIABLES                                   */
/*==============================================================================*/

/*==============================================================================*/
/** @brief      Integer input function for the console
 *
*/
int ConsoleIO_IntInput(char *Text, int min, int max, int def)
{
    int zahl, scanfReturn;
    do
    {
        printf(Text); printf(" (%d ... %d, default %d): ", min, max, def);
        fflush(stdin);

        char buffer [256];
		char* string;
		string = fgets(buffer, sizeof(buffer), stdin);
		string[strcspn(string, "\r\n")] = 0;

        if(string[0] == 0) sprintf(string, "%d", def);
        scanfReturn = sscanf(string, "%d", &zahl);
    }
    while((zahl < min) || (zahl > max) || (scanfReturn != 1));
    
    return zahl;
}
/*==============================================================================*/
/** @brief      Float input function for the console
 *
*/
float ConsoleIO_FloatInput(char *Text, float min, float max, float def)
{
    int scanfReturn;
    float zahl;
    do
    {
        printf(Text); printf(" (%f ... %f, default %f): ", min, max, def);
        fflush(stdin);

        char buffer [256];
		char* string;
		string = fgets(buffer, sizeof(buffer), stdin);
		string[strcspn(string, "\r\n")] = 0;

        if(string[0] == 0) sprintf(string, "%f", def);
        scanfReturn = sscanf(string, "%f", &zahl);
    }
    while((zahl < min) || (zahl > max) || (scanfReturn != 1));
    
    return zahl;
}
/*==============================================================================*/
/** @brief      Bool input function for the console
 *
*/
unsigned char ConsoleIO_YesNo(char *Text, unsigned char def)
{
    int scanfReturn;
    char answer;
    do
    {
        printf(Text); 
        if(def == 1) printf(" (default Y): ");
        if(def == 0) printf(" (default N): ");
        fflush(stdin);

        char buffer [256];
		char* string;
		string = fgets(buffer, sizeof(buffer), stdin);
		string[strcspn(string, "\r\n")] = 0;

        if(string[0] == 0)
        {
            if(def == 1) sprintf(string, "Y");
            else sprintf(string, "N");
        }
        scanfReturn = sscanf(string, "%c", &answer);
    }
    while((answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N') == 0 || scanfReturn != 1);

    if(answer == 'y' || answer == 'Y') return true; else return false;
}


/*==============================================================================*/
/** @brief      Set the Fron Color of the Console
 *
*/
void ConsoleIO_SetColor(ConsoleIO_Color Color)
{
	switch(Color)
	{
		case ConsoleIO_Reset:
			Console::ResetColor();
			break;
		case ConsoleIO_Red:
			Console::ForegroundColor = ConsoleColor::Red;
			break;
		case ConsoleIO_Green:
			Console::ForegroundColor = ConsoleColor::Green;
			break;
		case ConsoleIO_Cyan:
			Console::ForegroundColor = ConsoleColor::Cyan;
			break;
		default:
			Console::ResetColor();
			break;
	}
}

/*==============================================================================*/
/** @brief      Clears the Console
 *
*/
void ConsoleIO_Clear(void)
{
	Console::Clear();
}
