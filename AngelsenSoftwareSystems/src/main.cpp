#include <ServerImplementation.h>
#include <InputParser.h>

int main(int argc, char ** argv)
{
    InputParser parser(argc, argv);
    std::string rootDir = parser.getCmdOption("-rootDir");

    Angelsen::Config config;
    config.updateFromJson(rootDir + "/config.json");
    config.loadTemplate();

    Angelsen::runServer(config);
}
