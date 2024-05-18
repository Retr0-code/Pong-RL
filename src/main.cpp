#include <iostream>

#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/PlayerFollower.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#include "PlayerUCB.hpp"
#include "AgentLogger.hpp"

#define PADDLE_SIZE {10, 40}

int main(void)
{
    // std::shared_ptr<IPlayer> player1{ new PlayerHuman<ControlSchemeWASD>(IPlayer::Left, PADDLE_SIZE) };
    // std::shared_ptr<IPlayer> player2{ new PlayerHuman<ControlSchemeArrows>(IPlayer::Right, PADDLE_SIZE) };
    std::shared_ptr<IPlayer> player1{ new PlayerFollower(IPlayer::Left, PADDLE_SIZE) };
    std::shared_ptr<PlayerUCB> player2{ new PlayerUCB(IPlayer::Right, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);
    EnvironmentPong6I enviroment;
    player2->CreateAgent(enviroment);
    AgentLoggerCSV<float, IPlayer::PlayerAction> logPlayer(player2->Agent().get(), "player_ucb");
    logPlayer(100, 1);

    pong.Run();
    int option;
    bool run{true};
    while (run)
    {
        std::cin >> option;

        switch(option)
        {
            case 0:
            {
                run = false;
                break;
            }
            case 1:
            {
                std::cout << "Enter speed multiplier: ";
                float speedFactor{1.f};
                std::cin >> speedFactor;
                TheGameOfPong::SetSpeedMultiplier(speedFactor);
                break;
            }
            case 2:
            {
                std::cout << "Enter new epsilon: ";
                float epsilon{0.f};
                std::cin >> epsilon;
                player2->SetEpsilon(epsilon);
                break;
            }
        }
    }

    pong.Stop();

    return 0;
}