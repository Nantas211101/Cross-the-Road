#pragma once
namespace Category {
	enum Type {
		None    = 0,
		Scene   = 1 << 0,
		Player  = 1 << 1,
		River   = 1 << 2,
		Road    = 1 << 3,
		Grass   = 1 << 4,
		Tree	= 1 << 5,
		Car		= 1 << 6,
		Log		= 1 << 7,
		Train   = 1 << 8
	};
}