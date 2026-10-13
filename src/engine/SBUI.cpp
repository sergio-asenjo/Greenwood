#include "SBUI.h"

DECOMP_SIZE_ASSERT(SBUI, 0x17f8)

// FUNCTION: GAME 0x00618910
void SBUI::FUN_00618910(unsigned long surface)
{
    unsigned count = m_first == 0 ? 0 : m_last - m_first;
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, surface, 0, surface, 0);
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->V18(surface);
    g_unk0x6c1340->FUN_005f1700();
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e5260();
    g_unk0x6c1340->PopMouseBackground(false);
    ((RHUnkFXDraw *)m_draw)->FUN_005e6440(m_surface, surface, 0, surface, 0);
    for (index = 0; index < count; ++index)
        m_first[index]->V18(surface);
    g_unk0x6c1340->FUN_005f1700();
    ((RHUnkFXDraw *)g_unk0x6c11d0)->FUN_005e5260();
    g_unk0x6c1340->PopMouseBackground(false);
}

#include <vector>

class RHSaveGame;

template <class T>
class SBArray
{
public:
    void Insert(T *position, unsigned count, const T &value);
};

struct SBUIWindowArray
{
    unsigned allocator;
    SBUIWindowView **first;
    SBUIWindowView **last;
    SBUIWindowView **end;
    SBUIWindowView **cursor;
    bool dirty;
    bool cursorValid;
    undefined m_16[2];
    int index;
    SBUIWindowView *current;

    int Find(SBUIWindowView *window)
    {
        dirty = false;
        current = window;
        int count = first == 0 ? 0 : last - first;
        cursor = first;
        cursorValid = true;
        int position = 0;
        for (; position < count; ++position, ++cursor)
            if (*cursor == window)
                break;
        return position < count ? position : -1;
    }
};

class SBUIFlagArray : public std::vector<char>
{
public:
    char *cursor;
    bool dirty;
    void FUN_00619d00();

    void Insert(char *position, unsigned count, const char &value)
    {
        typedef char *(std::vector<char>::*Copy)(const char *, const char *, char *);
        typedef void (std::vector<char>::*Fill)(char *, unsigned, const char &);
        typedef void (std::vector<char>::*Destroy)(char *, char *);
        Copy copy = &SBUIFlagArray::_Ucopy;
        Fill fill = &SBUIFlagArray::_Ufill;
        Destroy destroy = &SBUIFlagArray::_Destroy;
        if ((unsigned)(_End - _Last) < count) {
            unsigned capacity = size() + (count < size() ? size() : count);
            char *storage = allocator.allocate(capacity, 0);
            char *destination = storage;
            for (char *source = _First; source != position; ++destination, ++source) {
                void (*construct)(char *, const char &) = &std::_Construct;
                construct(destination, *source);
            }
            (this->*fill)(destination, count, value);
            (this->*copy)(position, _Last, destination + count);
            (this->*destroy)(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + capacity;
            _Last = storage + size() + count;
            _First = storage;
        } else if ((unsigned)(_Last - position) < count) {
            (this->*copy)(position, _Last, position + count);
            (this->*fill)(_Last, count - (_Last - position), value);
            std::fill(position, _Last, value);
            _Last += count;
        } else if (count > 0) {
            (this->*copy)(_Last - count, _Last, _Last);
            std::copy_backward(position, _Last - count, _Last);
            std::fill(position, position + count, value);
            _Last += count;
        }
    }
};

// FUNCTION: GAME 0x00619800
bool SBUI::FUN_00619800(SBUIWindowView *window)
{
    SBUIWindowArray &windows = *(SBUIWindowArray *)((char *)this + 4);
    windows.index = windows.Find(window);
    if (windows.index == -1) {
        ((SBArray<RHSaveGame *> *)&windows)->Insert(
            (RHSaveGame **)windows.last, 1, (RHSaveGame *const &)window);
        windows.dirty = true;
        char flag = 1;
        SBUIFlagArray &flags = *(SBUIFlagArray *)((char *)this + 0x24);
        flags.Insert(flags.end(), 1, flag);
        flags.dirty = true;
        window->AttachToDisplay(m_display);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00619a00
void SBUI::FUN_00619a00(SBUIWindowView *window)
{
    m_index = Find(window);
    if (m_index != -1) {
        int index = m_index;
        unsigned char flag = m_flags[index];
        for (; index < Size() - 1; ++index) {
            m_first[index] = m_first[index + 1];
            m_flags[index] = m_flags[index + 1];
        }
        m_first[Size() - 1] = window;
        m_flags[Size() - 1] = flag;
    }
}

// FUNCTION: GAME 0x00619c20
bool SBUI::FUN_00619c20(unsigned long display)
{
    m_draw = g_unk0x6c11d0;
    m_display = display;
    unsigned count = Size();
    for (unsigned index = 0; index < count; ++index)
        m_first[index]->AttachToDisplay(display);
    if (m_tooltip != 0)
        m_tooltip->FUN_00627ee0(display);
    return true;
}

// FUNCTION: GAME 0x00619c80
void SBUI::FUN_00619c80(SBUIFontView *font, SBUIFontView *alternate)
{
    m_font = font;
    font->V14(m_renderer, false);
    m_alternate = alternate;
    if (alternate != 0)
        alternate->V14(m_renderer, false);
}

// FUNCTION: GAME 0x00619d00
void SBUIFlagArray::FUN_00619d00()
{
    erase(begin(), end());
    ((std::vector<char> *)this)->~vector();
}

void EmitSBUI(SBUI *ui, SBUIWindowView *window, SBUIFontView *font)
{
    ui->FUN_00618910(0);
    ui->FUN_00619800(window);
    ui->FUN_00619a00(window);
    ui->FUN_00619c20(0);
    ui->FUN_00619c80(font, font);
    ((SBUIFlagArray *)((char *)ui + 0x24))->FUN_00619d00();
}
