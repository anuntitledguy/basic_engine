#ifndef STATEID_H
#define STATEID_H

enum class STATEID
{
	DEFAULT,
	
	/*====== GAMESCENE =======*/
	START,
	GAME,
	GAMEOVER,
	
	/*====== END GAMESCENE =======*/
	
	/*====== PLAYER STATE ======*/
	IDL,
	MOVE,
	ATTACK
	
	/*====== END PLAYER STATE ======*/

};
#endif
