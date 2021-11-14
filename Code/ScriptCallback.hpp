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

	class RequestCollision : public AbstractCallback
	{
	public:
		explicit RequestCollision(std::int32_t entity, float x, float y):
			m_x(x),
			m_y(y),
			m_entity(entity)
		{
		}
		bool IsDone() override
		{
			if (found)
				return true;
			else
				return false;
		}

		void OnSuccess() override
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_entity, m_x, m_y, m_z + 2.f, FALSE, FALSE, FALSE);
		}

		void OnFailure() override
		{
			if (!found)
			{
				for (float z = 1000.f; z >= 0.f; z -= 100.f)
				{
					STREAMING::REQUEST_COLLISION_AT_COORD(m_x, m_y, z);
					std::this_thread::yield();
				}
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(m_x, m_y, 1000.f, &m_z, false, false))
			{
				found = true;
			}
			times++;
		}
	private:
		float m_x;
		float m_y;
		float m_z;
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
