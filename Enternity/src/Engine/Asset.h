#pragma once
namespace Enternity
{
	class Asset
	{
	public:
		enum LoadingMode
		{
			Sync,
			Asyn
		};

		enum LoadingState
		{
			loading_state_pending,
			loading_state_succeeded,
			loading_state_failed
		};
	public:
		virtual ~Asset(){}
	public:
		LoadingState getLoadingState() const;
		void load(LoadingMode mode);
	private:
		virtual void doLoad() = 0;
	protected:
		LoadingState m_state{ loading_state_pending };
	};

	inline Asset::LoadingState Asset::getLoadingState() const
	{
		return m_state;
	}
}