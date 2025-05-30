#pragma once

namespace Engine
{
#define BEGIN(NS) namespace NS {
#define END }
#define USING(NS) using namespace NS;

#define DISABLE_COPY_MOVE(CLASS) \
public: \
CLASS(const CLASS&) = delete; \
CLASS& operator=(const CLASS&) = delete; \
CLASS(CLASS&&) = delete; \
CLASS& operator=(CLASS&&) = delete; 

#define DECLAER_SINGLETON(CLASS) \
DISABLE_COPY_MOVE(CLASS) \
public: \
static CLASS& GetInstance() noexcept \
{ \
	static CLASS instance; \
	return instance; \
}

#ifdef ENGINE_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif // ENGINE_EXPORTS

}

using namespace Engine;