#pragma once

namespace Engine
{
enum class STATE : uint8_t { RIGHT, UP, LOOK, POSITION };
enum class RENDER_TYPE : uint8_t { PRIORITY, NONEBLEND, BLEND, UI, NONE, IDX };
enum class OBJECT_TYPE : uint8_t { PLAYER, IDX };
enum class CREATE_TYPE : uint8_t { STATIC, DYNAMIC, IDX };
enum class COLLISION_TYPE : uint8_t { STATIC, DYNAMIC, IDX };
enum class COLLISION_FILTER_TYPE : uint8_t { SD, DD, IDX };
enum class REGION_TYPE : uint8_t { IDX };
}