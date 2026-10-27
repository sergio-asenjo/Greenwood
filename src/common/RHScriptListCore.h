#ifndef RHSCRIPTLISTCORE_H
#define RHSCRIPTLISTCORE_H

#include <iterator>

struct RHUnk00571160Position;

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
    void *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
    RHScriptIter operator++(int)
    {
        RHScriptIter previous = *this;
        node = node->next;
        return previous;
    }
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

class RHUnk0046eb30
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool valid;
    char padding[3];
    int index;
    RHScriptIter erase(RHScriptIter position);
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter Unk0057c950(RHScriptIter position, const RHUnk00571160Position &value);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
    void *&Get(int wanted)
    {
        int size = count;
        if (valid)
        {
            if (wanted <= (size + 1) / 2)
            {
                cursor = head->next;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
            }
            else
            {
                cursor = head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
            }
            valid = false;
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
                        cursor = FUN_0046eb80().node;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + size) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                    else
                    {
                        cursor = head;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
                    }
                }
                index = wanted;
            }
        }
        return cursor->data;
    }
};

#endif
