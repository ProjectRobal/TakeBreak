#ifndef BREAKER_H
#define BREAKER_H

#include <cstdint>

/*!
 * \brief The Breaker class
 *
 * A class to shutdown the computer when time is up
 *
 */

constexpr uint32_t BREAKTIME_DEFAULT=5; // a time when computer shutdown when it is break in minutes

constexpr uint32_t TIMESTAMP_DEFAULT=45;



class Breaker
{
protected:

uint32_t timestamp; // a time when computer shutdown in minutes

uint32_t breaktime; //  a time when computer shutdown when it is break in minutes

bool Break; // is it break?

uint32_t currentTime;

bool Sleep;

public:
    Breaker();

    Breaker(uint32_t _timestamp,uint32_t _breaktime);

    /*!
     * \brief update
     *
     * A function to be called when cycle passed
     *
     */
    void update();

    /*!
     * \brief shutdown
     *
     * Shut the computer down
     *
     */
    void shutdown() const;

    /*!
     * \brief readConfiguration
     *
     * Read configuration from file
     *
     * \return true when configuration has been read ,false in other case
     */

    bool readConfiguration();

    bool saveConfiguration();

    uint32_t getTimestamp() const {return timestamp;}

    uint32_t getBreaktime() const {return breaktime;}

    uint32_t getCurrentTime() const {return currentTime;}

    uint32_t timeToBreak() const;

    bool toSleep() const {return Sleep;}

    void setDefault();

    void resetTimer();

    void setTimestamp(uint32_t _timestamp)
    {
        timestamp=_timestamp;
    }

    void setBreaktime(uint32_t _breaktime)
    {
        breaktime=_breaktime;
    }

    void setSleep(bool _sleep)
    {
        Sleep=_sleep;
    }

    bool isBreak() const {return Break;}
};

#endif // BREAKER_H
