#include <ServerImplementation.h>
#include <InputParser.h>

int main(int argc, char ** argv)
{
    InputParser parser(argc, argv);

    Angelsen::Config config;
    config.updateFromJson(parser.getCmdOption("-config"));
    config.loadTemplate();

    Angelsen::runServer(config);
}
