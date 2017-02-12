#ifndef PLAYER
#define PLAYER

class player{
public:
    player();
    player(int n_hp, int n_attk, int n_def);
    int getp_hp();
    int getp_attk();
    int getp_def();

private:
    int hp;
    int attk;
    int def;

};

#endif
