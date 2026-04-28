#include "maudio.hpp"
#include "mpv/client.h"

#define GET_PROPERTY(_type, _prop, _format) \
( [&]() ->_type { \
        _type _{}; mpv_get_property(impl->mpv, _prop, MPV_##_format, &_); \
        return _; }() )

struct Maudio::_Impl
{
    mpv_handle* mpv = nullptr;
};

void Maudio::_MAction(const std::string& cmd) {
    mpv_command_string(impl->mpv, cmd.data());
}

Maudio::Maudio () {
    impl = new _Impl();
    impl->mpv = mpv_create();
    mpv_set_option_string(impl->mpv, "video", "no");
}
Maudio::~Maudio () {
    mpv_terminate_destroy(impl->mpv);
    delete impl;
}

void Maudio::init()
{
    mpv_initialize(impl->mpv);
}
void Maudio::destroy()
{
    ;
}

void Maudio::load(const strview& path)
{
    const char* cmd[] = {"loadfile", path.data(), NULL};
    int err = mpv_command(impl->mpv, cmd);

    M_TRY( err >= 0,
        throw std::runtime_error("Failed to load music file!");
    )
}

bool Maudio::isEnded()
{
    mpv_event* event = mpv_wait_event(impl->mpv, 0);
    return event->event_id == MPV_EVENT_END_FILE;
}


void Maudio::setTimePoint(f64 time_p)
{
    this->action("set time-pos {}", time_p);
}
f64 Maudio::getTimePoint(f64 seek_seconds)
{
    return (seek_seconds + GET_PROPERTY(f64, "time-pos", FORMAT_DOUBLE));
}

void Maudio::seek(f64 seconds)
{
    this->action("seek {} relative", seconds);
}

f64 Maudio::getDuration()
{
    return GET_PROPERTY(f64, "duration", FORMAT_DOUBLE);
}


void Maudio::setPlaying(bool playing)
{
    this->action("set pause {}", playing? "no":"yes");
}
bool Maudio::getPlaying()
{
    return !GET_PROPERTY(int, "pause", FORMAT_FLAG);
}


void Maudio::setVolume(f64 percent_volume)
{
    this->action("set volume {}", percent_volume);
}
f64 Maudio::getVolume(f64 coefficient)
{
    return (coefficient * GET_PROPERTY(f64, "volume", FORMAT_DOUBLE));
}
