#ifndef LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064
#define LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064

#include "ILayer.h"
#include <list>

class LayerCollection
{
public:
	void Add(spLayer&& layer);
	void Next();
	void Prev();
	spLayer Active() const;

private:
	std::list<spLayer> m_Layers;
	std::list<spLayer>::iterator m_Active = m_Layers.end();
};

#endif // LAYERCOLLECTION_H_C708B479_AD8B_4B57_9752_4B396C401064