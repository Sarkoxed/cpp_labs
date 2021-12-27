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
    heal,
    skip
};

class Game{
    private:
        Level& l_lvl;
        bool a_team;
        bool a_endr;
        std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>>::iterator l_curplayer;
        std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>>::iterator l_curenemy;
    public:
        explicit Game(Level& lvl):l_lvl(lvl), a_team(true), a_endr(false), l_curplayer(l_lvl.l_players.begin()), l_curenemy(l_lvl.l_enemies.begin()){}
        void newRound();
        void action(Actions act, unsigned int x1 = 0, unsigned int y1 = 0);
        void checkRound(bool sk);
        bool getEnd() const { return a_endr;}
        ~Game() = default;
};
