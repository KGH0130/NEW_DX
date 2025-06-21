#pragma once

namespace Engine
{
enum class STATE : uint8_t { RIGHT, UP, LOOK, POSITION };
enum class RENDER_TYPE : uint8_t { PRIORITY, NONEBLEND, BLEND, UI, NONE, IDX };
enum class OBJECT_TYPE : uint8_t { PLAYER, ENEMY, IDX };
enum class CREATE_TYPE : uint8_t { STATIC, DYNAMIC, IDX };
enum class COLLISION_TYPE : uint8_t { STATIC, DYNAMIC, IDX };
enum class COLLISION_FILTER_TYPE : uint8_t { SD, DD, IDX };
enum class REGION_TYPE : uint8_t { NONE, IDX };

enum COLLISION_LAYER : uint32_t
{
	LAYER_PLAYER = 1 << 0,
	LAYER_ENEMY = 1 << 1,
	LAYER_TERRAIN = 1 << 2,
};
}