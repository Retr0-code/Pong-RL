#pragma once
#include <thread>
#include <memory>
#include <fstream>
#include <functional>

#include "IAgent.hpp"
#include "TheGameOfPong/IPlayer.hpp"

template <typename T, typename ActionEnum>
class AgentLoggerCSV;


template <typename T, typename ActionEnum>
class IAgentLogger
{
public:
    using IAgentPtr = IAgent<T, ActionEnum>*;

    typedef enum
    {
        CSV,
        XML
    } ExportType;

    IAgentLogger(IAgentPtr agent, const std::string& fileMark = "rl_agent");

    virtual ~IAgentLogger();

    virtual void operator()(size_t episodes = 1000, size_t step = 10) = 0;

    static IAgentLogger<T, ActionEnum>* LoggerFactory(
        ExportType type,
        IAgentPtr agent,
        const std::string& fileMark = "rl_agent"
    );

    void Stop(void);

protected:
    void OpenHandle(const std::string& extension);

protected:
    bool _run;
    IAgentPtr _agent;
    std::string _fileMark;
    std::thread _logger;
    std::ofstream _outHandle;
    std::string _extension;
};

template <typename T, typename ActionEnum>
class AgentLoggerCSV
    : public IAgentLogger<T, ActionEnum>
{
public:
    using IAgentPtr = IAgent<T, ActionEnum>*;

    AgentLoggerCSV(IAgentPtr agent, const std::string& fileMark = "rl_agent");

    virtual ~AgentLoggerCSV() = default;

    virtual void operator()(size_t episodes = 1000, size_t step = 10) override;

private:
    void LogCSV(size_t episodes, size_t step);
};
