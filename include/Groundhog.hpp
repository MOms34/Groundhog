/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef GROUNDHOG_HPP
    #define GROUNDHOG_HPP

    #include <iostream>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <utility>
    #include <memory>
    #include <csignal>
    #include <iostream>
    #include <cstring>
    #include <fstream>
    #include <string>
    #include <iomanip>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <regex>
    #include <iterator>
    #include <cctype>
    #include <cmath>
    #define ERROR 84
    #define SUCCESS 0

class Groundhog {
    public:
        Groundhog(int period);
        ~Groundhog(){}
        int cleanInput(std::string input);
        void loop();
        float string_to_float(std::string str);
        int calculateG();
        int calculateR();
        int calculateS();
        void calculateWeirdest();
        void calculateLast();
        void displayFinal();

    protected:
    private:
        std::vector<float> _allTemp;
        std::vector<float> _weirdest;
        std::vector<std::pair<float, float>> last;
        int _nbTemp;
        int _period;
        int _nbSwitch;
        float _temp;
        float _g;
        float _r;
        float _s;
        float _rT;
        bool _stop;
        bool _occurs;
        float _gT;
        float _sT;
};

#endif /* !GROUNDHOG_HPP */
