def seconds_difference(time_1, time_2):
    return time_2 - time_1

def hours_difference(time_1, time_2):
    return seconds_difference(time_1, time_2) / 3600

def to_float_hours(hours, minutes, seconds):
    return hours + minutes / 60 + seconds / 3600

def to_24_hour_clock(hours):
    return hours % 24

def get_hours(time):
    return int(time / 3600)

def get_minutes(time):
    return int((time % 3600) / 60)

def get_seconds(time):
    return int(time % 60)

def time_to_utc(utc_offset, time):
    time -= utc_offset
    while (time < 0):
        time += 24
    return to_24_hour_clock(time)

def time_from_utc(utc_offset, time):
    time += utc_offset
    while (time < 0):
        time += 24
    return to_24_hour_clock(time)



