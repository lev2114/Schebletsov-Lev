#include <iostream>

namespace {
const int kMinMinutes = 0;
const int kMaxMinutes = 59;
const int kMinHours = 0;
const int kMaxHours = 23;

const int kMorningBegin = 5;
const int kDayBegin = 12;
const int kEveningBegin = 18;
const int kNightBegin = 0;
const int kHighNoon = 12;

const int kHoursPluralAccusativeMin = 2;
const int kHoursPluralAccusativeMax = 4;
const int kMinutesPluralAccusativeMin = 2;
const int kMinutesPluralAccusativeMax = 4;
const int kHoursSingularNominative = 1;
const int kMinutesSingularNominative = 1;
const int kMinutesPluralGenitiveMin = 11;
const int kMinutesPluralGenitiveMax = 14;

const int kDecimalBase = 10;
}  // namespace

enum class DayTime {
    Morning,
    Day,
    Evening,
    Night,
};

int main(int, char**) {
    int hours = -1;
    int minutes = -1;

    std::cout << "Введите время в формате a b, где a - число от 0 до 23, b - число от 0 до 59: ";
    std::cin >> hours >> minutes;

    if (hours > kMaxHours || hours < kMinHours || minutes > kMaxMinutes || minutes < kMinMinutes) {
        std::cout << "Введены некорректные данные, пожалуйста, введите время в формате a b, где a - число от 0 до 23, b - число от 0 до 59!\n";
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
    } else if (hours >= kEveningBegin && hours <= kMaxHours) {
        Daytime = DayTime::Evening;
    }

    if (hours > kHighNoon) {
        hours %= kHighNoon;
    }

    if (hours == kHoursSingularNominative) {
        std::cout << hours << " час ";
    } else if (hours >= kHoursPluralAccusativeMin && hours <= kHoursPluralAccusativeMax) {
        std::cout << hours << " часа ";
    } else {
        std::cout << hours << " часов ";
    }

    int minutesLastDigit = minutes % kDecimalBase;

    if (minutes != kMinMinutes) {
        if ((minutesLastDigit == kMinutesSingularNominative) && (minutes < kMinutesPluralGenitiveMin || minutes > kMinutesPluralGenitiveMax)) {
            std::cout << minutes << " минута ";
        } else if ((minutesLastDigit >= kMinutesPluralAccusativeMin) && (minutesLastDigit <= kMinutesPluralAccusativeMax) &&
                   (minutes < kMinutesPluralGenitiveMin || minutes > kMinutesPluralGenitiveMax)) {
            std::cout << minutes << " минуты ";
        } else {
            std::cout << minutes << " минут ";
        }
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
        std::cout << "ровно";
    }
    std::cout << '\n';
    return 0;
}
