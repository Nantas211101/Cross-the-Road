#pragma once

// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		PlayerAircraft		= 1 << 1,
		AlliedAircraft		= 1 << 2,
		EnemyAircraft		= 1 << 3,
	};
}
