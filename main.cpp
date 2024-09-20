#include <iostream>

namespace {
const int kMaxMinutes = 59;
const int kMaxHours = 23;
const int kMinMinutes = 0;
const int kMinHours = 0;

const int kMorningBegin = 5;
const int kDayBegin = 12;
const int kEveningBegin = 18;
const int kNightBegin = 0;
const int kHighNoon = 12;

const int kHoursAndMinsAccusativeMin = 2;
const int kHoursAndMinsAccusativeMax = 4;
const int kHoursAndMinsNominative = 1;
const int kMinutesSpecialGenitiveZoneBeg = 11;
const int kMinutesSpecialGenitiveZoneEnd = 14;

const int kDecimalBase = 10;

}  // namespace

enum class DayTime {
    Morning,
    Day,
    Evening,
    Night,
};

int main(int, char**) {
    int hours = (kMaxHours + 1);
    int minutes = (kMaxMinutes + 1);

    std::cout << "Введите время: ";
    std::cin >> hours >> minutes;

    if ((hours > kMaxHours || hours < kMinHours) || (minutes > kMaxMinutes || minutes < kMinMinutes)) {
        std::cout << "Введены некорректные данные, пожалуйста, введите реалистичное число часов и минут!\n";
        return 1;
    }

    if (hours == kMinHours && minutes == kMinMinutes) {
        std::cout << "Полночь\n";
        return 0;
    } else if (hours == kHighNoon && minutes == kMinMinutes) {
        std::cout << "Полдень\n";
        return 0;
    }

    DayTime Daytime{};

    if (hours >= kNightBegin && hours < kMorningBegin) {
        Daytime = DayTime::Night;
    } else if (hours >= kMorningBegin && hours < kDayBegin) {
        Daytime = DayTime::Morning;
    } else if (hours >= kDayBegin && hours < kEveningBegin) {
        Daytime = DayTime::Day;
    } else if (hours >= kEveningBegin) {
        Daytime = DayTime::Evening;
    }

    hours %= kHighNoon;

    if (hours == kHoursAndMinsNominative) {
        std::cout << hours << " час ";
    } else if (hours >= kHoursAndMinsAccusativeMin && hours <= kHoursAndMinsAccusativeMax) {
        std::cout << hours << " часа ";
    } else {
        std::cout << hours << " часов ";
    }

    if (minutes == kMinMinutes) {
    } else if (minutes >= kMinutesSpecialGenitiveZoneBeg && minutes <= kMinutesSpecialGenitiveZoneEnd) {
        std::cout << minutes << " минут ";
    } else if (minutes % kDecimalBase == kHoursAndMinsNominative) {
        std::cout << minutes << " минута ";
    } else if ((minutes % kDecimalBase >= kHoursAndMinsAccusativeMin) && (minutes % kDecimalBase <= kHoursAndMinsAccusativeMax)) {
        std::cout << minutes << " минуты ";
    } else {
        std::cout << minutes << " минут ";
    }

    switch (Daytime) {
        case DayTime::Morning:
            std::cout << "утра ";
            break;
        case DayTime::Day:
            std::cout << "дня ";
            break;
        case DayTime::Evening:
            std::cout << "вечера ";
            break;
        case DayTime::Night:
            std::cout << "ночи ";
            break;
    }
    if (minutes == kMinMinutes) {
        std::cout << "ровно\n";
    } else {
        std::cout << "\n";
    }
    return 0;
}
