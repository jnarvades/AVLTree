//main.cpp
#include "AVL_Tree.h"

int main() {

// parse input
  int numCommands;
  std::cin >> numCommands;

  std::string command;
  std::vector<std::string> commands;
  std::vector<int> ids;
  for (int i = 0; i <= numCommands; i++)
  {
    std::getline(std::cin, command);
    commands.push_back(command);
  }

  //instance of tree
  auto UF_STUDENTS = new AVL_Tree();

  for (int i = 1; i <= numCommands; i++) {
  std::string input = commands.at(i);

  std::regex validInputRegex(R"(^(?:(remove|search)\s+\d{8})$|search\s+("[A-Za-z\s]+")|insert\s+("[A-Za-z\s]+")\s+\d{8}$|removeInorder\s+\d+$|([1-9]|[1-9][0-9]|[1-9][0-9][0-9]|1000)|printInorder|printPreorder|printPostorder|printLevelCount)");

  if (!std::regex_match(input, validInputRegex)) {std::cout << "unsuccessful" << std::endl; continue;}

  //remove quotes for printing
  input.erase(std::remove(input.begin(), input.end(), '"'), input.end());

  //ooga booga way to determine case
  bool insert = input.find("insert") != std::string::npos;
  bool remove = input.find("remove") != std::string::npos;
  bool search = input.find("search") != std::string::npos;
  bool Pre = input.find("Pre") != std::string::npos;
  bool Post = input.find("Post") != std::string::npos;
  bool In = input.find("In") != std::string::npos;
  bool containsID = std::any_of(input.begin(), input.end(), ::isdigit); //edge case 3

  //for traversal formatting
  bool first = true;

  //case 1: insert name ID
  if (insert) {
    std::string name = input.substr(7, input.rfind(' ') - 7);
    int gatorID = stoi(input.substr(input.size() - 8, 8));

    //check for duplicate IDs
    std::vector<int>::iterator it = std::find(ids.begin(), ids.end(), gatorID);
    if (it != ids.end()) {
      std::cout << "unsuccessful" << std::endl;
      continue;
    }

    ids.push_back(gatorID);
    auto gator = new Node(name, gatorID);
    auto root = UF_STUDENTS->getRoot();
    UF_STUDENTS->insert(root, gator, nullptr);
    std::cout << "successful" << std::endl;

  } 

  //case 2: removeInorder num
  else if (remove && In) {
    int n = stoi(input.substr(input.rfind(' ')));
    UF_STUDENTS->removeInorderN(UF_STUDENTS->getRoot(), n);
  }
  
  //case 3: remove ID
  else if (remove && containsID) {
    int ID = stoi(input.substr(7, input.rfind(' ') - 7));
    auto it = std::find(ids.begin(), ids.end(), ID);
    if(it != ids.end()) {ids.erase(it);}
    UF_STUDENTS->remove(UF_STUDENTS->getRoot(), ID, nullptr);
  }

  //case 4: search ID
  else if (search && containsID) {
    int ID = stoi(input.substr(7, input.rfind(' ') - 7));
    UF_STUDENTS->searchID(UF_STUDENTS->getRoot(), ID);
  }

  //case 5: search name
  else if (search) {
    std::string name = input.substr(7, input.rfind(' ') - 7);
    bool found = false;
    UF_STUDENTS->searchName(UF_STUDENTS->getRoot(), name, found);
    if (!found) {std::cout << "unsuccessful" << std::endl;}
  }

  //case 6: printPreorder
  else if (Pre) {
    UF_STUDENTS->printPreorder(UF_STUDENTS->getRoot(), first);
    std::cout << std::endl;
  }

  //case 7: printPostorder
  else if (Post) {
    UF_STUDENTS->printPostorder(UF_STUDENTS->getRoot(), first);
    std::cout << std::endl;
  }

  //case 8: printInorder
  else if (In) {
    UF_STUDENTS->printInorder(UF_STUDENTS->getRoot(), first);
    std::cout << std::endl;
  }

  //case 9: printLevelCount
  else {
    std::cout << UF_STUDENTS->getHeight(UF_STUDENTS->getRoot()) << std::endl;
  }

  }
  return 0;
}