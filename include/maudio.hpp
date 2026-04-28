#pragma once
#include "utils.hpp"

// Musique Audio
class Maudio
{
    struct _Impl;
    _Impl* impl = nullptr;
    struct{f64 now, max;} m_time;

    // implementator of @function action
    void _MAction(const std::string& _cmd);

public:

    template <class... Interpol>
    void action(std::format_string<Interpol...> fmt, Interpol&&... values) {
        _MAction(std::format(fmt, std::forward<Interpol>(values)...));
    }

    Maudio();
    ~Maudio();
    void init();
    void destroy();

    void load(const strview& path);
    bool isEnded();

    void setTimePoint(f64 time_p);
    f64 getTimePoint(f64 seek_seconds=0);
    void seek(f64 seconds);
    f64 getDuration();

    void setPlaying(bool playing);
    bool getPlaying();
    void setVolume(f64 percent_volume);
    f64 getVolume(f64 coefficient=1.0f);
};
