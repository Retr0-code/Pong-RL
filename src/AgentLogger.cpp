#include <ctime>
#include <chrono>
#include <iomanip>

#include "AgentLogger.hpp"

template <typename T, typename ActionEnum>
IAgentLogger<T, ActionEnum>::IAgentLogger(IAgentPtr agent, const std::string& fileMark)
    : _agent(agent), _fileMark(fileMark), _run(true) {  }

template <typename T, typename ActionEnum>
IAgentLogger<T, ActionEnum>::~IAgentLogger()
{
    _run = false;
    if (_logger.joinable())
        _logger.join();
    
    if (_outHandle.is_open())
        _outHandle.close();
}

template <typename T, typename ActionEnum>
IAgentLogger<T, ActionEnum>* IAgentLogger<T, ActionEnum>::LoggerFactory(ExportType type, IAgentPtr agent, const std::string& fileMark)
{
    IAgentLogger<T, ActionEnum>* logger;
    switch (type)
    {
    case CSV:
        logger = new AgentLoggerCSV<T, ActionEnum>(agent, fileMark);
        break;

    default:
        throw std::invalid_argument{"Error in [IAgentLogger<T, ActionEnum>* IAgentLogger<T, ActionEnum>::LoggerFactory(ExportType type, IAgentPtr agent, const std::string& fileMark)]:\n\tUnsupported export type."};
    }

    return logger;
}

template <typename T, typename ActionEnum>
void IAgentLogger<T, ActionEnum>::Stop(void)
{
    _run = false;
}

template <typename T, typename ActionEnum>
void IAgentLogger<T, ActionEnum>::OpenHandle(const std::string& extension)
{
    using std::chrono::system_clock;
    std::stringstream currentTime;
    auto chronoTime{system_clock::now()};
    time_t posixTime{system_clock::to_time_t(chronoTime)};
    currentTime << std::put_time(std::localtime(&posixTime), "%F_%R");

    std::string filename = currentTime.str() + '_' + _fileMark + extension;
    _outHandle.open(filename);

    if (!_outHandle.is_open())
        throw std::runtime_error{"Error in [void IAgentLogger<T, ActionEnum>::OpenHandle(void)]:\n\tUnable to open file."};
}

//----------

template <typename T, typename ActionEnum>
AgentLoggerCSV<T, ActionEnum>::AgentLoggerCSV(IAgentPtr agent, const std::string &fileMark)
    : IAgentLogger<T, ActionEnum>(agent, fileMark) {  }

template <typename T, typename ActionEnum>
void AgentLoggerCSV<T, ActionEnum>::operator()(size_t episodes, size_t step)
{
    this->OpenHandle(".csv");
    this->_logger = std::thread(&AgentLoggerCSV<T, ActionEnum>::LogCSV, this, episodes, step);
}

template <typename T, typename ActionEnum>
void AgentLoggerCSV<T, ActionEnum>::LogCSV(size_t episodes, size_t step)
{
    size_t currentEpisode{this->_agent->Episode()};
    size_t prevEpisode{0xffffffff};

    this->_outHandle << "episode;reward;\n";
    while (currentEpisode <= episodes && this->_run)
    {
        if (currentEpisode % step == 0 && currentEpisode != prevEpisode)
            this->_outHandle << currentEpisode << ';' << this->_agent->GetReward() << ";\n";

        prevEpisode = currentEpisode;
        currentEpisode = this->_agent->Episode();
    }
}

template class AgentLoggerCSV<float, IPlayer::PlayerAction>;
