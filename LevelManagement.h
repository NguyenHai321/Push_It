#ifndef LEVELMANAGEMENT_H_INCLUDED
#define LEVELMANAGEMENT_H_INCLUDED

class Level_Manage
{
public:
    static const int first_level = 1;
    Level( int whatLevel );

    void levelData( int x, int y , int num, const char* level );

    bool endLevel();

    int levelUp();

    int resetLevel();
private:
    int mLevel;
    int numObject;
};

#endif // LEVELMANAGEMENT_H_INCLUDED
