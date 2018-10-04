#ifndef GAMEBOY_EMULATOR_APPLICATION_H
#define GAMEBOY_EMULATOR_APPLICATION_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

namespace nsfgbe {

namespace po = boost::program_options;

class Application {
private:
    int argc;
    char **argv;

    std::string inputPath;

    void parseCommandLine();

    void printUsageAndExit(const po::options_description &all);

    po::options_description createPositionalOptionsDescription();

    po::positional_options_description createPositionalOptions();

    po::options_description createGeneralOptions();

public:
    Application(int argc, char *argv[]);
};

}


#endif //GAMEBOY_EMULATOR_APPLICATION_H
