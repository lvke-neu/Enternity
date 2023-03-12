#include "InputEventManager.h"

namespace Enternity
{
	void InputEventManager::NotifyKeyPress(Keyboard key)
	{
		if (!m_viewportFocused)
			return;

		m_keyPressMap[key] = true;
		m_keyReleaseMap[key] = false;
		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onKeyPress(key);
			}
		}
	}

	void InputEventManager::NotifyKeyRelease(Keyboard key)
	{
		m_keyPressMap[key] = false;
		m_keyReleaseMap[key] = true;
		if (!m_viewportFocused)
			return;

		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onKeyRelease(key);
			}
		}
	}

	void InputEventManager::NotifyMousePress(MouseState mouseState)
	{
		if (!m_viewportFocused)
			return;

		m_mousePressMap[mouseState.mouseButton] = true;

		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onMousePress(mouseState);
			}
		}
	}

	void InputEventManager::NotifyMouseRelease(MouseState mouseState)
	{
		if (!m_viewportFocused)
			return;
		m_mousePressMap[mouseState.mouseButton] = false;

		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onMouseRelease(mouseState);
			}
		}
	}

	void InputEventManager::NotifyMouseMove(MouseState mouseState)
	{
		if (!m_viewportFocused)
			return;

		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onMouseMove(mouseState);
			}
		}
	}

	void InputEventManager::NotifyMouseWheel(MouseState mouseState)
	{
		if (!m_viewportFocused)
			return;

		for (auto& event : m_events)
		{
			if (dynamic_cast<InputEvent*>(event))
			{
				dynamic_cast<InputEvent*>(event)->onMouseWheel(mouseState);
			}
		}
	}

	bool InputEventManager::IsKeyPress(Keyboard key)
	{
		if (m_keyPressMap.find(key) != m_keyPressMap.end())
			return m_keyPressMap[key];
		return false;
	}

	bool InputEventManager::IsKeyRelease(Keyboard key)
	{
		if (m_keyReleaseMap.find(key) != m_keyReleaseMap.end())
			return m_keyReleaseMap[key];
		return false;
	}

	bool InputEventManager::IsMousePress(MouseButton mouseButton)
	{
		if (m_mousePressMap.find(mouseButton) != m_mousePressMap.end())
			return m_mousePressMap[mouseButton];
		return false;
	}

}