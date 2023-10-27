#pragma once
#include <Windows.h>
#include <iostream>
#include "..\Entity.h"
#include "..\MenuConfig.hpp"

namespace HitSound
{
	inline void Run(const CEntity& aLocalPlayer, int& PreviousTotalHits) noexcept
	{
		if (!MenuConfig::HitSound)
			return;

		uintptr_t pBulletServices;
		int totalHits;
		ProcessMgr.ReadMemory(aLocalPlayer.Pawn.Address + Offset::Pawn.BulletServices, pBulletServices);
		ProcessMgr.ReadMemory(pBulletServices + Offset::Pawn.TotalHit, totalHits);
		std::cout << pBulletServices << ", " << totalHits << ", " << PreviousTotalHits << std::endl;

		if (totalHits != PreviousTotalHits) {
			if (totalHits == 0 && PreviousTotalHits != 0)
			{
				// `totalHits` changed from non-zero to zero, do not play hitsound
			}
			else
			{
				// Play the HitSound
				PlaySoundW(L"Hit.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		PreviousTotalHits = totalHits;
	}
}