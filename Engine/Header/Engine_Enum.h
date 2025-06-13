#pragma once

namespace Engine
{
enum class STATE : uint8_t { RIGHT, UP, LOOK, POSITION };
enum class RENDER_TYPE : uint8_t { PRIORITY, NONEBLEND, BLEND, UI, NONE, IDX };
enum class OBJECT_TYPE : uint8_t { PLAYER, IDX };
enum class COLLISION_TYPE : uint8_t { STATIC, DYNAMIC, IDX };
}