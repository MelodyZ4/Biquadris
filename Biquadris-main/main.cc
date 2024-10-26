#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "controller.h"
#include "model.h"
#include "showview.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char **argv) {
  BiquadrisModel model;

  // Declare the supported options
  po::options_description desc("Allowed options");
  desc.add_options()("text", "text-only mode")("seed", po::value<int>(),
                                               "seed")(
      "scriptfile1", po::value<std::string>()->default_value("sequence1.txt"),
      "player 1 Level 0 source of blocks")(
      "scriptfile2", po::value<std::string>()->default_value("sequence2.txt"),
      "player 2 Level 0 source of blocks")("startlevel",
                                           po::value<int>()->default_value(0),
                                           "starts the game in level n");

  po::variables_map vm;
  po::store(po::parse_command_line(
                argc, argv, desc,
                boost::program_options::command_line_style::default_style |
                    po::command_line_style::allow_long_disguise),
            vm);
  po::notify(vm);

  bool graphics = true;
  if (vm.count("text")) graphics = false;

  if (vm.count("seed")) srand(vm["seed"].as<int>());

  if (vm.count("scriptfile1"))
    model.getPlayerOne()->setSourceFile(vm["scriptfile1"].as<std::string>());

  if (vm.count("scriptfile2"))
    model.getPlayerTwo()->setSourceFile(vm["scriptfile2"].as<std::string>());

  if (vm.count("startlevel")) {
    model.getPlayerOne()->setCurrentLevel(vm["startlevel"].as<int>());
    model.getPlayerTwo()->setCurrentLevel(vm["startlevel"].as<int>());
  }

  model.init();
  BiquadrisController controller{&model};
  BiquadrisView view{&model, &controller, graphics};
}
