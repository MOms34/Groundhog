/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../include/Groundhog.hpp"

Groundhog::Groundhog(int period) : _period(period)
{
    _occurs = false;
    _nbSwitch = 0;
    _g = 0;
    _s = 0;
    _r = 0;
    _rT = 0;
    _gT = 0;
    _sT = 0;
}

int Groundhog::calculateG()
{
    size_t i = _allTemp.size() - (size_t)_period;

    if (_allTemp.size() <= (size_t)_period)
        return 2;
    for (; i != _allTemp.size(); i++) {
        float temp = _allTemp[i] - _allTemp[i - 1];
        if (temp > 0) _g += temp;
    }
    _g /= _period;
    std::cout << "g=" << std::fixed << std::setprecision(2) << _g;
    _gT = _g;
    _g = 0;
    return 0;
}

int Groundhog::calculateS()
{
    size_t i = _allTemp.size() - (size_t)_period;
    float sum = 0;

    if (_allTemp.size() < (size_t)_period)
        return 2;
    for (; i != _allTemp.size(); i++) {
        sum += _allTemp[i];
    }
    sum /= _period;
    i = _allTemp.size() - (size_t)_period;
    for (; i != _allTemp.size(); i++)
        _s += std::pow(_allTemp[i] - sum, 2);
    _s = std::sqrt(_s / _period);
    std::cout << "\ts=" << std::fixed << std::setprecision(2) << _s;
    _sT = _s;
    _s = 0;
    return 0;
}

int Groundhog::calculateR()
{
    size_t size = _allTemp.size();
    size_t temp = size - (size_t)_period - 1;

    if (_allTemp.size() <= (size_t)_period)
        return 2;
    if (_allTemp[temp] == 0)
        return 2;
    _r = ((_temp - _allTemp[temp]) / _allTemp[temp]) * 100;
    std::cout << "\tr=" << std::fixed << std::setprecision(0) << _r << "%";
    if ((_r < 0 && _rT >= 0) || (_r >= 0 && _rT < 0)) {
        _occurs = true;
        _nbSwitch++;
    }
    _rT = _r;
    _r = 0;
    return 0;  
}

float Groundhog::string_to_float(std::string str)
{
    char *temp;
    float value = std::strtof(str.c_str(), &temp);
    std::stringstream ss;

    if (*temp !='\0' && str != "STOP") {
        std::cerr << "The arg must be a number." << std::endl;
        exit(84);
    }
    if (str == "STOP" && _allTemp.size() < (size_t)_period) {
        exit(84);
    }
    if (str == "STOP") {
        _stop = true;
        return 0;
    }
    ss << std::fixed << std::setprecision(2) << value;
    std::string result = ss.str();
    value = std::stof(result);
    return value;
}

int Groundhog::cleanInput(std::string input)
{
    std::vector<std::string> args;

    std::istringstream iss(input);

    std::copy(std::istream_iterator<std::string>(iss >> std::ws),
              std::istream_iterator<std::string>(),
              std::back_inserter(args));
    if (args.size() != 1)
        return -1;
    _temp = string_to_float(args[0]);
    return 0;
}

void Groundhog::calculateWeirdest()
{
    if (_gT <= 0 || _sT <= 0)
        return;
    if (last.empty() == true)
        return;
    float min = (_sT * 3) - _gT;
    if (min < last.back().first || min > last.back().second)
        _weirdest.push_back(_temp);
}

void Groundhog::calculateLast()
{
    if (_gT <= 0 || _sT <= 0)
        return;
    float min = (_sT * 3) - _gT;
    float max = (_sT * 3) + _gT;
    last.push_back(std::make_pair(min, max));
}

void Groundhog::displayFinal()
{
    std::cout << "Global tendency switched " << _weirdest.size() << " times\n";
    std::cout << _weirdest.size() << " weirdest values are [";
    if (_weirdest.size() == 0) {
        std::cout << "0.0]\n";
        return;
    }
    std::sort(_weirdest.begin(), _weirdest.end());
    for (size_t i = 0; i < _weirdest.size(); i++) {
        std::cout << _weirdest[i];
        if (i != _weirdest.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void Groundhog::loop()
{
    std::string input;

    while (1) {
        if (!std::getline(std::cin, input)) {
            std::cerr << "The arg must be a number." << std::endl;
            exit(84);
        }
        if (cleanInput(input) != 0) {
            std::cerr << "The arg must be a number." << std::endl;
            exit(84);
        }
        if (_stop == true) return displayFinal();
        _allTemp.push_back(_temp);
        calculateLast();
        if (calculateG() != 0)
            std::cout << "g=nan";
        if (calculateR() != 0)
            std::cout << "\tr=nan%";
        if (calculateS() != 0)
            std::cout << "\ts=nan";
        calculateWeirdest();
        if (_occurs == true) {
            std::cout << "\ta switch occurs\n";
            _occurs = false;
        } else
            std::cout << "\n";
    }
}

