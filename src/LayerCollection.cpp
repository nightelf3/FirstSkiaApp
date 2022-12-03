#include "include/LayerCollection.h"

void LayerCollection::Add(std::shared_ptr<BaseLayer>&& layer)
{
	m_Layers.push_back(std::move(layer));
	if (m_Active == m_Layers.end())
		m_Active = m_Layers.begin();
}

void LayerCollection::Next()
{
	if (m_Active == m_Layers.end())
		return;

	if (++m_Active == m_Layers.end())
		m_Active = m_Layers.begin();
}

void LayerCollection::Prev()
{
	if (m_Active == m_Layers.end())
		return;

	if (m_Active == m_Layers.begin())
		m_Active = std::prev(m_Layers.end());
	else
		--m_Active;
}

std::shared_ptr<BaseLayer> LayerCollection::Active() const
{
	if (m_Active == m_Layers.end())
		return {};
	return *m_Active;
}