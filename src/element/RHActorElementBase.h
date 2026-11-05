#ifndef RHACTORELEMENTBASE_H
#define RHACTORELEMENTBASE_H

class SBFile;
class RHElevationLine;

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    int FUN_004671b0() const;
    void CrossElevationLine(RHElevationLine *line);
    char m_04[0xa4];
};

#endif
