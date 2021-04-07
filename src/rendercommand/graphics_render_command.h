#pragma once

#define ARG_COUNT(...) EXPAND(PP_SIZE(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,))
#define PP_SIZE(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size


#define EMPTY
#define REM(...) __VA_ARGS__
#define EAT(...)

#define EXPAND(x) x

// Strip off the type
#define STRIP(x) EAT x
// Show the type without parenthesis
#define PAIR(x) REM x

#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

#define DEFINE_VAR_1(code, ...)
#define DEFINE_VAR_2(var, ...)                                                                   \
	typename std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var; \
	EXPAND(DEFINE_VAR_1(__VA_ARGS__))
#define DEFINE_VAR_3(var, ...)                                                                   \
	typename std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var; \
	EXPAND(DEFINE_VAR_2(__VA_ARGS__))
#define DEFINE_VAR_4(var, ...)                                                                   \
	typename std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var; \
	EXPAND(DEFINE_VAR_3(__VA_ARGS__))
#define DEFINE_VAR_5(var, ...)                                                                   \
	typename std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var; \
	EXPAND(DEFINE_VAR_4(__VA_ARGS__))

#define DEFINE_VAR_N(N, ...) EXPAND(CONCATENATE(DEFINE_VAR_, N)(__VA_ARGS__))

#define EXEC_FUNCTION_1(code) code
#define EXEC_FUNCTION_2(var, code) \
	auto &var = this->var;         \
	EXPAND(EXEC_FUNCTION_1(code))

#define EXEC_FUNCTION_3(var, ...) \
	auto &var = this->var;        \
	EXPAND(EXEC_FUNCTION_2(__VA_ARGS__))

#define EXEC_FUNCTION_4(var, ...) \
	auto &var = this->var;        \
	EXPAND(EXEC_FUNCTION_3(__VA_ARGS__))
#define EXEC_FUNCTION_5(var, ...) \
	auto &var = this->var;        \
	EXPAND(EXEC_FUNCTION_4(__VA_ARGS__))
#define EXEC_FUNCTION_6(var, ...) \
	auto &var = this->var;        \
	EXPAND(EXEC_FUNCTION_5(__VA_ARGS__))

#define EXEC_FUNCTION_N(N, ...) EXPAND(CONCATENATE(EXEC_FUNCTION_, N)(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_ARGS_1(code)
#define EXEC_CONSTRUCTOR_ARGS_2(var, code) typename ::std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var \
	EXPAND(EXEC_CONSTRUCTOR_ARGS_1(code))

#define EXEC_CONSTRUCTOR_ARGS_3(var, ...) typename ::std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var, \
										  EXPAND(EXEC_CONSTRUCTOR_ARGS_2(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_ARGS_4(var, ...) typename ::std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var, \
										  EXPAND(EXEC_CONSTRUCTOR_ARGS_3(__VA_ARGS__))
#define EXEC_CONSTRUCTOR_ARGS_5(var, ...) typename ::std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var, \
										  EXPAND(EXEC_CONSTRUCTOR_ARGS_4(__VA_ARGS__))
#define EXEC_CONSTRUCTOR_ARGS_6(var, ...) typename ::std::remove_const<typename ::std::remove_reference<decltype(var)>::type>::type var, \
										  EXPAND(EXEC_CONSTRUCTOR_ARGS_5(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_ARGS_N(N, ...) EXPAND(CONCATENATE(EXEC_CONSTRUCTOR_ARGS_, N)(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_INIT_1(code)
#define EXEC_CONSTRUCTOR_INIT_2(var, code) \
	this->var = var;                       \
	EXPAND(EXEC_CONSTRUCTOR_INIT_1(code))

#define EXEC_CONSTRUCTOR_INIT_3(var, ...) \
	this->var = var;                      \
	EXPAND(EXEC_CONSTRUCTOR_INIT_2(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_INIT_4(var, ...) \
	this->var = var;                      \
	EXPAND(EXEC_CONSTRUCTOR_INIT_3(__VA_ARGS__))
#define EXEC_CONSTRUCTOR_INIT_5(var, ...) \
	this->var = var;                      \
	EXPAND(EXEC_CONSTRUCTOR_INIT_4(__VA_ARGS__))
#define EXEC_CONSTRUCTOR_INIT_6(var, ...) \
	this->var = var;                      \
	EXPAND(EXEC_CONSTRUCTOR_INIT_5(__VA_ARGS__))

#define EXEC_CONSTRUCTOR_INIT_N(N, ...) EXPAND(CONCATENATE(EXEC_CONSTRUCTOR_INIT_, N)(__VA_ARGS__))

#define G_RENDERCOMMAND(...)                                                             \
	struct CONCATENATE(_RenderCommand_, __LINE__) : public Renderer::RRenderCommand    \
	{                                                                                    \
		EXPAND(DEFINE_VAR_N(EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__))                \
		CONCATENATE(_RenderCommand_, __LINE__)                                           \
		(EXPAND(EXEC_CONSTRUCTOR_ARGS_N(EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__)))   \
		{                                                                                \
			EXPAND(EXEC_CONSTRUCTOR_INIT_N(EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__)) \
		}                                                                                \
		virtual void Execute()                                                           \
		{                                                                                \
			EXPAND(EXEC_FUNCTION_N(EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__))         \
		}                                                                                \
	};


#include <queue>

#include "graphics_shared_buffer.h"

#ifdef G_WIN
    #ifdef GRCMD_EXPORT
        #define G_RAPI __declspec(dllexport)
    #else
        #define G_RAPI __declspec(dllimport)
    #endif
#else
    #define G_RAPI
#endif
namespace Renderer
{
	class G_RAPI RRenderCommand
	{
	public:
		virtual ~RRenderCommand() = default;

		virtual void Execute() = 0;
	};

	/**
	 * The Command Queue is a statically created buffer which will process lambda like code.
	 * It is used to created multi threaded rendering code
	 */
	class G_RAPI RRenderCommandQueue
	{
	public:
		void Submit(RRenderCommand *renderCommand);

		void Execute();

		static RRenderCommandQueue& Get();

	private:
		std::queue<RRenderCommand *> fCommandQueue;
	};

}

#define G_RENDERCMD(code) \
	G_RENDERCOMMAND(code) \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)());
#define G_RENDERCMD1(var, code) \
	G_RENDERCOMMAND(var, code)  \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(var));
#define G_RENDERCMD2(var1, var2, code) \
	G_RENDERCOMMAND(var1, var2, code)  \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(var1, var2));
#define G_RENDERCMD3(var1, var2, var3, code) \
	G_RENDERCOMMAND(var1, var2, var3, code)  \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(var1, var2, var3));
#define G_RENDERCMD4(var1, var2, var3, var4, code) \
	G_RENDERCOMMAND(var1, var2, var3, var4, code)  \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(var1, var2, var3, var4));

#define G_RENDERCMD_S(code)     \
	auto self = this;           \
	G_RENDERCOMMAND(self, code) \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(self));
#define G_RENDERCMD_S1(var, code)    \
	auto self = this;                \
	G_RENDERCOMMAND(self, var, code) \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(self, var));
#define G_RENDERCMD_S2(var1, var2, code)    \
	auto self = this;                       \
	G_RENDERCOMMAND(self, var1, var2, code) \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(self, var1, var2));
#define G_RENDERCMD_S3(var1, var2, var3, code)    \
	auto self = this;                             \
	G_RENDERCOMMAND(self, var1, var2, var3, code) \
	Renderer::RRenderCommandQueue::Get().Submit(new CONCATENATE(_RenderCommand_, __LINE__)(self, var1, var2, var3));