bool checkParameters(std::string parameters);
bool checkFunction(std::vector<std::string> tokens);
bool checksemicolon(std::vector<std::string> tokens);
bool areParenthesisBalanced(std::vector<std::string> tokens, std::unordered_map<int, int> *imap);