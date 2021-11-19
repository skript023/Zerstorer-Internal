#pragma once
#include <JSON/json.hpp>

#pragma warning(disable:4840)
#pragma warning(disable:4477)

namespace big
{
	class TeleportManager
	{
	public:
		explicit TeleportManager()
		{
			std::snprintf(&teleport_directory[0], sizeof(teleport_directory) - 1, "%s\\" BIGBASE_NAME "\\Teleports\\", std::getenv("appdata"));
			try
			{
				if (!std::filesystem::exists(&teleport_directory[0]))
					std::filesystem::create_directory(&teleport_directory[0]);
			}
			catch (fs::filesystem_error const&)
			{
			}
		}

		const char* GetTeleportDirectory()
		{
			return &teleport_directory[0];
		}

		void AddTeleport(std::string name, NativeVector3 position)
		{
			char prefix[64] = {};
			std::snprintf(prefix, sizeof(prefix) - 1, "%s%s", name, ".big");

			m_FilePath.append(std::getenv("appdata"));
			m_FilePath.append(BIGBASE_NAME);
			m_FilePath.append("Teleports\\");
			if (!fs::exists(m_FilePath))
				fs::create_directory(m_FilePath);

			std::ofstream ofs(m_FilePath /= prefix);
			ofs << position.x << "," << position.y << "," << position.z;
			ofs.close();
		}

		~TeleportManager() noexcept = default;
		TeleportManager(TeleportManager const&) = delete;
		TeleportManager(TeleportManager&&) = delete;
		TeleportManager& operator=(TeleportManager const&) = delete;
		TeleportManager& operator=(TeleportManager&&) = delete;
	private:
		std::unordered_map<std::uint32_t, std::string> m_Teleports;
		char teleport_directory[1024] = {};
		fs::path m_FilePath;
	};

	inline std::unique_ptr<TeleportManager> g_teleport_persist;
}