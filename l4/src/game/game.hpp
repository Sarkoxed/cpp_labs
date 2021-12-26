#include "../level/level.hpp"

enum class Actions: short{
    mup,
    mdown,
    mleft,
    mright,
    shootxy,
    picki,
    throwi,
    reload,
    heal
};

class Game{
    private:
        Level& l_lvl;
        bool a_team;
        Character* p_curplayer;        
    public:
        explicit Game(Level& lvl):l_lvl(lvl), a_team(0), p_curplayer(nullptr){}
        
        void newRound();
        void action(Actions act);
};
