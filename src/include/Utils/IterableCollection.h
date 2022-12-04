#pragma once

template<typename TType, typename TToString>
class IterableCollection
{
public:
	void Add(TType&& layer)
	{
		m_Layers.push_back(std::move(layer));
		if (m_Active == m_Layers.end())
			m_Active = m_Layers.begin();
	}

	void Next()
	{
		if (m_Active == m_Layers.end())
			return;

		if (++m_Active == m_Layers.end())
			m_Active = m_Layers.begin();
	}

	void Prev()
	{
		if (m_Active == m_Layers.end())
			return;

		if (m_Active == m_Layers.begin())
			m_Active = std::prev(m_Layers.end());
		else
			--m_Active;
	}

	TType Active() const
	{
		if (m_Active == m_Layers.end())
			return {};
		return *m_Active;
	}

	SkString ToString() const
	{
		return TToString{}(Active());
	}

private:
	std::list<TType> m_Layers;
	typename std::list<TType>::iterator m_Active = m_Layers.end();
};