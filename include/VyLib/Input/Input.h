#include "VyLib/Input/InputCodes.h"
#include "VyLib/Common/Common.h"

namespace Vy
{
	enum class CursorMode
	{
		NORMAL,
		HIDDEN,
		LOCKED
	};

	class Input
	{
	protected:
		Input() = default;

	public:
		Input(const Input&)             = delete;
		Input& operator= (const Input&) = delete;

	public:
		static bool IsKeyPressed(Key keyCode);

		static bool IsMouseButtonPressed(Mouse mouseButton);
		static Pair<f32, f32> GetMousePosition();
		static f32 GetMouseX();
		static f32 GetMouseY();

		static void SetShowMouse(bool bShow);
		static void SetMousePos(f64 xPos, f64 yPos);

		static bool IsMouseVisible();
	};
}