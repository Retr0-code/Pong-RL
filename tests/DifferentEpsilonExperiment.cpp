#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FunctionContextTest 

#include <boost/test/unit_test.hpp>

#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/PlayerFollower.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#include "PlayerUCB.hpp"
#include "AgentLogger.hpp"

#define PADDLE_SIZE {10, 40}

BOOST_AUTO_TEST_CASE(experiment_DifferentEpsilon)
{
    std::shared_ptr<IPlayer> player1{ new PlayerFollower(IPlayer::Left, PADDLE_SIZE) };
    std::shared_ptr<PlayerUCB> player2{ new PlayerUCB(IPlayer::Right, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);
    EnvironmentPong enviroment;
    TheGameOfPong::SetSpeedMultiplier(4);
    player2->CreateAgent(enviroment);
    player2->SetEpsilon(0.1);

    // Epsilon = 0.1

    AgentLoggerCSV<float, IPlayer::PlayerAction> logPlayer(player2->Agent().get(), "ucb_eps_01");
    logPlayer(100, 1);
    pong.Run();

    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());

    // Epsilon = 0.5

    pong.Stop();
    pong.Reset();
    player2->SetEpsilon(0.5);

    logPlayer.SetFileMark("ucb_eps_05");
    logPlayer(100, 1);
    pong.Run();

    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());

    // Epsilon = 0.8

    pong.Stop();
    pong.Reset();
    player2->SetEpsilon(0.8);

    logPlayer.SetFileMark("ucb_eps_08");
    logPlayer(100, 1);
    pong.Run();
    
    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());

    pong.Stop();
}
