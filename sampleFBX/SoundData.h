// BGM/SE定義 (SoundData.h)
#pragma once

enum eBGM {
	SOUND_LABEL_TITLE = 0,		// BGM0 title
	SOUND_LABEL_GAMEMAIN,			// BGM1 game

	MAX_BGM
};

enum eSE {
	SOUND_LABEL_SE_CANSEL = 0,	// 戻る
	SOUND_LABEL_SE_POUSE,		// ポーズ
	SOUND_LABEL_SE_SELECT,		// 決定
	SOUND_LABEL_SE_FALL,		// 落下
	SOUND_LABEL_SE_RING,		// リングを動かす
	SOUND_LABEL_SE_SWIPE,		// カーソルを動かす音

	MAX_SE
};
