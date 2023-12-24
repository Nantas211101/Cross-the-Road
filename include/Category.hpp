#pragma once
namespace Category {
	enum Type {
		None    = 0,
		Scene   = 1 << 0,
		Player  = 1 << 1,
		
		// River
		River   = 1 << 2,
		Log		= 1 << 3,

		// Road
		Vehicle = 1 << 4,
		Animal	= 1 << 5,

		// Ground
		Obstacle= 1 << 6,

		// Railway
		Train   = 1 << 7,

		// lane -> Road, Ground
		Lane	= 1 << 8,

		// sound node
		SoundEffect = 1 << 9,
	};
}
