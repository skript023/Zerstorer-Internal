#pragma once
#include "Script.hpp"
#include "Natives.hpp"

namespace big
{
	class AbstractCallback
	{
	public:
		virtual ~AbstractCallback() noexcept = default;
		AbstractCallback(AbstractCallback const&) = delete;
		AbstractCallback& operator=(AbstractCallback const&) = delete;
		AbstractCallback(AbstractCallback&&) = delete;
		AbstractCallback& operator=(AbstractCallback&&) = delete;

		/**
		 * \brief Is the callback completed?
		 * \return bool
		 */
		virtual bool IsDone() = 0;

		/**
		 * \brief Called when IsDone() returns true
		 */
		virtual void OnSuccess() = 0;

		/**
		 * \brief Called when IsDone() returns false 
		 */
		virtual void OnFailure() = 0;
	protected:
		AbstractCallback() = default;
	};

	class ModelCallback : public AbstractCallback
	{
	public:
		explicit ModelCallback(std::uint32_t model, std::function<void()> action):
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_MODEL_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_MODEL(m_Model);
		}
	private:
		std::uint32_t m_Model;
		std::function<void()> m_Action;
	};

	class NetworkControlCallback : public AbstractCallback
	{
	public:
		explicit NetworkControlCallback(std::int32_t entity, std::function<void()> action):
			m_Entity(entity),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(m_Entity);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_Entity);
		}
	private:
		std::int32_t m_Entity;
		std::function<void()> m_Action;
	};

	class DelayCallback : public AbstractCallback
	{
	public:
		explicit DelayCallback(std::chrono::high_resolution_clock::duration delay, std::function<void()> action) :
			m_StartTime(std::chrono::high_resolution_clock::now()),
			m_Delay(delay),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return (std::chrono::high_resolution_clock::now() - m_StartTime).count() >= m_Delay.count();
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
		}

	private:
		std::chrono::steady_clock::time_point m_StartTime;
		std::chrono::high_resolution_clock::duration m_Delay;
		std::function<void()> m_Action;
	};

	class FadeCallback : public AbstractCallback
	{
	public:
		explicit FadeCallback(std::uint32_t fadeInTime, std::uint32_t fadeOutTime, std::function<void()> action) :
			m_FadeIn(fadeInTime),
			m_FadeOut(fadeOutTime),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			auto ret = CAM::IS_SCREEN_FADED_OUT();
			if (ret)
			{
				CAM::DO_SCREEN_FADE_IN(m_FadeIn);
			}
			return ret;
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			if (!CAM::IS_SCREEN_FADED_OUT() || !CAM::IS_SCREEN_FADING_OUT())
			{
				CAM::DO_SCREEN_FADE_OUT(m_FadeOut);
			}
		}
	private:
		std::uint32_t m_FadeIn;
		std::uint32_t m_FadeOut;
		std::function<void()> m_Action;
	};

	class ModelCollisionCallback : public AbstractCallback
	{
	public:
		explicit ModelCollisionCallback(Hash model, std::function<void()> action) :
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_COLLISION_FOR_MODEL_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_COLLISION_FOR_MODEL(m_Model);
		}
	private:
		Hash m_Model;
		std::function<void()> m_Action;
	};

	class PTFXAssetCallback : public AbstractCallback
	{
	public:
		explicit PTFXAssetCallback(const char* asset, std::function<void()> action) :
			m_Asset(asset),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(m_Asset);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(m_Asset);
		}
	private:
		const char* m_Asset;
		std::function<void()> m_Action;
	};

	class AssetCallback : public AbstractCallback
	{
	public:
		explicit AssetCallback(std::uint32_t asset, std::function<void()> action) :
			m_Asset(asset),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return WEAPON::HAS_WEAPON_ASSET_LOADED(m_Asset);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			WEAPON::REQUEST_WEAPON_ASSET(m_Asset, 31, false);
		}
	private:
		std::uint32_t m_Asset;
		std::function<void()> m_Action;
	};

	class KeyBoardCallBack : public AbstractCallback
	{
	public:
		explicit KeyBoardCallBack(const char* title, int input, std::function<void()> action) :
			Title(title),
			m_Action(std::move(action)),
			Input(input)
		{
		}

		bool IsDone() override
		{
			return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{

		}
	private:
		const char* Title;
		int Input;
		std::function<void()> m_Action;
	};

	class TeleportWaypoint : public AbstractCallback
	{
	public:
		explicit TeleportWaypoint(std::int32_t entity, float x, float y):
			m_entity(entity),
			m_x(x),
			m_y(y)
		{
		}
		bool IsDone() override
		{
			return (MISC::GET_GROUND_Z_FOR_3D_COORD(m_x, m_y, 1000.f, &ground, false, true) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(m_entity));
		}

		void OnSuccess() override
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_entity, m_x, m_y, ground + 2.f, FALSE, FALSE, FALSE);
		}

		void OnFailure() override
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_entity);
			STREAMING::REQUEST_COLLISION_AT_COORD(m_x, m_y, m_z);
			if (m_z == 0.f)
				m_z = 1000.f;
			m_z-=100.f;
		}
	private:
		float m_x;
		float m_y;
		float m_z = 1000.f;
		float ground = 0.f;
		bool found = false;
		std::int32_t m_entity;
		std::function<void()> m_Action;
		int times = 0;
	};

	class CallbackScript : public Script
	{
	public:
		explicit CallbackScript() = default;
		~CallbackScript() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;

		/**
		 * \brief Adds a callback to the list
		 * \param args... The arguments to be passed to CallbackType's constructor
		 */
		template <typename CallbackType, typename ...TArgs>
		void AddCallback(TArgs&&... args)
		{
			m_Callbacks.push_back(std::make_unique<CallbackType>(std::forward<TArgs>(args)...));
		}
	private:
		bool m_Initialized{};
		std::vector<std::unique_ptr<AbstractCallback>> m_Callbacks;
	};

	inline std::shared_ptr<CallbackScript> g_CallbackScript;
}
