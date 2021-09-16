#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include "bobombhax.h"

int doWait = 0;

const char* BGarcNameList [] = {
	"nokonokoA",
	NULL
};
/*****************************************************/
/**************Gabon Rock replacing shit**************/
/*Don't ask me how does it work, because i don't know*/
/*****************************************************/

extern "C" float pow(float num, float power);

int getNybbleValue(u32 settings, int fromNybble, int toNybble) {	 //Made that function because i wanted to, even if it's kinda useless. So shut up Meatball/CLF78
	int numberOfNybble = (toNybble  - fromNybble) + 1;               //gets how many nybbles are used for the process (example: nybbles 4-6 -> there's nybbles 4, 5 and 6 used -> numberOfNybble = 3) 
	int valueToUse = 48 - (4 * toNybble);                            //gets the value to use with the bitshift at the end 
	int fShit = pow(16, numberOfNybble) - 1;                         //gets the value to use with the "&" operator at the end 
	return ((settings >> valueToUse) & fShit);                       //uses everything to make the nybble value 
}

class daEnBomhei_c : public dEn_c {
public:
	u8 field524_from_daEnCarry_c;
	u8 _525;
	u8 _522;
	u8 _527;
	mAllocator_c allocator;
	u32 resFile;
	m3d::mdl_c model;
	m3d::fanm_c anmChr;
	m3d::banm_c anmClr;
	u32 field_5E8;
	u32 isBurning;
	u32 field_5F0;
	u8 _5F4;
	u8 _5F5;
	u8 _5F6;
	u8 _5F7;
	u32 cannonShootDirection;
	u8 _5FC;
	u8 _5FD;
	u8 _5FE;
	u8 _5FF;
	u8 _600;
	u8 _601;
	u8 _602;
	u8 _603;
	VEC3 field_604;
	u8 _610;
	u8 _611;
	u8 _612;
	u8 _613;
	u8 _614;
	u8 _615;
	u8 _616;
	u8 _617;
	u8 _618;
	u8 _619;
	u8 _61A;
	u8 _61B;
	u8 _61C;
	u8 _61D;
	u8 _61E;
	u8 _61F;
	u32 hitsRemainingBeforeCoinJumpSpawns;
	u32 holdingPlayerID;
	u32 countdown;
	u8 _62C;
	u8 _62D;
	u8 _62E;
	u8 _62F;
	u8 _630;
	u8 _631;
	u8 _632;
	u8 _633;
	u8 _634;
	u8 _635;
	u8 _636;
	u8 _637;
	mEf::es2 effect;

	// States
	USING_STATES(daEnBomhei_c);
	REF_NINTENDO_STATE(Sleep);

	int onCreate_orig();
	int newOnCreate();
	void doThrowing();
	int amIthrown;

	void playerCollision_orig(ActivePhysics *apThis, ActivePhysics *apOther);
	void newPlayerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
};

int daGabonRock_c::getsettings() {									 //I know bleh bleh bleh that's not optimised, but lemme ask something: Do I care ? The answer is no.
	int orig_val = this->onCreate_orig();
	u8 facing = dSprite_c__getXDirectionOfFurthestPlayerRelativeToVEC3(this, this->pos);

	// --------以下是修改的地方--------
	if(getNybbleValue(this->settings, 12, 12) > 1) {
		int playerID = getNybbleValue(this->settings, 6, 6);
		dAcPy_c *player = dAcPy_c::findByID(playerID);
		// int settings = 0 | (playerID << 4) | (player->direction << 8);
		VEC3 bombpos = {player->pos.x + ((player->direction == 1) ? -3 : 3), player->pos.y + 2, player->pos.z}; // 玩家的方向1
		if (facing != this->direction) { // 玩家的方向值判断
				this->direction = facing;
				if (this->direction == 1) {
					this->rot.y = 0xD800;
				}
				else {
					this->rot.y = 0x2800;
				}
			}
		if (this->direction == 1) { // 如果向右看
			Vec pos;
			pos.x = this->pos.x-2.5; // 那就向右扔
			pos.y = this->pos.y;      // Y和Z轴默认就行
			pos.z = this->pos.z;
			PlaySound(this, SE_EMY_KANIBO_THROW);
			dStageActor_c *spawned;
			spawned = CreateActor(56, 0x2, pos, 0, 0);
				 // 生成铁球

			}
			else {											// 如果不向右看，那就是向左看
				Vec pos;
			pos.x = this->pos.x+3;						// 那就向左扔
			pos.y = this->pos.y;
			pos.z = this->pos.z;
			PlaySound(this, SE_EMY_KANIBO_THROW);
			dStageActor_c *spawned;
				spawned = CreateActor(56, 0x2, pos, 0, 0);

			}
		
		
		// --------以上是修改的地方--------
		SaveFile *file = GetSaveFile();
		SaveBlock *block = file->GetBlock(file->header.current_file);
		block->powerups_available[7] = 99;
		block->powerups_available[8] = 49;
		block->powerups_available[9] = 21;
		block->powerups_available[10] = 32;

		OSReport("powerups_available -> %d %d %d %d\n", block->powerups_available[7], block->powerups_available[8], block->powerups_available[9], block->powerups_available[10]);
		OSReport("toad_level_idx -> %d %d %d %d\n", block->toad_level_idx[0], block->toad_level_idx[1], block->toad_level_idx[2], block->toad_level_idx[3]);
		// OSReport("toad_level_idx >> 0   -> %d\n", (block->toad_level_idx[0] >> 0) & 0xFF);
		// OSReport("toad_level_idx >> 4   -> %d\n", (block->toad_level_idx[0] >> 4) & 0xFF);
		// OSReport("toad_level_idx >> 8   -> %d\n", (block->toad_level_idx[0] >> 8) & 0xFF);

		doWait = 20;
	}
	return orig_val;
}

int dGameDisplay_c::doWaitCheck() {
	int orig_val = this->onExecute_orig();
	if(doWait > 0) {
		doWait--;
	}
	return orig_val;
}

int daEnBomhei_c::newOnCreate() {
	int orig_val = this->onCreate_orig();
	OSReport("Spawning EN_BOMHEI: %d\n", this->settings);
	return orig_val;
}

void daEnBomhei_c::doThrowing() {
	this->isBurning = 180;
	this->speed.x = 3 * ((this->direction == 1) ? -1 : 1);
	this->speed.y = 3;
	this->amIthrown = 1;
	doStateChange(&daEnBomhei_c::StateID_Sleep);
}

void daEnBomhei_c::newPlayerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	if(this->amIthrown != 1) {
		this->playerCollision_orig(apThis, apOther);
		OSReport("i'm not thrown, go ahead\n");
	}
	else {
		OSReport("i'm thrown, go away\n");
	}
}