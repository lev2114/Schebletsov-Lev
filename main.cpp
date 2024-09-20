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

    if ((hours >= kMaxHours or hours < kMin) or (minutes >= kMaxMinutes or minutes < kMin)) {
        std::cout << "Введены некорректные данные, перезапустите программу\n";
        return 0;
    }

    if (hours == kMin and minutes == kMin) {
        Daytime = Midnight;
    } else if (hours == kHighnoon and minutes == kMin) {
        Daytime = High_noon;
    } else if (hours >= kNightbeg and hours < kMorningbeg) {
        Daytime = Night;
    } else if (hours >= kMorningbeg and hours < kDaybeg) {
        Daytime = Morning;
    } else if (hours >= kDaybeg and hours < kEveningbeg) {
        Daytime = Day;
    } else if (hours >= kEveningbeg) {
        Daytime = Evening;
    }

    hours %= kHighNoon;

    if (hours == kHoursAndMinsNominative) {
        std::cout << hours << " час ";
    } else if (hours >= kHoursAndMinsAccusativeMin && hours <= kHoursAndMinsAccusativeMax) {
        std::cout << hours << " часа ";
    } else {
        std::cout << hours << " часов ";
    }

    if (minutes == kMin) {
        std::strcpy(minName, "ровно ");
    } else if (minutes >= kminspeczonebeg and minutes <= kminspeczoneend) {
        std::strcpy(minName, "минут ");
    } else if (minutes % klastnumberdef == kHoursAndMinsSpecPoint) {
        std::strcpy(minName, "минута ");
    } else if ((minutes % klastnumberdef >= kHoursAndMinsNameChangeMin) and (minutes % klastnumberdef <= kHoursAndMinsNameChangeMax)) {
        std::strcpy(minName, "минуты ");
    } else {
        std::strcpy(minName, "минут ");
    }

    if (minutes != kMin) {
        switch (Daytime) {
            case Midnight:
                std::cout << "Полночь\n";
                break;
            case High_noon:
                std::cout << "Полдень\n";
                break;
            case Morning:
                std::cout << hours << " " << hourName << minutes << " " << minName << "утра\n";
                break;
            case Day:
                std::cout << hours << " " << hourName << minutes << " " << minName << "дня\n";
                break;
            case Evening:
                std::cout << hours << " " << hourName << minutes << " " << minName << "вечера\n";
                break;
            case Night:
                std::cout << hours << " " << hourName << minutes << " " << minName << "ночи\n";
                break;
        }
    } else {
        switch (Daytime) {
            case Midnight:
                std::cout << "Полночь\n";
                break;
            case High_noon:
                std::cout << "Полдень\n";
                break;
            case Morning:
                std::cout << hours << " " << hourName << "утра" << minName;
                break;
            case Day:
                std::cout << hours << " " << hourName << "дня" << minName;
                break;
            case Evening:
                std::cout << hours << " " << hourName << "вечера" << minName;
                break;
            case Night:
                std::cout << hours << " " << hourName << "ночи" << minName;
                break;
        }
    }
    return 0;
}
