#pragma once
namespace Category {
	enum Type {
		None    = 0,
		Scene   = 1 << 0,
		Player  = 1 << 1,
		River   = 1 << 2,
		Road    = 1 << 3,
		Grass   = 1 << 4,
	};
}