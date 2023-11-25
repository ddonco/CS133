void printSet(set<string> &s) {
    cout << "{ ";
    for (string word : s) {
        cout << word << " ";
    }
    cout << "}" << endl;
}