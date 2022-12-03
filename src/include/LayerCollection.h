#ifndef LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064
#define LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064

#include "include/Layers/BaseLayer.h"
#include <list>

class LayerCollection
{
public:
	void Add(std::shared_ptr<BaseLayer>&& layer);
	void Next();
	void Prev();
	std::shared_ptr<BaseLayer> Active() const;

private:
	std::list<std::shared_ptr<BaseLayer>> m_Layers;
	std::list<std::shared_ptr<BaseLayer>>::iterator m_Active = m_Layers.end();
};

#endif // LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064