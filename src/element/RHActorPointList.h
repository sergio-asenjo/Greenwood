#ifndef RHACTORPOINTLIST_H
#define RHACTORPOINTLIST_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include <iterator>
#include <new>

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHActorPointNode
{
    RHActorPointNode *next;
    RHActorPointNode *previous;
    SBGeoPoint2D point;
};
struct RHActorPointIterator
{
    RHActorPointNode *node;
    RHActorPointIterator(RHActorPointNode *value) : node(value) {}
};
class RHActorPointList
{
public:
    void Clear()
    {
        while (count != 0)
        {
            RHActorPointNode *node = head->next;
            node->previous->next = node->next;
            node->next->previous = node->previous;
            node->point.~SBGeoPoint2D();
            operator delete(node);
            --count;
        }
    }
    ~RHActorPointList()
    {
        Clear();
        operator delete(head);
        head = 0;
    }
    int m_0;
    RHActorPointNode *head;
    int count;
    RHActorPointNode *cursor;
    char dirty;
    char m_11[3];
    int index;
    RHActorPointIterator begin() { return RHActorPointIterator(head->next); }
    RHActorPointIterator end() { return RHActorPointIterator(head); }
    SBGeoPoint2D &Get(int wanted)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(cursor = begin().node), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(cursor = end().node), wanted - size, category);
            }
            dirty = 0;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)(cursor = begin().node), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + size) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)(cursor = end().node), wanted - size, category);
                }
                index = wanted;
            }
        }
        return cursor->point;
    }
    RHActorPointNode *BuyNode(RHActorPointNode *next, RHActorPointNode *previous)
    {
        RHActorPointNode *node = (RHActorPointNode *)::operator new(sizeof(RHActorPointNode));
        node->next = next ? next : node;
        node->previous = previous ? previous : node;
        return node;
    }
    void Construct(SBGeoPoint2D *point, const SBGeoPoint2D &source)
    {
        new (point) SBGeoPoint2D(source);
    }
    RHActorPointIterator insert(RHActorPointIterator position, const SBGeoPoint2D &source)
    {
        RHActorPointNode *node = position.node;
        node->previous = BuyNode(node, node->previous);
        node = node->previous;
        node->previous->next = node;
        Construct(&node->point, source);
        ++count;
        dirty = 1;
        return RHActorPointIterator(node);
    }
};

#endif
