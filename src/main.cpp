#include <iostream>

#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#define PADDLE_SIZE {10, 40}

int main(void)
{
    std::shared_ptr<IPlayer> player1{ new PlayerHuman<ControlSchemeWASD>(IPlayer::Left, PADDLE_SIZE) };
    std::shared_ptr<IPlayer> player2{ new PlayerHuman<ControlSchemeArrows>(IPlayer::Right, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);
    pong.Run();
    std::cin.get();
    pong.Stop();

    return 0;
}