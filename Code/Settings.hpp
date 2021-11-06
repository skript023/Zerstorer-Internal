#pragma once

namespace big
{
	class Settings
	{
	public:
		std::atomic_bool m_LogWindow = false;
		std::atomic_bool m_LockMouse = false;
	};

	inline Settings g_Settings;
}
