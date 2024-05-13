#include <iostream>

#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/PlayerFollower.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#include "PlayerUCB.hpp"

#define PADDLE_SIZE {10, 40}

int main(void)
{
    std::shared_ptr<IPlayer> player1{ new PlayerHuman<ControlSchemeWASD>(IPlayer::Left, PADDLE_SIZE) };
    // std::shared_ptr<IPlayer> player2{ new PlayerHuman<ControlSchemeArrows>(IPlayer::Right, PADDLE_SIZE) };
    std::shared_ptr<PlayerUCB> player2{ new PlayerUCB(IPlayer::Right, PADDLE_SIZE) };
    // std::shared_ptr<IPlayer> player2{ new PlayerFollower(IPlayer::Right, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);
    EnviromentPong enviroment;
    player2->CreateAgent(enviroment);

    pong.Run();
    std::cin.get();
    pong.Stop();

    return 0;
}