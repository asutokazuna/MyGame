// BGM/SE定義 (SoundData.hpp)
#pragma once

LPCWSTR g_pszFileBGM[MAX_BGM] = {
	L"title.mp3",			// BGM0
	L"gamemain.mp3",		// BGM1
};

LPCWSTR g_pszFileSE[MAX_SE] = {
	L"cancel.wav",			// 戻る
	L"close_open_pose.wav",	// ポーズ
	L"select.wav",			// 決定
	L"fall.wav",			// 落下
	L"ring.wav",			// リングを動かす
	L"swipe.mp3",			// カーソルを動かす音
};
