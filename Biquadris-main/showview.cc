#include "showview.h"

#include <algorithm>  // For std::find and std::transform
#include <cctype>     // For std::tolower
#include <regex>      // For std::regex
#include <utility>    // For std::pair
#include <vector>     // For std::vector

using namespace std;

BiquadrisView::BiquadrisView(BiquadrisModel *m, BiquadrisController *c,
                             bool graphics)
    : model{m},
      controller{c},
      graphics{graphics},
      td{std::make_unique<TextView>(m, c)},
      gd{graphics ? std::make_unique<GraphicsView>(m, c) : nullptr} {
  // register view as observer of model.
  model->subscribe(this);

  update();
  getCommand();
}

BiquadrisView::~BiquadrisView() {}

void BiquadrisView::update() {
  td->displayGame();
  if (graphics) gd->displayGame();
}

void BiquadrisView::getCommand(const std::string &filename) {
  std::string cmd;
  std::ifstream in{filename};
  while (in >> cmd) {
    runCmd(cmd);
    if (model->getstated()) {
      // cout<<"game over"<<endl;
      break;
    }
  }
}

void BiquadrisView::getCommand() {
  cout << "Enter your command"<<endl;
  std::string cmd;
  while (cin >> cmd) {
    runCmd(cmd);
    if (model->getstated()) {
      // cout<<"game over"<<endl;
      break;
    }
  }
}

const std::vector<std::string> SUPPORTED_COMMANDS = {
    "left",     "right",   "down",      "clockwise", "counterclockwise",
    "drop",     "levelup", "leveldown", "norandom",  "random",
    "sequence", "restart", "I",         "J",         "T",
    "S",        "L",       "O",         "Z"};

const std::vector<std::string> NON_MULTIPLIER_SUPPORTED_COMMANDS = {
    "norandom", "random", "restart"};

// Helper function to convert a string to lowercase
std::string toLower(const std::string &input) {
  std::string output = input;
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return output;
}

// Function to check if cmd is a prefix of any command in the list
std::string findCommand(const std::string &cmd,
                        const std::vector<std::string> &commands) {
  std::vector<std::string> matches;
  for (const auto &command : commands) {
    if (command.substr(0, cmd.size()) == cmd) {
      matches.push_back(command);
    }
  }

  // Return the match if it's the only one, otherwise return an empty string
  return matches.size() == 1 ? matches.front() : "";
}

std::pair<int, std::string> parseCommand(const std::string &cmd) {
  // Regular expression to match the number part and the command part
  std::regex commandPattern("(\\d*)?(\\D+)");
  std::smatch matches;

  // Try to match the command string against the regex
  if (std::regex_match(cmd, matches, commandPattern) && matches.size() == 3) {
    std::string command = findCommand(matches[2].str(), SUPPORTED_COMMANDS);
    if (command.empty()) {
      return {0, ""};
    }
    // std::string command = matches[2];

    // Transform the command to lowercase
    // command = toLower(command);

    auto tmp = std::find(NON_MULTIPLIER_SUPPORTED_COMMANDS.begin(),
                         NON_MULTIPLIER_SUPPORTED_COMMANDS.end(), command);
    if (tmp != NON_MULTIPLIER_SUPPORTED_COMMANDS.end() &&
        !matches[1].str().empty()) {
      return {0, ""};
    }

    int number = 1;
    if (!matches[1].str().empty()) {
      number = std::stoi(matches[1]);
    }

    // Check if the extracted command is in the list of supported commands
    auto it = std::find(SUPPORTED_COMMANDS.begin(), SUPPORTED_COMMANDS.end(),
                        command);
    if (it != SUPPORTED_COMMANDS.end()) {
      // Command is supported, return the number and command
      return {number, *it};
    }
  }

  // Command is not supported, or input does not match expected format
  // Consider how you want to handle this case. For now, returning a default
  // value.
  return {0, ""};  // Alternatively, throw an exception or return an error code
}

void BiquadrisView::runCmd(const std::string &cmd) {
  // Call the parseCommand function with the commandInput
  std::pair<int, std::string> result = parseCommand(cmd);

  // Check if a valid command was returned
  if (!result.second.empty()) {
    auto parsedCommand = result.second;
    cout << result.first << std::endl;
    for (int i = 0; i < result.first; ++i) {
      if (parsedCommand == "left") {
        controller->moveLeft();
      } else if (parsedCommand == "right") {
        controller->moveRight();
      } else if (parsedCommand == "down") {
        controller->moveDown();
      } else if (parsedCommand == "clockwise") {
        controller->rotatecw();
      } else if (parsedCommand == "counterclockwise") {
        controller->rotateccw();
      } else if (parsedCommand == "drop") {
        controller->drop();
      } else if (parsedCommand == "levelup") {
        controller->levelUp();
      } else if (parsedCommand == "leveldown") {
        controller->levelDown();
      } else if (parsedCommand == "norandom") {
        std::string filename;
        cin >> filename;
        controller->turnRandomOff(filename);
      } else if (parsedCommand == "random") {
        controller->turnRandomOn();
      } else if (parsedCommand == "sequence") {
        std::string filename;
        cin >> filename;
        getCommand(filename);
      } else if (parsedCommand == "restart") {
        controller->restart();
      } else if (parsedCommand == "I" || parsedCommand == "J" ||
                 parsedCommand == "T" || parsedCommand == "S" ||
                 parsedCommand == "L" || parsedCommand == "O" ||
                 parsedCommand == "Z") {
        controller->swapBlock(cmd[0]);
      }
    }
    update();
  }
}
