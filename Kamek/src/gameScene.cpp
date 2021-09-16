#include <common.h>
#include <game.h>
#include <stage.h>
#include <g3dhax.h>
#include <sfx.h>
#include <gamescene.h> //It contains the dGameDisplay_c, which was RE'd by Grop (because i was a noob back when he did it), thanks to him !
#include "boss.h"


/******************************************************************************/
/**ALL THE STUFF BELOW IS TESTS, DEBUG MODE AND IS UNRELATED TO ANYTHING ELSE**/
/******************************************************************************/


/***************************/
/**Nybble getting function**/
/***************************/

extern "C" float pow(float num, float power);

int getNybbleValue(u32 settings, int fromNybble, int toNybble, bool doOSReport) { //This function is to get a nybble from a sprite's settings. It's unused but i used it for some tests, and i don't want to remove it :c
	int numberOfNybble = (toNybble  - fromNybble) + 1;               //gets how many nybbles are used for the process (example: nybbles 4-6 -> there's nybbles 4, 5 and 6 used -> numberOfNybble = 3) 
	int valueToUse = 48 - (4 * toNybble);                            //gets the value to use with the bitshift at the end 
	int fShit = pow(16, numberOfNybble) - 1;                         //gets the value to use with the "&" operator at the end 
	if(doOSReport) {
		OSReport("-> (settings >> %d) & 0x%x) => ", valueToUse, fShit);  //debugging
	}
	return ((settings >> valueToUse) & fShit);                       //uses everything to make the nybble value 
}

