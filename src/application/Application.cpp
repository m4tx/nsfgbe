#include "Application.hpp"

#include <iostream>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/parsers.hpp>

#include <rom/ROM.hpp>
#include <emulator/Emulator.hpp>
#include <frontends/sdl/SDLFrontend.hpp>

namespace gb {

Application::Application(int argc, char *argv[])
        : argc(argc), argv(argv) {
    parseCommandLine();
    ROM rom = ROM(inputPath.c_str());
    SDLFrontend frontend;
    Emulator(rom, frontend).runGame();
}

void Application::parseCommandLine() {
    po::options_description all("Allowed options");
    all
            .add(createPositionalOptionsDescription())
            .add(createGeneralOptions());
    po::positional_options_description positional = createPositionalOptions();

    po::variables_map vm;
    try {
        po::store(
                po::command_line_parser(argc, argv)
                        .options(all)
                        .positional(positional)
                        .run(),
                vm);
        po::notify(vm);
    } catch (po::error &e) {
        if (vm.count("help")) {
            printUsageAndExit(all);
        }

        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
    }

    if (vm.count("help")) {
        printUsageAndExit(all);
    }
}

void Application::printUsageAndExit(const po::options_description &all) {
    std::cout << "Usage: " << argv[0] << " [options] <input>"
              << std::endl
              << std::endl
              << all
              << std::endl;
    exit(0);
}

po::positional_options_description Application::createPositionalOptions() {
    po::positional_options_description positional;

    positional.add("input", 1);

    return positional;
}

po::options_description Application::createPositionalOptionsDescription() {
    po::options_description positional("Input");

    positional.add_options()
            ("input", po::value<std::string>(&inputPath)->required(),
             "name of the ROM file to load");

    return positional;
}

po::options_description Application::createGeneralOptions() {
    po::options_description general("General");

    general.add_options()
            ("help,h", "display this help and exit");

    return general;
}

}
